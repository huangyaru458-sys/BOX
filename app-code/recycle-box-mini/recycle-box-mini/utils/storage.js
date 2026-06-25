import { DEFAULT_CONFIG, DEMO_STATE_STORAGE_KEY, STORAGE_KEY } from './constants'

function normalizeBackendBaseUrl(value) {
	const baseUrl = String(value || '').trim().replace(/\/$/, '')
	if (!baseUrl) {
		return ''
	}

	// #ifdef APP-PLUS
	if (/^https?:\/\/(?:localhost|127(?:\.\d{1,3}){3}|0\.0\.0\.0)(?::\d+)?(?:\/|$)/i.test(baseUrl)) {
		return ''
	}
	// #endif

	return baseUrl
}

export function loadConfig() {
	const saved = uni.getStorageSync(STORAGE_KEY)
	if (!saved || typeof saved !== 'object') {
		return { ...DEFAULT_CONFIG }
	}

	const nextConfig = {
		...DEFAULT_CONFIG,
		...saved
	}

	nextConfig.backendBaseUrl = normalizeBackendBaseUrl(nextConfig.backendBaseUrl) || DEFAULT_CONFIG.backendBaseUrl
	nextConfig.localApBaseUrl = String(nextConfig.localApBaseUrl || '').trim().replace(/\/$/, '') || DEFAULT_CONFIG.localApBaseUrl

	return nextConfig
}

export function saveConfig(config) {
	const nextConfig = {
		...DEFAULT_CONFIG,
		...config
	}
	nextConfig.backendBaseUrl = normalizeBackendBaseUrl(nextConfig.backendBaseUrl) || DEFAULT_CONFIG.backendBaseUrl
	nextConfig.localApBaseUrl = String(nextConfig.localApBaseUrl || '').trim().replace(/\/$/, '') || DEFAULT_CONFIG.localApBaseUrl
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
