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
            当前充电
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
          <qiun-data-charts canvas2d type="arcbar" :opts="chargeOpts" :chartData="chargeChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            考试答题
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
          <qiun-data-charts canvas2d type="arcbar" :opts="examOpts" :chartData="examChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            出勤请假
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
        <view class="tn-flex tn-flex-row-between tn-flex-col-center" style="min-height: 500rpx;">
          <view class="justify-content-item tn-margin-left tn-color-gray--dark" style="width: 350rpx;">
            <view class="tn-text-xl">
              288次 / 349次
            </view>
            <view class="tn-text-sm tn-padding-top-xs">
              已打卡 / 应打卡
            </view>
          </view>
          <view class="justify-content-item" style="width: 400rpx;">
            <qiun-data-charts canvas2d type="arcbar" :opts="workOpts" :chartData="workChartData" />
          </view>
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            内存占用
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
        <view class="tn-flex tn-flex-row-between tn-flex-col-center" style="min-height: 500rpx;">
          <view class="justify-content-item tn-margin-left tn-color-gray--dark" style="width: 350rpx;">
            <view class="tn-text-xl">
              129 GB / 256 GB
            </view>
            <view class="tn-text-sm tn-padding-top-xs">
              已使用 / 全部
            </view>
          </view>
          <view class="justify-content-item" style="width: 400rpx;">
            <qiun-data-charts canvas2d type="arcbar" :opts="opts" :chartData="chartData" />
          </view>
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
        
        // 当前充电
        chargeChartData: {},
        chargeOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: undefined,
          title: {
            name: "92.65%",
            fontSize: 20,
            color: "#5F7E8B"
          },
          subtitle: {
            name: "充电量",
            fontSize: 12,
            color: "#78909C",
            offsetY: 6
          },
          extra: {
            arcbar: {
              type: "default",
              width: 8,
              backgroundColor: "#F8F7F8",
              startAngle: 0.75,
              endAngle: 0.25,
              gap: 2,
            }
          }
        },
        
        // 考试答题
        examChartData: {},
        examOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: undefined,
          title: {
            name: "82.46%",
            fontSize: 20,
            color: "#00C8B0"
          },
          subtitle: {
            name: "正确率",
            fontSize: 12,
            color: "#00C8B0",
            offsetY: 6
          },
          extra: {
            arcbar: {
              type: "circle",
              width: 8,
              backgroundColor: "#F8F7F8",
              startAngle: 1.5,
              endAngle: 0.25,
              gap: 2,
            }
          }
        },
        
        // 出勤请假
        workChartData: {},
        workOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: undefined,
          title: {
            name: "82.46%",
            fontSize: 20,
            color: "#4B98FE"
          },
          subtitle: {
            name: "全勤率",
            fontSize: 12,
            color: "#4B98FE",
            offsetY: 6
          },
          extra: {
            arcbar: {
              type: "circle",
              width: 8,
              backgroundColor: "#F8F7F8",
              startAngle: 1.5,
              endAngle: 0.25,
              gap: 2,
            }
          }
        },
        
        // 内存占用
        chartData: {},
        opts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: undefined,
          title: {
            name: "图鸟",
            fontSize: 20,
            color: "rgba(0,0,0,0)"
          },
          subtitle: {
            name: "全勤率",
            fontSize: 12,
            color: "rgba(0,0,0,0)",
            offsetY: 6
          },
          extra: {
            arcbar: {
              type: "circle",
              width: 8,
              backgroundColor: "#F8F7F8",
              startAngle: 1.5,
              endAngle: 0.25,
              gap: 2,
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
      this.drawChargeCharts();  //当前充电
      this.drawExamCharts();  //考试答题
      this.drawWorkCharts();  //出勤请假
      this.getServerData();  //内存占用
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
      
      // 当前充电 绘制
      drawChargeCharts() {
        let res = {
            series: [
              {
                name: "充电量",
                color: "#00D05E",
                data: 0.9265
              }
            ]
          };
        this.chargeChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 考试答题 绘制
      drawExamCharts() {
        let res = {
            series: [
              {
                name: "正确率",
                color: "#00C8B0",
                data: 0.8246
              }
            ]
          };
        this.examChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 出勤请假 绘制
      drawWorkCharts() {
        let res = {
            series: [
              {
                name: "全勤率",
                color: "#4B98FE",
                data: 0.8246
              }
            ]
          };
        this.workChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 内存占用 绘制
      getServerData() {
        let res = {
            series: [
              {
                name: "图鸟vue2",
                data: 0.8
              },
              {
                name: "图鸟vue3",
                data: 0.6
              },
              {
                name: "图鸟OA",
                data: 0.45
              },
              {
                name: "图鸟模板7",
                data: 0.3
              },
              {
                name: "图鸟模板8",
                data: 0.15
              }
            ]
          };
        this.chartData = JSON.parse(JSON.stringify(res));
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