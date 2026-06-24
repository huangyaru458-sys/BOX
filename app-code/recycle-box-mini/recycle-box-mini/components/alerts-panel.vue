<template>
	<view class="card panel">
		<view class="panel-header">
			<view class="section-title">告警列表</view>
			<view class="header-actions">
				<text class="count">{{ unreadCount }}/{{ alerts.length }} 条</text>
				<button
					v-if="alerts.length"
					class="read-btn"
					:class="readLoading ? 'is-disabled' : ''"
					:disabled="readLoading"
					@click="$emit('read-all')"
				>
					{{ readLoading ? '处理中' : '全部已读' }}
				</button>
			</view>
		</view>
		<view v-if="!alerts.length" class="empty">当前没有后端告警记录</view>
		<view v-for="(item, index) in alerts" :key="item.id || item.timestamp || index" class="row danger-row">
			<text class="row-title">{{ item.title || item.type || item.alertType || '告警事件' }}</text>
			<text class="row-time">{{ formatLineTime(item.timestamp || item.time || item.createdAt) }}</text>
			<text class="row-desc">{{ item.msg || item.message || item.detail || '暂无描述' }}</text>
			<text class="row-flag">{{ item.is_ack ? '已读' : '未读' }}</text>
		</view>
	</view>
</template>

<script>
	import { formatDateTime } from '../utils/format'

	export default {
		name: 'AlertsPanel',
		props: {
			alerts: {
				type: Array,
				default: () => []
			},
			readLoading: {
				type: Boolean,
				default: false
			}
		},
		computed: {
			unreadCount() {
				return this.alerts.filter((item) => !item.is_ack).length
			}
		},
		methods: {
			formatLineTime(value) {
				return formatDateTime(value)
			}
		}
	}
</script>

<style scoped>
	.panel {
		display: flex;
		flex-direction: column;
		gap: 16rpx;
	}

	.panel-header {
		display: flex;
		justify-content: space-between;
		align-items: center;
		gap: 16rpx;
	}

	.header-actions {
		display: flex;
		align-items: center;
		gap: 12rpx;
	}

	.count,
	.empty {
		font-size: 24rpx;
		color: #6d85a0;
	}

	.row {
		display: flex;
		flex-direction: column;
		gap: 8rpx;
		padding: 18rpx;
		border-radius: 20rpx;
	}

	.danger-row {
		background: #fff1f1;
	}

	.row-title {
		font-size: 28rpx;
		font-weight: 600;
		color: #ad3636;
	}

	.row-time,
	.row-desc {
		font-size: 24rpx;
		color: #6a7f96;
		line-height: 1.5;
	}

	.row-flag {
		font-size: 22rpx;
		color: #ad3636;
	}

	.read-btn {
		margin: 0;
		padding: 0 18rpx;
		border: none;
		border-radius: 18rpx;
		background: #f0f5fb;
		color: #17324d;
		font-size: 22rpx;
		line-height: 52rpx;
	}

	.read-btn::after {
		border: none;
	}

	.read-btn.is-disabled {
		opacity: 0.55;
	}
</style>
