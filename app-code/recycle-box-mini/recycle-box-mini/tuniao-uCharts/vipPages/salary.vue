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
        <view class="">到手所得</view>
        <view class="tn-text-bold tn-padding-top-xs" style="font-size:70rpx">4,873.42</view>
      </view>
      <view class="tn-margin tn-padding-left-sm tn-color-white">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm">税前收入</view>
            <view class="tn-text-xxl tn-text-bold tn-padding-top-xs">6,000</view>
          </view>
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm">五险一金</view>
            <view class="tn-text-xxl tn-text-bold tn-padding-top-xs">845.98</view>
          </view>
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm">个人所得税</view>
            <view class="tn-text-xxl tn-text-bold tn-padding-top-xs">280.6</view>
          </view>
        </view>
      </view>
    </view>
    
    <view class="tn-padding-bottom-xl tn-margin-top">
      <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          五险一金明细
        </view>
        <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <text class="tn-padding-left-xs tn-padding-right-xs">29年7月 - 29年8月</text>
          <text class="tn-icon-down tn-padding-right-xs"></text>
        </view>
      </view>
      <view class="" style="min-height: 500rpx;">
        <qiun-data-charts canvas2d type="rose" :opts="terminalOpts" :chartData="terminalChartData" />
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
        // 用户终端
        terminalChartData: {},
        terminalOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15,10,15,10],
          dataLabel: true,
          enableScroll: false,
          legend: {
            show: true,
            position: "left",
            lineHeight: 32
          },
          extra: {
            rose: {
              type: "radius",
              minRadius: 50,
              activeOpacity: 0.5,
              activeRadius: 10,
              offsetAngle: 0,
              labelWidth: 15,
              border: true,
              borderWidth: 2,
              borderColor: "#FFFFFF"
            }
          }
        },
      }
    },
    onReady() {
      this.drawTerminalCharts();  //用户终端
    },
    methods: {
      // 跳转
      tn(e) {
      	uni.navigateTo({
      		url: e,
      	});
      },
      
      // 用户终端 绘制
      drawTerminalCharts() {
        let res = {
            series: [
              {
                data: [{"name":"公积金","value":652},{"name":"医疗","value":508},{"name":"养老","value":422},{"name":"失业","value":346},{"name":"工伤","value":262},{"name":"生育","value":129}]
              }
            ]
          };
        this.terminalChartData = JSON.parse(JSON.stringify(res));
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
    background: linear-gradient(90deg, #F63A52, #F7A258);
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
    background: linear-gradient(90deg, #F73E67, #F75C53);	
  
  }
</style>
