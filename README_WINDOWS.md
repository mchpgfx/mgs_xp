# Building MGS XP on Windows

This guide describes how to build the MGS XP cross-platform graphics library on Windows.

## Prerequisites

### 1. CMake (3.14 or later)

1. Download the Windows installer from: https://cmake.org/download/
2. Run the installer
3. **Important**: Select "Add CMake to the system PATH" during installation

Verify installation by opening a new Command Prompt:
```cmd
cmake --version
```

### 2. MinGW-w64 Toolchain

Download a pre-built MinGW-w64 toolchain from winlibs: https://winlibs.com/

**Recommended download:**
- Go to the "Release versions" section
- Download: **GCC 13.x.x + LLVM/Clang/LLD/LLDB xx.x.x + MinGW-w64 xx.x.x (UCRT) - Win64: 7-Zip archive**
- Direct link (GCC 13.2.0): https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0posix-17.0.6-11.0.1-ucrt-r5/winlibs-x86_64-posix-seh-gcc-13.2.0-llvm-17.0.6-mingw-w64ucrt-11.0.1-r5.7z

**Installation:**

1. Extract the 7z archive to a location without spaces, e.g.:
   ```
   C:\mingw64
   ```

2. Add MinGW to your system PATH:
   - Press `Win + R`, type `sysdm.cpl`, press Enter
   - Click "Advanced" tab → "Environment Variables"
   - Under "System variables", select "Path" and click "Edit"
   - Click "New" and add: `C:\mingw64\bin`
   - Click "OK" on all dialogs

3. Open a **new** Command Prompt and verify:
   ```cmd
   gcc --version
   mingw32-make --version
   ```

### 3. Git (optional)

For cloning the repository: https://git-scm.com/download/win

## Building with VS Code

### Setup

1. **Install VS Code** from: https://code.visualstudio.com/

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
   - Select **GCC 13.x.x x86_64-w64-mingw32** (or similar MinGW option)
   
   If no MinGW kit appears:
   - Press `Ctrl+Shift+P` → "CMake: Scan for Kits"
   - Ensure MinGW is in your system PATH and restart VS Code

5. **Select build variant:**
   - Click on "CMake: [Debug]" in the status bar (bottom)
   - Or press `Ctrl+Shift+P` → "CMake: Select Variant"
   - Choose **Debug** or **Release**

### Building

- **Configure:** Press `Ctrl+Shift+P` → "CMake: Configure"
- **Build:** Press `F7` or `Ctrl+Shift+P` → "CMake: Build"
- **Clean:** Press `Ctrl+Shift+P` → "CMake: Clean"

### Running and Debugging

1. **Set launch target:**
   - Click on the launch target in the status bar (shows `[mgs_quickstart]`)
   - Or press `Ctrl+Shift+P` → "CMake: Set Debug Target" → Select `mgs_quickstart`

2. **Run without debugging:**
   - Press `Shift+F5`
   - Or click the play button in the status bar

3. **Debug:**
   - Set breakpoints by clicking left of line numbers
   - Press `Ctrl+F5` to start debugging
   - Use the debug toolbar to step through code

### VS Code Settings (Optional)

Create `.vscode/settings.json` in the project root for project-specific settings:

```json
{
    "cmake.generator": "MinGW Makefiles",
    "cmake.configureOnOpen": true,
    "C_Cpp.default.compilerPath": "C:/mingw64/bin/gcc.exe"
}
```

## Building from Command Line

The SDL2 library is bundled in the repository - no external SDL2 installation required.

### Quick Start

Open Command Prompt and run:

```cmd
cd C:\path\to\mgs_xp_github_mirror
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
```

The executable will be at: `build\apps\quickstart\mgs_quickstart.exe`

### Step-by-Step Instructions

1. **Open Command Prompt**
   
   Press `Win + R`, type `cmd`, press Enter.

2. **Navigate to the project directory:**
   ```cmd
   cd C:\path\to\mgs_xp_github_mirror
   ```

