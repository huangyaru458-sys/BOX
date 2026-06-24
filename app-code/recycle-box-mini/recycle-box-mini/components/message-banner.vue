<template>
	<view v-if="message" class="banner" :class="typeClass">
		<text class="banner-title">异常提示</text>
		<text class="banner-text">{{ message }}</text>
	</view>
</template>

<script>
	export default {
		name: 'MessageBanner',
		props: {
			type: {
				type: String,
				default: ''
			},
			message: {
				type: String,
				default: ''
			}
		},
		computed: {
			typeClass() {
				return this.type || 'info'
			}
		}
	}
</script>

<style scoped>
	.banner {
		display: flex;
		flex-direction: column;
		gap: 8rpx;
		padding: 20rpx 24rpx;
		border-radius: 22rpx;
	}

	.banner-title {
		font-size: 24rpx;
		font-weight: 700;
	}

	.banner-text {
		font-size: 26rpx;
		line-height: 1.5;
	}

	.backendOffline,
	.localApOffline {
		background: #fff1d9;
		color: #a75a00;
	}

	.hardwareOffline {
		background: #ffe4e4;
		color: #bb3434;
	}

	.info {
		background: #e8f4ff;
		color: #275b8f;
	}
</style>
