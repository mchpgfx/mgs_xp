/*******************************************************************************
  Vector Render APIs

  Company:
    Microchip Technology Inc.

  File Name:
    vector_render.c

  Summary:
    Span-based vector drawing APIs for lines, rectangles, and arcs.

  Description:
    Provides optimized vector drawing functions that bypass the general-purpose
    Legato vector kernel. Uses span-based rendering with edge anti-aliasing
    calculated via coverage values for maximum performance.
 *******************************************************************************/

#include "vector_render.h"
#include "vector_pixel.h"
#include "vector_math.h"
#include "gfx/legato/core/legato_real_i16.h"

#ifdef USE_OPTIMIZED_LINE_DRAWING
/*******************************************************************************
 * Optimized Line Drawing using Scanline Rasterization
 *
 * Uses 16.16 fixed-point math and analytically computes X spans per scanline.
 * Only calculates distance once per pixel (vs twice in the original version).
 * Properly handles round caps via circle intersection.
 ******************************************************************************/
static void drawAALine_Optimized(const RenderContext* ctx,
                                  fix16_t x0, fix16_t y0,
                                  fix16_t x1, fix16_t y1,
                                  fix16_t width,
                                  uint32_t color, uint32_t alpha)
{
    fix16_t dx = x1 - x0;
    fix16_t dy = y1 - y0;
    int64_t lineLenSq = FIX16_MUL64(dx, dx) + FIX16_MUL64(dy, dy);
    fix16_t lineLen = fix16_sqrt64(lineLenSq);

    if (lineLen < 64) return;

    fix16_t dirX = FIX16_DIV(dx, lineLen);
    fix16_t dirY = FIX16_DIV(dy, lineLen);
    fix16_t perpX = -dirY;
    fix16_t perpY = dirX;

    fix16_t halfWidth = width >> 1;

    fix16_t perpHalfX = FIX16_MUL(perpX, halfWidth);
    fix16_t perpHalfY = FIX16_MUL(perpY, halfWidth);

    fix16_t corners[8] = {
        x0 + perpHalfX, y0 + perpHalfY,
        x0 - perpHalfX, y0 - perpHalfY,
        x1 + perpHalfX, y1 + perpHalfY,
        x1 - perpHalfX, y1 - perpHalfY
    };

    fix16_t minX = corners[0], maxX = corners[0];
    fix16_t minY = corners[1], maxY = corners[1];
    for (int i = 2; i < 8; i += 2)
    {
        if (corners[i] < minX) minX = corners[i];
        if (corners[i] > maxX) maxX = corners[i];
        if (corners[i+1] < minY) minY = corners[i+1];
        if (corners[i+1] > maxY) maxY = corners[i+1];
    }

    minX -= halfWidth;
    maxX += halfWidth;
    minY -= halfWidth;
    maxY += halfWidth;

    int startY = FIX16_FLOOR(minY);
    int endY = FIX16_CEIL(maxY);
    int startX = FIX16_FLOOR(minX);
    int endX = FIX16_CEIL(maxX);

    if (startY < ctx->clip.y) startY = ctx->clip.y;
    if (endY > ctx->clip.y + ctx->clip.height) endY = ctx->clip.y + ctx->clip.height;
    if (startX < ctx->clip.x) startX = ctx->clip.x;
    if (endX > ctx->clip.x + ctx->clip.width) endX = ctx->clip.x + ctx->clip.width;

    fix16_t halfWidthSq = FIX16_MUL(halfWidth, halfWidth);

    for (int py = startY; py < endY; py++)
    {
        fix16_t cy = FIX16_FROM_INT(py) + FIX16_HALF;

        fix16_t scanMinX = maxX + FIX16_ONE;
        fix16_t scanMaxX = minX - FIX16_ONE;

        fix16_t cdy0 = cy - y0;
        if (fix16_abs(cdy0) <= halfWidth)
        {
            fix16_t cdy0Sq = FIX16_MUL(cdy0, cdy0);
            fix16_t capDx = fix16_sqrt(halfWidthSq - cdy0Sq);
            fix16_t capLeft = x0 - capDx;
            fix16_t capRight = x0 + capDx;
            if (capLeft < scanMinX) scanMinX = capLeft;
            if (capRight > scanMaxX) scanMaxX = capRight;
        }

        fix16_t cdy1 = cy - y1;
        if (fix16_abs(cdy1) <= halfWidth)
        {
            fix16_t cdy1Sq = FIX16_MUL(cdy1, cdy1);
            fix16_t capDx = fix16_sqrt(halfWidthSq - cdy1Sq);
            fix16_t capLeft = x1 - capDx;
            fix16_t capRight = x1 + capDx;
            if (capLeft < scanMinX) scanMinX = capLeft;
            if (capRight > scanMaxX) scanMaxX = capRight;
        }

        if (fix16_abs(dy) > 64)
        {
            fix16_t edge1Y0 = y0 + perpHalfY;
            fix16_t edge1Y1 = y1 + perpHalfY;
            fix16_t edge1X0 = x0 + perpHalfX;
            fix16_t edge1X1 = x1 + perpHalfX;
            if ((cy >= edge1Y0 && cy <= edge1Y1) || (cy >= edge1Y1 && cy <= edge1Y0))
            {
                fix16_t t1 = FIX16_DIV(cy - edge1Y0, edge1Y1 - edge1Y0);
                fix16_t ix1 = edge1X0 + FIX16_MUL(t1, edge1X1 - edge1X0);
                if (ix1 < scanMinX) scanMinX = ix1;
                if (ix1 > scanMaxX) scanMaxX = ix1;
            }

            fix16_t edge2Y0 = y0 - perpHalfY;
            fix16_t edge2Y1 = y1 - perpHalfY;
            fix16_t edge2X0 = x0 - perpHalfX;
            fix16_t edge2X1 = x1 - perpHalfX;
            if ((cy >= edge2Y0 && cy <= edge2Y1) || (cy >= edge2Y1 && cy <= edge2Y0))
            {
                fix16_t t2 = FIX16_DIV(cy - edge2Y0, edge2Y1 - edge2Y0);
                fix16_t ix2 = edge2X0 + FIX16_MUL(t2, edge2X1 - edge2X0);
                if (ix2 < scanMinX) scanMinX = ix2;
                if (ix2 > scanMaxX) scanMaxX = ix2;
            }
        }
        else
        {
            fix16_t bodyMinY = (y0 < y1 ? y0 : y1) - halfWidth;
            fix16_t bodyMaxY = (y0 > y1 ? y0 : y1) + halfWidth;
            if (cy >= bodyMinY && cy <= bodyMaxY)
            {
                fix16_t bodyLeft = (x0 < x1 ? x0 : x1);
                fix16_t bodyRight = (x0 > x1 ? x0 : x1);
                if (bodyLeft < scanMinX) scanMinX = bodyLeft;
                if (bodyRight > scanMaxX) scanMaxX = bodyRight;
            }
        }

        if (scanMinX > scanMaxX) continue;

        int pxStart = FIX16_FLOOR(scanMinX);
        int pxEnd = FIX16_CEIL(scanMaxX);
        if (pxStart < ctx->clip.x) pxStart = ctx->clip.x;
        if (pxEnd > ctx->clip.x + ctx->clip.width) pxEnd = ctx->clip.x + ctx->clip.width;

        for (int px = pxStart; px < pxEnd; px++)
        {
            fix16_t cx = FIX16_FROM_INT(px) + FIX16_HALF;

            fix16_t toCenterX = cx - x0;
            fix16_t toCenterY = cy - y0;

            fix16_t dotProd = FIX16_MUL(toCenterX, dirX) + FIX16_MUL(toCenterY, dirY);
            fix16_t t = FIX16_DIV(dotProd, lineLen);

            fix16_t distance;

            if (t < 0)
            {
                fix16_t dcx = cx - x0;
                fix16_t dcy = cy - y0;
                fix16_t distSq = FIX16_MUL(dcx, dcx) + FIX16_MUL(dcy, dcy);
                distance = fix16_sqrt(distSq);
            }
            else if (t > FIX16_ONE)
            {
                fix16_t dcx = cx - x1;
                fix16_t dcy = cy - y1;
                fix16_t distSq = FIX16_MUL(dcx, dcx) + FIX16_MUL(dcy, dcy);
                distance = fix16_sqrt(distSq);
            }
            else
            {
                fix16_t closestX = x0 + FIX16_MUL(t, dx);
                fix16_t closestY = y0 + FIX16_MUL(t, dy);
                fix16_t dcx = cx - closestX;
                fix16_t dcy = cy - closestY;
                fix16_t distSq = FIX16_MUL(dcx, dcx) + FIX16_MUL(dcy, dcy);
                distance = fix16_sqrt(distSq);
            }

            if (distance > halfWidth) continue;

            uint32_t pixelAlpha;
            fix16_t edgeDist = halfWidth - distance;

            if (edgeDist >= FIX16_ONE)
            {
                pixelAlpha = alpha;
            }
            else if (edgeDist <= 0)
            {
                continue;
            }
            else
            {
                pixelAlpha = (uint32_t)((alpha * edgeDist) >> FIX16_SHIFT);
            }

            if (pixelAlpha > 0)
                ctx->funcs->putPixelBlend(ctx, px, py, color, (uint8_t)pixelAlpha);
        }
    }
}

