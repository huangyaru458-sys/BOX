import { CHANNELS, DEMO_MODE_ENABLED, DEMO_SCENES, ERROR_MESSAGES, MODES } from './constants'
import {
	fetchBackendAlerts,
	fetchBackendCommands,
	fetchBackendHealth,
	fetchBackendHistory,
	fetchBackendStatus,
	readBackendAlerts,
	fetchLocalStatus,
	sendBackendControl,
	sendLocalControl,
	switchLocalNetMode,
	unlockLocalBackDoor
} from './api'
import { clearDemoState, loadDemoState, saveDemoState } from './storage'

let demoStateCache = null
const TILT_ALERT_THRESHOLD = 25

function normalizeBool(value) {
	if (typeof value === 'string') {
		return ['1', 'true', 'on', 'open', 'opened'].includes(value.toLowerCase())
	}
	return !!value
}

function pickValue(source, keys, fallback) {
	for (let index = 0; index < keys.length; index += 1) {
		const key = keys[index]
		if (source[key] !== undefined && source[key] !== null && source[key] !== '') {
			return source[key]
		}
	}
	return fallback
}

function normalizeStatus(payload = {}) {
	const status = payload.data || payload.status || payload
	const frontDoor = normalizeBool(pickValue(status, ['frontDoor', 'frontLight', 'front_door'], false))
	const backDoor = normalizeBool(pickValue(status, ['backDoor', 'backLight', 'back_door'], false))
	const tiltAngle = Number(pickValue(status, ['tiltAngle', 'tilt_angle'], 0))
	const faultText = Array.isArray(status.sensorFaults) ? status.sensorFaults.join(' ') : Array.isArray(status.sensor_faults) ? status.sensor_faults.join(' ') : ''
	return {
		online: status.online !== undefined ? normalizeBool(status.online) : normalizeBool(status.mqttOnline) || normalizeBool(status.mqttBrokerOnline),
		temperature: Number(pickValue(status, ['temperature', 'temp'], 0)),
		humidity: Number(pickValue(status, ['humidity', 'hum'], 0)),
		airQuality: Number(pickValue(status, ['airQuality', 'air_quality', 'mq135'], 0)),
		capacity: Number(pickValue(status, ['capacity', 'fullness'], 0)),
		humanDetect: normalizeBool(pickValue(status, ['humanDetect', 'human_detect', 'pir'], false)),
		boxTiltAlert: normalizeBool(pickValue(status, ['boxTiltAlert', 'box_tilt_alert'], false)) || tiltAngle >= TILT_ALERT_THRESHOLD || /tilt|倾斜/.test(faultText),
		fanStatus: normalizeBool(pickValue(status, ['fanStatus', 'fan_status'], false)),
		frontLight: frontDoor,
		backLight: backDoor,
		frontDoor,
		backDoor,
		tiltAngle,
		netMode: pickValue(status, ['netMode', 'net_mode', 'currentNetMode'], '--'),
		systemState: pickValue(status, ['systemState', 'system_state'], '--'),
		deviceId: status.deviceId || status.device_id || 'ESP32_BOX_001',
		sensorFaults: Array.isArray(status.sensorFaults) ? status.sensorFaults : (Array.isArray(status.sensor_faults) ? status.sensor_faults : []),
		buzzerMode: status.buzzerMode || status.buzzer_mode || 'off',
		mqttOnline: status.mqttOnline !== undefined ? normalizeBool(status.mqttOnline) : true,
		updatedAt: pickValue(status, ['updatedAt', 'updated_at', 'lastSeen', 'last_seen', 'timestamp'], Date.now())
	}
}

function normalizeHistoryPayload(payload = {}) {
	const source = payload.data || payload
	if (Array.isArray(source)) return source.map(normalizeStatusHistoryItem)
	if (Array.isArray(payload.records)) return payload.records.map(normalizeStatusHistoryItem)
	if (Array.isArray(source.timeline) && source.timeline.length) {
		const timeline = source.timeline
		return timeline.map((label, index) => normalizeStatusHistoryItem({
			timestamp: Date.now() - (timeline.length - index) * 5 * 60 * 1000,
			timeLabel: label,
			temperature: Array.isArray(source.tempData) ? source.tempData[index] : source.temperature,
			humidity: Array.isArray(source.humidityData) ? source.humidityData[index] : source.humidity,
			capacity: Array.isArray(source.capacityData) ? source.capacityData[index] : source.capacity,
			airQuality: Array.isArray(source.airData) ? source.airData[index] : source.airQuality,
			tiltAngle: Array.isArray(source.tiltData) ? source.tiltData[index] : source.tiltAngle
		}))
	}
	return []
}

