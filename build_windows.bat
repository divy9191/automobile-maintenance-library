@echo off
echo Building Automobile Maintenance Library for Windows...

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake using MinGW Makefiles to avoid nmake issues
echo Configuring with CMake...
cmake -G "MinGW Makefiles" ..
if errorlevel 1 (
    echo.
    echo CMake configuration failed. Trying alternative generators...
    
    REM Try MSYS Makefiles if MinGW fails
    cmake -G "MSYS Makefiles" ..
    if errorlevel 1 (
        echo.
        echo Trying Visual Studio generator...
        cmake -G "Visual Studio 16 2019" ..
        if errorlevel 1 (
            echo.
            echo All generators failed. Please check your CMake and compiler installation.
            echo.
            echo Requirements:
            echo - CMake 3.16 or higher
            echo - Either MinGW-w64, MSYS2, or Visual Studio with C++ support
            echo.
            echo For MinGW installation: https://www.mingw-w64.org/
            echo For MSYS2 installation: https://www.msys2.org/
            pause
            exit /b 1
        )
    )
)

REM Build the project
echo Building the project...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed. Please check the error messages above.
    pause
    exit /b 1
)

REM Copy web files
echo Copying web interface files...
if exist ..\public (
    xcopy ..\public public\ /E /I /Y > nul
    echo Web files copied successfully.
) else (
    echo Warning: public directory not found. Web interface may not work.
)

echo.
echo Build completed successfully!
echo.
echo To run the server:
if exist maintenance_server.exe (
    echo   maintenance_server.exe
) else (
    echo   Release\maintenance_server.exe
)
echo.
echo IMPORTANT: After running the server, look for the message:
echo "Server started successfully!"
echo.
echo Then open your browser and use the URL shown in the server output.
echo Usually it will be: http://localhost:5000
echo.
echo If you get "can't reach this page", see WINDOWS_TROUBLESHOOTING.md
echo.
pause