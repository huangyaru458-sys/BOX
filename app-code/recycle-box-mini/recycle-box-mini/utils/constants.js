export const STORAGE_KEY = 'recycle-box-mini-config'
export const DEMO_STATE_STORAGE_KEY = 'recycle-box-mini-demo-state'

export const MODES = {
	auto: 'auto',
	backend: 'backend',
	localAp: 'localAp'
}

export const CHANNELS = {
	none: 'none',
	backend: 'backend',
	localAp: 'localAp'
}

export const DEMO_SCENES = {
	normal: 'normal',
	full: 'full',
	tilt: 'tilt',
	offline: 'offline'
}

function getDefaultBackendBaseUrl() {
	// #ifdef H5
	if (
		typeof window !== 'undefined' &&
		window.location &&
		/^https?:$/.test(window.location.protocol) &&
		window.location.host
	) {
		return window.location.origin
	}
	// #endif
	return 'http://192.168.222.228:1880'
}

export const DEFAULT_CONFIG = {
	mode: MODES.auto,
	backendBaseUrl: getDefaultBackendBaseUrl(),
	localApBaseUrl: 'http://192.168.4.1',
	deviceId: 'ESP32_BOX_001',
	adminToken: '',
	localUnlockPassword: '123456',
	demoScenario: DEMO_SCENES.normal
}

export const POLL_INTERVAL = 5000
export const REQUEST_TIMEOUT = 4000
export const LOG_LIMIT = 10
export const HISTORY_LIMIT = 24
export const FULL_CAPACITY_THRESHOLD = 90
export const DEMO_MODE_ENABLED = false

export const CONTROL_ACTIONS = [
	{ key: 'OPEN_FRONT', label: '打开前门', type: 'danger' },
	{ key: 'CLOSE_FRONT', label: '关闭前门', type: 'neutral' },
	{ key: 'OPEN_BACK', label: '打开后门', type: 'primary' },
	{ key: 'CLOSE_BACK', label: '关闭后门', type: 'neutral' },
	{ key: 'FAN_ON', label: '开启风扇', type: 'primary' },
	{ key: 'FAN_OFF', label: '关闭风扇', type: 'neutral' },
	{ key: 'ALARM_STOP', label: '停止告警', type: 'warning' }
]

export const LOCAL_MODE_ACTIONS = [
	{ key: 'UNLOCK_LOCAL', label: '本地密码解锁', type: 'primary' },
	{ key: 'SWITCH_TO_AP', label: '切到 AP', type: 'neutral' },
	{ key: 'SWITCH_TO_STA', label: '切到 STA', type: 'neutral' }
]

export const ERROR_MESSAGES = {
	backendOffline: 'Node-RED 后端无法访问，自动尝试本地地址',
	backendMissing: '手机端不能使用 localhost，请填写电脑局域网 IP，例如 http://192.168.1.23:1880',
	localApOffline: '请检查本地地址是否可达；若使用 192.168.4.1，请先连接 ESP32 热点',
	hardwareOffline: 'ESP32 设备硬件离线，请检查设备上电与 WiFi',
	demoMode: '当前为演示模式：已跳过真实端口与接口检测，使用本地模拟数据打通 UI 与交互流程'
}
