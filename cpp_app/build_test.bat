@echo off
echo Building MediCheck Test Suite...

:: Create build directory if it doesn't exist
if not exist "bin" mkdir bin

:: Compile test file with all dependencies
echo Compiling test suite...
g++ -std=c++17 -Wall -Wextra -O2 test_medicheck.cpp patient.cpp patient_manager.cpp diagnosis.cpp -o bin\test_medicheck.exe

if %errorlevel% neq 0 (
    echo Test build failed!
    pause
    exit /b 1
)

echo Test build successful! Executable created: bin\test_medicheck.exe
echo.
echo To run the tests, execute: bin\test_medicheck.exe
pause
