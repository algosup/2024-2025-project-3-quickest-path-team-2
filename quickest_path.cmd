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

:: 2. Install the required packages on the Downloads folder

echo.
echo Before do the following steps, make sure to install the following packages in your downloads folder:
echo - Boost Zip (Windows 10) : https://archives.boost.io/release/1.87.0/source/boost_1_87_0.zip
echo - Boost 7z (Windows 11) : https://archives.boost.io/release/1.87.0/source/boost_1_87_0.7z
echo - CMake : https://github.com/Kitware/CMake/releases/download/v3.31.5/cmake-3.31.5-windows-x86_64.msi
echo - Git : https://github.com/git-for-windows/git/releases/download/v2.47.1.windows.2/Git-2.47.1.2-64-bit.exe

echo.
echo Once is done, press any key to continue... (Don't install them manually, the script will do it for you)
pause>nul

:: 3. Navigating to the Downloads folder

cd /d "%USERPROFILE%\\Downloads" 2>nul || (
    echo.
    echo The folder specified in the code does not exist.
    echo.
    echo The script has been automatically stopped. Click on any key to restart it.
    pause >nul
)

:: 4. Install Boost

echo.
IF EXIST "boost_1_87_0.zip" (
    echo Extracting Boost Zip...
    echo This takes approximately 45 minutes, please wait...
    powershell -Command "Expand-Archive -Path boost_1_87_0.zip -DestinationPath boost_1_87_0"
) ELSE IF EXIST "boost_1_87_0.7z" (
    echo Extracting Boost 7z...
    echo You need to install 7-Zip to extract the 7z file if you want to do it automatically.
    echo If not, please extract the file manually.
    echo.
    choice /c yn /n /m "Do you want to extract Boost manually? [y/n]" 2>nul
    if %errorlevel% neq 0 (
        echo 7-Zip: https://www.7-zip.org/a/7z2409-x64.exe
        echo.
        echo Once is done, press any key to continue...
        pause>nul
        echo Installing 7-Zip...
        run "7z2409-x64.exe"
        if %errorlevel% neq 0 (
            echo.
            echo An error occurred while installing 7-Zip.
            echo Please install it manually and try again.
            echo.
            echo Press any key to exit...
            pause>nul
            exit /b
        ) else (
            echo.
            echo 7-Zip has been installed successfully.
            pause
        )
        echo.
        echo Extracting Boost 7z...
        7z x -y boost_1_87_0.7z -o boost_1_87_0
    ) else (
        echo.
        echo Please extract the file manually in your Downloads folder.
        echo.
        echo When you're done, press any key to continue...
        pause>nul
    )
) ELSE (
    echo No Boost package found. Please download it and try again.
    echo.
    echo Press any key to exit...
    pause>nul
    exit /b
)

cd /d "C:\" 2>nul || (
    echo.
    echo The folder specified in the code does not exist.
    echo.
    echo The script has been automatically stopped. Click on any key to restart it.
    pause >nul
)
echo.
echo Creating the Boost folder...
mkdir "Boost"
echo.
echo Moving the Boost files to the Boost folder...
move "%USERPROFILE%\\Downloads\\boost_1_87_0" "C:\\Boost"

:: 5. Install CMake

echo.
echo Installing CMake...
run "cmake-3.31.5-windows-x86_64.msi"
if %errorlevel% neq 0 (
    echo.
    echo An error occurred while installing CMake.
    echo Please install it manually and try again.
    echo.
    pause
) else (
    echo.
    echo CMake has been installed successfully.
    pause
)

:: 6. Install Git

echo.
echo Installing Git...
run "Git-2.47.1.2-64-bit.exe"
if %errorlevel% neq 0 (
    echo.
    echo An error occurred while installing Git.
    echo Please install it manually and try again.
    echo.
    pause
) else (
    echo.
    echo Git has been installed successfully.
    echo.
    pause
)

:: 7. Compile and Build Boost Files

cd /d "C:\Boost\boost_1_87_0" 2>nul || (
    echo.
    echo The folder specified in the code does not exist.
    echo.
    echo The script has been automatically stopped. Click on any key to restart it.
    pause >nul
)
echo Compiling Boost files...
bootstrap.bat mingw
echo.
echo Building Boost files...
b2 --with-system --with-thread --with-filesystem toolset=gcc link=static runtime-link=static variant=release

