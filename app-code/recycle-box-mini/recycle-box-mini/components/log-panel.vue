<template>
	<view class="card panel">
		<view class="section-title">操作日志</view>
		<view v-if="!logs.length" class="empty">暂无操作记录</view>
		<view v-for="item in logs" :key="item.id" class="log-item">
			<view class="log-head">
				<text class="log-time">{{ item.time }}</text>
				<text :class="item.success ? 'success-text' : 'danger-text'">{{ item.success ? '成功' : '失败' }}</text>
			</view>
			<text class="log-message">{{ item.message }}</text>
		</view>
	</view>
</template>

<script>
	export default {
		name: 'LogPanel',
		props: {
			logs: {
				type: Array,
				default: () => []
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

	.empty {
		font-size: 26rpx;
		color: #7e93a8;
	}

	.log-item {
		padding: 18rpx 20rpx;
		border-radius: 18rpx;
		background: #f6f9fc;
		display: flex;
		flex-direction: column;
		gap: 10rpx;
	}

	.log-head {
		display: flex;
		justify-content: space-between;
		gap: 20rpx;
	}

	.log-time {
		font-size: 24rpx;
		color: #67809a;
	}

	.log-message {
		font-size: 26rpx;
		color: #183450;
		line-height: 1.5;
	}
</style>
