del .\main.exe

if exist %cd%\build rmdir %cd%\build /q /s

mkdir %cd%\build

cd %cd%\build

cmake -G "MinGW Makefiles" ..

cmake --build .

cd %cd%\..\

.\main.exe