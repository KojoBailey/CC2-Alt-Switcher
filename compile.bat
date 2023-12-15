@ECHO OFF

echo Compiling...
g++ src/main.cpp src/functions.cpp src/json.cpp src/convert.cpp -o "CC2 Alt Switch.exe" -std=c++20 -static -static-libgcc -static-libstdc++