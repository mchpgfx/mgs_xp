# MGS XP - Microchip Graphics Suite Cross-Platform

A cross-platform port of the [Microchip Graphics Suite (MGS)](https://developerhelp.microchip.com/xwiki/bin/view/software-tools/mgs/) graphics library, enabling GUI applications to run on Linux and Windows desktop environments.

## Overview

MGS XP allows developers to build GUI applications using the same MGS graphics library and MGS Composer design tool used for Microchip embedded systems. This enables:

- **Design once, deploy everywhere** - Create screens in MGS Composer and run them on desktop Linux, Windows, or embedded targets
- **Rapid prototyping** - Develop and test GUI designs on a desktop before deploying to hardware
- **Cross-platform consistency** - Same graphics library across bare metal, RTOS, and Linux platforms

For detailed information, see the [MGS Cross-Platform User Guide](https://developerhelp.microchip.com/xwiki/bin/view/software-tools/mgs/cross-platform-user-guide/).

## Supported Platforms

| Platform | Display Backends | Status |
|----------|------------------|--------|
| Linux (x86_64) | SDL2, Framebuffer | Tested on Ubuntu 24.04 |
| Linux (ARM) | DRM/KMS, Framebuffer, SDL2 | For embedded Linux on Microchip MPUs |
| Windows | SDL2 | MinGW-w64 toolchain |

## Quick Start

### Clone the Repository

```bash
git clone https://github.com/mchpgfx/mgs_xp.git
cd mgs_xp
```

### Build and Run

**Linux:**
```bash
mkdir -p build && cd build
cmake ..
make -j$(nproc)
./apps/quickstart/mgs_quickstart
```

**Windows (MinGW):**
```cmd
mkdir build && cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
apps\quickstart\mgs_quickstart.exe
```

## Documentation

- [Linux Build Guide](README_LINUX.md) - Detailed Linux build instructions, VS Code setup, troubleshooting
- [Windows Build Guide](README_WINDOWS.md) - Windows/MinGW setup, VS Code configuration
- [Widget Examples](apps/examples/README.md) - Example applications demonstrating MGS widgets
- [MGS Cross-Platform User Guide (Linux)](https://developerhelp.microchip.com/xwiki/bin/view/software-tools/mgs/cross-platform-user-guide/linux/) - Official Microchip documentation

## Project Structure

```
mgs_xp/
├── apps/
│   ├── quickstart/           # Main demo application
│   └── examples/             # Widget example applications
├── gfx/middleware/legato/    # MGS graphics library
│   ├── library/src/gfx/      # Core library source
│   └── composer/             # MGS Composer tool (Win/Linux/macOS)
├── system/
│   ├── linux/                # Linux platform (display, input, timer)
│   └── windows/              # Windows platform (display, timer, SDL2)
└── CMakeLists.txt
```

## MGS Composer

GUI designs are created using MGS Composer, located at `gfx/middleware/legato/composer/`:
- Windows: `windows/composer.exe`
- Linux: `linux/composer`
- macOS: `osx/composer`

Composer exports generated code to `apps/*/gfx/legato/generated/`.

## License

See individual source files for license information. The MGS graphics library is provided by Microchip Technology Inc.
