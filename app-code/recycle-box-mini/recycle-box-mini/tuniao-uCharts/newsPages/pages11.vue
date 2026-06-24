<template>
  <view class="template-content">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar :isBack="false" :bottomShadow="false" backgroundColor="#FFFFFF00">
      <view class="custom-nav tn-flex tn-flex-col-center tn-flex-row-left">
        <view class="custom-nav__back">
          <text class="">区域销售</text>
        </view>
      </view>
    </tn-nav-bar>
    
    <!-- 模拟器上，图表是显示在最上层挡住很多东西，真机是没有问题的，因为加了canvas2d处理 -->
    <!-- 如因一次性加载太多太多，所以会慢，也因懒得写延时加载，所以实际应用中自行延时处理 -->
    
    <view class="" :style="{paddingTop: vuex_custom_bar_height + 10 + 'px'}">
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            销售数据
          </view>
          <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="year">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{date}}年</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="mount" :opts="saleOpts" :chartData="saleChartData" />
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
        
        // 区域销售
        saleChartData: {},
        saleOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
            // axisLineColor: "#E6E6E6"
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.6)",
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
            mount: {
              type: "mount",
              widthRatio: 1.8,
              borderWidth: 0.5,
              linearType: "opacity",
              linearOpacity: 0,
            }
          }
        },
        
      }
    },
    onReady() {
      this.drawSaleCharts();  //区域销售
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
      
      // 区域销售 绘制
      drawSaleCharts() {
        let res = {
            series: [
              {
                data: [
                  {"name":"广东","value":82,legendShape: "circle",color:"#456EFD"},
                  {"name":"湖北","value":63,legendShape: "circle",color:"#1CCEA0"},
                  {"name":"河南","value":86,legendShape: "circle",color:"#FF6850"},
                  {"name":"其他","value":79,legendShape: "circle",color:"#FBAF2A"},
                ],
              }
            ],
            
          };
        this.saleChartData = JSON.parse(JSON.stringify(res));
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
