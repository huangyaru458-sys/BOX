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
          <qiun-data-charts canvas2d type="line" :opts="monthOpts" :chartData="monthChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            经济情况
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
          <qiun-data-charts canvas2d type="line" :opts="economyOpts" :chartData="economyChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            公司营收
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
          <qiun-data-charts canvas2d type="line" :opts="incomeOpts" :chartData="incomeChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            投资理财
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
          <qiun-data-charts canvas2d type="line" :opts="investOpts" :chartData="investChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            连点成线
          </view>
          <picker @change="bindPickerChange" :value="index" :range="array">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{array[index]}}</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="line" :opts="gameOpts" :chartData="gameChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            高低电平
          </view>
          <picker @change="bindPickerChange" :value="index" :range="array">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{array[index]}}</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="line" :opts="levelOpts" :chartData="levelChartData" />
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
        
        index: 0,
        array: ['今日', '近七天', '本月'],
        
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
              type: "straight",
              width: 2,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
            },
          },
        },
        
        // 经济情况
        economyChartData: {},
        economyOpts: {
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
            line: {
              type: "curve",
              width: 2,
              activeType: "hollow"
            },
          },
        },
        
        // 公司营收
        incomeChartData: {},
        incomeOpts: {
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
            area: {
              type: "curve",
              opacity: 0.9,
              addLine: true,
              width: 2,
              gradient: true,
            },
          },
        },
        
        // 投资理财
        investChartData: {},
        investOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          dataPointShape: false,
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
            line: {
              type: "curve",
              width: 2,
              activeType: "hollow",
              linearType: "custom",
              onShadow: true,
            },
          },
        },
        
        // 连点成线
        gameChartData: {},
        gameOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          dataPointShapeType: 'hollow',
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
            line: {
              type: "curve",
              width: 2,
              activeType: "hollow"
            },
          },
        },
        
        // 高低电平
        levelChartData: {},
        levelOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          dataPointShape: false,
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
              min: -15,
              max: 15
            }, ],
          },
          legend: {
            show: false,
            position: "top",
            float: "right",
          },
          extra: {
            line: {
              type: "step",
              width: 2,
              activeType: "hollow"
            },
          },
        },
        
        
      };
    },
    onShow() {
    },
    onLoad() {
    },
    onReady() {
      this.drawMonthCharts();  //收入支出
      this.drawEconomyCharts();  //经济情况
      this.drawIncomeCharts();  //公司营收
      this.drawInvestCharts();  //投资理财
      this.drawGameCharts();  //连点成线
      this.drawLevelCharts();  //高低电平
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
      
      bindPickerChange: function(e) {
        this.index = e.detail.value
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
      
      // 经济情况 绘制
      drawEconomyCharts() {
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
              data: [1800, 1668, 1508, 1900, 1588, 1880, 1700, 1777, 1760],
              legendShape: "circle",
              color: "#4B98FE",
            },
            {
              name: "支出",
              data: [1290, 1293, 1262, 1557, 1689, 1432, 1643, 1321, 1438],
              legendShape: "circle",
              color: "#FFAC00",
            },
          ],
        };
        this.economyChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 公司营收 绘制
      drawIncomeCharts() {
        let res = {
          categories: [
            "7月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "8月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "9月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "10月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "11月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "12月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "1月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "2月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "3月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
          ],
          series: [{
            name: "收益",
            legendShape: "circle",
            color: "#4B98FE",
            pointShape: "none",
            data: [
              13000,
              8000,
              12000,
              14000,
              15000,
              18000,
              19000,
              10000, // 7
              19000,
              18000,
              16000,
              12000,
              11000,
              11800,
              17600,
              12000, // 8
              20555,
              25455,
              24555,
              25454,
              27678,
              27453,
              27432,
              27678, // 9
              32880,
              32560,
              36560,
              47560,
              62345,
              66522,
              64560,
              66560, // 10
              53400,
              43244,
              43355,
              54440,
              65550,
              76660,
              67770,
              68880, // 11
              89990,
              65500,
              51110,
              52220,
              53330,
              54440,
              55550,
              56660, // 12
              57770,
              48880,
              49990,
              41000,
              41330,
              41110,
              42220,
              43330, // 2024
              44440,
              45550,
              56660,
              47770,
              48880,
              55990,
              51110,
              52220, // 2
              53555,
              53330,
              54440,
              55550,
              56660,
              57770,
              65680,
              68880, // 3
            ],
          }],
        };
        this.incomeChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 投资理财 绘制
      drawInvestCharts() {
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
              name: "投资理财",
              data: [990, 1293, 1062, 1457, 1232, 1443, 1321, 1438, 1689],
              legendShape: "circle",
              linearColor: [[0,"#FFAC00"],[0.25,"#FE871B"],[0.5,"#FB6A67"],[0.75,"#F674D6"],[1,"#957BFE"]],
            },
          ],
        };
        this.investChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 连点成线 绘制
      drawGameCharts() {
        let res = {
          series: [
            {
              name: "线条",
              data: [[0,10],[15,20],[20,40]],
              legendShape: "circle",
              color: "#F674D6",
            },
            {
              name: "曲线",
              data: [[0,0],[6,20],[0,40]],
              legendShape: "circle",
              color: "#FFAC00",
            }
          ],
        };
        this.gameChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 高低电平 绘制
      drawLevelCharts() {
        let res = {
          categories: [
            "0时",
            "3时",
            "6时",
            "9时",
            "12时",
            "15时",
            "18时",
            "21时",
            "24时",
          ],
          series: [{
              name: "高低电平",
              data: [-12, -6, -8, 0, -4, 12, 2, 6, 4],
              legendShape: "circle",
              color: "#00C8B0",
            }
          ],
        };
        this.levelChartData = JSON.parse(JSON.stringify(res));
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