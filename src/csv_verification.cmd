@echo off

:: Navigate to the src directory
cd /d "%~dp0"

:: Compile the verification program
echo.
echo Compiling verification program...
g++ -o verification.exe main_verification.cpp verification.cpp -std=c++17 -pthread
if %errorlevel% neq 0 (
    echo.
    echo Compilation failed. Exiting...
    exit /b 1
)

:: Run the verification program
echo.
echo Running verification program...
verification.exe
if %errorlevel% equ 0 (
    echo.
    echo Verification completed successfully.
) else (
    echo.
    echo Verification failed. Exiting...
    exit /b 1
)