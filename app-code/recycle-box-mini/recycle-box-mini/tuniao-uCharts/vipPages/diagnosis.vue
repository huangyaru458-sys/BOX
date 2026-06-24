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
      <view class="tn-text-center" style="position: absolute;top: 10rpx;right:0;font-size: 400rpx;opacity: 0.1;">
        <view class="tn-icon-rocket tn-color-white"></view>
      </view>
      <view class="tn-margin tn-padding-left-sm tn-padding-bottom-xl tn-padding-top tn-color-white">
        <view class="">今日访问量</view>
        <view class="tn-text-bold tn-padding-top-xs" style="font-size:70rpx">1,508</view>
      </view>
      <view class="tn-margin tn-padding-left-sm tn-color-white">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm">累计用户数</view>
            <view class="tn-text-xxl tn-text-bold tn-padding-top-xs">20,362</view>
          </view>
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm">新增用户数</view>
            <view class="tn-text-xxl tn-text-bold tn-padding-top-xs">1,208</view>
          </view>
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm">用户留存</view>
            <view class="tn-text-xxl tn-text-bold tn-padding-top-xs">206</view>
          </view>
        </view>
      </view>
    </view>
    
    <view class="tn-padding-top-xl tn-padding-bottom-xl">
      <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          流量分析
        </view>
        <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <text class="tn-padding-left-xs tn-padding-right-xs">近7日</text>
          <text class="tn-icon-down tn-padding-right-xs"></text>
        </view>
      </view>
      <view class="" style="min-height: 500rpx;">
        <qiun-data-charts canvas2d type="area" :opts="revenueOpts" :chartData="revenueChartData" />
      </view>
    </view>
      
      
      
  </view>
</template>

<script>
  import template_page_mixin from '@/libs/mixin/template_page_mixin.js'
  export default {
    name: 'TemplateContent',
    mixins: [template_page_mixin],
    data(){
      return {
        // 公司营收
        revenueChartData: {},
        revenueOpts: {
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
      }
    },
    onReady() {
      this.drawRevenueCharts();  //公司营收
    },
    methods: {
      // 跳转
      tn(e) {
      	uni.navigateTo({
      		url: e,
      	});
      },
      
      // 公司营收 绘制
      drawRevenueCharts() {
        let res = {
          categories: [
            "12.02",
            "12.03",
            "12.04",
            "12.05",
            "12.06",
            "12.07",
            "12.08",
          ],
          series: [{
              name: "收入",
              data: [92, 1668, 1508, 1900, 1588, 880, 600],
              legendShape: "circle",
              color: "#4B98FE",
              // pointShape: "none",
            }
          ],
        };
        this.revenueChartData = JSON.parse(JSON.stringify(res));
      },
      
    }
  }
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
    background: linear-gradient(90deg, #4B98FE, #00B9FE);
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
    background: linear-gradient(90deg, #4B98FE, #4B98FE);	
  
  }
</style>
