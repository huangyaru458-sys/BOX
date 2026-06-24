import { DEFAULT_CONFIG, DEMO_STATE_STORAGE_KEY, STORAGE_KEY } from './constants'

export function loadConfig() {
	const saved = uni.getStorageSync(STORAGE_KEY)
	if (!saved || typeof saved !== 'object') {
		return { ...DEFAULT_CONFIG }
	}

	return {
		...DEFAULT_CONFIG,
		...saved
	}
}

export function saveConfig(config) {
	const nextConfig = {
		...DEFAULT_CONFIG,
		...config
	}
	uni.setStorageSync(STORAGE_KEY, nextConfig)
	return nextConfig
}

export function loadDemoState() {
	try {
		const saved = uni.getStorageSync(DEMO_STATE_STORAGE_KEY)
		if (!saved || typeof saved !== 'object' || typeof saved.status !== 'object') {
			return null
		}
		return saved
	} catch (error) {
		console.warn('loadDemoState failed', error)
		return null
	}
}

export function saveDemoState(snapshot) {
	try {
		uni.setStorageSync(DEMO_STATE_STORAGE_KEY, snapshot)
		return true
	} catch (error) {
		console.warn('saveDemoState failed', error)
		return false
	}
}

export function clearDemoState() {
	try {
		uni.removeStorageSync(DEMO_STATE_STORAGE_KEY)
	} catch (error) {
		console.warn('clearDemoState failed', error)
	}
}
