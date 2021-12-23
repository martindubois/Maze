
# Author    KMS - Martin Dubois, P. Eng.
# Copyright (C) 2021 KMS
# License   http://www.apache.org/licenses/LICENSE-2.0
# Product   Maze
# File      Scripts/ExecTestCmd.ps1

Write-Output ( "Executing  Scripts/ExecTestCmd.ps1 " + $args + " ..." )

# ===== Initialisation ======================================================

$Folder = $args[0]

$Group = $args[1]

$Config = $args[2]

$Filter = "Test" + $Group + "_*.cmd"

# ===== Functions ===========================================================

function ExecuteTest
{
    param($Name)

    & $Folder\$Name $Config
    if (!$?)
    {
        Write-Error ERROR  The test failed
        exit 10
    }
}

# ===== Execution ===========================================================

$Tests = Get-ChildItem -Filter $Filter -Path $Folder
if ((!$?) -Or (0 -ge $Tests.Length))
{
    Write-Error ERROR  No test to execute
    exit 10
}

$Tests | ForEach-Object { ExecuteTest -Name $_ }

# ===== End =================================================================

Write-Output OK
