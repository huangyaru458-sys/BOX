<template>
  <view class="template-content bg-gray">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar :isBack="false" :bottomShadow="false" backgroundColor="#FFFFFF00">
      <view class="custom-nav tn-flex tn-flex-col-center tn-flex-row-left">
        <view class="custom-nav__back">
          <text class="">访客统计</text>
        </view>
      </view>
    </tn-nav-bar>
    
    <!-- 模拟器上，图表是显示在最上层挡住很多东西，真机是没有问题的，因为加了canvas2d处理 -->
    <!-- 如因一次性加载太多太多，所以会慢，也因懒得写延时加载，所以实际应用中自行延时处理 -->
    
    <view class="" :style="{paddingTop: vuex_custom_bar_height + 10 + 'px'}">
      
      <view class="tn-margin">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="tn-text-bold">
            <text style="font-size: 70rpx;">495</text>
            <text class="tn-icon-up-arrow tn-padding-left tn-padding-right-xs tn-color-green"></text>
            <text class="tn-color-green">18%</text>
          </view>
          <view class="tn-color-gray">
            <text>今日 12月29日 星期五</text>
          </view>
        </view>
      </view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            访问来源
          </view>
          <picker @change="bindPickerChange" :value="index" :range="array">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-white tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{array[index]}}</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="margin: 30rpx 30rpx 0rpx 30rpx;border-radius: 20rpx;overflow: hidden;background-color: #FFFFFF;">
          <qiun-data-charts canvas2d type="column" :opts="totalOpts" :chartData="totalChartData" background="#FFFFFF" />
        </view>
      </view>
      
      <!-- 回到首页悬浮按钮-->
      <nav-index-button></nav-index-button>
      
    </view>
  </view>
</template>

<script>
  import NavIndexButton from '@/libs/components/nav-index-button.vue'
  import template_page_mixin from '@/libs/mixin/template_page_mixin.js'
  export default {
    name: 'TemplateContent',
    components: {NavIndexButton},
    mixins: [template_page_mixin],
    data(){
      return {
        index: 2,
        array: ['今日', '近七天', '本月'],
        
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
      bindPickerChange: function(e) {
        this.index = e.detail.value
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
  /* 自定义导航栏内容 start */
  .custom-nav {
    height: 100%;
    
    &__back {
      margin: auto 5rpx;
      font-size: 45rpx;
      margin-right: 10rpx;
      margin-left: 30rpx;
      flex-basis: 5%;
    }
  }
  /* 自定义导航栏内容 end */
  
  .bg-gray{
    background-color: #F9F9F9;
    min-height: 100vh;
  }
  
</style>
