<template>
	<view class="card panel">
		<view class="panel-header">
			<view class="section-title">后端健康状态</view>
			<view class="status-pill" :class="health.ok ? 'success' : 'warning'">{{ health.ok ? '正常' : '待检查' }}</view>
		</view>
		<view class="health-grid">
			<view class="health-item">
				<text class="item-label">服务状态</text>
				<text class="item-value">{{ health.service || '--' }}</text>
			</view>
			<view class="health-item">
				<text class="item-label">Broker</text>
				<text class="item-value">{{ health.broker || '--' }}</text>
			</view>
			<view class="health-item full">
				<text class="item-label">最近检查</text>
				<text class="item-value">{{ checkedAt }}</text>
			</view>
		</view>
	</view>
</template>

<script>
	import { formatTime } from '../utils/format'

	export default {
		name: 'HealthPanel',
		props: {
			health: {
				type: Object,
				default: () => ({ ok: false, broker: '--', service: '--', updatedAt: 0 })
			}
		},
		computed: {
			checkedAt() {
				return formatTime(this.health.updatedAt)
			}
		}
	}
</script>

<style scoped>
	.panel {
		display: flex;
		flex-direction: column;
		gap: 18rpx;
	}

	.panel-header {
		display: flex;
		justify-content: space-between;
		align-items: center;
		gap: 20rpx;
	}

	.status-pill {
		padding: 8rpx 18rpx;
		border-radius: 999rpx;
		font-size: 24rpx;
		font-weight: 600;
	}

	.success {
		background: rgba(44, 168, 108, 0.16);
		color: #1f8b58;
	}

	.warning {
		background: rgba(240, 173, 78, 0.18);
		color: #a96818;
	}

	.health-grid {
		display: grid;
		grid-template-columns: repeat(2, minmax(0, 1fr));
		gap: 16rpx;
	}

	.health-item {
		padding: 18rpx;
		border-radius: 20rpx;
		background: #f5f8fc;
		display: flex;
		flex-direction: column;
		gap: 8rpx;
	}

	.full {
		grid-column: 1 / -1;
	}

	.item-label {
		font-size: 24rpx;
		color: #66819d;
	}

	.item-value {
		font-size: 28rpx;
		font-weight: 600;
		color: #17324d;
	}
</style>
