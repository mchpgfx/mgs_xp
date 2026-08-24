# Building MGS XP on Linux

This guide describes how to build the MGS XP cross-platform graphics library on Linux.

Tested on Ubuntu 24.04.01 LTS.

## Prerequisites

### All Dependencies (Recommended)

**Debian/Ubuntu:**
```bash
sudo apt-get update
sudo apt install build-essential cmake pkg-config libinput-dev libsdl2-dev libsdl2-2.0-0
```

**Fedora:**
```bash
sudo dnf install gcc gcc-c++ cmake pkg-config libinput-devel systemd-devel SDL2-devel
```

**Arch Linux:**
```bash
sudo pacman -S base-devel cmake pkg-config libinput sdl2
```

### Optional Libraries

**libdrm** (for DRM/KMS display on ARM platforms - auto-detected):

**Debian/Ubuntu:**
```bash
sudo apt install libdrm-dev
```

## Cloning the Repository

Clone with submodules to obtain the MGS graphics library:

**Via HTTPS:**
```bash
git clone --recurse-submodules https://github.com/mchpgfx/mgs_xp.git
```

**Via SSH:**
```bash
git clone --recurse-submodules git@github.com:mchpgfx/mgs_xp.git
```

If you already cloned without `--recurse-submodules`, initialize submodules manually:
```bash
cd mgs_xp
git submodule update --init --recursive
```

## Building with VS Code

### Setup

1. **Install VS Code:**
   
   **Debian/Ubuntu:**
   ```bash
   sudo snap install code --classic
   ```
   
   Or download from: https://code.visualstudio.com/

2. **Install required extensions:**
   - Open VS Code
   - Go to Extensions (`Ctrl+Shift+X`)
   - Install **CMake Tools** by Microsoft
   - Install **C/C++** by Microsoft

3. **Open the project:**
   - File → Open Folder → Select `mgs_xp_github_mirror`

4. **Configure CMake Kit:**
   - Press `Ctrl+Shift+P` to open Command Palette
   - Type "CMake: Select a Kit" and press Enter
   - Select **GCC** (e.g., "GCC 11.4.0 x86_64-linux-gnu")

5. **Select build variant:**
   - Click on "CMake: [Debug]" in the status bar
   - Choose **Debug** or **Release**

### Building

- **Configure:** Press `Ctrl+Shift+P` → "CMake: Configure"
- **Build:** Press `F7` or `Ctrl+Shift+P` → "CMake: Build"
- **Clean:** Press `Ctrl+Shift+P` → "CMake: Clean"

### Running and Debugging

1. **Set launch target:**
   - Press `Ctrl+Shift+P` → "CMake: Set Debug Target" → Select `mgs_quickstart`

2. **Run without debugging:**
   - Press `Shift+F5`

3. **Debug:**
   - Set breakpoints by clicking left of line numbers
   - Press `Ctrl+F5` to start debugging

### VS Code Settings (Optional)

Create `.vscode/settings.json` in the project root:

```json
{
    "cmake.configureOnOpen": true,
    "C_Cpp.default.compilerPath": "/usr/bin/gcc"
}
```

## Building from Command Line

### Quick Start

```bash
cd mgs_xp
mkdir -p build/host
cd build/host
cmake ../../
make all
```

The executable will be at: `build/host/apps/quickstart/mgs_quickstart`

### Step-by-Step Instructions

1. **Navigate to the project directory:**
   ```bash
   cd mgs_xp
   ```

2. **Create the build directory:**
   ```bash
   mkdir -p build/host
   cd build/host
   ```

3. **Configure the project with CMake:**
   ```bash
   cmake ../../
   ```
   
   Expected output:
   ```
   -- The C compiler identification is GNU 11.4.0
   -- Building for Linux
   -- Found SDL2
   -- Configuring done
   -- Generating done
   ```

4. **Build the project:**
   ```bash
   make all
   ```
   
   For faster builds using all CPU cores:
   ```bash
   make -j$(nproc)
   ```

   To build a specific target instead of everything:
   ```bash
   make example_button
   make example_slider
   ```

   Or using cmake (more portable):
   ```bash
   cmake --build . --target example_button
   ```

   To list all available targets:
   ```bash
   cmake --build . --target help
   ```

