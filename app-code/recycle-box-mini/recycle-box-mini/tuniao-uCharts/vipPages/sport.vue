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
    
    <view class="tn-margin-xl tn-color-black map-footerfixed" @click="openLocation" :style="{paddingTop: vuex_custom_bar_height + 50 + 'px'}">
      <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center position-info">
        <view class="icon-border">
          <view class="icon-pic">
            <view class="icon-image" style="background-image:url('https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242409-assets/web-upload/fcc4eab6-b2ce-44eb-9165-c49b51f5f830.jpeg');width: 70rpx;height: 70rpx;background-size: cover;overflow: hidden;">
            </view>
          </view>
        </view>
        <view class="bubble">
          <view class="tn-color-white tn-padding-sm">
            <view class="">
              <text class="tn-text-sm">附近有超多人在晨跑</text>
              <text class="tn-icon-route tn-padding-left-xs" style="color: #00FFC6;"></text>
            </view>
            <view class="tn-text-xs tn-padding-top-xs">贡献路线一起快乐跑 ~</view>
          </view>
        </view>
      </view>
    </view>
    <map class="map" :latitude="latitude" :longitude="longitude" :markers="covers"
      @click="openLocation" :enable-scroll="false" :enable-zoom="false">
    </map>
    
    <view class="tn-color-black tn-padding-top-lg tn-margin-top-lg">
      <view class="tn-flex tn-flex-col-center tn-text-center">
        <view class="justify-content-item tn-flex-1">
          <view class="tn-text-lg tn-text-bold">226千卡</view>
          <view class="tn-text-sm tn-padding-top-xs" style="opacity: 0.8;">
            <text class="tn-icon-fire-fill tn-padding-right-xs"></text>
            <text>卡路里</text>
          </view>
        </view>
        <view class="justify-content-item tn-flex-1">
          <view class="tn-text-lg tn-text-bold">0时26分31秒</view>
          <view class="tn-text-sm tn-padding-top-xs" style="opacity: 0.8;">
            <text class="tn-icon-time-fill tn-padding-right-xs"></text>
            <text>时间</text>
          </view>
        </view>
        <view class="justify-content-item tn-flex-1">
          <view class="tn-text-lg tn-text-bold">3.03公里</view>
          <view class="tn-text-sm tn-padding-top-xs" style="opacity: 0.8;">
            <text class="tn-icon-location-fill tn-padding-right-xs"></text>
            <text>距离</text>
          </view>
        </view>
      </view>
    </view>
    
    <view class="tn-padding-top-xl tn-padding-bottom-xl">
      <!-- <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          运动统计
        </view>
        <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <text class="tn-padding-left-xs tn-padding-right-xs">23年7月 - 至今</text>
          <text class="tn-icon-down tn-padding-right-xs"></text>
        </view>
      </view> -->
      <view class="tn-flex tn-flex-row-between tn-flex-col-center" style="min-height: 500rpx;">
        <view class="justify-content-item tn-margin-left-xl tn-padding-left-xs tn-color-gray--dark" style="width: 350rpx;">
          <view class="tn-text-xl">
            5,024步 / 6,000步
          </view>
          <view class="tn-text-sm tn-padding-top-xs">
            已完成 / 目标
          </view>
        </view>
        <view class="justify-content-item" style="width: 400rpx;">
          <qiun-data-charts canvas2d type="arcbar" :opts="workOpts" :chartData="workChartData" />
        </view>
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
        
        id: 0, // 使用 marker点击事件 需要填写id
        title: 'map',
        latitude: 22.961836,
        longitude: 113.330067,
        /* covers: [{
        	latitude: 22.961836,
        	longitude: 113.330067,
        	iconPath: 'https://cdn.nlark.com/yuque/0/2023/png/280373/1675936271542-assets/web-upload/8f3d0a29-cad4-4e4d-995b-0e08467dff02.png'
        }]*/
        
        // 运动统计
        workChartData: {},
        workOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: undefined,
          title: {
            name: "82.46%",
            fontSize: 20,
            color: "#00000080"
          },
          subtitle: {
            name: "每日目标",
            fontSize: 12,
            color: "#AAAAAA",
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
    onReady() {
      this.drawWorkCharts();  //每日目标
    },
    methods: {
      
      openLocation() {
        wx.vibrateShort();
        uni.openLocation({
          longitude: 113.3298396012573,
          latitude: 22.961803525530176,
          name: '祈福新村',
          address: '祈福新村'
        })
      },
      
      // 每日目标 绘制
      drawWorkCharts() {
        let res = {
            series: [
              {
                name: "每日目标",
                color: "#00FFC6",
                data: 0.8246
              }
            ]
          };
        this.workChartData = JSON.parse(JSON.stringify(res));
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
  
  /* 固定到地图上*/
  .map-footerfixed {
    position: absolute;
    width: calc(100vw - 100rpx);
    z-index: 2;
    margin-top: 100rpx;
  }
  
  .map {
    // width: calc(100vw - 60rpx);
    width: 100vw;
    height: 40vh;
    // border-radius: 8rpx;
    // border: 1rpx solid #F8F7F8;
    // margin: 30rpx 30rpx 100rpx 30rpx;
  }
  
  .bubble {
    position: absolute;
    background-color: #333333;
    border-radius: 20rpx;
    top: 0;
    left: 50%;
    transform: scale(0.9) translate(calc(-50% - 10rpx), calc(-100% - 24rpx));
  }
  
  .bubble::after {
    position: absolute;
    content: "";
    width: 0px;
    height: 0px;
    background: transparent;
    border-color: #333333 transparent transparent transparent;
    border-width: 20rpx;
    border-style: solid;
    box-sizing: content-box;
    // margin-top: -4px;
    left: 50%;
    bottom: 0;
    transform: translate(-50%, 88%);
  }
  
  .position-info {
    position: relative;
  }
  
  /* icon start */
  .icon-image {
    width: 70rpx;
    height: 70rpx;
    position: relative;
    overflow: hidden;
    border-radius: 100rpx;
  }
  
  .icon-pic {
    background-size: cover;
    background-repeat: no-repeat;
    // background-attachment:fixed;
    background-position: top;
    border: 12rpx solid #00FFC6;
    border-radius: 50%;
    overflow: hidden;
    // background-color: #FFFFFF;
  }
  
  .icon-border {
    margin: 20rpx 0 0 10rpx;
    border-radius: 100rpx;
    border: 26rpx solid #00FFC630;
  }
  
</style>
