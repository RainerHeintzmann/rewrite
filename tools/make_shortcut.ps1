# Creates a Desktop shortcut "rewrite" (Windows): the MSYS2 terminal (mintty)
# with tools/rewrite-rl (rlwrap: history, \alpha TAB -> α) in the project
# folder, with the icon tools/rewrite.ico.
# Needs MSYS2 in C:\msys64 with rlwrap (pacman -S rlwrap). Run it once:
#     powershell -ExecutionPolicy Bypass -File tools\make_shortcut.ps1
param([string] $Msys = 'C:\msys64')

$project = Split-Path -Parent $PSScriptRoot
$mintty  = Join-Path $Msys 'usr\bin\mintty.exe'
if (-not (Test-Path $mintty)) { throw "mintty not found: $mintty (MSYS2 installed elsewhere? use -Msys <folder>)" }

$desktop = [Environment]::GetFolderPath('Desktop')
$shell   = New-Object -ComObject WScript.Shell
$link    = $shell.CreateShortcut((Join-Path $desktop 'rewrite.lnk'))
$link.TargetPath       = $mintty
# UCRT64 environment, login shell in the project folder (CHERE_INVOKING);
# the window stays open if rewrite ends with an error
$link.Arguments        = '-i "' + (Join-Path $project 'tools\rewrite.ico') + '" -t rewrite --hold error ' +
                         '/usr/bin/env MSYSTEM=UCRT64 CHERE_INVOKING=1 /usr/bin/bash -lc tools/rewrite-rl'
$link.WorkingDirectory = $project
$link.IconLocation     = (Join-Path $project 'tools\rewrite.ico') + ',0'
$link.Description      = 'rewrite: term rewriting, with history and \alpha completion'
$link.Save()
Write-Host "created: $(Join-Path $desktop 'rewrite.lnk')"
