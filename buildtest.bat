@echo off
setlocal

REM Root directory
set ROOT_DIR=src\main\algorithm\tests

REM Paths
set TARGET_DIR=target
set SRC_INCLUDE_DIR=src\main\algorithm\include
set OBJECT_DIR=%TARGET_DIR%\object
set TEST_OBJECT_DIR=%TARGET_DIR%\tests
set TEST_INCLUDE_DIR=%ROOT_DIR%\include
set TEST_EXE=%TARGET_DIR%\tests.exe

REM Compiler and flags
set CC=gcc
set CFLAGS=-Wall -Wextra -pedantic -std=c11 

REM Remove old .o files if they exist
if exist "%TEST_OBJECT_DIR%\*.o" (
    echo Deleting old test object files...
    del /q "%TEST_OBJECT_DIR%\*.o"
)

if not exist "%TEST_OBJECT_DIR%" (
    echo Creating tests object directory: %TEST_OBJECT_DIR%
    mkdir "%TEST_OBJECT_DIR%"
    if errorlevel 1 (
        echo ERROR: Failed to create tests object directory.
        exit /b 1
    )
)

REM Compile test files
echo Compiling test files...
setlocal enabledelayedexpansion

for %%f in (%ROOT_DIR%\*.c) do (
    echo Compiling %%f...
    set TEMPFILE=%TEST_OBJECT_DIR%\%%~nxf.o
    %CC% %CFLAGS% -I%TEST_INCLUDE_DIR% -I%SRC_INCLUDE_DIR% -c "%%f" -o "!TEMPFILE!"
    if errorlevel 1 (
        echo ERROR: Compilation failed for %%f
        exit /b 1
    )
)

REM Link object files to produce the final test executable
echo Linking object files...
set LINK_FILES=
for %%f in (%OBJECT_DIR%\*.o) do (
    if not "%%~nxf"=="main.o" (
        set LINK_FILES=!LINK_FILES! "%%f"
    )
)
for %%f in (%TEST_OBJECT_DIR%\*.o) do (
    set LINK_FILES=!LINK_FILES! "%%f"
)
%CC% %CFLAGS% -o "%TEST_EXE%" !LINK_FILES!
if errorlevel 1 (
    echo ERROR: Linking failed.
    exit /b 1
)

REM Check if the build was successful
echo Build successful.
echo Test executable created at: %TEST_EXE%

REM Check if the build was successful
echo Build successful.
echo Starting the executable...
echo.
"%TEST_EXE%"

endlocal