3. **Create the build directory:**
   ```cmd
   mkdir build
   cd build
   ```

4. **Configure the project with CMake:**
   ```cmd
   cmake -G "MinGW Makefiles" ..
   ```
   
   Expected output:
   ```
   -- The C compiler identification is GNU 13.2.0
   -- Building for Windows
   -- Found SDL2 (bundled)
   -- Configuring done
   -- Generating done
   ```

5. **Build the project:**
   ```cmd
   mingw32-make
   ```
   
   This compiles all source files and links the executable. Build time is approximately 1-2 minutes.

   To build a specific target instead of everything:
   ```cmd
   mingw32-make example_button
   mingw32-make example_slider
   ```

   Or using cmake (more portable):
   ```cmd
   cmake --build . --target example_button
   ```

   To list all available targets:
   ```cmd
   mingw32-make help
   ```

6. **Run the application:**
   ```cmd
   apps\quickstart\mgs_quickstart.exe
   ```

## Running the Application

The quickstart demo opens an 800x480 SDL2 window displaying the Legato UI. Use the mouse to click buttons and navigate between screens.

To run from any directory:
```cmd
C:\path\to\mgs_xp_github_mirror\build\apps\quickstart\mgs_quickstart.exe
```

## Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `WITH_SDL2` | `ON` | Enable SDL2 display backend |

Example with options:
```cmd
cmake -G "MinGW Makefiles" -DWITH_SDL2=ON ..
```

## Rebuilding

After making changes to source files:
```cmd
cd build
mingw32-make
```

To do a clean rebuild:
```cmd
cd build
mingw32-make clean
mingw32-make
```

To reconfigure (after changing CMakeLists.txt):
```cmd
cd build
del CMakeCache.txt
cmake -G "MinGW Makefiles" ..
mingw32-make
```

## Troubleshooting

### "cmake is not recognized as an internal or external command"

CMake is not in your PATH. Either:
- Reinstall CMake and select "Add CMake to system PATH"
- Manually add `C:\Program Files\CMake\bin` to your PATH environment variable

### "gcc is not recognized" or "mingw32-make is not recognized"

MinGW is not in your PATH. Verify:
1. MinGW is extracted to `C:\mingw64` (or your chosen location)
2. `C:\mingw64\bin` is added to your system PATH
3. You opened a **new** Command Prompt after modifying PATH

### "cmake: command not found" (in Git Bash)

Use the full path or ensure CMake is in PATH:
```bash
"/c/Program Files/CMake/bin/cmake" -G "MinGW Makefiles" ..
```

### Build fails with "cannot find -lSDL2"

The bundled SDL2 library was not found. Ensure you're building from the repository root:
```cmd
cd C:\path\to\mgs_xp_github_mirror
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
```

### Application crashes or window doesn't appear

Verify `SDL2.dll` is in the same directory as the executable:
```cmd
dir build\apps\quickstart\SDL2.dll
```

If missing, rebuild or manually copy:
```cmd
copy system\windows\sdl2\bin\SDL2.dll build\apps\quickstart\
```

## Project Structure

```
mgs_xp_github_mirror/
├── apps/quickstart/          # Example application
├── gfx/middleware/legato/    # Legato graphics library
├── system/
│   ├── linux/                # Linux platform support
│   └── windows/              # Windows platform support
│       ├── display/sdl2/     # SDL2 display driver
│       ├── timer/            # SDL2-based timer
│       └── sdl2/             # Bundled SDL2 SDK
│           ├── bin/          # SDL2.dll runtime
│           ├── include/      # SDL2 headers
│           └── lib/          # Import libraries & CMake config
└── CMakeLists.txt            # Build configuration
```

## Bundled Dependencies

| Library | Version | License | Website |
|---------|---------|---------|---------|
| SDL2 | 2.30.3 | zlib | https://www.libsdl.org/ |

SDL2 is bundled in `system/windows/sdl2/` for convenience. No additional downloads required.
