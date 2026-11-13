@echo off
setlocal
cd /d "%~dp0"

where cmake >nul 2>&1
if errorlevel 1 (
    echo CHUA CO CMAKE: Hay cai CMake va bo cong cu bien dich C++17.
    exit /b 1
)

cmake -S . -B ket_qua_bien_dich
if errorlevel 1 exit /b 1

cmake --build ket_qua_bien_dich --config Debug
if errorlevel 1 exit /b 1

echo DA BIEN DICH XONG.
echo Neu dung Visual Studio generator, mo: ket_qua_bien_dich\Debug\mo_phong_bo_nho.exe
exit /b 0