void leDraw_VectorBasicLine(const struct leVector2* p0,
                            const struct leVector2* p1,
                            uint32_t color,
                            uint8_t alpha,
                            int32_t width)
{
    RenderContext ctx;
    if (!initRenderContext(&ctx))
        return;

    int32_t x0 = leReal_i16_ToInt(p0->x);
    int32_t y0 = leReal_i16_ToInt(p0->y);
    int32_t x1 = leReal_i16_ToInt(p1->x);
    int32_t y1 = leReal_i16_ToInt(p1->y);

    if (x0 == x1 && y0 == y1)
    {
        ctx.funcs->putPixelBlend(&ctx, x0, y0, color, alpha);
        return;
    }

    drawAALine_Optimized(&ctx,
                         FIX16_FROM_INT(x0), FIX16_FROM_INT(y0),
                         FIX16_FROM_INT(x1), FIX16_FROM_INT(y1),
                         FIX16_FROM_INT(width),
                         color, alpha);
}

#else /* !USE_OPTIMIZED_LINE_DRAWING */
/*******************************************************************************
 * Original Line Drawing using Bounding Box Scan
 *
 * Brute-force approach that tests every pixel in the bounding box.
 * Computes distance twice per pixel (once for span detection, once for alpha).
 ******************************************************************************/