5. **Run the application:**
   ```bash
   ./apps/quickstart/mgs_quickstart
   ```

## Running the Application

The quickstart demo opens an 800x480 SDL2 window displaying the Legato UI. Use the mouse to click buttons and navigate between screens.

```bash
./build/host/apps/quickstart/mgs_quickstart
```

### Running on Embedded Linux (without desktop)

On embedded systems without X11/Wayland, the application uses DRM/KMS or framebuffer backends:

```bash
# May require root for direct framebuffer access
sudo ./mgs_quickstart
```

## Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `WITH_SDL2` | `ON` | Enable SDL2 display backend |
| `CMAKE_BUILD_TYPE` | `Debug` | Build type (Debug/Release) |

Examples:
```bash
# Release build
cmake -DCMAKE_BUILD_TYPE=Release ..

# Disable SDL2 (for embedded systems without SDL2)
cmake -DWITH_SDL2=OFF ..

# Combined options
cmake -DCMAKE_BUILD_TYPE=Release -DWITH_SDL2=OFF ..
```

## Rebuilding

After making changes to source files:
```bash
cd build/host
make -j$(nproc)
```

To do a clean rebuild:
```bash
cd build/host
make clean
make all
```

To reconfigure (after changing CMakeLists.txt):
```bash
cd build/host
rm CMakeCache.txt
cmake ../../
make all
```

## Troubleshooting

### "cmake: command not found"

Install CMake:
```bash
# Debian/Ubuntu
sudo apt install cmake

# Fedora
sudo dnf install cmake
```

### "Could not find libinput" or "Could not find libudev"

Install the required development packages:
```bash
# Debian/Ubuntu
sudo apt install libinput-dev libudev-dev

# Fedora
sudo dnf install libinput-devel systemd-devel
```

### "SDL2 not found" (optional dependency)

Install SDL2 development package:
```bash
# Debian/Ubuntu
sudo apt install libsdl2-dev

# Fedora
sudo dnf install SDL2-devel
```

Or disable SDL2:
```bash
cmake -DWITH_SDL2=OFF ..
```

### "Permission denied" when running on framebuffer

Direct framebuffer access requires elevated privileges:
```bash
sudo ./mgs_quickstart
```

Or add your user to the `video` group:
```bash
sudo usermod -a -G video $USER
# Log out and back in for changes to take effect
```

### Window doesn't appear (SDL2 build)

Ensure you have a display server running (X11 or Wayland) and the `DISPLAY` environment variable is set:
```bash
echo $DISPLAY
# Should output something like ":0" or ":1"
```

### Application exits immediately

Check for error messages in the terminal. Common issues:
- Missing display backend (install SDL2 or run on a system with DRM/KMS)
- Insufficient permissions for framebuffer access

## Display Backends

The application automatically selects a display backend in this order:

1. **DRM/KMS** - Direct Rendering Manager (ARM platforms: armv5l, armv7l)
2. **Framebuffer** - Linux framebuffer (`/dev/fb0`)
3. **SDL2** - Desktop window (requires SDL2 and display server)

## Cross-Compiling for Embedded Linux

For ARM targets, use a cross-compilation toolchain:

```bash
mkdir build-arm && cd build-arm
cmake -DCMAKE_TOOLCHAIN_FILE=/path/to/arm-toolchain.cmake ..
make -j$(nproc)
```

## Project Structure

```
mgs_xp_github_mirror/
├── apps/quickstart/          # Example application
├── gfx/middleware/legato/    # Legato graphics library
├── system/
│   ├── linux/                # Linux platform support
│   │   ├── display/          # Display backends (drm/, fbdev/, sdl2/)
│   │   ├── input/            # libinput touch/mouse handling
│   │   └── timer/            # Timer implementation
│   └── windows/              # Windows platform support
└── CMakeLists.txt            # Build configuration
```

## Dependencies Summary

| Dependency | Required | Purpose |
|------------|----------|---------|
| CMake | Yes | Build system |
| GCC | Yes | C compiler |
| pkg-config | Yes | Library detection |
| libinput | Yes | Touch/mouse input |
| libudev | Yes | Device management |
| SDL2 | No | Desktop display/input |
| libdrm | No | DRM/KMS display (ARM) |