function normalizeAlerts(payload = {}) {
	const list = Array.isArray(payload) ? payload : payload.data || payload.records || payload.alerts || []
	return Array.isArray(list) ? list.slice(0, 5) : []
}

function normalizeCommands(payload = {}) {
	const list = Array.isArray(payload) ? payload : payload.data || payload.records || payload.commands || []
	return Array.isArray(list) ? list.slice(0, 6) : []
}

function normalizeHealth(payload = {}) {
	const source = payload.data || payload
	const mqttOnline = source.mqttBrokerOnline !== undefined ? normalizeBool(source.mqttBrokerOnline) : normalizeBool(source.brokerOnline)
	return {
		ok: source.ok !== undefined ? normalizeBool(source.ok) : true,
		broker: mqttOnline ? 'MQTT 在线' : 'MQTT 离线',
		service: source.httpPort || source.mqttPort ? `HTTP ${source.httpPort || '--'} / MQTT ${source.mqttPort || '--'}` : source.serviceStatus || source.status || source.msg || '--',
		mqttOnline,
		updatedAt: source.updatedAt || Date.now()
	}
}

function normalizeStatusHistoryItem(item = {}) {
	return {
		timestamp: item.timestamp || item.ts || item.time || item.createdAt || Date.now(),
		timeLabel: item.timeLabel || item.timelineLabel || item.label || '',
		temperature: Number(item.temperature || 0),
		humidity: Number(item.humidity || 0),
		airQuality: Number(item.airQuality || item.air_quality || 0),
		capacity: Number(item.capacity || 0),
		tiltAngle: Number(item.tiltAngle || item.tilt_angle || 0)
	}
}

function createDemoHistory(scene) {
	const now = Date.now()
	return Array.from({ length: 12 }).map((_, index) => {
		const step = 11 - index
		let capacity = 48 + index * 3
		let temperature = 25 + (index % 4)
		let humidity = 55 + (index % 6) * 2
		if (scene === DEMO_SCENES.full) capacity = 82 + index
		if (scene === DEMO_SCENES.tilt) {
			temperature = 28 + (index % 3)
			humidity = 62 + (index % 4)
		}
		if (scene === DEMO_SCENES.offline) {
			capacity = 0
			temperature = 0
			humidity = 0
		}
		return {
			timestamp: now - step * 5 * 60 * 1000,
			temperature,
			humidity,
			capacity
		}
	})
}

function createDemoSnapshot(config) {
	const useLocalChannel = config.mode === MODES.localAp
	const scene = config.demoScenario || DEMO_SCENES.normal
	const baseStatus = {
		online: true,
		temperature: 27.3,
		humidity: 61.2,
		airQuality: 218,
		capacity: 72,
		humanDetect: false,
		boxTiltAlert: false,
		fanStatus: false,
		frontDoor: false,
		backDoor: false,
		netMode: useLocalChannel ? 'AP' : 'STA',
		updatedAt: Date.now()
	}
	const sceneMap = {
		[DEMO_SCENES.normal]: {
			status: baseStatus,
			alerts: [{ id: 'demo-alert-1', alertType: '容量预警', message: '演示数据：容量接近预警线，请及时关注箱体状态', timestamp: Date.now() - 10 * 60 * 1000 }]
		},
		[DEMO_SCENES.full]: {
			status: { ...baseStatus, capacity: 96, airQuality: 265, humanDetect: true },
			alerts: [{ id: 'demo-alert-full', alertType: '满载锁定', message: '演示数据：箱体满载，前门开启已被禁用', timestamp: Date.now() - 6 * 60 * 1000 }]
		},
		[DEMO_SCENES.tilt]: {
			status: { ...baseStatus, capacity: 78, boxTiltAlert: true, fanStatus: true, humanDetect: true, airQuality: 301 },
			alerts: [{ id: 'demo-alert-tilt', alertType: '倾斜告警', message: '演示数据：检测到箱体倾斜，前门开启已被禁用', timestamp: Date.now() - 2 * 60 * 1000 }]
		},
		[DEMO_SCENES.offline]: {
			status: { ...baseStatus, online: false, temperature: 0, humidity: 0, airQuality: 0, capacity: 0, humanDetect: false, boxTiltAlert: false, fanStatus: false },
			alerts: [{ id: 'demo-alert-offline', alertType: '设备离线', message: '演示数据：ESP32 设备硬件离线，请检查供电与 WiFi', timestamp: Date.now() - 1 * 60 * 1000 }]
		}
	}
	const currentScene = sceneMap[scene] || sceneMap[DEMO_SCENES.normal]
	return {
		ok: true,
		channel: useLocalChannel ? CHANNELS.localAp : CHANNELS.backend,
		status: currentScene.status,
		history: createDemoHistory(scene),
		alerts: currentScene.alerts,
		commands: [
			{ id: 'demo-command-1', action: 'OPEN_BACK', code: 200, message: '演示数据：后门打开成功', timestamp: Date.now() - 8 * 60 * 1000 },
			{ id: 'demo-command-2', action: scene === DEMO_SCENES.offline ? 'ALARM_STOP' : 'FAN_ON', code: 200, message: scene === DEMO_SCENES.offline ? '演示数据：离线场景已记录' : '演示数据：风扇已启动', timestamp: Date.now() - 3 * 60 * 1000 }
		],
		health: { ok: scene !== DEMO_SCENES.offline, broker: '演示模式', service: useLocalChannel ? '本地 AP 演示链路' : '后端演示链路', updatedAt: Date.now() },
		demoMode: true,
		demoScene: scene
	}
}