void leDraw_VectorBasicLine(const struct leVector2* p0,
                            const struct leVector2* p1,
                            uint32_t color,
                            uint8_t alpha,
                            int32_t width)
{
    RenderContext ctx;
    if (!initRenderContext(&ctx))
        return;

    int32_t x0 = leReal_i16_ToInt(p0->x);
    int32_t y0 = leReal_i16_ToInt(p0->y);
    int32_t x1 = leReal_i16_ToInt(p1->x);
    int32_t y1 = leReal_i16_ToInt(p1->y);

    int32_t dx = x1 - x0;
    int32_t dy = y1 - y0;

    if (dx == 0 && dy == 0)
    {
        ctx.funcs->putPixelBlend(&ctx, x0, y0, color, alpha);
        return;
    }

    int32_t halfWidth = width / 2;
    if (halfWidth < 1) halfWidth = 1;

    int32_t halfWidthSq256 = halfWidth * halfWidth * 256;
    int32_t aaThreshSq256 = (halfWidth > 1) ? (halfWidth - 1) * (halfWidth - 1) * 256 : 0;

    int64_t lenSq = (int64_t)dx * dx + (int64_t)dy * dy;

    int32_t minX = (x0 < x1 ? x0 : x1) - halfWidth - 1;
    int32_t maxX = (x0 > x1 ? x0 : x1) + halfWidth + 1;
    int32_t minY = (y0 < y1 ? y0 : y1) - halfWidth - 1;
    int32_t maxY = (y0 > y1 ? y0 : y1) + halfWidth + 1;

    if (minX < ctx.clip.x) minX = ctx.clip.x;
    if (maxX >= ctx.clip.x + ctx.clip.width) maxX = ctx.clip.x + ctx.clip.width - 1;
    if (minY < ctx.clip.y) minY = ctx.clip.y;
    if (maxY >= ctx.clip.y + ctx.clip.height) maxY = ctx.clip.y + ctx.clip.height - 1;

    for (int32_t row = minY; row <= maxY; row++)
    {
        int32_t spanStart = -1;
        int32_t spanEnd = -1;

        for (int32_t col = minX; col <= maxX; col++)
        {
            int32_t distSq256 = pointToSegmentDistSq256(col, row, x0, y0, x1, y1, lenSq);

            if (distSq256 <= halfWidthSq256)
            {
                if (spanStart < 0) spanStart = col;
                spanEnd = col;
            }
            else if (spanStart >= 0)
            {
                break;
            }
        }

        if (spanStart >= 0 && spanEnd >= spanStart)
        {
            for (int32_t col = spanStart; col <= spanEnd; col++)
            {
                int32_t distSq256 = pointToSegmentDistSq256(col, row, x0, y0, x1, y1, lenSq);
                uint8_t pixAlpha = alpha;

                if (distSq256 > aaThreshSq256 && distSq256 <= halfWidthSq256)
                {
                    int32_t t = 256 - ((distSq256 - aaThreshSq256) * 256) / (halfWidthSq256 - aaThreshSq256 + 1);
                    if (t < 0) t = 0;
                    if (t > 256) t = 256;
                    pixAlpha = (uint8_t)(((uint32_t)alpha * t) >> 8);
                }

                if (pixAlpha > 0)
                    ctx.funcs->putPixelBlend(&ctx, col, row, color, pixAlpha);
            }
        }
    }
}
#endif /* USE_OPTIMIZED_LINE_DRAWING */

