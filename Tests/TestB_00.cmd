@echo off

rem Author    KMS - Martin Dubois, P. Eng.
rem Copyright (C) 2021 KMS
rem License   http://www.apache.org/licenses/LICENSE-2.0
rem Product   Maze
rem File      Tests/TestB_00.cmd

echo Executing  Tests/TestB_00.cmd %1  ...

rem ===== Configuration =====================================================

set GENERATOR="Generator=Maze_Gen0.exe"

set SLOW="Slow=0"

set TCP_PORT="TcpPort=49151"

set ZOOM_RACE="Zoom=4"

set ZOOM_RUNNER="Zoom=0"

rem ===== Initialisation ====================================================

set LOCALHOST="IPv4=127.0.0.1"

set CONFIG=%1

set MAZE_RACE_EXE="%CONFIG%\Maze_Race.exe"
set MAZE_RUN0_EXE="%CONFIG%\Maze_Run0.exe"

set RUNNER_COUNT="RunnerCount=2"

rem ===== Verification ======================================================

if ""=="%1" (
    echo USER ERROR  Invalid command line
    echo Usage  Tests\TestB_00.cmd {Config}
    echo                           Debug
    echo                           Release
    pause
    exit /B 10
)

if not exist %MAZE_RACE_EXE% (
    echo FATAL_ERROR  %MAZE_RACE_EXE%  does not exist
    echo Build the solution
    pause
    exit /B 20
)

if not exist %MAZE_RUN0_EXE% (
    echo FATAL_ERROR  %MAZE_RUN0_EXE%  does not exist
    echo Build the solution
    pause
    exit /B 30
)

rem ===== Execution =========================================================

Start "Race" /B %MAZE_RACE_EXE% %GENERATOR% %SLOW% %RUNNER_COUNT% %TCP_PORT% %ZOOM_RACE%
if ERRORLEVEL 1 (
    echo ERROR  Start "Race" %MAZE_RACE_EXE% %GENERATOR% %SLOW% %RUNNER_COUNT% %TCP_PORT% %ZOOM_RACE%  failed - %ERRORLEVEL%
    pause
    exit /B 40
)

echo INSTRUCTION Press enter once the labyrinthe is generated
pause

Start "Left" /B %MAZE_RUN0_EXE% %LOCALHOST% Name=Left %TCP_PORT% %ZOOM_RUNNER%
if ERRORLEVEL 1 (
    echo ERROR  Start %MAZE_RUN0_EXE% %LOCALHOST% Name=Left %TCP_PORT% %ZOOM_RUNNER%  failed - %ERRORLEVEL%
    pause
    exit /B 50
)

%MAZE_RUN0_EXE% Hand=1 %LOCALHOST% Name=Right %TCP_PORT% %ZOOM_RUNNER%
if ERRORLEVEL 1 (
    echo ERROR  %MAZE_RUN0_EXE% Hand=1 %LOCALHOST% Name=Right %TCP_PORT% %ZOOM_RUNNER%  failed - %ERRORLEVEL%
    pause
    exit /B 60
)

rem ===== End ===============================================================

echo OK
