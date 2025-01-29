@echo off

:: Navigate to the src folder
cd /d "%~dp0\src" || (
    echo Could not find the src directory. Verify the path and try again.
    pause >nul
)

:: Compile and run the shortest_path program
echo Compiling and running Quickest Path System...
g++ -o shortest_path main.cpp graph.cpp preprocessing.cpp -std=c++17 -pthread
if %errorlevel% neq 0 (
    echo Compilation failed. Re-execute the program.
    pause >nul
)
shortest_path.exe data/usa_roads.csv 1 1000000
if %errorlevel% neq 0 (
    echo Shortest path program failed. Re-execute the program.
    pause >nul
)
echo Shortest path program executed successfully.
pause >nul