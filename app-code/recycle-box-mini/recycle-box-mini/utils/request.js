import { REQUEST_TIMEOUT } from './constants'

function buildQuery(params = {}) {
	const entries = Object.keys(params)
		.filter((key) => params[key] !== '' && params[key] !== undefined && params[key] !== null)
		.map((key) => `${encodeURIComponent(key)}=${encodeURIComponent(params[key])}`)

	return entries.length ? `?${entries.join('&')}` : ''
}

export function request({
	baseUrl,
	url,
	method = 'GET',
	data = {},
	timeout = REQUEST_TIMEOUT,
	validateResponse
}) {
	const requestMethod = String(method || 'GET').toUpperCase()

	if (!baseUrl) {
		return Promise.resolve({
			ok: false,
			errorType: 'config',
			errorMessage: '后端地址未配置'
		})
	}

	const fullUrl = `${baseUrl}${url}${requestMethod === 'GET' ? buildQuery(data) : ''}`

	return new Promise((resolve) => {
		uni.request({
			url: fullUrl,
			method: requestMethod,
			data: requestMethod === 'GET' ? undefined : data,
			header: requestMethod === 'GET' ? {} : { 'content-type': 'application/json' },
			dataType: 'json',
			timeout,
			success: (response) => {
				const { statusCode, data: responseData } = response
				if (statusCode < 200 || statusCode >= 300) {
					resolve({
						ok: false,
						errorType: 'http',
						errorMessage: `HTTP ${statusCode}`,
						statusCode,
						data: responseData
					})
					return
				}

				if (typeof validateResponse === 'function') {
					const validation = validateResponse(responseData)
					if (validation && validation.ok === false) {
						resolve({
							ok: false,
							errorType: validation.errorType || 'business',
							errorMessage: validation.errorMessage || 'business error',
							statusCode,
							data: responseData
						})
						return
					}
				}

				resolve({ ok: true, data: responseData, statusCode })
			},
			fail: (error) => {
				resolve({
					ok: false,
					errorType: 'network',
					errorMessage: error && error.errMsg ? error.errMsg : 'network error'
				})
			}
		})
	})
}
