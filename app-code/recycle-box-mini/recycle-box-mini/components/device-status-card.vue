<template>
	<view class="card panel">
		<view class="panel-header">
			<view>
				<view class="section-title">实时状态</view>
				<text class="subtext">最近刷新：{{ lastUpdatedText }}</text>
			</view>
			<view class="pill" :class="status.online ? 'success' : 'error'">{{ status.online ? '设备在线' : '设备离线' }}</view>
		</view>
		<view class="grid">
			<view v-for="item in items" :key="item.label" class="metric" :class="item.highlight">
				<text class="metric-label">{{ item.label }}</text>
				<text class="metric-value">{{ item.value }}</text>
			</view>
		</view>
	</view>
</template>

<script>
	import { formatConnectivity, formatHumanDetect, formatNetMode, formatStatus, formatTime } from '../utils/format'

	export default {
		name: 'DeviceStatusCard',
		props: {
			status: {
				type: Object,
				required: true
			},
			connectionState: {
				type: Object,
				required: true
			}
		},
		computed: {
			lastUpdatedText() {
				return formatTime(this.status.updatedAt)
			},
			items() {
				return [
					{ label: '设备编号', value: this.status.deviceId || 'ESP32_BOX_001' },
					{ label: '连接模式', value: this.connectionState.selectedModeText },
					{ label: '网络状态', value: formatConnectivity(this.connectionState.activeChannel), highlight: this.connectionState.activeChannel === 'none' ? 'danger' : '' },
					{ label: '网络模式', value: formatNetMode(this.status.netMode) },
					{ label: '系统状态', value: this.status.systemState || '--' },
					{ label: '温度', value: `${this.formatNumber(this.status.temperature, 1)} °C` },
					{ label: '湿度', value: `${this.formatNumber(this.status.humidity, 1)} %` },
					{ label: '空气质量', value: `${this.formatNumber(this.status.airQuality, 0)} %` },
					{ label: '容量', value: `${this.formatNumber(this.status.capacity, 1)} %`, highlight: Number(this.status.capacity) >= 90 ? 'warning' : '' },
					{ label: '倾角', value: `${this.formatNumber(this.status.tiltAngle, 1)} °`, highlight: Number(this.status.tiltAngle) >= 25 ? 'warning' : '' },
					{ label: '人体靠近', value: formatHumanDetect(this.status.humanDetect) },
					{ label: '倾斜告警', value: this.status.boxTiltAlert ? '告警中' : '正常', highlight: this.status.boxTiltAlert ? 'warning' : '' },
					{ label: '风扇', value: formatStatus(this.status.fanStatus) },
					{ label: '前门', value: formatStatus(this.status.frontDoor) },
					{ label: '后门', value: formatStatus(this.status.backDoor) }
				]
			}
		},
		methods: {
			formatNumber(value, digits) {
				const numberValue = Number(value)
				if (!Number.isFinite(numberValue)) {
					return digits > 0 ? (0).toFixed(digits) : '0'
				}
				return digits > 0 ? numberValue.toFixed(digits) : `${Math.round(numberValue)}`
			}
		}
	}
</script>

<style scoped>
	.panel {
		display: flex;
		flex-direction: column;
		gap: 20rpx;
	}

	.panel-header {
		display: flex;
		justify-content: space-between;
		gap: 20rpx;
		align-items: flex-start;
	}

	.subtext {
		font-size: 24rpx;
		color: #6f87a0;
	}

	.grid {
		display: grid;
		grid-template-columns: repeat(2, minmax(0, 1fr));
		gap: 18rpx;
	}

	.metric {
		padding: 20rpx;
		border-radius: 22rpx;
		background: #f5f8fc;
		display: flex;
		flex-direction: column;
		gap: 8rpx;
	}

	.metric-label {
		font-size: 24rpx;
		color: #66819d;
	}

	.metric-value {
		font-size: 30rpx;
		color: #16324d;
		font-weight: 600;
	}

	.metric.warning .metric-value {
		color: #d67719;
	}

	.metric.danger .metric-value {
		color: #d14b4b;
	}

	.pill {
		padding: 10rpx 18rpx;
		border-radius: 999rpx;
		font-size: 24rpx;
		font-weight: 600;
	}

	.success {
		background: rgba(44, 168, 108, 0.16);
		color: #1f8b58;
	}

	.error {
		background: rgba(209, 75, 75, 0.16);
		color: #c23d3d;
	}
</style>