void leDraw_VectorBasicRectFill(const struct leRectF* rect,
                                uint32_t color,
                                uint8_t alpha,
                                int32_t cornerRadius)
{
    RenderContext ctx;
    if (!initRenderContext(&ctx))
        return;

    int32_t cx = leReal_i16_ToInt(rect->origin.x);
    int32_t cy = leReal_i16_ToInt(rect->origin.y);
    int32_t halfW = leReal_i16_ToInt(rect->extents.x);
    int32_t halfH = leReal_i16_ToInt(rect->extents.y);

    if (halfW <= 0 || halfH <= 0)
        return;

    int32_t x1 = cx - halfW;
    int32_t y1 = cy - halfH;
    int32_t x2 = cx + halfW;
    int32_t y2 = cy + halfH;
    int32_t w = x2 - x1;
    int32_t h = y2 - y1;

    if (cornerRadius <= 0)
    {
        for (int32_t row = y1; row < y2; row++)
        {
            uint8_t rowAlpha = alpha;
            if (row == y1 || row == y2 - 1)
                rowAlpha = (uint8_t)(((uint32_t)alpha * 192) >> 8);
            ctx.funcs->drawHSpan(&ctx, row, x1, x2, color, rowAlpha);
        }
        return;
    }

    if (cornerRadius > w / 2) cornerRadius = w / 2;
    if (cornerRadius > h / 2) cornerRadius = h / 2;

    int32_t r2 = cornerRadius * cornerRadius;
    int32_t aaThresh = (cornerRadius > 1) ? (cornerRadius - 1) * (cornerRadius - 1) : 0;

    for (int32_t row = y1; row < y2; row++)
    {
        int32_t spanLeft = x1;
        int32_t spanRight = x2;
        int32_t leftAA = 0, rightAA = 0;

        int32_t dy_top = row - (y1 + cornerRadius);
        int32_t dy_bottom = row - (y2 - 1 - cornerRadius);

        if (dy_top < 0)
        {
            int32_t dy2 = dy_top * dy_top;
            int32_t xOffset = 0;
            for (int32_t dxx = cornerRadius; dxx >= 0; dxx--)
            {
                int32_t dist2 = dxx * dxx + dy2;
                if (dist2 <= r2)
                {
                    xOffset = cornerRadius - dxx;
                    if (dist2 > aaThresh)
                        leftAA = 128;
                    break;
                }
            }
            spanLeft = x1 + xOffset;
            spanRight = x2 - xOffset;
            rightAA = leftAA;
        }
        else if (dy_bottom > 0)
        {
            int32_t dy2 = dy_bottom * dy_bottom;
            int32_t xOffset = 0;
            for (int32_t dxx = cornerRadius; dxx >= 0; dxx--)
            {
                int32_t dist2 = dxx * dxx + dy2;
                if (dist2 <= r2)
                {
                    xOffset = cornerRadius - dxx;
                    if (dist2 > aaThresh)
                        leftAA = 128;
                    break;
                }
            }
            spanLeft = x1 + xOffset;
            spanRight = x2 - xOffset;
            rightAA = leftAA;
        }

        if (spanLeft < spanRight)
        {
            if (leftAA > 0 || rightAA > 0)
                ctx.funcs->drawHSpanAA(&ctx, row, spanLeft, spanRight, leftAA, rightAA, color, alpha);
            else
                ctx.funcs->drawHSpan(&ctx, row, spanLeft, spanRight, color, alpha);
        }
    }
}

