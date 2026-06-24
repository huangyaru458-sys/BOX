<template>
  <view class="template-content">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar :isBack="false" :bottomShadow="false" backgroundColor="#FFFFFF00">
      <view class="custom-nav tn-flex tn-flex-col-center tn-flex-row-left">
        <view class="custom-nav__back">
          <text class="">考勤统计</text>
        </view>
      </view>
    </tn-nav-bar>
    
    <!-- 模拟器上，图表是显示在最上层挡住很多东西，真机是没有问题的，因为加了canvas2d处理 -->
    <!-- 如因一次性加载太多太多，所以会慢，也因懒得写延时加载，所以实际应用中自行延时处理 -->
    
    <view class="home-fixed">
     
    </view>
    
    <view class="" :style="{paddingTop: vuex_custom_bar_height + 'px'}">
      
      <view class="tn-margin" style="border-radius: 20rpx;background-color: #00000005;">
        <view class="tn-padding tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="tn-text-xl tn-text-bold">
            23,895
          </view>
          <view class="">
            <text class="tn-icon-up-arrow tn-padding-right-xs"></text>
            <text>18%</text>
          </view>
        </view>
      </view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            考勤打卡
          </view>
          <picker @change="bindPickerChange" :value="index" :range="array">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{array[index]}}</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="column" :opts="activeOpts" :chartData="activeChartData" />
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
        index: 0,
        array: ['上周', '本周'],
        
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
            disabled: true,
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
              type: "stack",
              width: 5,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
            }
          },
        },
        
        
      }
    },
    onReady() {
      this.drawActiveCharts();  //活跃用户
    },
    methods: {
      bindPickerChange: function(e) {
        this.index = e.detail.value
      },
      
      // 活跃用户 绘制
      drawActiveCharts() {
        let res = {
            categories: ["周一","周二","周三","周四","周五","周六","周日"],
            series: [
              {
                name: "准时",
                data: [42,46,33,36,32,38,38],
                legendShape: "circle",
                color: "#6729FF"
              },
              {
                name: "踩点",
                data: [38,27,42,24,42,46,46],
                legendShape: "circle",
                color: "#B2B2F2"
              },
              {
                name: "迟到",
                data: [20,27,25,40,26,16,16],
                legendShape: "circle",
                color: "#E6E6E6"
              }
            ]
          };
        this.activeChartData = JSON.parse(JSON.stringify(res));
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
  
  // 四个角渐变底色
  .home-fixed{
    position: fixed;
    background: linear-gradient(90deg, #FFFFFF, #B2B2F2);
    top: 0;
    width: 100%;
    transition: all 0.25s ease-out;
    z-index: -1;
    min-height: 20vh;
  }
  .home-fixed:before{
    content: "";
    position: absolute;
    top: 0;
    left: 0;
    bottom: 0;
    right: 0;
    z-index: -1;
    mask-image: linear-gradient(to bottom, transparent, black);
    background: linear-gradient(90deg, #FFFFFF, #FFFFFF);	
  
  }
</style>
