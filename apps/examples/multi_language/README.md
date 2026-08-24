# Multi-Language Example

This example demonstrates how to create a multi-language GUI application using Microchip Graphics Suite (MGS) Legato. It shows "Good Morning" in 14 different languages, with each language using an appropriate font that supports its character set.

## Overview

The application displays a single button with a greeting message. Each time the button is pressed, the display cycles to the next language. The example demonstrates:

- UTF-8 string encoding for international text
- Multiple font assets for different scripts (Latin, Arabic, CJK, Devanagari, etc.)
- Language-specific font assignment in the string table
- Runtime language switching via `leSetStringLanguage()`

## Supported Languages

| Language | Greeting | Font Used |
|----------|----------|-----------|
| English (Default) | Good Morning | FontNotoCJKtc |
| Arabic | صباح الخير | FontNotoArabic |
| Amharic (Ethiopian) | ምልካም እድል | FontNotoEthiopic |
| Swahili | Habari za asubuhi | NotoRegular |
| Afrikaans | Goeiemôre | NotoRegular |
| Zulu | Sawubona | NotoRegular |
| Portuguese | Bom dia | NotoRegular |
| Spanish | Buen Dia | NotoRegular |
| Chinese (Simplified) | 早上好 | FontNotoCJKtc |
| Korean | 좋은 아침이에요 | FontNotoCJKtc |
| Japanese | おはよう | FontNotoCJKtc |
| Hindi | शुभ प्रभात | FontDevan |
| Russian | Доброе утро | NotoRegular |
| Greek | Καλημέρα | NotoRegular |

## Font Assets

The project uses 5 font assets to cover all required scripts. Download the required fonts from Google Fonts:

| Font Name | Source TTF | Scripts Covered | Languages | Download |
|-----------|------------|-----------------|-----------|----------|
| FontNotoCJKtc | NotoSansCJKtc-Regular | CJK + Basic Latin | Chinese, Japanese, Korean, English | [Google Fonts](https://fonts.google.com/noto/specimen/Noto+Sans+TC) |
| FontNotoArabic | NotoSansArabic | Arabic script | Arabic | [Google Fonts](https://fonts.google.com/noto/specimen/Noto+Sans+Arabic) |
| FontNotoEthiopic | NotoSansEthiopic | Ethiopic script | Amharic | [Google Fonts](https://fonts.google.com/noto/specimen/Noto+Sans+Ethiopic) |
| FontDevan | NotoSansDevanagari | Devanagari script | Hindi | [Google Fonts](https://fonts.google.com/noto/specimen/Noto+Sans+Devanagari) |
| NotoRegular | NotoSans-Regular | Latin, Greek, Cyrillic | Swahili, Afrikaans, Zulu, Portuguese, Spanish, Russian, Greek | [Google Fonts](https://fonts.google.com/noto/specimen/Noto+Sans) |

### Font Selection Notes

- **NotoSansCJKtc** is used for CJK languages but does NOT include Greek Extended characters. Use **NotoSans-Regular** for Greek text with diacritical marks (e.g., έ, ή, ώ).
- Each language in the string table has a font ID that maps to the appropriate font for that script.
- The font list is defined in `le_gen_stringtable.c`.
- To modify fonts in MGS Composer, download the TTF files from the links above and import them into your design.

## Project Structure

```
multi_language/
├── CMakeLists.txt              # Build configuration
├── main.c                      # Application entry point
├── default_design.zip          # MGS Composer design file
├── apps/
│   └── app_screen0.c           # Button event handler (language cycling)
├── gfx/legato/
│   ├── legato_config.h         # Legato configuration
│   └── generated/              # MGS Composer generated code
│       ├── le_gen_assets.h     # Asset declarations (fonts, strings, images)
│       ├── le_gen_stringtable.c # String table with UTF-8 encoded text
│       ├── font/
│       │   └── le_gen_fonts.c  # Font glyph data
│       └── screen/
│           └── le_gen_screen_Screen0.c  # Screen layout
```

## How It Works

1. **Initialization**: The application initializes with the default language (English).

2. **Language Cycling**: When the button is pressed, `app_screen0.c` handles the event:
   ```c
   void event_Screen0_ButtonWidget_0_OnReleased(leButtonWidget* btn)
   {
       uint32_t count = leStringTable_GetLanguageCount(leGetState()->stringTable);
       languageID = (languageID + 1) % count;
       leSetStringLanguage(languageID);
   }
   ```

3. **String Rendering**: Legato automatically:
   - Looks up the string for the current language
   - Selects the font assigned to that language/string combination
   - Decodes UTF-8 text to Unicode codepoints
   - Renders glyphs from the appropriate font asset

## Building

### Windows
```cmd
cd build
mingw32-make example_multilanguage
```

### Linux
```bash
cd build
make example_multilanguage
```

## Running

```bash
./build/apps/examples/multi_language/example_multilanguage
```

Click the button to cycle through all 14 languages.

## Modifying the Design

1. Open `default_design.zip` in MGS Composer
2. Edit strings in the String Table asset
3. Add/modify fonts ensuring they cover required Unicode ranges
4. Assign appropriate fonts to each language in the string table
5. Generate code and export to `gfx/legato/generated/`

### Important: Enable UTF-8 Encoding

For multi-language support with non-ASCII characters, you must set the String Table encoding to UTF-8:

1. In MGS Composer, select the **String Table** asset
2. In the Properties panel, find the **Encoding** setting
3. Change it from **ASCII** to **UTF8**

Without UTF-8 encoding, characters outside the basic ASCII range (0x00-0x7F) will not render correctly.

### Adding a New Language

1. In MGS Composer, add a new language to the String Table
2. Add the translated text for each string
3. Assign a font that supports the required characters
4. If needed, create a new font asset with the required glyph ranges
5. Regenerate the code

### Unicode Range Reference

When adding fonts for specific scripts, include these Unicode ranges:

| Script | Unicode Range | Decimal |
|--------|---------------|---------|
| Basic Latin | U+0020-U+007E | 32-126 |
| Latin Extended | U+00C0-U+00FF | 192-255 |
| Greek | U+0370-U+03FF | 880-1023 |
| Cyrillic | U+0400-U+04FF | 1024-1279 |
| Arabic | U+0600-U+06FF | 1536-1791 |
| Devanagari | U+0900-U+097F | 2304-2431 |
| Ethiopic | U+1200-U+137F | 4608-4991 |
| Hiragana | U+3040-U+309F | 12352-12447 |
| Katakana | U+30A0-U+30FF | 12448-12543 |
| CJK Unified | U+4E00-U+9FFF | 19968-40959 |
| Hangul | U+AC00-U+D7AF | 44032-55215 |
