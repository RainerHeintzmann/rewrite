# Creates a Desktop shortcut "rewrite" (Windows): tools/rewrite-rl (rlwrap:
# history, \alpha TAB -> α, colours) in the project folder, in Windows
# Terminal if it is installed (Ctrl+C copies selected text, otherwise it
# interrupts a computation; Ctrl+Shift+M selects with the keyboard), else in
# the MSYS2 terminal mintty. Icon: tools/rewrite.ico.
# Needs MSYS2 in C:\msys64 with rlwrap (pacman -S rlwrap). Run it once:
#     powershell -ExecutionPolicy Bypass -File tools\make_shortcut.ps1
#     ... -Terminal mintty      to use mintty also with Windows Terminal installed
param([string] $Msys = 'C:\msys64', [string] $Terminal = 'auto')

$project = Split-Path -Parent $PSScriptRoot
$icon    = Join-Path $project 'tools\rewrite.ico'
$mintty  = Join-Path $Msys 'usr\bin\mintty.exe'
$envexe  = Join-Path $Msys 'usr\bin\env.exe'
if (-not (Test-Path $envexe)) { throw "MSYS2 not found in $Msys (use -Msys <folder>)" }
# the MSYS2 UCRT64 environment, a login shell in the project folder
$run = 'MSYSTEM=UCRT64 CHERE_INVOKING=1 /usr/bin/bash -lc tools/rewrite-rl'

$wt = (Get-Command wt.exe -ErrorAction SilentlyContinue).Source
$desktop = [Environment]::GetFolderPath('Desktop')
$shell   = New-Object -ComObject WScript.Shell
$link    = $shell.CreateShortcut((Join-Path $desktop 'rewrite.lnk'))
if ($wt -and $Terminal -ne 'mintty') {
    $link.TargetPath = $wt
    $link.Arguments  = '--title rewrite -d "' + $project + '" "' + $envexe + '" ' + $run
    $used = 'Windows Terminal'
} else {
    if (-not (Test-Path $mintty)) { throw "mintty not found: $mintty" }
    $link.TargetPath = $mintty
    # the window stays open if rewrite ends with an error
    $link.Arguments  = '-i "' + $icon + '" -t rewrite --hold error /usr/bin/env ' + $run
    $used = 'mintty'
}
$link.WorkingDirectory = $project
$link.IconLocation     = $icon + ',0'
$link.Description      = 'rewrite: term rewriting, with history and \alpha completion'
$link.Save()
Write-Host "created: $(Join-Path $desktop 'rewrite.lnk') ($used)"