function cloneDemoSnapshot(snapshot) {
	return {
		...snapshot,
		status: { ...snapshot.status },
		history: Array.isArray(snapshot.history) ? snapshot.history.map((item) => ({ ...item })) : [],
		alerts: Array.isArray(snapshot.alerts) ? snapshot.alerts.map((item) => ({ ...item })) : [],
		commands: Array.isArray(snapshot.commands) ? snapshot.commands.map((item) => ({ ...item })) : [],
		health: { ...snapshot.health }
	}
}

function isValidDemoSnapshot(snapshot) {
	return !!(
		snapshot &&
		typeof snapshot === 'object' &&
		typeof snapshot.status === 'object' &&
		Array.isArray(snapshot.history) &&
		Array.isArray(snapshot.alerts) &&
		Array.isArray(snapshot.commands) &&
		typeof snapshot.health === 'object'
	)
}

function persistDemoState() {
	if (!demoStateCache) {
		return
	}
	saveDemoState(cloneDemoSnapshot(demoStateCache))
}

function normalizeDemoScene(scene) {
	return Object.prototype.hasOwnProperty.call(DEMO_SCENES, scene) ? scene : DEMO_SCENES.normal
}

function applyDemoRuntimeState(snapshot, config) {
	const nextSnapshot = cloneDemoSnapshot(snapshot)
	const useLocalChannel = config.mode === MODES.localAp
	nextSnapshot.demoScene = normalizeDemoScene(nextSnapshot.demoScene || config.demoScenario)
	nextSnapshot.channel = useLocalChannel ? CHANNELS.localAp : CHANNELS.backend
	nextSnapshot.status = {
		...nextSnapshot.status,
		netMode: useLocalChannel ? 'AP' : nextSnapshot.status.netMode === 'AP' ? 'STA' : nextSnapshot.status.netMode,
		updatedAt: Date.now()
	}
	nextSnapshot.health = {
		...nextSnapshot.health,
		service: useLocalChannel ? '本地 AP 演示链路' : '后端演示链路',
		updatedAt: Date.now()
	}
	return nextSnapshot
}

function restoreDemoSnapshot(config) {
	const scene = normalizeDemoScene(config.demoScenario)
	if (demoStateCache && demoStateCache.demoScene === scene) {
		return demoStateCache
	}

	const savedState = loadDemoState()
	if (isValidDemoSnapshot(savedState) && normalizeDemoScene(savedState.demoScene) === scene) {
		demoStateCache = savedState
		return demoStateCache
	}

	if (savedState && normalizeDemoScene(savedState.demoScene) !== scene) {
		clearDemoState()
	}

	demoStateCache = createDemoSnapshot({
		...config,
		demoScenario: scene
	})
	persistDemoState()
	return demoStateCache
}

function getDemoSnapshot(config) {
	demoStateCache = applyDemoRuntimeState(restoreDemoSnapshot(config), config)
	persistDemoState()
	return cloneDemoSnapshot(demoStateCache)
}

function appendDemoCommand(action, message) {
	if (!demoStateCache) return
	demoStateCache.commands = [
		{ id: `demo-command-${Date.now()}`, action, code: 200, message, timestamp: Date.now() },
		...demoStateCache.commands
	].slice(0, 6)
}

function applyDemoControl(action) {
	if (!demoStateCache) return
	const status = { ...demoStateCache.status }
	switch (action) {
		case 'OPEN_FRONT': status.frontDoor = true; break
		case 'CLOSE_FRONT': status.frontDoor = false; break
		case 'OPEN_BACK': status.backDoor = true; break
		case 'CLOSE_BACK': status.backDoor = false; break
		case 'FAN_ON': status.fanStatus = true; break
		case 'FAN_OFF': status.fanStatus = false; break
		case 'ALARM_STOP': status.boxTiltAlert = false; break
	}
	status.updatedAt = Date.now()
	demoStateCache.status = status
	appendDemoCommand(action, `演示模式：${action} 已处理`)
	persistDemoState()
}