:: 8. Rename Boost files

cd /d "C:\Boost\boost_1_87_0\stage\lib" 2>nul || (
    echo.
    echo The folder specified in the code does not exist.
    echo.
    echo The script has been automatically stopped. Click on any key to restart it.
    pause >nul
)
echo.
echo Renaming Boost files...
rename libboost_filesystem-mgw14-mt-s-x64-1_87.a libboost_filesystem.a
rename libboost_system-mgw14-mt-s-x64-1_87.a libboost_system.a
rename libboost_thread-mgw14-mt-s-x64-1_87.a libboost_thread.a

:: 9. Cloning and compiling the vcpkg repository

cd /d "%USERPROFILE%\\Downloads" 2>nul || (
    echo.
    echo The folder specified in the code does not exist.
    echo.
    echo The script has been automatically stopped. Click on any key to restart it.
    pause >nul
)
echo.
echo Cloning the vcpkg repository...
git clone https://github.com/microsoft/vcpkg
echo.
echo Moving into the vcpkg folder...
cd /d "%USERPROFILE%\\Downloads\\vcpkg" 2>nul || (
    echo.
    echo The folder specified in the code does not exist.
    echo.
    echo The script has been automatically stopped. Click on any key to restart it.
    pause >nul
)
echo.
echo Compiling vcpkg repository...
.\bootstrap-vcpkg.bat
echo.
echo Integrating vcpkg to your environment...
.\vcpkg integrate install
echo.
echo Installing Asio...
.\vcpkg install asio

:: 10. Moving asio into the API folder

cd /d "%USERPROFILE%\\Downloads\\vcpkg\\packages\\asio_x64-windows\\include\\asio.hpp" 2>nul || (
    echo.
    echo The folder specified in the code does not exist.
    echo.
    echo The script has been automatically stopped. Click on any key to restart it.
    pause >nul
)
echo.
echo Moving Asio into the API folder...
move "%USERPROFILE%\\Downloads\\vcpkg\\packages\\asio_x64-windows\\include\\asio.hpp" "%USERPROFILE%\\Downloads\\2024-2025-project-3-quickest-path-team-2\\src\\api\\include\\asio.hpp"
move "%USERPROFILE%\\Downloads\\vcpkg\\packages\\asio_x64-windows\\include\\asio" "%USERPROFILE%\\Downloads\\2024-2025-project-3-quickest-path-team-2\\src\\api\\include\\asio"

:: 11. Install MSYS2

echo.
echo MSYS2: https://github.com/msys2/msys2-installer/releases/download/2024-12-08/msys2-x86_64-20241208.exe
echo.
echo Once is done, press any key to continue...
pause>nul
echo.
echo Installing MSYS2...
run "msys2-x86_64-20241208.exe"
echo.
echo Follow all the steps in the MSYS2 installer without changing anything to the default parameters. 
echo When you're done, press any key to continue...
pause>nul
echo Launching MINGW64...
cd /d "C:\msys64" 2>nul || (
    echo.
    echo The folder specified in the code does not exist.
    echo.
    echo The script has been automatically stopped. Click on any key to restart it.
    pause >nul
)

:: 12. Execute the commands into the MINGW64 terminal

run "mingw64.exe"
echo Write the bellowing command in the MINGW64 terminal:
echo pacman -Syu
echo pacman -S mingw-w64-x86_64-make
echo.
echo Follow the steps indicated in the MINGW64 terminal.
echo Once is done, press any key to continue...
pause>nul

:: 13. Put the required files in the PATH

echo.
echo Adding the required files to the PATH...
setx /M PATH "%PATH%;C:\msys64\mingw64\bin;C:\Program Files\CMake\bin"

:: 14. Launch the new terminal

cd /d "%USERPROFILE%\\Downloads\\2024-2025-project-3-quickest-path-team-2" 2>nul || (
    echo.
    echo The folder specified in the code does not exist.
    echo.
    echo The script has been automatically stopped. Click on any key to restart it.
    pause >nul
)
echo.
echo Launching the new terminal...
run "build_api.cmd"
