<template>
	<scroll-view class="page" scroll-y>
		<view class="hero">
			<text class="hero-kicker">Recycle Box Mobile Ops</text>
			<text class="hero-title">回收箱运维终端</text>
			<text class="hero-desc">手机端补齐 Web 运维能力，支持后端联调与现场热点应急控制。</text>
		</view>

		<connection-panel :config="config" @update:config="handleConfigChange" />
		<message-banner :type="banner.type" :message="banner.message" />
		<health-panel :health="backendHealth" />
		<device-status-card :status="deviceStatus" :connection-state="connectionSummary" />
		<control-panel
			:loading="controlLoading"
			:block-reason="frontDoorBlockReason"
			:local-available="isLocalChannelActive"
			@action="handleControl"
			@local-action="handleLocalAction"
		/>
		<alerts-panel :alerts="alertsList" :read-loading="alertsReadLoading" @read-all="handleReadAlerts" />
		<commands-panel :commands="commandsList" />
		<history-chart :history="historyData" />
		<log-panel :logs="operationLogs" />
	</scroll-view>
</template>

<script>
	import AlertsPanel from '../../components/alerts-panel.vue'
	import CommandsPanel from '../../components/commands-panel.vue'
	import ConnectionPanel from '../../components/connection-panel.vue'
	import ControlPanel from '../../components/control-panel.vue'
	import DeviceStatusCard from '../../components/device-status-card.vue'
	import HealthPanel from '../../components/health-panel.vue'
	import HistoryChart from '../../components/history-chart.vue'
	import LogPanel from '../../components/log-panel.vue'
	import MessageBanner from '../../components/message-banner.vue'
	import { CHANNELS, CONTROL_ACTIONS, DEFAULT_CONFIG, LOCAL_MODE_ACTIONS, LOG_LIMIT, MODES, POLL_INTERVAL } from '../../utils/constants'
	import { buildBannerState, readAlerts, resolveDeviceSnapshot, sendControl, sendLocalModeSwitch, sendLocalUnlock } from '../../utils/connection'
	import { formatDateTime } from '../../utils/format'
	import { getFrontDoorBlockReason, isFrontDoorBlocked } from '../../utils/guards'
	import { appendHistoryPoint, mergeHistory } from '../../utils/history'
	import { createPoller } from '../../utils/polling'
	import { loadConfig, saveConfig } from '../../utils/storage'

	export default {
		components: {
			AlertsPanel,
			CommandsPanel,
			ConnectionPanel,
			ControlPanel,
			DeviceStatusCard,
			HealthPanel,
			HistoryChart,
			LogPanel,
			MessageBanner
		},
		data() {
			return {
				config: { ...DEFAULT_CONFIG },
				deviceStatus: {
					online: false,
					temperature: 0,
					humidity: 0,
					airQuality: 0,
					capacity: 0,
					tiltAngle: 0,
					humanDetect: false,
					boxTiltAlert: false,
					fanStatus: false,
					frontDoor: false,
					backDoor: false,
					deviceId: 'ESP32_BOX_001',
					staIp: '',
					apIp: '',
					netMode: '--',
					systemState: '--',
					updatedAt: 0
				},
				historyData: [],
				alertsList: [],
				commandsList: [],
				backendHealth: {
					ok: false,
					broker: '--',
					service: '--',
					updatedAt: 0
				},
				operationLogs: [],
				connectionState: {
					selectedMode: MODES.auto,
					activeChannel: CHANNELS.none,
					lastError: ''
				},
				banner: {
					type: '',
					message: ''
				},
				controlLoading: false,
				alertsReadLoading: false,
				poller: null
			}
		},
		computed: {
			connectionSummary() {
				const modeTextMap = {
					[MODES.auto]: '自动模式',
					[MODES.backend]: '后端模式',
					[MODES.localAp]: '本地 AP 模式'
				}
				return {
					selectedMode: this.connectionState.selectedMode,
					selectedModeText: modeTextMap[this.connectionState.selectedMode] || '自动模式',
					activeChannel: this.connectionState.activeChannel
				}
			},
			frontDoorBlockReason() {
				return getFrontDoorBlockReason(this.deviceStatus)
			},
			actionLabelMap() {
				const allActions = CONTROL_ACTIONS.concat(LOCAL_MODE_ACTIONS)
				return allActions.reduce((result, item) => {
					result[item.key] = item.label
					return result
				}, {})
			},
			isLocalChannelActive() {
				return this.connectionState.activeChannel === CHANNELS.localAp || this.config.mode === MODES.localAp || !!this.deviceStatus.staIp
			}
		},
		watch: {
			config: {
				deep: true,
				handler(nextValue) {
					this.connectionState.selectedMode = nextValue.mode
					saveConfig(nextValue)
					if (this.poller) {
						this.poller.start()
					}
				}
			}
		},
		onLoad() {
			this.config = loadConfig()
			this.connectionState.selectedMode = this.config.mode
			this.poller = createPoller(this.refreshSnapshot, POLL_INTERVAL)
		},
		onShow() {
			if (this.poller) {
				this.poller.start()
			}
		},
		onHide() {
			if (this.poller) {
				this.poller.stop()
			}
		},
		onUnload() {
			if (this.poller) {
				this.poller.stop()
			}
		},
		methods: {
			handleConfigChange(nextConfig) {
				this.config = {
					...this.config,
					...nextConfig
				}
			},
			async refreshSnapshot() {
				const snapshot = await resolveDeviceSnapshot(this.config)
				this.banner = buildBannerState(snapshot)
				if (!snapshot.ok) {
					this.connectionState.activeChannel = CHANNELS.none
					this.connectionState.lastError = this.banner.message
					this.backendHealth = {
						ok: false,
						broker: '--',
						service: '不可用',
						updatedAt: Date.now()
					}
					return
				}

				this.deviceStatus = snapshot.status
				if (snapshot.status && snapshot.status.staIp) {
					const learnedBaseUrl = `http://${snapshot.status.staIp}`
					if (this.config.localApBaseUrl !== learnedBaseUrl) {
						this.config = {
							...this.config,
							localApBaseUrl: learnedBaseUrl
						}
					}
				}
				this.connectionState.activeChannel = snapshot.channel
				this.connectionState.lastError = ''
				this.historyData = snapshot.history.length ? mergeHistory(this.historyData, snapshot.history) : appendHistoryPoint(this.historyData, snapshot.status)
				this.alertsList = snapshot.alerts || []
				this.commandsList = snapshot.commands || []
				this.backendHealth = snapshot.health || this.backendHealth
			},
			pushLog(action, success, message) {
				const label = this.actionLabelMap[action] || action
				this.operationLogs = [
					{
						id: `${Date.now()}-${Math.random().toString(16).slice(2, 6)}`,
						time: formatDateTime(Date.now()),
						success,
						message: `${label}：${message}`
					},
					...this.operationLogs
				].slice(0, LOG_LIMIT)
			},
			async handleControl(action) {
				if (action === 'OPEN_FRONT' && isFrontDoorBlocked(this.deviceStatus)) {
					this.pushLog(action, false, this.frontDoorBlockReason)
					return
				}

				this.controlLoading = true
				const result = await sendControl(this.config, this.connectionState.activeChannel, action)
				this.controlLoading = false
				if (result.ok) {
					const payload = result.data && result.data.data ? result.data.data : {}
					if (payload.offlineWarning) {
						this.banner = {
							type: 'hardwareOffline',
							message: '设备当前离线，指令已下发但请等待设备重新联机后生效'
						}
					}
					this.pushLog(action, true, payload.offlineWarning ? '已下发，但设备当前离线' : '执行成功')
					await this.refreshSnapshot()
					return
				}

				const fallbackLocalBaseUrl = this.deviceStatus.staIp ? `http://${this.deviceStatus.staIp}` : ''
				if (this.config.mode === MODES.backend && fallbackLocalBaseUrl) {
					const fallbackConfig = {
						...this.config,
						localApBaseUrl: fallbackLocalBaseUrl
					}
					const fallbackResult = await sendControl(fallbackConfig, CHANNELS.localAp, action)
					if (fallbackResult.ok) {
						this.config = {
							...this.config,
							localApBaseUrl: fallbackLocalBaseUrl
						}
						const payload = fallbackResult.data && fallbackResult.data.data ? fallbackResult.data.data : {}
						this.pushLog(action, true, payload.offlineWarning ? '已回退到本地直连，但设备当前离线' : '已回退到本地直连')
						await this.refreshSnapshot()
						return
					}
				}

				this.pushLog(action, false, result.errorMessage || '执行失败')
			},
			async handleReadAlerts() {
				if (!this.alertsList.length || this.alertsReadLoading) {
					return
				}

				this.alertsReadLoading = true
				const result = await readAlerts(this.config)
				this.alertsReadLoading = false

				if (result.ok) {
					this.pushLog('ALERTS_READ', true, '告警已标记为已读')
					await this.refreshSnapshot()
					return
				}

				this.pushLog('ALERTS_READ', false, result.errorMessage || '告警已读失败')
			},
			async handleLocalAction(action) {
				if (!this.isLocalChannelActive) {
					this.pushLog(action, false, '当前未连接本地直连通道')
					return
				}

				this.controlLoading = true
				let result = null
				let successMessage = '执行成功'
				if (action === 'UNLOCK_LOCAL') {
					result = await sendLocalUnlock(this.config)
				} else if (action === 'SWITCH_TO_AP') {
					result = await sendLocalModeSwitch(this.config, 'AP')
					successMessage = '已切换到 AP 模式'
				} else if (action === 'SWITCH_TO_STA') {
					result = await sendLocalModeSwitch(this.config, 'STA')
					successMessage = '已切换到 STA 模式'
				}
				this.controlLoading = false

				if (result && result.ok) {
					if (action === 'SWITCH_TO_AP') {
						this.config = {
							...this.config,
							mode: MODES.localAp
						}
					} else if (action === 'SWITCH_TO_STA') {
						this.config = {
							...this.config,
							mode: MODES.auto
						}
					}
					if (result.data && result.data.currentNetMode) {
						this.deviceStatus = {
							...this.deviceStatus,
							netMode: result.data.currentNetMode,
							updatedAt: Date.now()
						}
					}
					this.pushLog(action, true, result.data && result.data.msg ? result.data.msg : successMessage)
					await this.refreshSnapshot()
					return
				}

				this.pushLog(action, false, result && result.errorMessage ? result.errorMessage : '执行失败')
			}
		}
	}
