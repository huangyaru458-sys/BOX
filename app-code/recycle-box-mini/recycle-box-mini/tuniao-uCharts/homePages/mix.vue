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
            营收占比
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
          <qiun-data-charts canvas2d type="mix" :opts="opts" :chartData="chartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            营收占比
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
          <qiun-data-charts canvas2d type="mix" :opts="opts2" :chartData="chartData2" />
        </view>
      </view>
      
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
        
        // 混合图
        chartData: {},
        opts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
            title: "/年"
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.6)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            showTitle: true,
            data: [
              {
                axisLineColor: "#FFFFFF",
                position: "left",
                title: "折线"
              },
              {
                axisLineColor: "#FFFFFF",
                position: "right",
                min: 0,
                max: 200,
                title: "柱状图",
                textAlign: "left"
              }
            ]
          },
          extra: {
            mix: {
              column: {
                type: "group",
                width: 16,
                activeBgColor: "#000000",
                activeBgOpacity: 0.04,
              },
            }
          }
        },
        
        // 混合图2
        chartData2: {},
        opts2: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
            title: "/年"
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.6)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            showTitle: true,
            data: [
              {
                axisLineColor: "#FFFFFF",
                position: "left",
                title: "折线"
              },
              {
                axisLineColor: "#FFFFFF",
                position: "right",
                min: 0,
                max: 200,
                title: "柱状图",
                textAlign: "left"
              },
              {
                position: "right",
                min: 0,
                max: 200,
                title: "点",
                textAlign: "left"
              }
            ]
          },
          extra: {
            mix: {
              column: {
                type: "stack",
                width: 16,
                barBorderCircle: true,
                activeBgColor: "#000000",
                activeBgOpacity: 0.04,
              },
            }
          }
        }
        
        
      };
    },
    onShow() {
    },
    onLoad() {
    },
    onReady() {
      this.getServerData();
      this.getServerData2();
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
      
      // 混合图
      getServerData() {
        let res = {
            categories: ["2019","2020","2021","2022","2023","2024"],
            series: [
              {
                name: "曲面",
                type: "area",
                style: "curve",
                data: [70,50,85,130,64,88],
                legendShape: "circle",
                color: "#00D05E",
              },
              {
                name: "柱1",
                index: 1,
                type: "column",
                data: [40,{"value":30,"color":"#f04864"},55,110,24,58],
                legendShape: "circle",
                color: "#4B98FE",
              },
              {
                name: "柱2",
                index: 1,
                type: "column",
                data: [50,20,75,60,34,38],
                legendShape: "circle",
                color: "#FFAC00",
              },
              {
                name: "曲线",
                type: "line",
                style: "curve",
                disableLegend: true,
                data: [70,50,85,130,64,88],
                legendShape: "circle",
                color: "#00D05E",
              },
              {
                name: "折线",
                type: "line",
                data: [120,140,105,170,95,160],
                legendShape: "circle",
                color: "#FB6A67",
              }
            ]
          };
        this.chartData = JSON.parse(JSON.stringify(res));
      },
      
      // 混合图
      getServerData2() {
        let res = {
            categories: ["2019","2020","2021","2022","2023","2024"],
            series: [
              {
                name: "曲面",
                type: "area",
                style: "curve",
                data: [70,50,85,130,64,88],
                legendShape: "circle",
                color: "#00D05E",
              },
              {
                name: "柱1",
                index: 1,
                type: "column",
                data: [40,{"value":30,"color":"#f04864"},55,110,24,58],
                legendShape: "circle",
                color: "#4B98FE",
              },
              {
                name: "柱2",
                index: 1,
                type: "column",
                data: [50,20,75,60,34,38],
                legendShape: "circle",
                color: "#FFAC00",
              },
              {
                name: "曲线",
                type: "line",
                style: "curve",
                disableLegend: true,
                data: [70,50,85,130,64,88],
                legendShape: "circle",
                color: "#00D05E",
              },
              {
                name: "折线",
                type: "line",
                data: [120,140,105,170,95,160],
                legendShape: "circle",
                color: "#FB6A67",
              },
              {
                name: "点点",
                index: 2,
                type: "point",
                color: "#f04864",
                data: [100,80,125,150,112,132]
              }
            ]
          };
        this.chartData2 = JSON.parse(JSON.stringify(res));
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