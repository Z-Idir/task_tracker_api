@echo off
call build.bat
if %errorlevel% neq 0 exit /b %errorlevel%

task_tracker.exe %*