void leDraw_VectorBasicRectStroke(const struct leRectF* rect,
                                  uint32_t color,
                                  uint8_t alpha,
                                  int32_t strokeWidth,
                                  int32_t cornerRadius)
{
    RenderContext ctx;
    if (!initRenderContext(&ctx))
        return;

    int32_t cx = leReal_i16_ToInt(rect->origin.x);
    int32_t cy = leReal_i16_ToInt(rect->origin.y);
    int32_t halfW = leReal_i16_ToInt(rect->extents.x);
    int32_t halfH = leReal_i16_ToInt(rect->extents.y);

    if (halfW <= 0 || halfH <= 0)
        return;

    if (strokeWidth < 1) strokeWidth = 1;

    int32_t x1 = cx - halfW;
    int32_t y1 = cy - halfH;
    int32_t x2 = cx + halfW;
    int32_t y2 = cy + halfH;
    int32_t w = x2 - x1;
    int32_t h = y2 - y1;

    if (cornerRadius <= 0)
    {
        for (int32_t row = y1; row < y1 + strokeWidth && row < y2; row++)
            ctx.funcs->drawHSpan(&ctx, row, x1, x2, color, alpha);

        for (int32_t row = y2 - strokeWidth; row < y2; row++)
        {
            if (row >= y1 + strokeWidth)
                ctx.funcs->drawHSpan(&ctx, row, x1, x2, color, alpha);
        }

        for (int32_t row = y1 + strokeWidth; row < y2 - strokeWidth; row++)
        {
            ctx.funcs->drawHSpan(&ctx, row, x1, x1 + strokeWidth, color, alpha);
            ctx.funcs->drawHSpan(&ctx, row, x2 - strokeWidth, x2, color, alpha);
        }
        return;
    }

    if (cornerRadius > w / 2) cornerRadius = w / 2;
    if (cornerRadius > h / 2) cornerRadius = h / 2;

    int32_t outerR = cornerRadius;
    int32_t innerR = cornerRadius - strokeWidth;
    if (innerR < 0) innerR = 0;

    int32_t outerR2 = outerR * outerR;
    int32_t innerR2 = innerR * innerR;

    for (int32_t row = y1; row < y2; row++)
    {
        int32_t dy_top = row - (y1 + cornerRadius);
        int32_t dy_bottom = row - (y2 - 1 - cornerRadius);

        leBool inCornerRegion = (dy_top < 0 || dy_bottom > 0);

        if (!inCornerRegion)
        {
            ctx.funcs->drawHSpan(&ctx, row, x1, x1 + strokeWidth, color, alpha);
            ctx.funcs->drawHSpan(&ctx, row, x2 - strokeWidth, x2, color, alpha);
            continue;
        }

        int32_t dy = (dy_top < 0) ? dy_top : dy_bottom;
        int32_t dy2 = dy * dy;

        int32_t outerOffset = cornerRadius;
        int32_t innerOffset = cornerRadius;

        for (int32_t dxx = cornerRadius; dxx >= 0; dxx--)
        {
            int32_t dist2 = dxx * dxx + dy2;
            if (dist2 <= outerR2)
            {
                outerOffset = cornerRadius - dxx;
                break;
            }
        }

        if (innerR > 0)
        {
            for (int32_t dxx = innerR; dxx >= 0; dxx--)
            {
                int32_t dist2 = dxx * dxx + dy2;
                if (dist2 <= innerR2)
                {
                    innerOffset = cornerRadius - dxx;
                    break;
                }
            }
        }
        else
        {
            innerOffset = cornerRadius;
        }

        int32_t leftOuter = x1 + outerOffset;
        int32_t leftInner = x1 + innerOffset;
        int32_t rightInner = x2 - innerOffset;
        int32_t rightOuter = x2 - outerOffset;

        leBool inTopStrokeRegion = (row < y1 + strokeWidth);
        leBool inBottomStrokeRegion = (row >= y2 - strokeWidth);

        if (inTopStrokeRegion || inBottomStrokeRegion)
        {
            ctx.funcs->drawHSpan(&ctx, row, leftOuter, rightOuter, color, alpha);
        }
        else
        {
            if (leftOuter < leftInner)
                ctx.funcs->drawHSpan(&ctx, row, leftOuter, leftInner, color, alpha);
            if (rightInner < rightOuter)
                ctx.funcs->drawHSpan(&ctx, row, rightInner, rightOuter, color, alpha);
        }
    }
}

void leDraw_VectorBasicArcStroke(const struct leVector2* center,
                                 int32_t radius,
                                 int32_t startAngle16,
                                 int32_t spanAngle16,
                                 uint32_t color,
                                 uint8_t alpha,
                                 int32_t strokeWidth,
                                 enum leCapStyle capStyle)
{
    RenderContext ctx;
    if (!initRenderContext(&ctx))
        return;

    int32_t cx = leReal_i16_ToInt(center->x);
    int32_t cy = leReal_i16_ToInt(center->y);
    int32_t r = leReal_i16_ToInt(radius);

    if (r <= 0 || spanAngle16 == 0)
        return;

