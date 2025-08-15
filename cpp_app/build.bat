@echo off
echo Building MediCheck C++ Application...

:: Create build directory if it doesn't exist
if not exist "bin" mkdir bin

:: Compile all source files
echo Compiling source files...
g++ -std=c++17 -Wall -Wextra -O2 main.cpp patient.cpp patient_manager.cpp diagnosis.cpp -o bin\medicheck.exe

if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo Build successful! Executable created: bin\medicheck.exe
echo.
echo To run the application, execute: bin\medicheck.exe
pause
