<template>
	<view class="panel card">
		<view class="section-title">连接配置</view>
		<picker class="picker" :range="modeOptions" range-key="label" :value="modeIndex" @change="handleModeChange">
			<view class="picker-value">连接模式：{{ currentModeLabel }}</view>
		</picker>
		<picker v-if="showDemoScenePicker" class="picker" :range="demoSceneOptions" range-key="label" :value="demoSceneIndex" @change="handleDemoSceneChange">
			<view class="picker-value">演示场景：{{ currentDemoSceneLabel }}</view>
		</picker>
		<view v-if="showDemoScenePicker" class="hint">可切换正常运行、满载禁开、倾斜告警、设备离线四种答辩演示场景。</view>
		<view class="field">
			<text class="label">后端地址</text>
			<input class="input" :value="config.backendBaseUrl" placeholder="http://localhost:1880" @input="emitField('backendBaseUrl', $event.detail.value)" />
		</view>
		<view class="field">
			<text class="label">本地地址</text>
			<input class="input" :value="config.localApBaseUrl" placeholder="http://192.168.4.1 或 STA 局域网 IP" @input="emitField('localApBaseUrl', $event.detail.value)" />
			<text class="hint">可填写 ESP32 AP 地址 `192.168.4.1`，也可填写 STA 模式下的局域网 IP。</text>
		</view>
		<view class="field">
			<text class="label">设备 ID</text>
			<input class="input" :value="config.deviceId" placeholder="ESP32_BOX_001" @input="emitField('deviceId', $event.detail.value)" />
		</view>
		<view class="field">
			<text class="label">管理员令牌</text>
			<input class="input" password :value="config.adminToken" placeholder="请输入管理员 token" @input="emitField('adminToken', $event.detail.value)" />
		</view>
		<view class="field">
			<text class="label">本地解锁密码</text>
			<input class="input" password :value="config.localUnlockPassword" placeholder="请输入本地解锁密码" @input="emitField('localUnlockPassword', $event.detail.value)" />
		</view>
	</view>
</template>

<script>
	import { DEMO_MODE_ENABLED, DEMO_SCENES, MODES } from '../utils/constants'

	export default {
		name: 'ConnectionPanel',
		props: {
			config: {
				type: Object,
				required: true
			}
		},
		data() {
			return {
				modeOptions: [
					{ label: '自动模式', value: MODES.auto },
					{ label: '后端模式', value: MODES.backend },
					{ label: '本地 AP 模式', value: MODES.localAp }
				],
				demoSceneOptions: [
					{ label: '正常运行', value: DEMO_SCENES.normal },
					{ label: '满载禁开', value: DEMO_SCENES.full },
					{ label: '倾斜告警', value: DEMO_SCENES.tilt },
					{ label: '设备离线', value: DEMO_SCENES.offline }
				]
			}
		},
		computed: {
			showDemoScenePicker() {
				return DEMO_MODE_ENABLED
			},
			modeIndex() {
				const index = this.modeOptions.findIndex((item) => item.value === this.config.mode)
				return index === -1 ? 0 : index
			},
			currentModeLabel() {
				const current = this.modeOptions[this.modeIndex]
				return current ? current.label : '自动模式'
			},
			demoSceneIndex() {
				const index = this.demoSceneOptions.findIndex((item) => item.value === this.config.demoScenario)
				return index === -1 ? 0 : index
			},
			currentDemoSceneLabel() {
				const current = this.demoSceneOptions[this.demoSceneIndex]
				return current ? current.label : '正常运行'
			}
		},
		methods: {
			handleModeChange(event) {
				const next = this.modeOptions[Number(event.detail.value)]
				this.emitField('mode', next.value)
			},
			handleDemoSceneChange(event) {
				const next = this.demoSceneOptions[Number(event.detail.value)]
				this.emitField('demoScenario', next.value)
			},
			emitField(field, value) {
				this.$emit('update:config', {
					...this.config,
					[field]: value
				})
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

	.picker,
	.field {
		display: flex;
		flex-direction: column;
		gap: 10rpx;
	}

	.picker-value,
	.input {
		min-height: 80rpx;
		padding: 0 24rpx;
		border-radius: 24rpx;
		background: #f4f7fb;
		font-size: 28rpx;
		color: #17324d;
		line-height: 80rpx;
	}

	.label {
		font-size: 24rpx;
		color: #53718f;
	}

	.hint {
		font-size: 22rpx;
		line-height: 1.5;
		color: #6c86a1;
	}
</style>
