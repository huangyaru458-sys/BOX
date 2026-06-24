export function createPoller(task, interval) {
	let timer = null
	let running = false

	const execute = async () => {
		if (running) {
			return
		}

		running = true
		try {
			await task()
		} finally {
			running = false
		}
	}

	return {
		async start() {
			await execute()
			if (timer) {
				clearInterval(timer)
			}
			timer = setInterval(execute, interval)
		},
		stop() {
			if (timer) {
				clearInterval(timer)
				timer = null
			}
		}
	}
}
