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
            收入支出
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
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
          <qiun-data-charts canvas2d type="column" :opts="monthOpts" :chartData="monthChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            活跃用户
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
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
          <qiun-data-charts canvas2d type="column" :opts="activeOpts" :chartData="activeChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            目标盈利
          </view>
          <picker @change="bindPickerChange" :value="index" :range="array">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{array[index]}}</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="column" :opts="targetOpts" :chartData="targetChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            累计用户
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
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
          <qiun-data-charts canvas2d type="column" :opts="totalOpts" :chartData="totalChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            收益盈亏
          </view>
          <picker @change="bindPickerChange" :value="index" :range="array">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{array[index]}}</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="column" :opts="surplusOpts" :chartData="surplusChartData" />
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
        
        index: 1,
        array: ['近三年', '近六年'],
        
        // 累计用户
        totalChartData: {},
        totalOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.6)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              axisLineColor: "#FFFFFF",
            }, ],
          },
          legend: {
            show: false,
            position: "top",
            float: "right",
          },
          extra: {
            column: {
              type: "group",
              width: 18,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
            }
          },
        },
        
        // 目标盈利
        targetChartData: {},
        targetOpts: {
          color: ["#4B98FE","#A5CCFF","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.6)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '2',
            data: [{
              axisLineColor: "#FFFFFF",
            }, ],
          },
          legend: {
            show: true,
            position: "top",
            float: "right",
          },
          extra: {
            column: {
              type: "meter",
              width: 18,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
              meterBorder: 2,
              meterFillColor: "#4B98FE",
            }
          }
        },
        
        // 收入支出
        monthChartData: {},
        monthOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.6)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              axisLineColor: "#FFFFFF",
            }, ],
          },
          legend: {
            show: true,
            position: "top",
            float: "right",
          },
          extra: {
            column: {
              type: "group",
              width: 16,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
            }
          },
        },
        
        // 活跃用户
        activeChartData: {},
        activeOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.6)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              axisLineColor: "#FFFFFF",
            }, ],
          },
          legend: {
            show: true,
            position: "top",
            float: "right",
          },
          extra: {
            column: {
              type: "stack",
              width: 16,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
            }
          },
        },
        
        // 收益盈亏
        surplusChartData: {},
        surplusOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.6)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            splitNumber: 6,
            data: [{
              axisLineColor: "#FFFFFF",
              min: -60,
              max: 60
            }, ],
          },
          legend: {
            show: false,
            position: "top",
            float: "right",
          },
          extra: {
            column: {
              type: "group",
              width: 18,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
            }
          },
        },
        
      };
    },
    onShow() {
    },
    onLoad() {
    },
    onReady() {
      this.drawTotalCharts();  //累计用户
      this.drawTargetCharts();   //目标盈利
      this.drawMonthCharts();  //收入支出
      this.drawActiveCharts();  //活跃用户
      this.drawSurplusCharts();  //收益盈亏
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
      
      /* 年范围*/
      bindPickerChange: function(e) {
        this.index = e.detail.value
      },
      
      // 累计用户 绘制
      drawTotalCharts() {
        let res = {
          categories: [
            "Android",
            "iPhone",
            "Win PC",
            "Mac PC",
            "其他",
          ],
          series: [{
              name: "累计用户",
              data: [{"value":66,"color":"#4B98FE"}, {"value":46,"color":"#00D05E"}, {"value":31,"color":"#FFAC00"},{"value":33,"color":"#FB6A67"}, {"value":13,"color":"#957BFE"}],
              legendShape: "circle",
            },
          ],
        };
        this.totalChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 目标盈利 绘制
      drawTargetCharts() {
        let res = {
            categories: ["2019","2020","2021","2022","2023","2024"],
            series: [
              {
                name: "目标值",
                data: [35,36,31,33,43,34],
                legendShape: "circle",
              },
              {
                name: "完成量",
                data: [18,27,21,24,35,28],
                legendShape: "circle",
              }
            ]
          };
        this.targetChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 收入支出 绘制
      drawMonthCharts() {
        let res = {
          categories: [
            "7月",
            "8月",
            "9月",
            "10月",
            "11月",
            "12月",
            "1月",
            "2月",
            "3月",
          ],
          series: [{
              name: "收入",
              data: [300, 1340, 2578, 3700, 6688, 8980, 5800, 4677, 3700],
              legendShape: "circle",
              color: "#4B98FE",
            },
            {
              name: "支出",
              data: [332, 1193, 1162, 1157, 1189, 2432, 1643, 1321, 1238],
              legendShape: "circle",
              color: "#FFAC00",
            },
          ],
        };
        this.monthChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 活跃用户 绘制
      drawActiveCharts() {
        let res = {
            categories: ["Android","iPhone","Win PC","Mac PC","其他"],
            series: [
              {
                name: "老用户",
                data: [66,46,31,33,13],
                legendShape: "circle",
              },
              {
                name: "新用户",
                data: [36,27,21,24,6],
                legendShape: "circle",
              },
              {
                name: "未知",
                data: [12,6,5,6,8],
                legendShape: "circle",
              }
            ]
          };
        this.activeChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 收益盈亏 绘制
      drawSurplusCharts() {
        let res = {
            categories: ["2019","2020","2021","2022","2023","2024"],
            series: [
              {
                name: "收益",
                data: [52,{"value":-44,"color":"#FB6A67"},28,{"value":-56,"color":"#FB6A67"},{"value":-32,"color":"#FB6A67"},33],
                legendShape: "circle",
              },
            ]
          };
        this.surplusChartData = JSON.parse(JSON.stringify(res));
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
