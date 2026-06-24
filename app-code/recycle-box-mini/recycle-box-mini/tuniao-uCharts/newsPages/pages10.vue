<template>
  <view class="template-content">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar :isBack="false" :bottomShadow="false" backgroundColor="#FFFFFF00">
      <view class="custom-nav tn-flex tn-flex-col-center tn-flex-row-left">
        <view class="custom-nav__back">
          <text class="">收益来源</text>
        </view>
      </view>
    </tn-nav-bar>
    
    <!-- 模拟器上，图表是显示在最上层挡住很多东西，真机是没有问题的，因为加了canvas2d处理 -->
    <!-- 如因一次性加载太多太多，所以会慢，也因懒得写延时加载，所以实际应用中自行延时处理 -->
    
    <view class="" :style="{paddingTop: vuex_custom_bar_height + 10 + 'px'}">
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            金额数据
          </view>
          <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="year">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{date}}年</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="ring" :opts="makeupOpts" :chartData="makeupChartData" />
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
        date: '2024',
        
        // 营收占比
        makeupChartData: {},
        makeupOpts: {
          rotate: false,
          rotateLock: false,
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15,10,15,10],
          dataLabel: true,
          enableScroll: false,
          legend: {
            show: true,
            position: "left",
            lineHeight: 32
          },
          title: {
            name: "",
            fontSize: 15,
            color: "#666666"
          },
          subtitle: {
            name: "",
            fontSize: 25,
            color: "#4B98FE"
          },
          extra: {
            ring: {
              ringWidth: 12,
              activeOpacity: 0.5,
              activeRadius: 10,
              offsetAngle: 0,
              labelWidth: 15,
              border: false,
              // borderWidth: 2,
              borderColor: "#FFFFFF",
              // linearType: "custom",
            }
          }
        },
        
      }
    },
    onReady() {
      this.drawMakeupCharts();  //营收占比
    },
    methods: {
      // 时间
      startDate() {
        return this.getDate('start');
      },
      endDate() {
        return this.getDate('end');
      },
      
      bindDateChange: function(e) {
          this.date = e.detail.value
      },
      
      // 营收占比 绘制
      drawMakeupCharts() {
        let res = {
          series: [
            {
              data: [{"name":"前端","value":5000,color:"#3F49C2"},{"name":"设计","value":3000,color:"#83D6FE"},{"name":"赞赏","value":2000,color:"#FECE3C"},{"name":"原型","value":1800,color:"#01E4D0"},{"name":"运维","value":900,color:"#FB716F"}]
            }
          ]
        };
        this.makeupChartData = JSON.parse(JSON.stringify(res));
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
  
</style>
