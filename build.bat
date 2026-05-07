@echo off
gcc main.c search_engine.c file_merge.c encryption.c file_organizer.c -o FileUtility.exe
if %ERRORLEVEL% EQU 0 (
    echo Build completed successfully.
    echo Run FileUtility.exe to start the program.
) else (
    echo Build failed.
)
