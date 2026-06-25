import { HISTORY_LIMIT } from './constants'
import { request } from './request'

function resolveBackendBaseUrl(config) {
	const baseUrl = String(config.backendBaseUrl || '').trim().replace(/\/$/, '')
	if (!baseUrl) {
		return ''
	}
	return baseUrl.endsWith('/api/v1/box') ? baseUrl : `${baseUrl}/api/v1/box`
}

function resolveLocalBaseUrl(config) {
	return String(config.localApBaseUrl || '').trim().replace(/\/$/, '')
}

function validateControlResponse(payload = {}) {
	if (payload && typeof payload === 'object' && 'code' in payload) {
		if (Number(payload.code) === 200) {
			return { ok: true }
		}
		return {
			ok: false,
			errorMessage: payload.msg || '控制命令被拒绝'
		}
	}

	return { ok: true }
}

export function fetchBackendStatus(config) {
	return request({
		baseUrl: resolveBackendBaseUrl(config),
		url: '/status',
		data: { deviceId: config.deviceId }
	})
}

export function fetchBackendHistory(config) {
	return request({
		baseUrl: resolveBackendBaseUrl(config),
		url: '/history',
		data: { deviceId: config.deviceId, limit: HISTORY_LIMIT }
	})
}

export function fetchBackendAlerts(config) {
	return request({
		baseUrl: resolveBackendBaseUrl(config),
		url: '/alerts',
		data: { deviceId: config.deviceId }
	})
}

export function readBackendAlerts(config, id) {
	return request({
		baseUrl: resolveBackendBaseUrl(config),
		url: '/alerts/read',
		method: 'POST',
		data: {
			deviceId: config.deviceId,
			id
		},
		validateResponse: validateControlResponse
	})
}

export function fetchBackendCommands(config) {
	return request({
		baseUrl: resolveBackendBaseUrl(config),
		url: '/commands',
		data: { deviceId: config.deviceId }
	})
}

export function fetchBackendHealth(config) {
	return request({
		baseUrl: resolveBackendBaseUrl(config),
		url: '/health'
	})
}

export function sendBackendControl(config, action) {
	return request({
		baseUrl: resolveBackendBaseUrl(config),
		url: '/control',
		method: 'POST',
		data: {
			deviceId: config.deviceId,
			action,
			adminToken: config.adminToken
		},
		validateResponse: validateControlResponse
	})
}

export function fetchLocalStatus(config) {
	return request({
		baseUrl: resolveLocalBaseUrl(config),
		url: '/api/local/status'
	})
}

export function sendLocalControl(config, action) {
	const localBaseUrl = resolveLocalBaseUrl(config)
	if (action === 'FAN_ON' || action === 'FAN_OFF') {
		const fanState = action === 'FAN_ON'
		return request({
			baseUrl: localBaseUrl,
			url: '/api/local/fan',
			method: 'POST',
			data: {
				action: fanState ? 'ON' : 'OFF',
				cmd: fanState ? 'ON' : 'OFF',
				state: fanState
			},
			validateResponse: validateControlResponse
		})
	}

	return request({
		baseUrl: localBaseUrl,
		url: '/api/local/control',
		method: 'POST',
		data: {
			action,
			cmd: action,
			command: action
		},
		validateResponse: validateControlResponse
	})
}

export function unlockLocalBackDoor(config) {
	return request({
		baseUrl: resolveLocalBaseUrl(config),
		url: '/api/local/unlock',
		method: 'POST',
		data: {
			pwd: config.localUnlockPassword,
			password: config.localUnlockPassword,
			unlockPassword: config.localUnlockPassword
		},
		validateResponse: validateControlResponse
	})
}

export function switchLocalNetMode(config, targetMode) {
	return request({
		baseUrl: resolveLocalBaseUrl(config),
		url: '/api/local/switch_mode',
		method: 'POST',
		data: {
			targetMode,
			mode: targetMode,
			netMode: targetMode
		},
		validateResponse: validateControlResponse
	})
}
