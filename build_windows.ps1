# PowerShell build script for Windows
Write-Host "Building Automobile Maintenance Library for Windows..." -ForegroundColor Green

# Create build directory
if (!(Test-Path "build")) {
    New-Item -ItemType Directory -Name "build"
}
Set-Location "build"

# Configure with CMake
Write-Host "Configuring with CMake..." -ForegroundColor Yellow
$configSuccess = $false

# Try MinGW Makefiles first
try {
    cmake -G "MinGW Makefiles" ..
    if ($LASTEXITCODE -eq 0) {
        $configSuccess = $true
        Write-Host "Configuration successful with MinGW Makefiles" -ForegroundColor Green
    }
} catch {
    Write-Host "MinGW Makefiles failed, trying alternatives..." -ForegroundColor Yellow
}

# Try MSYS Makefiles if MinGW failed
if (!$configSuccess) {
    try {
        cmake -G "MSYS Makefiles" ..
        if ($LASTEXITCODE -eq 0) {
            $configSuccess = $true
            Write-Host "Configuration successful with MSYS Makefiles" -ForegroundColor Green
        }
    } catch {
        Write-Host "MSYS Makefiles failed, trying Visual Studio..." -ForegroundColor Yellow
    }
}

# Try Visual Studio as last resort
if (!$configSuccess) {
    try {
        cmake -G "Visual Studio 16 2019" ..
        if ($LASTEXITCODE -eq 0) {
            $configSuccess = $true
            Write-Host "Configuration successful with Visual Studio" -ForegroundColor Green
        }
    } catch {
        # Try newer Visual Studio
        cmake -G "Visual Studio 17 2022" ..
        if ($LASTEXITCODE -eq 0) {
            $configSuccess = $true
            Write-Host "Configuration successful with Visual Studio 2022" -ForegroundColor Green
        }
    }
}

if (!$configSuccess) {
    Write-Host "All CMake generators failed!" -ForegroundColor Red
    Write-Host ""
    Write-Host "Requirements:" -ForegroundColor Yellow
    Write-Host "- CMake 3.16 or higher"
    Write-Host "- One of the following:"
    Write-Host "  * MinGW-w64: https://www.mingw-w64.org/"
    Write-Host "  * MSYS2: https://www.msys2.org/"
    Write-Host "  * Visual Studio with C++ support"
    Write-Host ""
    Read-Host "Press Enter to exit"
    exit 1
}

# Build the project
Write-Host "Building the project..." -ForegroundColor Yellow
cmake --build . --config Release

if ($LASTEXITCODE -ne 0) {
    Write-Host "Build failed! Please check the error messages above." -ForegroundColor Red
    Read-Host "Press Enter to exit"
    exit 1
}

# Copy web files
Write-Host "Copying web interface files..." -ForegroundColor Yellow
if (Test-Path "..\public") {
    Copy-Item "..\public" -Destination "public" -Recurse -Force
    Write-Host "Web files copied successfully." -ForegroundColor Green
} else {
    Write-Host "Warning: public directory not found. Web interface may not work." -ForegroundColor Yellow
}

Write-Host ""
Write-Host "Build completed successfully!" -ForegroundColor Green
Write-Host ""
Write-Host "To run the server:" -ForegroundColor Yellow

if (Test-Path "maintenance_server.exe") {
    Write-Host "  .\maintenance_server.exe" -ForegroundColor Cyan
} elseif (Test-Path "Release\maintenance_server.exe") {
    Write-Host "  .\Release\maintenance_server.exe" -ForegroundColor Cyan
} else {
    Write-Host "  Look for maintenance_server.exe in the current directory" -ForegroundColor Cyan
}

Write-Host ""
Write-Host "Then open your browser to: http://localhost:5000" -ForegroundColor Cyan
Write-Host ""
Read-Host "Press Enter to exit"