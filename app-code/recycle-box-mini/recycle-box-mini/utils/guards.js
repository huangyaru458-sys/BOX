import { FULL_CAPACITY_THRESHOLD } from './constants'

export function isFrontDoorBlocked(status) {
	return Number(status.capacity) >= FULL_CAPACITY_THRESHOLD || !!status.boxTiltAlert
}

export function getFrontDoorBlockReason(status) {
	if (Number(status.capacity) >= FULL_CAPACITY_THRESHOLD) {
		return '箱体满载，禁止打开前门'
	}

	if (status.boxTiltAlert) {
		return '箱体倾斜告警，禁止打开前门'
	}

	return ''
}
