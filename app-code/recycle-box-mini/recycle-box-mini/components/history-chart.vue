<template>
	<view class="card panel">
		<view class="section-title">历史趋势</view>
		<view v-if="!history.length" class="empty">暂无历史数据</view>
		<view v-else class="chart-block">
			<text class="chart-title">温湿度曲线</text>
			<qiun-data-charts type="line" canvas2d :opts="tempHumidityOpts" :chartData="tempHumidityData" />
		</view>
		<view v-if="history.length" class="chart-block">
			<text class="chart-title">箱体容量曲线</text>
			<qiun-data-charts type="line" canvas2d :opts="capacityOpts" :chartData="capacityData" />
		</view>
		<view v-if="history.length" class="chart-block">
			<text class="chart-title">空气质量曲线</text>
			<qiun-data-charts type="line" canvas2d :opts="airQualityOpts" :chartData="airQualityData" />
		</view>
		<view v-if="history.length" class="chart-block">
			<text class="chart-title">倾角曲线</text>
			<qiun-data-charts type="line" canvas2d :opts="tiltOpts" :chartData="tiltData" />
		</view>
	</view>
</template>

<script>
	export default {
		name: 'HistoryChart',
		props: {
			history: {
				type: Array,
				default: () => []
			}
		},
		computed: {
			categories() {
				return this.history.map((item) => {
					if (item.timeLabel) {
						return item.timeLabel
					}
					const date = new Date(item.timestamp)
					const hours = `${date.getHours()}`.padStart(2, '0')
					const minutes = `${date.getMinutes()}`.padStart(2, '0')
					return `${hours}:${minutes}`
				})
			},
			tempHumidityData() {
				return {
					categories: this.categories,
					series: [
						{
							name: '温度',
							data: this.history.map((item) => Number(item.temperature || 0))
						},
						{
							name: '湿度',
							data: this.history.map((item) => Number(item.humidity || 0))
						}
					]
				}
			},
			capacityData() {
				return {
					categories: this.categories,
					series: [
						{
							name: '容量',
							data: this.history.map((item) => Number(item.capacity || 0))
						}
					]
				}
			},
			airQualityData() {
				return {
					categories: this.categories,
					series: [
						{
							name: '空气质量',
							data: this.history.map((item) => Number(item.airQuality || 0))
						}
					]
				}
			},
			tiltData() {
				return {
					categories: this.categories,
					series: [
						{
							name: '倾角',
							data: this.history.map((item) => Number(item.tiltAngle || 0))
						}
					]
				}
			},
			tempHumidityOpts() {
				return {
					color: ['#db6b31', '#2d7dd2'],
					padding: [15, 10, 0, 10],
					dataLabel: false,
					enableScroll: true,
					legend: {
						show: true,
						position: 'top',
						float: 'right'
					},
					xAxis: {
						disableGrid: true,
						scrollShow: true,
						itemCount: 6
					},
					yAxis: {
						gridType: 'dash',
						dashLength: 4,
						data: [
							{
								title: '温湿度'
							}
						]
					},
					extra: {
						line: {
							type: 'curve',
							width: 2,
							activeType: 'hollow'
						}
					}
				}
			},
			capacityOpts() {
				return {
					color: ['#0e7a61'],
					padding: [15, 10, 0, 10],
					dataLabel: false,
					enableScroll: true,
					legend: {
						show: true,
						position: 'top',
						float: 'right'
					},
					xAxis: {
						disableGrid: true,
						scrollShow: true,
						itemCount: 6
					},
					yAxis: {
						min: 0,
						max: 100,
						gridType: 'dash',
						dashLength: 4,
						data: [
							{
								title: '容量%'
							}
						]
					},
					extra: {
						line: {
							type: 'straight',
							width: 2,
							activeType: 'hollow'
						}
					}
				}
			},
			airQualityOpts() {
				return {
					color: ['#6f42c1'],
					padding: [15, 10, 0, 10],
					dataLabel: false,
					enableScroll: true,
					legend: {
						show: true,
						position: 'top',
						float: 'right'
					},
					xAxis: {
						disableGrid: true,
						scrollShow: true,
						itemCount: 6
					},
					yAxis: {
						gridType: 'dash',
						dashLength: 4,
						data: [
							{
								title: '空气质量'
							}
						]
					},
					extra: {
						line: {
							type: 'curve',
							width: 2,
							activeType: 'hollow'
						}
					}
				}
			},
			tiltOpts() {
				return {
					color: ['#d67719'],
					padding: [15, 10, 0, 10],
					dataLabel: false,
					enableScroll: true,
					legend: {
						show: true,
						position: 'top',
						float: 'right'
					},
					xAxis: {
						disableGrid: true,
						scrollShow: true,
						itemCount: 6
					},
					yAxis: {
						min: 0,
						gridType: 'dash',
						dashLength: 4,
						data: [
							{
								title: '倾角°'
							}
						]
					},
					extra: {
						line: {
							type: 'straight',
							width: 2,
							activeType: 'hollow'
						}
					}
				}
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

	.empty {
		font-size: 26rpx;
		color: #7c92a8;
	}

	.chart-block {
		display: flex;
		flex-direction: column;
		gap: 16rpx;
		padding: 18rpx;
		border-radius: 20rpx;
		background: #f7fafc;
	}

	.chart-title {
		font-size: 26rpx;
		font-weight: 600;
		color: #17324d;
	}
</style>
