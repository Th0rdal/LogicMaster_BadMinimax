@echo off
setlocal

REM Standard paths
set SRC_PATH=src
set TARGET_DIR=target
set OBJECT_DIR=%TARGET_DIR%\production
set ROOT_DIR=%CD%
if "%1" == "" (
    set EXE_TARGET_DIR=%ROOT_DIR%
) else (
    set EXE_TARGET_DIR=%1%
)
set EXE_NAME=BadMinimax.exe

REM Compiler and flags
set CC=gcc
set CFLAGS= -s -O2 -fstack-protector-strong -std=c11 -I%ROOT_DIR%\include

REM Target executable
set TARGET=%EXE_TARGET_DIR%\%EXE_NAME%


REM Remove old .o and .s files if they exist
if exist "%OBJECT_DIR%\*.o" (
    echo Deleting old object files...
    del /q "%OBJECT_DIR%\*.o"
)

REM Create target directories if they don't exist
echo Creating target directories...
if not exist "%TARGET_DIR%" (
    echo Creating target directory: %TARGET_DIR%
    mkdir "%TARGET_DIR%"
    if errorlevel 1 (
        echo ERROR: Failed to create target directory.
        exit /b 1
    )
)
if not exist "%OBJECT_DIR%" (
    echo Creating object directory: %OBJECT_DIR%
    mkdir "%OBJECT_DIR%"
    if errorlevel 1 (
        echo ERROR: Failed to create object directory.
        exit /b 1
    )
)



REM Compile all source files in the source directory and subdirectories, excluding the tests folder
echo Compiling files...
setlocal enabledelayedexpansion
for /R "%ROOT_DIR%" %%f in (*.c) do (
    echo %%f | find "%ROOT_DIR%\tests\" >nul
    if errorlevel 1 (
        echo Compiling %%f...
        set TEMPFILE=%OBJECT_DIR%\%%~nf.o
        echo !TEMPFILE!
        echo Command: %CC% %CFLAGS% -c "%%f" -o !TEMPFILE!
        %CC% %CFLAGS% -c "%%f" -o !TEMPFILE!
        if errorlevel 1 (
            echo ERROR: Compilation failed for %%f
            exit /b 1
        )
    )
)

REM Link object files to produce the final executable
echo Linking object files...
%CC% %CFLAGS% -o "%TARGET%" "%OBJECT_DIR%\*.o"
if errorlevel 1 (
    echo ERROR: Linking failed.
    exit /b 1
)

REM Check if the folder exists before deleting
if exist "%OBJECT_DIR%" (
    rd /s /q "%OBJECT_DIR%"
)


REM Check if the build was successful
echo Build successful.

endlocal