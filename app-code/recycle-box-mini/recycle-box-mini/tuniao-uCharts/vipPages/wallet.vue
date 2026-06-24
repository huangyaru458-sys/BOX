<template>
  <view class="template-content bg-gray">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed customBack :bottomShadow="false" backgroundColor="#FFFFFF">
      <view slot="back" class='tn-custom-nav-bar__back'
        @click="goBack">
        <text class='icon tn-icon-left'></text>
        <text class='icon tn-icon-home-capsule-fill'></text>
      </view>
      <view class="tn-flex tn-flex-col-center tn-flex-row-center ">
        <text class="tn-text-bold tn-text-xl" style="color: #48505B;">Wallet</text>
      </view>
    </tn-nav-bar>
    
    <!-- 模拟器上，图表是显示在最上层挡住很多东西，真机是没有问题的，因为加了canvas2d处理 -->
    <!-- 如因一次性加载太多太多，所以会慢，也因懒得写延时加载，所以实际应用中自行延时处理 -->
    
    <view class="" :style="{paddingTop: vuex_custom_bar_height + 10 + 'px'}">
      
      <view class="tn-color-gray" style="margin: 30rpx 10rpx">
        <tn-tabs :list="fixedList" :current="current" :isScroll="false" barHeight="6" barWidth="28" :showBar="false"
          :activeItemStyle="activeItemStyle" :inactiveItemStyle="inactiveItemStyle" :barStyle="barStyle" inactiveColor="#ABB8C1" activeColor="#FFFFFF" :bold="true" :fontSize="30" :badgeOffset="[10, 30]"
          @change="tabChange" backgroundColor="#FFFFFF00" :height="60"></tn-tabs>
      </view>
      
      <!-- 天 -->
      <view v-if="current==0" class="">
        
        <view class="tn-padding-bottom-xl wallet-shadow" style="min-height: 500rpx;max-height: 500rpx;margin: 30rpx 40rpx 0rpx 40rpx;overflow: hidden;background-color: #FFFFFF;">
          <qiun-data-charts canvas2d type="column" :opts="totalOpts" :chartData="totalChartData" background="#FFFFFF" />
        </view>
        
        <view class="tn-flex tn-margin-sm">
          <view class="tn-flex-1 wallet-shadow tn-bg-white tn-margin-sm" style="padding: 30rpx 0;" @click="tn('')">
            <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
              <view class="icon20__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-cool-bg-color-5 tn-color-white">
                <view class="tn-icon-meteor-fill"></view>
              </view>  
              <view class="tn-text-center" style="font-size: 30rpx;color: #48505B;">
                <view class="tn-text-ellipsis tn-text-bold">Buy TNN</view>
              </view>
            </view>
          </view>
          <view class="tn-flex-1 wallet-shadow tn-bg-white tn-margin-sm" style="padding: 30rpx 0;" @click="tn('')">
            <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
              <view class="icon20__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-cool-bg-color-5 tn-color-white">
                <view class="tn-icon-rocket-fill"></view>
              </view>  
              <view class="tn-text-center" style="font-size: 30rpx;color: #48505B;">
                <view class="tn-text-ellipsis tn-text-bold">Sell TNN</view>
              </view>
            </view>
          </view>
        </view>
        
      </view>
      
      <!-- 周 -->
      <view v-if="current==1" class="">
        
        <view class="tn-padding-bottom-xl wallet-shadow" style="min-height: 500rpx;max-height: 500rpx;margin: 30rpx 40rpx 0rpx 40rpx;overflow: hidden;background-color: #FFFFFF;">
          <qiun-data-charts canvas2d type="column" :opts="totalOpts" :chartData="totalChartData" background="#FFFFFF" />
        </view>
        
        <view class="tn-flex tn-margin-sm">
          <view class="tn-flex-1 wallet-shadow tn-bg-white tn-margin-sm" style="padding: 30rpx 0;" @click="tn('')">
            <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
              <view class="icon20__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-cool-bg-color-5 tn-color-white">
                <view class="tn-icon-meteor-fill"></view>
              </view>  
              <view class="tn-text-center" style="font-size: 30rpx;color: #48505B;">
                <view class="tn-text-ellipsis tn-text-bold">Buy TNN</view>
              </view>
            </view>
          </view>
          <view class="tn-flex-1 wallet-shadow tn-bg-white tn-margin-sm" style="padding: 30rpx 0;" @click="tn('')">
            <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
              <view class="icon20__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-cool-bg-color-5 tn-color-white">
                <view class="tn-icon-rocket-fill"></view>
              </view>  
              <view class="tn-text-center" style="font-size: 30rpx;color: #48505B;">
                <view class="tn-text-ellipsis tn-text-bold">Sell TNN</view>
              </view>
            </view>
          </view>
        </view>
        
      </view>
      
      <!-- 月-->
      <view v-if="current==2" class="">
        
        <view class="tn-padding-bottom-xl wallet-shadow" style="min-height: 500rpx;max-height: 500rpx;margin: 30rpx 40rpx 0rpx 40rpx;overflow: hidden;background-color: #FFFFFF;">
          <qiun-data-charts canvas2d type="column" :opts="totalOpts" :chartData="totalChartData" background="#FFFFFF" />
        </view>
        
        <view class="tn-flex tn-margin-sm">
          <view class="tn-flex-1 wallet-shadow tn-bg-white tn-margin-sm" style="padding: 30rpx 0;" @click="tn('')">
            <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
              <view class="icon20__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-cool-bg-color-5 tn-color-white">
                <view class="tn-icon-meteor-fill"></view>
              </view>  
              <view class="tn-text-center" style="font-size: 30rpx;color: #48505B;">
                <view class="tn-text-ellipsis tn-text-bold">Buy TNN</view>
              </view>
            </view>
          </view>
          <view class="tn-flex-1 wallet-shadow tn-bg-white tn-margin-sm" style="padding: 30rpx 0;" @click="tn('')">
            <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
              <view class="icon20__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-cool-bg-color-5 tn-color-white">
                <view class="tn-icon-rocket-fill"></view>
              </view>  
              <view class="tn-text-center" style="font-size: 30rpx;color: #48505B;">
                <view class="tn-text-ellipsis tn-text-bold">Sell TNN</view>
              </view>
            </view>
          </view>
        </view>
        
      </view>
      
      <!-- 年-->
      <view v-if="current==3" class="">
        
        <view class="tn-padding-bottom-xl wallet-shadow" style="min-height: 500rpx;max-height: 500rpx;margin: 30rpx 40rpx 0rpx 40rpx;overflow: hidden;background-color: #FFFFFF;">
          <qiun-data-charts canvas2d type="column" :opts="totalOpts" :chartData="totalChartData" background="#FFFFFF" />
        </view>
        
        <view class="tn-flex tn-margin-sm">
          <view class="tn-flex-1 wallet-shadow tn-bg-white tn-margin-sm" style="padding: 30rpx 0;" @click="tn('')">
            <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
              <view class="icon20__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-cool-bg-color-5 tn-color-white">
                <view class="tn-icon-meteor-fill"></view>
              </view>  
              <view class="tn-text-center" style="font-size: 30rpx;color: #48505B;">
                <view class="tn-text-ellipsis tn-text-bold">Buy TNN</view>
              </view>
            </view>
          </view>
          <view class="tn-flex-1 wallet-shadow tn-bg-white tn-margin-sm" style="padding: 30rpx 0;" @click="tn('')">
            <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
              <view class="icon20__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-cool-bg-color-5 tn-color-white">
                <view class="tn-icon-rocket-fill"></view>
              </view>  
              <view class="tn-text-center" style="font-size: 30rpx;color: #48505B;">
                <view class="tn-text-ellipsis tn-text-bold">Sell TNN</view>
              </view>
            </view>
          </view>
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
    data(){
      return {
        barStyle: {
          borderRadius: '100rpx',
          backgroundColor: '#FF1C40'
        },
        activeItemStyle: {
          borderRadius: '100rpx',
          // border: "1rpx solid #1D1F24",
          backgroundColor: '#ABB8C1',
          margin: "30rpx",
        },
        inactiveItemStyle: {
          borderRadius: '100rpx',
          // border: "1rpx solid #1D1F24",
          margin: "30rpx",
        },
        current: 1,
        fixedList: [
          {name: 'Day'},
          {name: 'Week'},
          {name: 'Month'},
          {name: 'Year'}
        ],
        
        // 访问来源
        totalChartData: {},
        totalOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [30, 10, 20, 20],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
            axisLineColor: "#FFFFFF",
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.6)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              axisLineColor: "#FFFFFF",
              min: 0,
              max: 200
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
              width: 24,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
              barBorderRadius: [16,16,16,16]
            }
          },
        },
        
        
      }
    },
    onReady() {
      this.drawTotalCharts();  //访问来源
    },
    methods: {
      // tab选项卡切换
      tabChange(index) {
        this.current = index
      },
      
      // 访问来源 绘制
      drawTotalCharts() {
        let res = {
          categories: [
            "微信",
            "抖音",
            "快手",
            "其他",
          ],
          series: [{
              name: "访问来源",
              data: [{"value":129,"color":"#00D05E"}, {"value":168,"color":"#FFAC00"},{"value":116,"color":"#FB6A67"}, {"value":46,"color":"#957BFE"}],
              legendShape: "circle",
            },
          ],
        };
        this.totalChartData = JSON.parse(JSON.stringify(res));
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
  
  .bg-gray{
    background-color: #F3F4F8;
    min-height: 100vh;
  }
  
  /* 页面 start*/
  .wallet-shadow {
    border-radius: 40rpx;
    box-shadow: 0rpx 6rpx 50rpx 0rpx rgba(0, 0, 0, 0.07);
  }
  
  .icon20 {
    &__item {
      width: 30%;
      background-color: #FFFFFF;
      border-radius: 10rpx;
      padding: 30rpx;
      margin: 20rpx 10rpx;
      transform: scale(1);
      transition: transform 0.3s linear;
      transform-origin: center center;
      
      &--icon {
        width: 90rpx;
        height: 90rpx;
        font-size: 50rpx;
        border-radius: 50%;
        margin-bottom: 18rpx;
        position: relative;
        z-index: 1;
        
        &::after {
          content: " ";
          position: absolute;
          z-index: -1;
          width: 100%;
          height: 100%;
          left: 0;
          bottom: 0;
          border-radius: inherit;
          opacity: 1;
          transform: scale(1, 1);
          background-size: 100% 100%;
          background-image: url(https://resource.tuniaokj.com/images/cool_bg_image/icon_bg.png);
        }
      }
    }
  }
  
</style>
