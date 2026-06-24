$path = 'D:\finish-tsask\back-code\flows.json'
$text = Get-Content -Raw -Path $path

$telemetryPattern = '(?s)"id": "fn_telemetry".*?"id": "mqtt_in_alert"'
$telemetryValue = @'
"id": "fn_telemetry",
        "type": "function",
        "z": "tab_core",
        "name": "遥测处理",
        "func": "const d = msg.payload || {};\nconst ts = Date.now();\nconst front = !!(d.frontLight || d.frontDoor || d.front_door);\nconst back = !!(d.backLight || d.backDoor || d.back_door);\nconst data = {\n  deviceId: d.deviceId || d.device_id || 'ESP32_BOX_001',\n  temperature: Number(d.temperature || d.temp || 0),\n  humidity: Number(d.humidity || d.hum || 0),\n  capacity: Number(d.capacity || d.fullness || 0),\n  airQuality: Number(d.airQuality || d.air_quality || d.mq135 || 0),\n  humanDetect: !!(d.humanDetect || d.human_detect || d.pir),\n  fanStatus: !!(d.fanStatus || d.fan_status),\n  frontLight: front,\n  backLight: back,\n  frontDoor: front,\n  backDoor: back,\n  tiltAngle: Number(d.tiltAngle || d.tilt_angle || 0),\n  sensorFaults: Array.isArray(d.sensorFaults) ? d.sensorFaults : (Array.isArray(d.sensor_faults) ? d.sensor_faults : []),\n  buzzerMode: d.buzzerMode || d.buzzer_mode || 'off',\n  netMode: d.netMode || d.net_mode || 'STA',\n  systemState: d.systemState || 'STANDBY',\n  lastSeen: ts,\n  mqttOnline: true,\n  mqttBrokerOnline: true\n};\nglobal.set('latestTelemetry', data);\nglobal.set('latestTelemetryRaw', d);\nconst status = [\n  '设备: ' + data.deviceId,\n  '在线: 是',\n  '温度: ' + data.temperature.toFixed(1) + ' C',\n  '湿度: ' + data.humidity.toFixed(1) + ' %',\n  '满载率: ' + data.capacity.toFixed(1) + ' %',\n  '空气质量: ' + data.airQuality,\n  '倾角: ' + data.tiltAngle.toFixed(1) + ' deg',\n  '风扇: ' + (data.fanStatus ? '开' : '关'),\n  '前门: ' + (data.frontLight ? '开' : '关'),\n  '后门: ' + (data.backLight ? '开' : '关'),\n  '故障: ' + (data.sensorFaults.length ? data.sensorFaults.join(',') : '无')\n].join('\\n');\nreturn [\n  { payload: data.temperature, topic: 'temperature' },\n  { payload: data.humidity, topic: 'humidity' },\n  { payload: data.capacity, topic: 'capacity' },\n  { payload: data.airQuality, topic: 'airQuality' },\n  { payload: data.tiltAngle, topic: 'tiltAngle' },\n  { payload: status },\n  { topic: 'INSERT INTO telemetry (device_id,ts,temperature,humidity,capacity,air_quality,human_detect,fan_status,front_door,back_door,tilt_angle,sensor_faults,buzzer_mode,raw_json) VALUES ($p1,$p2,$p3,$p4,$p5,$p6,$p7,$p8,$p9,$p10,$p11,$p12,$p13,$p14)', payload: [data.deviceId, ts, data.temperature, data.humidity, data.capacity, data.airQuality, data.humanDetect ? 1 : 0, data.fanStatus ? 1 : 0, data.frontLight ? 1 : 0, data.backLight ? 1 : 0, data.tiltAngle, JSON.stringify(data.sensorFaults), data.buzzerMode, JSON.stringify(d)] },\n  { topic: 'INSERT INTO devices (device_id,device_name,online,last_seen,mqtt_online) VALUES ($p1,$p2,$p3,$p4,$p5) ON CONFLICT(device_id) DO UPDATE SET device_name=excluded.device_name,online=excluded.online,last_seen=excluded.last_seen,mqtt_online=excluded.mqtt_online', payload: [data.deviceId, 'ESP32_BOX_001', 1, ts, 1] }\n];",
        "outputs": 8,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 560,
        "y": 220,
        "wires": [
            [],
            [],
            [],
            [],
            [],
            [
                "debug_telemetry"
            ],
            [
                "db_core"
            ],
            [
                "db_core"
            ]
        ]
    },
    {
        "id": "mqtt_in_alert"
'@

$alertPattern = '(?s)"id": "fn_alert".*?"id": "mqtt_in_ack"'
$alertValue = @'
"id": "fn_alert",
        "type": "function",
        "z": "tab_core",
        "name": "告警处理",
        "func": "const d = msg.payload || {};\nconst ts = Date.now();\nconst type = d.alertType || d.type || 'ALERT';\nconst text = d.alertMsg || d.message || d.msg || JSON.stringify(d);\nconst suppressUntil = global.get('alarmSuppressUntil') || 0;\nconst suppressed = Date.now() < suppressUntil && /alarm|tilt|door|buzzer|fire|smoke/i.test(type + ' ' + text);\nconst list = global.get('alertList') || [];\nlist.unshift({ id: ts, deviceId: d.deviceId || d.device_id || 'ESP32_BOX_001', type: type, text: text, ts: ts, suppressed: suppressed });\nglobal.set('alertList', list.slice(0, 20));\nconst view = list.slice(0, 20).map(function (i) {\n  return (i.suppressed ? '[抑制] ' : '') + '[' + new Date(i.ts).toLocaleString('zh-CN', { hour12: false }) + '] ' + i.type + ' - ' + i.text;\n}).join('\\n');\nreturn [{ payload: view }, { topic: 'INSERT INTO alerts (device_id,ts,alert_type,alert_msg,is_ack) VALUES ($p1,$p2,$p3,$p4,$p5)', payload: [d.deviceId || d.device_id || 'ESP32_BOX_001', ts, type, text, suppressed ? 1 : 0] }];",
        "outputs": 2,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 560,
        "y": 290,
        "wires": [
            [],
            [
                "db_core"
            ]
        ]
    },
    {
        "id": "mqtt_in_ack"
'@

$refreshPattern = '(?s)"id": "fn_refresh".*?"id": "catch_all"'
$refreshValue = @'
"id": "fn_refresh",
        "type": "function",
        "z": "tab_core",
        "name": "刷新摘要",
        "func": "const d = global.get('latestTelemetry') || {};\nconst ts = d.lastSeen || 0;\nconst age = ts ? Date.now() - ts : null;\nconst online = age !== null && age < 15000;\nconst front = !!(d.frontLight || d.frontDoor);\nconst back = !!(d.backLight || d.backDoor);\nconst suppressed = (global.get('alarmSuppressUntil') || 0) > Date.now();\nconst status = [\n  '设备: ' + (d.deviceId || 'ESP32_BOX_001'),\n  '在线: ' + (online ? '是' : '否'),\n  '最后上报: ' + (ts ? new Date(ts).toLocaleString('zh-CN', { hour12: false }) : '未知'),\n  '离线时长: ' + (age === null ? '未知' : Math.floor(age / 1000) + ' 秒'),\n  '风扇: ' + (d.fanStatus ? '开' : '关'),\n  '前门: ' + (front ? '开' : '关'),\n  '后门: ' + (back ? '开' : '关'),\n  '告警抑制: ' + (suppressed ? '开启' : '关闭')\n].join('\\n');\nreturn [{ payload: status }];",
        "outputs": 1,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 390,
        "y": 410,
        "wires": [
            []
        ]
    },
    {
        "id": "catch_all"
'@

$dashPattern = '(?s)"id": "fn_dash_control".*?"id": "db_dash"'
$dashValue = @'
"id": "fn_dash_control",
        "type": "function",
        "z": "tab_dash",
        "name": "面板控制",
        "func": "const action = msg.payload;\nconst latest = global.get('latestTelemetry') || {};\nconst age = latest.lastSeen ? Date.now() - latest.lastSeen : 1e12;\nconst deviceId = latest.deviceId || 'ESP32_BOX_001';\nif (age > 15000) { return [{ payload: null }, { payload: null }, { payload: '设备离线，禁止控制' }]; }\nif (action === 'ALARM_STOP') { global.set('alarmSuppressUntil', Date.now() + 300000); }\nconst cmd = { deviceId: deviceId, cmd: action, action: action, ts: Date.now() };\nreturn [{ topic: 'device/clothes_box/control', payload: JSON.stringify(cmd) }, { topic: 'INSERT INTO commands (device_id,ts,action,status,source,raw_json) VALUES ($p1,$p2,$p3,$p4,$p5,$p6)', payload: [deviceId, Date.now(), action, 'sent', 'dashboard', JSON.stringify({ action: action })] }, { payload: '动作: ' + action + '\\n设备: ' + deviceId + '\\n时间: ' + new Date().toLocaleString('zh-CN', { hour12: false }) }];",
        "outputs": 3,
        "noerr": 0,
        "initialize": "",
        "finalize": "",
        "libs": [],
        "x": 300,
        "y": 110,
        "wires": [
            [],
            [
                "db_dash"
            ],
            [
                "ui_tpl_status"
            ]
        ]
    },
    {
        "id": "db_dash"
'@

$text = [regex]::Replace($text, $telemetryPattern, $telemetryValue, 1)
$text = [regex]::Replace($text, $alertPattern, $alertValue, 1)
$text = [regex]::Replace($text, $refreshPattern, $refreshValue, 1)
$text = [regex]::Replace($text, $dashPattern, $dashValue, 1)

Set-Content -Path $path -Value $text -Encoding utf8
Write-Host 'patched flows.json'
