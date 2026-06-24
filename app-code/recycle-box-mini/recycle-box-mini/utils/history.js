import { HISTORY_LIMIT } from './constants'

function normalizeNumber(value, fallback = 0) {
	const numberValue = Number(value)
	return Number.isFinite(numberValue) ? numberValue : fallback
}

export function normalizeHistoryItem(item = {}) {
	return {
		timestamp: item.timestamp || item.time || item.createdAt || Date.now(),
		temperature: normalizeNumber(item.temperature || item.temp),
		humidity: normalizeNumber(item.humidity || item.hum),
		capacity: normalizeNumber(item.capacity || item.fullness),
		airQuality: normalizeNumber(item.airQuality || item.air_quality),
		tiltAngle: normalizeNumber(item.tiltAngle || item.tilt_angle)
	}
}

export function trimHistory(items = []) {
	return items.slice(-HISTORY_LIMIT)
}

export function mergeHistory(history = [], incoming = []) {
	if (!Array.isArray(incoming) || !incoming.length) {
		return trimHistory(history)
	}

	const normalized = incoming.map(normalizeHistoryItem)
	return trimHistory(normalized)
}

export function appendHistoryPoint(history = [], status = {}) {
	const next = history.concat({
		timestamp: status.updatedAt || Date.now(),
		temperature: normalizeNumber(status.temperature || status.temp),
		humidity: normalizeNumber(status.humidity || status.hum),
		capacity: normalizeNumber(status.capacity || status.fullness),
		airQuality: normalizeNumber(status.airQuality),
		tiltAngle: normalizeNumber(status.tiltAngle)
	})

	return trimHistory(next)
}