</script>

<style>
	page {
		background: linear-gradient(180deg, #f0f5fb 0%, #e5eef8 34%, #f8fbff 100%);
	}

	.page {
		height: 100vh;
		padding: 28rpx 24rpx 36rpx;
		box-sizing: border-box;
	}

	.hero {
		padding: 34rpx 28rpx;
		margin-bottom: 24rpx;
		border-radius: 32rpx;
		background: linear-gradient(135deg, #17324d 0%, #204f6c 52%, #0e7a61 100%);
		box-shadow: 0 18rpx 40rpx rgba(20, 50, 77, 0.18);
		display: flex;
		flex-direction: column;
		gap: 12rpx;
	}

	.hero-kicker {
		font-size: 22rpx;
		color: rgba(255, 255, 255, 0.68);
		text-transform: uppercase;
		letter-spacing: 2rpx;
	}

	.hero-title {
		font-size: 46rpx;
		font-weight: 700;
		color: #ffffff;
	}

	.hero-desc {
		font-size: 26rpx;
		line-height: 1.6;
		color: rgba(255, 255, 255, 0.84);
	}

	.card {
		margin-bottom: 24rpx;
		padding: 24rpx;
		border-radius: 30rpx;
		background: rgba(255, 255, 255, 0.92);
		box-shadow: 0 10rpx 24rpx rgba(62, 94, 126, 0.08);
		backdrop-filter: blur(12rpx);
	}

	.section-title {
		font-size: 32rpx;
		font-weight: 700;
		color: #16324d;
	}

	.warning-text {
		color: #cb7b16;
	}

	.success-text {
		color: #1f8b58;
	}

	.danger-text {
		color: #c23d3d;
	}
</style>
