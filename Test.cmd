@echo off

rem Author    KMS - Martin Dubois, P. Eng.
rem Copyright (C) 2021 KMS
rem License   http://www.apache.org/licenses/LICENSE-2.0
rem Product   Maze
rem File      Test.cmd

echo Executing  Test.cmd  ...

rem ===== Initialisation ====================================================

set EXEC_TEST_CMD=Scripts\ExecTestCmd.ps1

set MAZE_GEN0=Maze_Gen0\Tests

rem ===== Execution =========================================================

Debug/Maze_Lib_Test.exe
if ERRORLEVEL 1 (
    echo ERROR  Debug/Maze_Lib_Test.exe  failed - %ERRORLEVEL%
    exit /B 10
)

Release/Maze_Lib_Test.exe
if ERRORLEVEL 1 (
    echo ERROR  Debug/Maze_Lib_Test.exe  failed - %ERRORLEVEL%
    exit /B 20
)

PowerShell.exe %EXEC_TEST_CMD% %MAZE_GEN0% A Debug
if ERRORLEVEL 1 (
    echo ERROR  PowerShell.exe %EXEC_TEST_CMD% %MAZE_GEN0% A Debug  failed - %ERRORLEVEL%
    exit /B 30
)

PowerShell.exe %EXEC_TEST_CMD% %MAZE_GEN0% A Release
if ERRORLEVEL 1 (
    echo ERROR  PowerShell.exe %EXEC_TEST_CMD% %MAZE_GEN0% A Release  failed - %ERRORLEVEL%
    exit /B 40
)

rem ===== End ===============================================================

echo OK