function applyDemoLocalUnlock() {
	if (!demoStateCache) return
	demoStateCache.status = { ...demoStateCache.status, backDoor: true, updatedAt: Date.now() }
	appendDemoCommand('UNLOCK_LOCAL', '演示模式：本地密码解锁成功，后门已打开')
	persistDemoState()
}

function applyDemoModeSwitch(targetMode) {
	if (!demoStateCache) return
	demoStateCache.status = { ...demoStateCache.status, netMode: targetMode, updatedAt: Date.now() }
	appendDemoCommand(`SWITCH_TO_${targetMode}`, `演示模式：已切换到 ${targetMode} 模式`)
	persistDemoState()
}

async function queryBackend(config) {
	const statusResult = await fetchBackendStatus(config)
	if (!statusResult.ok) return { ok: false, channel: CHANNELS.backend, errorKey: 'backendOffline', message: ERROR_MESSAGES.backendOffline }
	const [historyResult, alertsResult, commandsResult, healthResult] = await Promise.all([
		fetchBackendHistory(config),
		fetchBackendAlerts(config),
		fetchBackendCommands(config),
		fetchBackendHealth(config)
	])
	return {
		ok: true,
		channel: CHANNELS.backend,
		status: normalizeStatus(statusResult.data),
		history: historyResult.ok ? normalizeHistoryPayload(historyResult.data) : [],
		alerts: alertsResult.ok ? normalizeAlerts(alertsResult.data) : [],
		commands: commandsResult.ok ? normalizeCommands(commandsResult.data) : [],
		health: healthResult.ok ? normalizeHealth(healthResult.data) : { ok: false, broker: '--', service: 'health unavailable', updatedAt: Date.now() }
	}
}

async function queryLocal(config) {
	const statusResult = await fetchLocalStatus(config)
	if (!statusResult.ok) return { ok: false, channel: CHANNELS.localAp, errorKey: 'localApOffline', message: ERROR_MESSAGES.localApOffline }
	return { ok: true, channel: CHANNELS.localAp, status: normalizeStatus(statusResult.data), history: [], alerts: [], commands: [], health: { ok: true, broker: '--', service: '本地直连模式', updatedAt: Date.now() } }
}

export async function resolveDeviceSnapshot(config) {
	if (DEMO_MODE_ENABLED) return getDemoSnapshot(config)
	if (config.mode === MODES.backend) return queryBackend(config)
	if (config.mode === MODES.localAp) return queryLocal(config)
	const backendResult = await queryBackend(config)
	if (backendResult.ok) return backendResult
	const localResult = await queryLocal(config)
	if (localResult.ok) return { ...localResult, fallbackFrom: CHANNELS.backend, fallbackMessage: ERROR_MESSAGES.backendOffline }
	return localResult
}

export function buildBannerState(snapshot) {
	if (snapshot.demoMode) return { type: 'info', message: ERROR_MESSAGES.demoMode }
	if (!snapshot.ok) return { type: snapshot.errorKey, message: snapshot.message }
	if (!snapshot.status.online) return { type: 'hardwareOffline', message: ERROR_MESSAGES.hardwareOffline }
	if (snapshot.fallbackMessage) return { type: 'backendOffline', message: snapshot.fallbackMessage }
	return { type: '', message: '' }
}

export async function sendControl(config, activeChannel, action) {
	if (DEMO_MODE_ENABLED) {
		getDemoSnapshot(config)
		applyDemoControl(action)
		return { ok: true, data: { code: 200, msg: `演示模式：${action} 已处理` } }
	}
	if (config.mode === MODES.localAp || activeChannel === CHANNELS.localAp) return sendLocalControl(config, action)
	return sendBackendControl(config, action)
}

export function sendLocalUnlock(config) {
	if (DEMO_MODE_ENABLED) {
		getDemoSnapshot(config)
		applyDemoLocalUnlock()
		return Promise.resolve({ ok: true, data: { code: 200, msg: '演示模式：本地密码解锁成功，后门已打开' } })
	}
	return unlockLocalBackDoor(config)
}

export function sendLocalModeSwitch(config, targetMode) {
	if (DEMO_MODE_ENABLED) {
		getDemoSnapshot(config)
		applyDemoModeSwitch(targetMode)
		return Promise.resolve({ ok: true, data: { code: 200, msg: `演示模式：已切换到 ${targetMode} 模式`, currentNetMode: targetMode } })
	}
	return switchLocalNetMode(config, targetMode)
}

export function readAlerts(config, id) {
	if (DEMO_MODE_ENABLED) {
		return Promise.resolve({ ok: true, data: { code: 200, msg: '演示模式：告警已读' } })
	}
	return readBackendAlerts(config, id)
}
