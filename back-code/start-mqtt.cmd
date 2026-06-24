@echo off
echo Starting MQTT broker on 0.0.0.0:1883 ...
cd /d "%~dp0"
node mqtt-broker.js
