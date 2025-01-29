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
)

:: Run the verification program
echo.
echo Running verification program...
verification.exe
if %errorlevel% equ 0 (
    echo Verification completed successfully.
    pause >nul
) else (
    echo Verification failed. Re-execute the verification process. 
    pause >nul
)

:: Compile and run the shortest_path program
echo Compiling and running shortest_path program...
echo.
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