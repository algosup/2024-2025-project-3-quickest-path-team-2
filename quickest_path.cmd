@echo off

:: Navigate to the src folder
cd /d "%~dp0\src" || (
    echo Could not find the src directory. Exiting...
    exit /b 1
)

:: Compile and run the verification program
echo Compiling and running verification program...
echo.
g++ -o verification main_verification.cpp verification.cpp -std=c++17 -pthread
if %errorlevel% neq 0 (
    echo Compilation failed. Exiting...
    exit /b 1
)
verification.exe
if %errorlevel% neq 0 (
    echo Verification failed. Exiting...
    exit /b 1
)
echo Verification completed successfully.
echo.

:: Compile and run the shortest_path program
echo Compiling and running shortest_path program...
echo.
g++ -o shortest_path main.cpp graph.cpp preprocessing.cpp -std=c++17 -pthread
if %errorlevel% neq 0 (
    echo Compilation failed. Exiting...
    exit /b 1
)
shortest_path.exe data/usa_roads.csv 1 1000000
if %errorlevel% neq 0 (
    echo Shortest path program failed. Exiting...
    exit /b 1
)
echo Shortest path program executed successfully.
echo.