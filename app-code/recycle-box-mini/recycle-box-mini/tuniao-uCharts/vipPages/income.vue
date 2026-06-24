<template>
  <view class="template-content">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed alpha customBack>
      <view slot="back" class='tn-custom-nav-bar__back'
        @click="goBack">
        <text class='icon tn-icon-left'></text>
        <text class='icon tn-icon-home-capsule-fill'></text>
      </view>
    </tn-nav-bar>
    
    <view class="top-fixed" :style="{paddingTop: vuex_custom_bar_height + 'px'}">
      <view class="tn-text-center" style="position: absolute;top: -80rpx;right:-80rpx;font-size: 500rpx;opacity: 0.1;transform: rotate(39deg);">
        <view class="tn-icon-money tn-color-white"></view>
      </view>
      <view class="tn-margin tn-padding-left-sm tn-padding-bottom-xl tn-padding-top tn-color-white">
        <view class="">
          <text>昨日收益（元）</text>
          <text style="opacity: 0.6;margin-left: 10rpx;">明细</text>
          <text class="tn-icon-right" style="opacity: 0.6;"></text>
        </view>
        <view class="tn-text-bold tn-padding-top-xs" style="font-size:70rpx">82.96</view>
      </view>
      <view class="tn-margin tn-padding-left-sm tn-color-white">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm" style="opacity: 0.6;">日环比</view>
            <view class="tn-text-lg tn-text-bold tn-padding-top-xs">+68.62%</view>
          </view>
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm" style="opacity: 0.6;">周同比</view>
            <view class="tn-text-lg tn-text-bold tn-padding-top-xs">+26.09%</view>
          </view>
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm" style="opacity: 0.6;">本月收益（元）</view>
            <view class="tn-text-lg tn-text-bold tn-padding-top-xs">1,506.22</view>
          </view>
        </view>
      </view>
    </view>
    
    <view class="tn-padding-top-xl tn-padding-bottom-xl">
      <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          收益趋势
        </view>
        <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <text class="tn-padding-left-xs tn-padding-right-xs">28年7月 - 29年3月</text>
          <text class="tn-icon-down tn-padding-right-xs"></text>
        </view>
      </view>
      <view class="" style="min-height: 500rpx;">
        <qiun-data-charts canvas2d type="area" :opts="incomeOpts" :chartData="incomeChartData" />
      </view>
    </view>
      
      
      
  </view>
</template>

<script>
  import template_page_mixin from '@/libs/mixin/template_page_mixin.js'
  export default {
    name: 'TemplateContent',
    mixins: [template_page_mixin],
    data() {
      return {
        
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
        
      };
    },
    onReady() {
      this.drawIncomeCharts();  //公司营收
    },
    methods: {
      // 跳转
      tn(e) {
      	uni.navigateTo({
      		url: e,
      	});
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
            color: "#05C160",
            pointShape: "none",
            data: [
              300,
              80,
              200,
              400,
              500,
              800,
              900,
              1000, // 7
              900,
              800,
              600,
              200,
              100,
              180,
              760,
              2000, // 8
              2055,
              2545,
              2455,
              2545,
              2767,
              2745,
              2743,
              2767, // 9
              3288,
              3256,
              3656,
              4756,
              6234,
              6652,
              6456,
              6656, // 10
              5340,
              4324,
              4335,
              5444,
              6555,
              7666,
              6777,
              6888, // 11
              8990,
              6500,
              5110,
              5220,
              5330,
              5440,
              5555,
              5666, // 12
              5777,
              4880,
              4990,
              4100,
              4133,
              4111,
              4220,
              4330, // 2024
              4440,
              4550,
              5660,
              4777,
              4888,
              5599,
              5111,
              5222, // 2
              5355,
              5333,
              5440,
              5555,
              5666,
              5777,
              6568,
              6888, // 3
            ],
          }],
        };
        this.incomeChartData = JSON.parse(JSON.stringify(res));
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
  
  .top-fixed{
    position: relative;
    background: linear-gradient(90deg, #05C160, #05C160);
    top: 0;
    width: 100%;
    height: 580rpx;
    transition: all 0.25s ease-out;
    z-index: -1;
  }
  .top-fixed:before{
    content: "";
    position: absolute;
    top: 0;
    left: 0;
    bottom: 0;
    right: 0;
    z-index: -1;
    mask-image: linear-gradient(to bottom, transparent, black);
    background: linear-gradient(90deg, #05C160, #05C160);	
  
  }
</style>
