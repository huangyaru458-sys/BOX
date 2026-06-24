export function formatTime(value) {
	if (!value) {
		return '--'
	}

	const date = new Date(value)
	if (Number.isNaN(date.getTime())) {
		return '--'
	}

	const pad = (num) => `${num}`.padStart(2, '0')
	return `${pad(date.getHours())}:${pad(date.getMinutes())}:${pad(date.getSeconds())}`
}

export function formatDateTime(value) {
	if (!value) {
		return '--'
	}

	const date = new Date(value)
	if (Number.isNaN(date.getTime())) {
		return '--'
	}

	const pad = (num) => `${num}`.padStart(2, '0')
	return `${date.getFullYear()}-${pad(date.getMonth() + 1)}-${pad(date.getDate())} ${pad(date.getHours())}:${pad(date.getMinutes())}:${pad(date.getSeconds())}`
}

export function formatStatus(value, truthy = '开启', falsy = '关闭') {
	return value ? truthy : falsy
}

export function formatHumanDetect(value) {
	return value ? '检测到' : '未检测到'
}

export function formatConnectivity(channel) {
	if (channel === 'backend') {
		return '后端在线'
	}
	if (channel === 'localAp') {
		return '本地热点在线'
	}
	return '未连接'
}

export function formatNetMode(value) {
	if (!value) {
		return '--'
	}

	const mode = String(value).toUpperCase()
	if (mode === 'STA') {
		return 'STA 组网'
	}
	if (mode === 'AP') {
		return 'AP 热点'
	}
	if (mode === 'STA+AP') {
		return 'STA + AP'
	}
	return String(value)
}
