@echo off

cd /d "%~dp0out"

cmake ..

cmake --build . --config Debug

echo .
echo Running program ..
.\Game\Debug\Game.exe

pause
