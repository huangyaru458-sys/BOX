@echo off
set "USER_DIR=%~dp0"
if "%USER_DIR:~-1%"=="\" set "USER_DIR=%USER_DIR:~0,-1%"
cd /d "%USER_DIR%"
echo Starting Node-RED on http://localhost:1880 ...
node-red -u "%USER_DIR%" -p 1880
