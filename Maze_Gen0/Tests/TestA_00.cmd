@echo off

rem Author    KMS - Martin Dubois, P. Eng.
rem Copyright (C) 2021 KMS
rem License   http://www.apache.org/licenses/LICENSE-2.0
rem Product   Maze
rem File      Maze_Gen0/Tests/TestA_00.cmd

echo Executing  Maze_Gen0/Tests/TestA_00.cmd %1  ...

rem ===== Initialisation ====================================================

set CONFIG=%1

set EXE=%CONFIG%\Maze_Gen0.exe

set OUTPUT_BMP=Test.bmp

set EXPECTED_BMP=Maze_Gen0\Tests\TestA_00.bmp

rem ===== Verification ======================================================

if ""=="%1" (
    echo USER ERROR  Invalid command line
    echo Usage  Maze_Gen0\Tests\TestA_00.cmd {Config}
    echo                                     Debug
    echo                                     Release
    exit /B 10
)

if not exist %EXE% (
    echo FATAL ERROR  %EXE%  does not exist
    echo Compile the solution
    exit /B 20
)

rem ===== Execution =========================================================

%EXE% Output=%OUTPUT_BMP% Seed=1 Zoom=0
if ERRORLEVEL 1 (
    echo ERROR  %EXE% Output=%OUTPUT_BMP% Seed=1 Zoom=0  failed - %ERRORLEVEL%
    exit /B 30
)

if not exist %EXPECTED_BMP% (
    echo WARNING  %EXPECTED_BMP% does not exist
    copy %OUTPUT_BMP% %EXPECTED_BMP%
)

fc /B %OUTPUT_BMP% %EXPECTED_BMP%
if ERRORLEVEL 1 (
    echo ERROR  fc /B %OUTPUT_BMP% %EXPECTED_BMP%  failed - %EERORLEVEL%
    exit /B 40
)

rem ===== End ===============================================================

echo OK