    if (strokeWidth < 1) strokeWidth = 1;

    int32_t halfStroke = strokeWidth / 2;
    int32_t outerR = r + halfStroke;
    int32_t innerR = r - halfStroke;
    if (innerR < 0) innerR = 0;

    int32_t outerR2 = outerR * outerR;
    int32_t innerR2 = innerR * innerR;

    int32_t startDeg = startAngle16 / 16;
    int32_t spanDeg = spanAngle16 / 16;

    if (spanDeg < 0)
    {
        startDeg += spanDeg;
        spanDeg = -spanDeg;
    }

    startDeg = startDeg % 360;
    if (startDeg < 0) startDeg += 360;
    int32_t endDeg = startDeg + spanDeg;

    int32_t startCapCx = 0, startCapCy = 0;
    int32_t endCapCx = 0, endCapCy = 0;
    int32_t capR = halfStroke + 1;
    int32_t capR2 = capR * capR;
    leBool drawRoundCaps = (capStyle == LE_CAPSTYLE_ROUND && spanDeg < 360);

    if (drawRoundCaps)
    {
        int32_t startCapDeg = startDeg - 1;
        int32_t endCapDeg = startDeg + spanDeg + 1;

        leReal_i16 startRad = LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(startCapDeg), LE_REAL_I16_RADIANS);
        leReal_i16 endRad = LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(endCapDeg), LE_REAL_I16_RADIANS);

        leReal_i16 cosStart = leReal_i16_Cos(startRad);
        leReal_i16 sinStart = leReal_i16_Sin(startRad);
        leReal_i16 cosEnd = leReal_i16_Cos(endRad);
        leReal_i16 sinEnd = leReal_i16_Sin(endRad);

        startCapCx = cx + leReal_i16_ToInt(LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(r), cosStart));
        startCapCy = cy - leReal_i16_ToInt(LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(r), sinStart));
        endCapCx = cx + leReal_i16_ToInt(LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(r), cosEnd));
        endCapCy = cy - leReal_i16_ToInt(LE_REAL_I16_MULTIPLY(leReal_i16_FromInt(r), sinEnd));
    }

    int32_t y1 = cy - outerR - 1;
    int32_t y2 = cy + outerR + 1;

    if (drawRoundCaps)
    {
        int32_t capY1 = (startCapCy < endCapCy ? startCapCy : endCapCy) - halfStroke - 1;
        int32_t capY2 = (startCapCy > endCapCy ? startCapCy : endCapCy) + halfStroke + 1;
        if (capY1 < y1) y1 = capY1;
        if (capY2 > y2) y2 = capY2;
    }

    if (y1 < ctx.clip.y) y1 = ctx.clip.y;
    if (y2 >= ctx.clip.y + ctx.clip.height) y2 = ctx.clip.y + ctx.clip.height - 1;

    for (int32_t row = y1; row <= y2; row++)
    {
        int32_t dy = row - cy;
        int32_t dy2 = dy * dy;

        int32_t x1 = cx - outerR - 1;
        int32_t x2 = cx + outerR + 1;

        if (drawRoundCaps)
        {
            int32_t capX1 = (startCapCx < endCapCx ? startCapCx : endCapCx) - halfStroke - 1;
            int32_t capX2 = (startCapCx > endCapCx ? startCapCx : endCapCx) + halfStroke + 1;
            if (capX1 < x1) x1 = capX1;
            if (capX2 > x2) x2 = capX2;
        }

        if (x1 < ctx.clip.x) x1 = ctx.clip.x;
        if (x2 >= ctx.clip.x + ctx.clip.width) x2 = ctx.clip.x + ctx.clip.width - 1;

        if (spanDeg >= 360 && dy2 <= outerR2)
        {
            int32_t outerX = isqrt(outerR2 - dy2);
            int32_t innerX = (dy2 < innerR2) ? isqrt(innerR2 - dy2) : 0;

            if (innerX > 0)
            {
                ctx.funcs->drawHSpan(&ctx, row, cx - outerX, cx - innerX, color, alpha);
                ctx.funcs->drawHSpan(&ctx, row, cx + innerX, cx + outerX + 1, color, alpha);
            }
            else
            {
                ctx.funcs->drawHSpan(&ctx, row, cx - outerX, cx + outerX + 1, color, alpha);
            }
            continue;
        }

        for (int32_t px = x1; px <= x2; px++)
        {
            int32_t dx = px - cx;
            int32_t dist2 = dx * dx + dy2;

            leBool inArc = LE_FALSE;
            leBool inStartCap = LE_FALSE;
            leBool inEndCap = LE_FALSE;

            if (dist2 <= outerR2 && dist2 >= innerR2)
            {
                int32_t angleDeg;
                if (dx == 0 && dy == 0)
                {
                    angleDeg = 0;
                }
                else
                {
                    angleDeg = atan2Deg256(-dy, dx);
                }

                if (endDeg <= 360)
                {
                    inArc = (angleDeg >= startDeg && angleDeg <= endDeg);
                }
                else
                {
                    int32_t endDegWrapped = endDeg % 360;
                    inArc = (angleDeg >= startDeg || angleDeg <= endDegWrapped);
                }
            }

            if (drawRoundCaps)
            {
                int32_t dxStart = px - startCapCx;
                int32_t dyStart = row - startCapCy;
                int32_t distStartCap2 = dxStart * dxStart + dyStart * dyStart;
                if (distStartCap2 <= capR2)
                    inStartCap = LE_TRUE;

                int32_t dxEnd = px - endCapCx;
                int32_t dyEnd = row - endCapCy;
                int32_t distEndCap2 = dxEnd * dxEnd + dyEnd * dyEnd;
                if (distEndCap2 <= capR2)
                    inEndCap = LE_TRUE;
            }

            if (inArc || inStartCap || inEndCap)
            {
                uint8_t pixAlpha = alpha;

                if (inArc)
                {
                    int32_t distFromOuter = outerR2 - dist2;
                    int32_t distFromInner = dist2 - innerR2;

                    if (outerR > 0 && distFromOuter < outerR * 2)
                        pixAlpha = (uint8_t)(((uint32_t)alpha * distFromOuter) / (outerR * 2));
                    else if (innerR > 0 && distFromInner < innerR * 2)
                        pixAlpha = (uint8_t)(((uint32_t)alpha * distFromInner) / (innerR * 2));
                }
                else if (inStartCap)
                {
                    int32_t dxStart = px - startCapCx;
                    int32_t dyStart = row - startCapCy;
                    int32_t distStartCap2 = dxStart * dxStart + dyStart * dyStart;
                    int32_t distFromEdge = capR2 - distStartCap2;
                    if (capR > 0 && distFromEdge < capR * 2)
                        pixAlpha = (uint8_t)(((uint32_t)alpha * distFromEdge) / (capR * 2));
                }
                else if (inEndCap)
                {
                    int32_t dxEnd = px - endCapCx;
                    int32_t dyEnd = row - endCapCy;
                    int32_t distEndCap2 = dxEnd * dxEnd + dyEnd * dyEnd;
                    int32_t distFromEdge = capR2 - distEndCap2;
                    if (capR > 0 && distFromEdge < capR * 2)
                        pixAlpha = (uint8_t)(((uint32_t)alpha * distFromEdge) / (capR * 2));
                }

                if (pixAlpha > 0)
                    ctx.funcs->putPixelBlend(&ctx, px, row, color, pixAlpha);
            }
        }
    }
}

