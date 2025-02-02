@echo off

:: Navigate to the src folder
cd /d "%~dp0\src" || (
    echo Could not find the src directory. Verify the path and try again.
    pause >nul
)

:: Compile the verification program
echo Compiling verification program...
g++ -o verification.exe main_verification.cpp verification.cpp -std=c++17 -pthread
if %errorlevel% neq 0 (
    echo.
    echo Compilation failed. Re-execute the verification process.
    pause >nul
    exit /b
)

:: Run the verification program
echo.
echo Running verification program...
verification.exe
if %errorlevel% equ 0 (
    echo Verification completed successfully.
) else (
    echo Verification failed. Re-execute the verification process. 
    pause >nul
    exit /b
)

:: Compile the shortest_path program
echo.
echo Compiling Quickest Path System...
g++ -std=c++17 -O3 -o shortest_path main.cpp graph.cpp preprocessing.cpp -pthread
if %errorlevel% neq 0 (
    echo Compilation failed. Re-execute the program.
    pause >nul
    exit /b
)

:: Run the shortest_path program
echo.
echo Running Quickest Path System...
shortest_path.exe data/usa_roads.csv 1 1000000
if %errorlevel% neq 0 (
    echo Shortest path program failed. Re-execute the program.
    pause >nul
    exit /b
) else (
    echo Shortest path program executed successfully. You can close the window.
    pause >nul
    exit /b
)