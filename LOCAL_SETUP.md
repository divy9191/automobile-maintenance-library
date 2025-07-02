# Running Automobile Maintenance Library Locally

## Prerequisites

### Required Software:
1. **C++ Compiler** (GCC 7+ or Clang 10+)
2. **CMake** (version 3.16 or higher)
3. **Make** (or equivalent build tool)
4. **Git** (to clone the repository)

## Installation by Operating System

### Windows

#### Option 1: Using Visual Studio
1. Download and install [Visual Studio Community](https://visualstudio.microsoft.com/downloads/)
2. During installation, select "Desktop development with C++"
3. Install [CMake](https://cmake.org/download/) - choose "Add CMake to system PATH"

#### Option 2: Using MinGW-w64
1. Install [MSYS2](https://www.msys2.org/)
2. Open MSYS2 terminal and run:
```bash
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-cmake
pacman -S mingw-w64-x86_64-make
```

### macOS
1. Install Xcode Command Line Tools:
```bash
xcode-select --install
```
2. Install CMake using Homebrew:
```bash
brew install cmake
```

### Linux (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install build-essential cmake git pkg-config
```

### Linux (CentOS/RHEL/Fedora)
```bash
# For CentOS/RHEL:
sudo yum groupinstall "Development Tools"
sudo yum install cmake git pkgconfig

# For Fedora:
sudo dnf groupinstall "Development Tools"
sudo dnf install cmake git pkgconfig
```

## Download and Setup

### Step 1: Get the Project Files
If you have the project as a zip file, extract it. Otherwise, if it's in a repository:
```bash
git clone [repository-url]
cd automobile-maintenance-library
```

### Step 2: Verify Your Project Structure
Make sure you have this folder structure:
```
automobile-maintenance-library/
├── CMakeLists.txt
├── src/
│   ├── Automobile.h
│   ├── Automobile.cpp
│   ├── MaintenanceTask.h
│   ├── MaintenanceTask.cpp
│   ├── MaintenanceLibrary.h
│   ├── MaintenanceLibrary.cpp
│   └── main.cpp
├── public/
│   ├── index.html
│   ├── style.css
│   └── app.js
├── tests/
│   ├── test_automobile.cpp
│   └── test_maintenance_library.cpp
└── demo_script.md
```

## Building and Running

### Step 1: Create Build Directory
```bash
mkdir build
cd build
```

### Step 2: Configure with CMake
```bash
cmake ..
```

If you get errors, try specifying the compiler:
```bash
# For GCC:
cmake -DCMAKE_CXX_COMPILER=g++ ..

# For Clang:
cmake -DCMAKE_CXX_COMPILER=clang++ ..
```

### Step 3: Build the Project
```bash
# On Linux/macOS:
make

# On Windows with Visual Studio:
cmake --build . --config Release

# Alternative for Windows with MinGW:
mingw32-make
```

### Step 4: Copy Web Files
```bash
# Copy the web interface files to the build directory
cp -r ../public .

# On Windows:
xcopy ..\public public\ /E /I
```

### Step 5: Run the Server
```bash
# On Linux/macOS:
./maintenance_server

# On Windows:
maintenance_server.exe
```

You should see:
```
Server running on http://0.0.0.0:5000
```

### Step 6: Access the Web Interface
Open your web browser and go to:
```
http://localhost:5000
```

## Troubleshooting

### Common Issues:

#### 1. CMake Not Found
```bash
# Verify CMake installation:
cmake --version

# If not found, add to PATH or reinstall CMake
```

#### 2. Compiler Errors
```bash
# Check GCC version (needs 7+):
gcc --version

# Update if needed:
# Ubuntu/Debian:
sudo apt install gcc-9 g++-9

# macOS:
brew install gcc
```

#### 3. Port Already in Use
If port 5000 is busy, edit `src/main.cpp` and change:
```cpp
SimpleHTTPServer server(5000, library);  // Change 5000 to another port like 8080
```
Then rebuild and run.

#### 4. Permission Denied (Linux/macOS)
```bash
chmod +x maintenance_server
```

#### 5. Web Files Not Loading
Make sure you copied the `public` folder to the build directory:
```bash
ls -la public/  # Should show index.html, style.css, app.js
```

### Building with Tests (Optional)
To enable unit tests, uncomment the test section in `CMakeLists.txt`:
```cmake
# Uncomment these lines in CMakeLists.txt:
find_package(GTest REQUIRED)
add_executable(run_tests
    tests/test_automobile.cpp
    tests/test_maintenance_library.cpp
    src/Automobile.cpp
    src/MaintenanceTask.cpp
    src/MaintenanceLibrary.cpp
)
target_include_directories(run_tests PRIVATE src)
target_link_libraries(run_tests GTest::gtest GTest::gtest_main pthread)
```

Then install Google Test and rebuild.

## Development Tips

### Code Changes
After modifying C++ source files:
1. Run `make` (or `cmake --build .`) in the build directory
2. Restart the server
3. Refresh your browser

### Web Interface Changes
After modifying HTML/CSS/JavaScript files:
1. Copy files to build directory: `cp -r ../public .`
2. Refresh your browser (no need to restart server)

### Different Build Types
```bash
# Debug build (for development):
cmake -DCMAKE_BUILD_TYPE=Debug ..

# Release build (for production):
cmake -DCMAKE_BUILD_TYPE=Release ..
```

## Project Structure Explanation

- **src/**: C++ source code (backend)
- **public/**: Web interface files (frontend)
- **tests/**: Unit tests
- **build/**: Generated build files (created during compilation)
- **CMakeLists.txt**: Build configuration

## Performance Notes

- The server uses a simple HTTP implementation suitable for development
- For production use, consider integrating with a proper web server like Apache or Nginx
- The application stores data in memory - data will be lost when the server restarts
- Consider adding database persistence for production use

## Next Steps

Once running locally, you can:
1. Follow the demo script to test all features
2. Modify the C++ code to add new vehicle types or maintenance tasks
3. Customize the web interface styling
4. Add new features like maintenance scheduling
5. Integrate with databases for data persistence

## Getting Help

If you encounter issues:
1. Check the error messages carefully
2. Verify all prerequisites are installed
3. Ensure file permissions are correct
4. Try building in a clean directory (`rm -rf build` then start over)