void leDraw_VectorBasicArcFill(const struct leVector2* center,
                               int32_t radius,
                               int32_t startAngle16,
                               int32_t spanAngle16,
                               uint32_t color,
                               uint8_t alpha)
{
    RenderContext ctx;
    if (!initRenderContext(&ctx))
        return;

    int32_t cx = leReal_i16_ToInt(center->x);
    int32_t cy = leReal_i16_ToInt(center->y);
    int32_t r = leReal_i16_ToInt(radius);

    if (r <= 0 || spanAngle16 == 0)
        return;

    int32_t r2 = r * r;
    int32_t aaR2 = (r > 1) ? (r - 1) * (r - 1) : 0;

    int32_t startDeg = startAngle16 / 16;
    int32_t spanDeg = spanAngle16 / 16;

    if (spanDeg < 0)
    {
        startDeg += spanDeg;
        spanDeg = -spanDeg;
    }

    startDeg = startDeg % 360;
    if (startDeg < 0) startDeg += 360;
    int32_t endDeg = startDeg + spanDeg;

    int32_t y1 = cy - r - 1;
    int32_t y2 = cy + r + 1;

    if (y1 < ctx.clip.y) y1 = ctx.clip.y;
    if (y2 >= ctx.clip.y + ctx.clip.height) y2 = ctx.clip.y + ctx.clip.height - 1;

    for (int32_t row = y1; row <= y2; row++)
    {
        int32_t dy = row - cy;
        int32_t dy2 = dy * dy;

        if (dy2 > r2)
            continue;

        int32_t maxX = isqrt(r2 - dy2);

        if (spanDeg >= 360)
        {
            int32_t leftAA = 0, rightAA = 0;

            int32_t dist2Left = maxX * maxX + dy2;
            if (dist2Left > aaR2)
                leftAA = 128;

            rightAA = leftAA;
            ctx.funcs->drawHSpanAA(&ctx, row, cx - maxX, cx + maxX + 1, leftAA, rightAA, color, alpha);
            continue;
        }

        for (int32_t px = cx - maxX; px <= cx + maxX; px++)
        {
            int32_t dx = px - cx;
            int32_t dist2 = dx * dx + dy2;

            if (dist2 > r2)
                continue;

            int32_t angleDeg;
            if (dx == 0 && dy == 0)
            {
                angleDeg = startDeg;
            }
            else
            {
                angleDeg = atan2Deg256(-dy, dx);
            }

            leBool inArc = LE_FALSE;
            if (endDeg <= 360)
            {
                inArc = (angleDeg >= startDeg && angleDeg <= endDeg);
            }
            else
            {
                int32_t endDegWrapped = endDeg % 360;
                inArc = (angleDeg >= startDeg || angleDeg <= endDegWrapped);
            }

            if (inArc)
            {
                uint8_t pixAlpha = alpha;
                if (dist2 > aaR2 && r > 0)
                {
                    int32_t edgeDist = r2 - dist2;
                    int32_t denom = r * 2;
                    if (denom > 0)
                        pixAlpha = (uint8_t)(((uint32_t)alpha * (denom + edgeDist)) / denom);
                }

                if (pixAlpha > 0)
                    ctx.funcs->putPixelBlend(&ctx, px, row, color, pixAlpha);
            }
        }
    }
}

