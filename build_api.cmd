@echo off

:: 1. Verify if the script is running as administrator
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo Ask for elevation...
    powershell -Command "Start-Process '%~0' -Verb RunAs"
    exit /b
) else (
    echo Script exécuté avec privilèges administrateur.
)

:: 2. Execute the commands into the Powershell terminal
cd /d "%USERPROFILE%\\Downloads\\2024-2025-project-3-quickest-path-team-2\\src\\api" 2>nul || (
    echo.
    echo The folder specified in the code does not exist.
    echo.
    echo The script has been automatically stopped. Click on any key to restart it.
    pause >nul
)
echo.
echo Creating the build folder...
mkdir "build"
cd "build"
echo.
echo Generating the build files...
cmake -S .. -G "MinGW Makefiles"
echo.
echo Building the project...
mingw32-make
echo.
echo The project has been built successfully.

:: 3. Execute the project
echo.
echo Executing the project...
run ""
echo.
echo The project has been executed successfully. Click on any key to close the terminal.
pause<nul
exit /b