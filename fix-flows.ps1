$path = 'D:\finish-tsask\back-code\flows.json'
$text = Get-Content -Raw -LiteralPath $path

$text = $text.Replace(
'"id": "fn_telemetry",
    "type": "function",
    "z": "tab_core",
    "name": "閬ユ祴澶勭悊",
    "func": "const d=msg.payload||{};const ts=Date.now();const data={deviceId:d.deviceId||d.device_id||''ESP32_BOX_001'',temperature:Number(d.temperature??d.temp??0),humidity:Number(d.humidity??d.hum??0),capacity:Number(d.capacity??d.fullness??0),airQuality:Number(d.airQuality??d.air_quality??d.mq135??0),humanDetect:Boolean(d.humanDetect??d.human_detect??d.pir??false),fanStatus:Boolean(d.fanStatus??d.fan_status??false),frontLight:Boolean(d.(d.frontLight??d.frontLight??d.front_door??false)),backLight:Boolean(d.(d.backLight??d.backLight??d.back_door??false)),tiltAngle:Number(d.tiltAngle??d.tilt_angle??0),sensorFaults:Array.isArray(d.sensorFaults)?d.sensorFaults:(Array.isArray(d.sensor_faults)?d.sensor_faults:[]),buzzerMode:d.buzzerMode||d.buzzer_mode||''off'',netMode:d.netMode||d.net_mode||''STA'',lastSeen:ts,mqttOnline:true,mqttBrokerOnline:true};global.set(''latestTelemetry'',data);const online=true;const status=[''璁惧: ''+data.deviceId,''鐘舵€? ''+(online?''鍦ㄧ嚎'':''绂荤嚎''),''娓╁害: ''+data.temperature.toFixed(1)+'' 掳C'',''婀垮害: ''+data.humidity.toFixed(1)+'' %'',''婊¤浇鐜? ''+data.capacity.toFixed(1)+'' %'',''绌烘皵璐ㄩ噺: ''+data.airQuality,''鍊炬枩瑙? ''+data.tiltAngle.toFixed(1)+'' 掳'',''椋庢墖: ''+(data.fanStatus?''寮€鍚?:''鍏抽棴''),''鍓嶉棬: ''+(data.frontLight?''寮€鍚?:''鍏抽棴''),''鍚庨棬: ''+(data.backLight?''寮€鍚?:''鍏抽棴''),''鏁呴殰: ''+(data.sensorFaults.length?data.sensorFaults.join('','') :''鏃?)].join(''\\n'');return[{payload:data.temperature,topic:''temperature''},{payload:data.humidity,topic:''humidity''},{payload:data.capacity,topic:''capacity''},{payload:data.airQuality,topic:''airQuality''},{payload:data.tiltAngle,topic:''tiltAngle''},{payload:status},{topic:''INSERT INTO telemetry (device_id,ts,temperature,humidity,capacity,air_quality,human_detect,fan_status,front_door,back_door,tilt_angle,sensor_faults,buzzer_mode,raw_json) VALUES ($p1,$p2,$p3,$p4,$p5,$p6,$p7,$p8,$p9,$p10,$p11,$p12,$p13,$p14)'',payload:[data.deviceId,ts,data.temperature,data.humidity,data.capacity,data.airQuality,data.humanDetect?1:0,data.fanStatus?1:0,data.frontLight?1:0,data.backLight?1:0,data.tiltAngle,JSON.stringify(data.sensorFaults),data.buzzerMode,JSON.stringify(d)]},{topic:''INSERT INTO devices (device_id,device_name,online,last_seen,mqtt_online) VALUES ($p1,$p2,$p3,$p4,$p5) ON CONFLICT(device_id) DO UPDATE SET device_name=excluded.device_name,online=excluded.online,last_seen=excluded.last_seen,mqtt_online=excluded.mqtt_online'',payload:[data.deviceId,''智能衣物回收箱'',1,ts,1]}];",',
'"id": "fn_telemetry",
    "type": "function",
    "z": "tab_core",
    "name": "遥测处理",
    "func": "const d = msg.payload || {}; const ts = Date.now(); const front = Boolean(d.frontLight ?? d.frontDoor ?? d.front_door ?? false); const back = Boolean(d.backLight ?? d.backDoor ?? d.back_door ?? false); const data = { deviceId: d.deviceId || d.device_id || 'ESP32_BOX_001', temperature: Number(d.temperature ?? d.temp ?? 0), humidity: Number(d.humidity ?? d.hum ?? 0), capacity: Number(d.capacity ?? d.fullness ?? 0), airQuality: Number(d.airQuality ?? d.air_quality ?? d.mq135 ?? 0), humanDetect: Boolean(d.humanDetect ?? d.human_detect ?? d.pir ?? false), fanStatus: Boolean(d.fanStatus ?? d.fan_status ?? false), frontLight: front, backLight: back, frontDoor: front, backDoor: back, tiltAngle: Number(d.tiltAngle ?? d.tilt_angle ?? 0), sensorFaults: Array.isArray(d.sensorFaults) ? d.sensorFaults : (Array.isArray(d.sensor_faults) ? d.sensor_faults : []), buzzerMode: d.buzzerMode || d.buzzer_mode || 'off', netMode: d.netMode || d.net_mode || 'STA', lastSeen: ts, mqttOnline: true, mqttBrokerOnline: true }; global.set('latestTelemetry', data); global.set('latestTelemetryRaw', d); const status = ['设备: ' + data.deviceId, '状态: 在线', '温度: ' + data.temperature.toFixed(1) + ' °C', '湿度: ' + data.humidity.toFixed(1) + ' %', '满载率: ' + data.capacity.toFixed(1) + ' %', '空气质量: ' + data.airQuality, '倾斜角: ' + data.tiltAngle.toFixed(1) + ' °', '风扇: ' + (data.fanStatus ? '开启' : '关闭'), '前门: ' + (data.frontLight ? '开启' : '关闭'), '后门: ' + (data.backLight ? '开启' : '关闭'), '故障: ' + (data.sensorFaults.length ? data.sensorFaults.join(',') : '无')].join('\\n'); return [{ payload: data.temperature, topic: 'temperature' }, { payload: data.humidity, topic: 'humidity' }, { payload: data.capacity, topic: 'capacity' }, { payload: data.airQuality, topic: 'airQuality' }, { payload: data.tiltAngle, topic: 'tiltAngle' }, { payload: status }, { topic: 'INSERT INTO telemetry (device_id,ts,temperature,humidity,capacity,air_quality,human_detect,fan_status,front_door,back_door,tilt_angle,sensor_faults,buzzer_mode,raw_json) VALUES ($p1,$p2,$p3,$p4,$p5,$p6,$p7,$p8,$p9,$p10,$p11,$p12,$p13,$p14)', payload: [data.deviceId, ts, data.temperature, data.humidity, data.capacity, data.airQuality, data.humanDetect ? 1 : 0, data.fanStatus ? 1 : 0, data.frontLight ? 1 : 0, data.backLight ? 1 : 0, data.tiltAngle, JSON.stringify(data.sensorFaults), data.buzzerMode, JSON.stringify(d)] }, { topic: 'INSERT INTO devices (device_id,device_name,online,last_seen,mqtt_online) VALUES ($p1,$p2,$p3,$p4,$p5) ON CONFLICT(device_id) DO UPDATE SET device_name=excluded.device_name,online=excluded.online,last_seen=excluded.last_seen,mqtt_online=excluded.mqtt_online', payload: [data.deviceId, '智能衣物回收箱', 1, ts, 1] }];",')

$text = $text.Replace(
'"id": "fn_refresh",
    "type": "function",
    "z": "tab_core",
    "name": "鍒锋柊鎽樿",
    "func": "const d=global.get('latestTelemetry')||{};const ts=d.lastSeen||0;const age=ts?Date.now()-ts:null;const online=age!==null&&age<15000;const status=['璁惧: '+(d.deviceId||'ESP32_BOX_001'),'鐘舵€? '+(online?'鍦ㄧ嚎':'绂荤嚎'),'鏈€鍚庢暟鎹? '+(ts?new Date(ts).toLocaleString('zh-CN',{hour12:false}):'鏃?'),'绂荤嚎鏃堕暱: '+(age===null?'鏈煡':Math.floor(age/1000)+' 绉?'),'椋庢墖: '+(d.fanStatus?'寮€鍚?:'鍏抽棴'),'鍓嶉棬: '+(d.frontLight?'寮€鍚?:'鍏抽棴'),'鍚庨棬: '+(d.backLight?'寮€鍚?:'鍏抽棴'),'鍛婅鎶戝埗: '+((global.get('alarmSuppressUntil')||0)>Date.now()?'寮€鍚?:'鍏抽棴')].join('\\n');return[{payload:status}];",',
'"id": "fn_refresh",
    "type": "function",
    "z": "tab_core",
    "name": "刷新摘要",
    "func": "const d = global.get('latestTelemetry') || {}; const ts = d.lastSeen || 0; const age = ts ? Date.now() - ts : null; const online = age !== null && age < 15000; const status = ['设备: ' + (d.deviceId || 'ESP32_BOX_001'), '状态: ' + (online ? '在线' : '离线'), '最后数据: ' + (ts ? new Date(ts).toLocaleString('zh-CN', { hour12: false }) : '无'), '离线时长: ' + (age === null ? '未知' : Math.floor(age / 1000) + ' 秒'), '风扇: ' + (d.fanStatus ? '开启' : '关闭'), '前门: ' + ((d.frontLight ?? d.frontDoor) ? '开启' : '关闭'), '后门: ' + ((d.backLight ?? d.backDoor) ? '开启' : '关闭'), '告警抑制: ' + ((global.get('alarmSuppressUntil') || 0) > Date.now() ? '开启' : '关闭')].join('\\n'); return [{ payload: status }];",')

$text = $text.Replace(
'"id": "fn_api_status",
    "type": "function",
    "z": "tab_api",
    "name": "鐘舵€丣SON",
    "func": "const d=global.get('latestTelemetry')||{deviceId:'ESP32_BOX_001',temperature:0,humidity:0,capacity:0,airQuality:0,humanDetect:false,fanStatus:false,frontLight:false,backLight:false,tiltAngle:0,sensorFaults:[],buzzerMode:'off',netMode:'STA',lastSeen:0,mqttOnline:false,mqttBrokerOnline:true};const age=d.lastSeen?Date.now()-d.lastSeen:null;msg.statusCode=200;msg.payload={code:200,msg:'ok',data:{...d,frontLight:(d.frontLight??d.frontDoor??d.front_door??false),backLight:(d.backLight??d.backDoor??d.back_door??false),online:age!==null&&age<15000,lastTelemetryAgeMs:age,mqttBrokerOnline:true}};return msg;",',
'"id": "fn_api_status",
    "type": "function",
    "z": "tab_api",
    "name": "状态JSON",
    "func": "const d = global.get('latestTelemetry') || { deviceId: 'ESP32_BOX_001', temperature: 0, humidity: 0, capacity: 0, airQuality: 0, humanDetect: false, fanStatus: false, frontLight: false, backLight: false, frontDoor: false, backDoor: false, tiltAngle: 0, sensorFaults: [], buzzerMode: 'off', netMode: 'STA', lastSeen: 0, mqttOnline: false, mqttBrokerOnline: true }; const age = d.lastSeen ? Date.now() - d.lastSeen : null; const front = Boolean(d.frontLight ?? d.frontDoor ?? d.front_door ?? false); const back = Boolean(d.backLight ?? d.backDoor ?? d.back_door ?? false); msg.statusCode = 200; msg.payload = { code: 200, msg: 'ok', data: { ...d, frontLight: front, frontDoor: front, backLight: back, backDoor: back, online: age !== null && age < 15000, lastTelemetryAgeMs: age, mqttBrokerOnline: true, systemState: d.systemState || (age !== null && age < 15000 ? 'STANDBY' : 'OFFLINE') } }; return msg;",')

$text = $text.Replace(
'"id": "fn_control",
    "type": "function",
    "z": "tab_api",
    "name": "鎺у埗涓嬪彂",
    "func": "const body=msg.payload||{};const latest=global.get('latestTelemetry')||{};const age=latest.lastSeen?Date.now()-latest.lastSeen:1e12;const action=body.action||body.command;const deviceId=body.deviceId||latest.deviceId||'ESP32_BOX_001';if(body.adminToken&&body.adminToken!=='admin_auth_secret01'){msg.statusCode=401;msg.payload={code:401,msg:'绠＄悊鍛楾oken閿欒'};return [null,null,msg];}if(!action){msg.statusCode=400;msg.payload={code:400,msg:'缂哄皯action'};return [null,null,msg];}if(age>15000){msg.statusCode=409;msg.payload={code:409,msg:'璁惧绂荤嚎锛屼笉鑳借繙绋嬫帶鍒剁‖浠?};return [null,{topic:'INSERT INTO commands (device_id,ts,action,status,source,raw_json) VALUES ($p1,$p2,$p3,$p4,$p5,$p6)',payload:[deviceId,Date.now(),action,'rejected','http',JSON.stringify(body)]},msg];}if(action==='ALARM_STOP'){global.set('alarmSuppressUntil',Date.now()+300000);}const cmd={deviceId,cmd:action,action,ts:Date.now()};msg.statusCode=200;msg.payload={code:200,msg:'ok',data:{sent:true,topic:'device/clothes_box/control',command:cmd}};return [{topic:'device/clothes_box/control',payload:JSON.stringify(cmd)},{topic:'INSERT INTO commands (device_id,ts,action,status,source,raw_json) VALUES ($p1,$p2,$p3,$p4,$p5,$p6)',payload:[deviceId,Date.now(),action,'sent','http',JSON.stringify(body)]},msg];",',
'"id": "fn_control",
    "type": "function",
    "z": "tab_api",
    "name": "控制下发",
    "func": "const body = msg.payload || {}; const latest = global.get('latestTelemetry') || {}; const age = latest.lastSeen ? Date.now() - latest.lastSeen : 1e12; const action = body.action || body.command; const deviceId = body.deviceId || latest.deviceId || 'ESP32_BOX_001'; if (body.adminToken && body.adminToken !== 'admin_auth_secret01') { msg.statusCode = 401; msg.payload = { code: 401, msg: '管理员Token错误' }; return [null, null, msg]; } if (!action) { msg.statusCode = 400; msg.payload = { code: 400, msg: '缺少action' }; return [null, null, msg]; } if (age > 15000) { msg.statusCode = 409; msg.payload = { code: 409, msg: '设备离线，不能远程控制硬件' }; return [null, { topic: 'INSERT INTO commands (device_id,ts,action,status,source,raw_json) VALUES ($p1,$p2,$p3,$p4,$p5,$p6)', payload: [deviceId, Date.now(), action, 'rejected', 'http', JSON.stringify(body)] }, msg]; } if (action === 'ALARM_STOP') { global.set('alarmSuppressUntil', Date.now() + 300000); } const cmd = { deviceId, cmd: action, action, ts: Date.now() }; msg.statusCode = 200; msg.payload = { code: 200, msg: 'ok', data: { sent: true, topic: 'device/clothes_box/control', command: cmd } }; return [{ topic: 'device/clothes_box/control', payload: JSON.stringify(cmd) }, { topic: 'INSERT INTO commands (device_id,ts,action,status,source,raw_json) VALUES ($p1,$p2,$p3,$p4,$p5,$p6)', payload: [deviceId, Date.now(), action, 'sent', 'http', JSON.stringify(body)] }, msg];",')

$text = $text.Replace('\"name\": \"鍒濆鍖栧缓琛?\"', '\"name\": \"初始化建表\"')
$text = $text.Replace('\"name\": \"娓呯悊鏃ф暟鎹?\"', '\"name\": \"清理旧数据\"')
$text = $text.Replace('\"name\": \"鍛婅杈撳叆\"', '\"name\": \"告警输入\"')
$text = $text.Replace('\"name\": \"鍛婅澶勭悊\"', '\"name\": \"告警处理\"')
$text = $text.Replace('\"name\": \"鍘嗗彶鎺ュ彛\"', '\"name\": \"历史接口\"')
$text = $text.Replace('\"name\": \"璁惧鎺ュ彛\"', '\"name\": \"设备接口\"')
$text = $text.Replace('\"name\": \"閰嶇疆鎺ュ彛\"', '\"name\": \"配置接口\"')
$text = $text.Replace('\"name\": \"鍛婅宸茶\"', '\"name\": \"告警已读\"')
$text = $text.Replace('\"name\": \"闈㈡澘鎺у埗\"', '\"name\": \"面板控制\"')
$text = $text.Replace('\"name\": \"閬ユ祴澶勭悊\"', '\"name\": \"遥测处理\"')
$text = $text.Replace('\"name\": \"鍒锋柊鎽樿\"', '\"name\": \"刷新摘要\"')
$text = $text.Replace('\"name\": \"鏈湴MQTT\"', '\"name\": \"本地MQTT\"')
$text = $text.Replace('\"label\": \"鏁版嵁閲囬泦\"', '\"label\": \"数据采集\"')
$text = $text.Replace('\"label\": \"鎺ュ彛鏈嶅姟\"', '\"label\": \"接口服务\"')
$text = $text.Replace('\"label\": \"浠〃鐩?,', '\"label\": \"仪表盘\",')

Set-Content -LiteralPath $path -Value $text -Encoding utf8
