@echo off
REM This file is used to move every !fileNum! files into one folder
set /a fileNum = 2
set /a nf = 0
set /a nd = 0
setlocal enabledelayedexpansion
for %%i in (*.txt) do (
    if !nf!==0 (
        echo creat folder ./!nd!
        md !nd! 
    )
    echo move %%i into !nd!
    move %%i ./!nd!/%%i
    set /a nf += 1
    if !nf! == !fileNum! (
        set /a nd += 1
        set /a nf = 0
    ) 
)

pause
