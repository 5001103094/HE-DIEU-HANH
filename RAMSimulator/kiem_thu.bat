@echo off
setlocal
cd /d "%~dp0"

call "%~dp0bien_dich.bat"
if errorlevel 1 exit /b 1

pushd "ket_qua_bien_dich"
ctest -C Debug --output-on-failure
set "KET_QUA=%ERRORLEVEL%"
popd

if not "%KET_QUA%"=="0" (
    echo CO BO KIEM THU THAT BAI.
    exit /b %KET_QUA%
)
echo DA CHAY XONG 7 BO KIEM THU.
exit /b 0
