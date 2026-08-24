# MGS Legato Widget Examples

This directory contains example applications demonstrating various widgets and features of the Microchip Graphics Suite (MGS) Legato library. Each example is a standalone application that can be built and run independently.

## Building Examples

From the project build directory:

```bash
# Build all examples
make

# Build a specific example
make example_button
make example_slider
# etc.
```

## Examples Overview

### Basic Widgets

| Example | Description |
|---------|-------------|
| [button](button/) | Demonstrates button widgets with press/release events. Shows how to toggle label visibility and change text on button state changes. |
| [checkbox](checkbox/) | Shows checkbox widgets with checked/unchecked state handling. Displays different images based on checkbox selections. |
| [label](label/) | Basic label widget display. Demonstrates static text rendering with different fonts and styles. |
| [image](image/) | Displays image widgets with various image formats and configurations. |
| [panel](panel/) | Panel container widget example. Shows how to group widgets and toggle panel visibility. |

### Input Widgets

| Example | Description |
|---------|-------------|
| [slider](slider/) | Horizontal and vertical slider widgets. Demonstrates value change callbacks and synchronizing multiple sliders. |
| [circular_slider](circular_slider/) | Circular/radial slider widget for rotary input. Shows dynamic string updates based on slider value. |
| [progress_bar](progress_bar/) | Progress bar widget controlled by a slider. Demonstrates value change events and dynamic label updates. |
| [keypad](keypad/) | Numeric keypad widget for PIN/number entry interfaces. |
| [qwerty](qwerty/) | Full QWERTY keyboard widget for text input. |

### Data Visualization

| Example | Description |
|---------|-------------|
| [bargraph](bargraph/) | Bar graph widget with multiple data series. Shows unit conversion between different measurement systems. |
| [line_graph](line_graph/) | Line graph widget with multiple data series. Demonstrates random data generation and static data display. |
| [line](line/) | Line widget demonstration. Shows line rotation at 45-degree increments on button press. |

### Lists and Sequences

| Example | Description |
|---------|-------------|
| [list](list/) | List widget with scrolling, item selection, and dynamic item addition. Shows both static and dynamic list management. |
| [image_sequence](image_sequence/) | Image sequence widget for animations and slideshows. Demonstrates manual navigation and automatic playback. |

### Advanced Features

| Example | Description |
|---------|-------------|
| [multi_language](multi_language/) | Multi-language support with 14 languages. Demonstrates UTF-8 strings, language switching, and font selection for different scripts. See [detailed README](multi_language/README.md). |
| [calendar](calendar/) | Calendar/date picker widget. Shows month/year navigation and date selection. |
| [custom_widget](custom_widget/) | Creating custom widgets with the draw surface. Demonstrates drawing arcs with different colors and styles. |
| [draw_surface](draw_surface/) | Draw surface widget for custom graphics. Shows rectangle drawing, random pixel plotting, and screen clearing. |
| [global_widgets](global_widgets/) | Sharing widgets across multiple screens. Demonstrates adding/removing global widgets from screen roots. |
| [runtime_str](runtime_str/) | Runtime string manipulation. Shows both fixed strings (stack-allocated) and dynamic strings (heap-allocated) with timer-based updates. |

## Example Structure

Each example follows a consistent structure:

```
example_name/
├── CMakeLists.txt              # Build configuration
├── main.c                      # Application entry point
├── apps/
│   └── app_screen0.c           # Event handlers and application logic
├── gfx/legato/
│   ├── legato_config.h         # Legato configuration
│   └── generated/              # MGS Composer generated code
│       ├── le_gen_assets.h     # Asset declarations
│       ├── le_gen_init.c/h     # Initialization code
│       ├── font/               # Font assets
│       ├── image/              # Image assets
│       └── screen/             # Screen definitions
└── *_design.zip                # MGS Composer design file (if present)
```

## Key Concepts Demonstrated

### Event Handling
Most examples show how to handle widget events:
```c
void event_Screen0_ButtonWidget_0_OnReleased(leButtonWidget* btn)
{
    // Handle button release
}
```

### Dynamic Strings
Several examples demonstrate runtime string creation:
```c
// Fixed string (stack-allocated, known max size)
static leFixedString myString;
static leChar myBuffer[32];
leFixedString_Constructor(&myString, myBuffer, 32);

// Dynamic string (heap-allocated, variable size)
leDynamicString* dynStr = leDynamicString_New();
```

### Widget Visibility
Toggling widget visibility:
```c
widget->fn->setVisible(widget, LE_TRUE);   // Show
widget->fn->setVisible(widget, LE_FALSE);  // Hide
```

### Value Updates
Updating widget values programmatically:
```c
slider->fn->setValue(slider, newValue);
progressBar->fn->setValue(progressBar, percentage);
graph->fn->setDataInSeries(graph, seriesIndex, dataIndex, value);
```

## Creating New Examples

1. Copy an existing example directory as a template
2. Modify `CMakeLists.txt` with the new example name
3. Create/modify the design in MGS Composer
4. Export generated code to `gfx/legato/generated/`
5. Implement event handlers in `apps/app_screen0.c`
6. Add the example to `apps/examples/CMakeLists.txt`

## Resources

- [MGS Composer User Guide](https://www.microchip.com/mgs)
- [Legato API Reference](../../gfx/middleware/legato/library/src/gfx/legato/)
- [Main Project README](../../README.md)
