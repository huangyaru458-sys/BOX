<template>
  <view class="template-ucharts tn-safe-area-inset-bottom">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed alpha customBack>
      <view slot="back" class='tn-custom-nav-bar__back'
        @click="goBack">
        <text class='icon tn-icon-left'></text>
        <text class='icon tn-icon-home-capsule-fill'></text>
      </view>
    </tn-nav-bar>
    
    <!--
    写在前面：uCharts一直是图鸟最大的支持者，从图鸟UI刚出生，uCharts就在默默支持，详见地址右上角专属且唯一的广告位：https://www.ucharts.cn/v2/#/ask/index
     
    推出 图表 -【图鸟UI & uCharts】，更多是为了感谢粉丝们的支持，也感恩一起成长的小伙伴们
    
    以下是【图鸟UI & uCharts】的部分模板，因一次性加载会慢，也因懒得写延时加载，所以实际应用中自行延时处理
     -->
    
    
    <view class="" :style="{paddingTop: vuex_custom_bar_height + 10 +  'px'}">
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            系统性能
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark" style="border-radius: 12rpx;">
            <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="month">
              <text class="tn-padding-left-xs tn-padding-right-xs">{{date}}</text>
            </picker>
            <view class="tn-icon-sequence">
            </view>
            <picker @change="bindDateChange1" mode="date" :value="date1" :start="startDate1" :end="endDate1" fields="month">
              <text class="tn-padding-left-xs tn-padding-right-xs">{{date1}}</text>
            </picker>
          </view>
        </view>
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin-left tn-color-gray--dark" style="width: 350rpx;">
            <view class="tn-padding-top-sm">
              服务器：6个
            </view>
            <view class="tn-padding-top-sm">
              数据库：6个
            </view>
            <view class="tn-padding-top-sm">
              启动项：6个
            </view>
            <view class="tn-padding-top-sm">
              风险：0个
            </view>
            <view class="tn-padding-top-sm">
              病毒：0个
            </view>
          </view>
          <view class="justify-content-item" style="max-height: 400rpx;min-height: 400rpx;width: 400rpx;">
            <qiun-data-charts canvas2d type="gauge" :opts="systemOpts" :chartData="systemChartData" />
          </view>
        </view>
      
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            速度表盘
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark" style="border-radius: 12rpx;">
            <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="month">
              <text class="tn-padding-left-xs tn-padding-right-xs">{{date}}</text>
            </picker>
            <view class="tn-icon-sequence">
            </view>
            <picker @change="bindDateChange1" mode="date" :value="date1" :start="startDate1" :end="endDate1" fields="month">
              <text class="tn-padding-left-xs tn-padding-right-xs">{{date1}}</text>
            </picker>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="gauge" :opts="speedOpts" :chartData="speedChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
    </view>
      
  </view>
</template>

<script>
  import template_page_mixin from '@/libs/mixin/template_page_mixin.js'
  export default {
    mixins: [template_page_mixin],
    data() {
      return {
        date: '2023-07',
        date1: '2024-03',
        
        // 系统性能
        systemChartData: {},
        systemOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: true,
          title: {
            name: "686",
            fontSize: 32,
            color: "#4B98FE",
            offsetY: 0
          },
          subtitle: {
            name: "综合评分",
            fontSize: 12,
            color: "#4B98FE",
            offsetY: 6
          },
          extra: {
            gauge: {
              type: "progress",
              width: 26,
              labelColor: "#E6E6E6",
              labelOffset: 50,
              startAngle: 0.75,
              endAngle: 0.25,
              startNumber: 0,
              endNumber: 100,
              labelFormat: "",
              splitLine: {
                fixRadius: -30,
                splitNumber: 10,
                width: 40,
                color: "#FFFFFF",
                childNumber: 5,
                childWidth: 12
              },
              pointer: {
                width: 16,
                color: "auto"
              }
            }
          }
        },
        
        // 速度表盘
        speedChartData: {},
        speedOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: true,
          title: {
            name: "84 Km/H",
            fontSize: 16,
            color: "#4B98FE",
            offsetY: 80
          },
          subtitle: {
            name: "实时速度",
            fontSize: 12,
            color: "#4B98FE",
            offsetY: 6
          },
          extra: {
            gauge: {
              type: "default",
              width: 26,
              labelColor: "#838383",
              labelOffset: 20,
              startAngle: 0.75,
              endAngle: 0.25,
              startNumber: 0,
              endNumber: 240,
              labelFormat: "4444",
              splitLine: {
                fixRadius: 2,
                splitNumber: 12,
                width: 40,
                color: "#FFFFFF",
                childNumber: 5,
                childWidth: 12
              },
              pointer: {
                width: 22,
                color: "auto"
              }
            }
          }
        },
        
      };
    },
    onShow() {
    },
    onLoad() {
    },
    onReady() {
      this.drawSystemCharts();  //系统性能
      this.drawSpeedCharts();  //速度表盘
    },
    mounted() {
    },
    methods: {
      // 时间
      startDate() {
        return this.getDate('start');
      },
      endDate() {
        return this.getDate('end');
      },
      
      // 时间
      startDate1() {
        return this.getDate('start');
      },
      endDate1() {
        return this.getDate('end');
      },
      
      bindDateChange: function(e) {
          this.date = e.detail.value
      },
      
      bindDateChange1: function(e) {
          this.date1 = e.detail.value
      },
      
      // 系统性能 绘制
      drawSystemCharts() {
        let res = {
            categories: [{"value":0.2,"color":"#4B98FE"},{"value":0.8,"color":"#00D05E"},{"value":1,"color":"#FB6A67"}],
            series: [
              {
                name: "综合评分",
                data: 0.686
              }
            ]
          };
        this.systemChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 速度表盘 绘制
      drawSpeedCharts() {
        let res = {
            categories: [{"value":0.5,"color":"#00B9FE"},{"value":0.75,"color":"#4B98FE"},{"value":1,"color":"#FB6A67"}],
            series: [
              {
                name: "速度表盘",
                data: 0.35
              }
            ]
          };
        this.speedChartData = JSON.parse(JSON.stringify(res));
      },
      
    },
  };
</script>
<style lang="scss" scoped>
  /* 胶囊*/
  .tn-custom-nav-bar__back {
    width: 100%;
    height: 100%;
    position: relative;
    display: flex;
    justify-content: space-evenly;
    align-items: center;
    box-sizing: border-box;
    background-color: rgba(0, 0, 0, 0.15);
    border-radius: 1000rpx;
    border: 1rpx solid rgba(255, 255, 255, 0.5);
    color: #FFFFFF;
    font-size: 18px;
    
    .icon {
      display: block;
      flex: 1;
      margin: auto;
      text-align: center;
    }
    
    &:before {
      content: " ";
      width: 1rpx;
      height: 110%;
      position: absolute;
      top: 22.5%;
      left: 0;
      right: 0;
      margin: auto;
      transform: scale(0.5);
      transform-origin: 0 0;
      pointer-events: none;
      box-sizing: border-box;
      opacity: 0.7;
      background-color: #FFFFFF;
    }
  }
  
  
  /* 间隔线 start*/
  .tn-strip-bottom {
    width: 100%;
    border-bottom: 20rpx solid #F8F7F8;
  }

  /* 间隔线小 start*/
  .tn-strip-bottom-min {
    width: 100%;
    border-bottom: 1rpx solid #F8F7F8;
  }
  
</style>