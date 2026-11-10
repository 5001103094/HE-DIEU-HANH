
@echo off
setlocal

echo ========================================
echo       RAM SIMULATOR - BUILD C++17
echo ========================================

set "SOLUTION=%~dp0RAMSimulator.sln"
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"

if not exist "%SOLUTION%" (
    echo ERROR: Cannot find RAMSimulator.sln
    exit /b 1
)

if not exist "%VSWHERE%" (
    echo ERROR: Visual Studio Installer not found.
    exit /b 1
)

set "MSBUILD="

for /f "usebackq delims=" %%I in (`"%VSWHERE%" -latest -products * -version "[17.0,18.0)" -requires Microsoft.Component.MSBuild -find "MSBuild\**\Bin\MSBuild.exe"`) do (
    if not defined MSBUILD set "MSBUILD=%%I"
)

if not defined MSBUILD (
    echo ERROR: Visual Studio 2022 MSBuild not found.
    exit /b 1
)

echo Building Debug x64...
"%MSBUILD%" "%SOLUTION%" /m /p:Configuration=Debug /p:Platform=x64 /verbosity:minimal

if errorlevel 1 (
    echo.
    echo BUILD FAILED.
    exit /b 1
)

echo.
echo BUILD SUCCEEDED.
exit /b 0
