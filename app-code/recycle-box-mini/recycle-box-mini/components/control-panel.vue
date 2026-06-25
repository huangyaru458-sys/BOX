<template>
	<view class="card panel">
		<view class="section-title">远程控制</view>
		<view v-if="blockReason" class="tip warning-text">{{ blockReason }}</view>
		<view class="actions">
			<button
				v-for="action in actions"
				:key="action.key"
				class="action-btn"
				:class="action.type"
				:disabled="loading || isDisabled(action.key)"
				@click="$emit('action', action.key)"
			>
				{{ action.label }}
			</button>
		</view>
		<view class="local-tools">
			<view class="tool-title">本地 AP 专属操作</view>
			<view class="tool-actions">
				<button
					v-for="action in localActions"
					:key="action.key"
					class="tool-btn"
					:class="action.type"
					:disabled="loading || !localAvailable"
					@click="$emit('local-action', action.key)"
				>
					{{ action.label }}
				</button>
			</view>
			<text class="tool-hint">本地直连通道可用时可操作</text>
		</view>
	</view>
</template>

<script>
	import { CONTROL_ACTIONS, LOCAL_MODE_ACTIONS } from '../utils/constants'

	export default {
		name: 'ControlPanel',
		props: {
			loading: {
				type: Boolean,
				default: false
			},
			blockReason: {
				type: String,
				default: ''
			},
			localAvailable: {
				type: Boolean,
				default: false
			}
		},
		data() {
			return {
				actions: CONTROL_ACTIONS,
				localActions: LOCAL_MODE_ACTIONS
			}
		},
		methods: {
			isDisabled(actionKey) {
				return actionKey === 'OPEN_FRONT' && !!this.blockReason
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

	.tip {
		font-size: 24rpx;
	}

	.actions,
	.tool-actions {
		display: grid;
		grid-template-columns: repeat(2, minmax(0, 1fr));
		gap: 16rpx;
	}

	.local-tools {
		padding-top: 10rpx;
		display: flex;
		flex-direction: column;
		gap: 14rpx;
	}

	.tool-title {
		font-size: 26rpx;
		font-weight: 600;
		color: #17324d;
	}

	.tool-hint {
		font-size: 22rpx;
		color: #6e87a0;
	}

	.action-btn,
	.tool-btn {
		margin: 0;
		border: none;
		border-radius: 24rpx;
		font-size: 28rpx;
		font-weight: 600;
	}

	.action-btn::after,
	.tool-btn::after {
		border: none;
	}

	.primary {
		background: #0e7a61;
		color: #fff;
	}

	.neutral {
		background: #dbe7f3;
		color: #17324d;
	}

	.warning {
		background: #f0ad4e;
		color: #fff;
	}

	.danger {
		background: #cf5c42;
		color: #fff;
	}
</style>
