@echo off
setlocal ENABLEDELAYEDEXPANSION

rem === Paths ===
set SFML_DIR=C:\Users\Owner\SFML-2.6.1
set SRC_DIR=%~dp0..\src
set INCLUDE_DIR=%~dp0..\headers
set MAIN=%~dp0..\main.cpp
set OUT=%~dp0..\main.exe

rem === Compiler flags ===
set INCLUDES=-I"%SFML_DIR%\include" -I"%INCLUDE_DIR%"
set LIBS=-L"%SFML_DIR%\lib" -lsfml-graphics -lsfml-window -lsfml-system

rem === Gather all .cpp files in src ===
set SOURCES=
for %%f in ("%SRC_DIR%\*.cpp") do (
    set SOURCES=!SOURCES! "%%f"
)

rem === Compile ===
echo Compiling...
g++ -std=c++17 -g -fno-omit-frame-pointer "%MAIN%" %SOURCES% %INCLUDES% %LIBS% -o "%OUT%"

if %ERRORLEVEL% neq 0 (
    echo Build failed.
    pause
    exit /b %ERRORLEVEL%
)

rem === Run program ===
echo Build succeeded. Running program...
"%OUT%"
pause
endlocal