/*******************************************************************************
 * API-Compatible Wrapper Functions
 ******************************************************************************/

void leDrawExt_VectorBasicLine(const struct leVector2* p0,
                               const struct leVector2* p1,
                               const struct leVectorLineAttr* attr)
{
    if (p0 == NULL || p1 == NULL || attr == NULL)
        return;

    int32_t width = leReal_i16_ToInt(attr->width);
    if (width < 1) width = 1;

    leDraw_VectorBasicLine(p0, p1, attr->color, attr->alpha, width);
}

void leDrawExt_VectorBasicRectFill(const struct leRectF* rect,
                                   const struct leVectorRect_FillAttr* attr)
{
    if (rect == NULL || attr == NULL)
        return;

    int32_t cornerRadius = (leReal_i16_ToInt(attr->topLeftRadius) +
                            leReal_i16_ToInt(attr->topRightRadius) +
                            leReal_i16_ToInt(attr->bottomLeftRadius) +
                            leReal_i16_ToInt(attr->bottomRightRadius)) / 4;

    leDraw_VectorBasicRectFill(rect, attr->color, attr->alpha, cornerRadius);
}

void leDrawExt_VectorBasicRectStroke(const struct leRectF* rect,
                                     const struct leVectorRect_StrokeAttr* attr)
{
    if (rect == NULL || attr == NULL)
        return;

    int32_t strokeWidth = leReal_i16_ToInt(attr->width);
    if (strokeWidth < 1) strokeWidth = 1;

    int32_t cornerRadius = (leReal_i16_ToInt(attr->topLeftRadius) +
                            leReal_i16_ToInt(attr->topRightRadius) +
                            leReal_i16_ToInt(attr->bottomLeftRadius) +
                            leReal_i16_ToInt(attr->bottomRightRadius)) / 4;

    leDraw_VectorBasicRectStroke(rect, attr->color, attr->alpha, strokeWidth, cornerRadius);
}

void leDrawExt_VectorBasicArcStroke(const struct leVector2* center,
                                    leReal_i16 radius,
                                    int32_t start,
                                    int32_t span,
                                    const struct leVectorArc_StrokeAttr* attr)
{
    if (center == NULL || attr == NULL)
        return;

    int32_t strokeWidth = leReal_i16_ToInt(attr->width);
    if (strokeWidth < 1) strokeWidth = 1;

    leDraw_VectorBasicArcStroke(center, radius, start, span,
                                attr->color, attr->alpha, strokeWidth,
                                attr->capStyle);
}

void leDrawExt_VectorBasicArcFill(const struct leVector2* center,
                                  leReal_i16 radius,
                                  int32_t start,
                                  int32_t span,
                                  const struct leVectorArc_FillAttr* attr)
{
    if (center == NULL || attr == NULL)
        return;

    leDraw_VectorBasicArcFill(center, radius, start, span,
                              attr->color, attr->alpha);
}
