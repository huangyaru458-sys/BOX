<template>
	<view class="card panel">
		<view class="panel-header">
			<view class="section-title">控制记录</view>
			<text class="count">{{ commands.length }} 条</text>
		</view>
		<view v-if="!commands.length" class="empty">当前没有后端控制记录</view>
		<view v-for="(item, index) in commands" :key="item.id || item.timestamp || index" class="row">
			<view class="row-head">
				<text class="row-title">{{ item.action || item.cmd || item.command || '未知指令' }}</text>
				<text class="row-status" :class="resolveStatusClass(item)">{{ resolveStatusText(item) }}</text>
			</view>
			<text class="row-time">{{ formatLineTime(item.timestamp || item.time || item.createdAt) }}</text>
			<text class="row-desc">{{ item.msg || item.message || item.result || '暂无结果说明' }}</text>
		</view>
	</view>
</template>

<script>
	import { formatDateTime } from '../utils/format'

	export default {
		name: 'CommandsPanel',
		props: {
			commands: {
				type: Array,
				default: () => []
			}
		},
		methods: {
			formatLineTime(value) {
				return formatDateTime(value)
			},
			resolveStatusText(item) {
				if (item.success === true || Number(item.code) === 200) {
					return '成功'
				}
				if (item.success === false || (item.code && Number(item.code) !== 200)) {
					return '失败'
				}
				return '已记录'
			},
			resolveStatusClass(item) {
				if (item.success === true || Number(item.code) === 200) {
					return 'success'
				}
				if (item.success === false || (item.code && Number(item.code) !== 200)) {
					return 'danger'
				}
				return 'neutral'
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

	.panel-header,
	.row-head {
		display: flex;
		justify-content: space-between;
		align-items: center;
		gap: 16rpx;
	}

	.count,
	.empty,
	.row-time,
	.row-desc {
		font-size: 24rpx;
		color: #6d85a0;
		line-height: 1.5;
	}

	.row {
		display: flex;
		flex-direction: column;
		gap: 8rpx;
		padding: 18rpx;
		border-radius: 20rpx;
		background: #f5f8fc;
	}

	.row-title {
		font-size: 28rpx;
		font-weight: 600;
		color: #17324d;
	}

	.row-status {
		font-size: 22rpx;
		font-weight: 600;
	}

	.success {
		color: #1f8b58;
	}

	.danger {
		color: #c23d3d;
	}

	.neutral {
		color: #6d85a0;
	}
</style>
