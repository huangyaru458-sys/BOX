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
            员工年龄
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">员工总数：23人</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="scatter" :opts="ageOpts" :chartData="ageChartData" />
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
        
        // 员工年龄
        ageChartData: {},
        ageOpts: {
          color: ["#4B98FE","#FB6A67","#FFAC00","#00D05E","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15,15,0,15],
          dataLabel: false,
          enableScroll: false,
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
            // show: true,
            // position: "top",
            // float: "right",
            lineHeight: 25
          },
          extra: {
            scatter: {}
          }
        },
        
      };
    },
    onShow() {
    },
    onLoad() {
    },
    onReady() {
      this.drawAgeCharts();  //员工年龄
    },
    mounted() {
    },
    methods: {
      
      // 员工年龄 绘制
      drawAgeCharts() {
        let res = {
            series: [
              {
                name: "男员工年龄工龄",
                data: [[1.5,24],[3.9,36],[6.3,52],[3.3,36],[1.7,26],[7.2,42],[5.0,38],[8.3,51],[1.2,39],[0.6,28],[9.1,48]]
              },
              {
                name: "女员工年龄工龄",
                data: [[4.3,26],[2.4,26],[5.2,43],[0.5,24],[6.6,54],[3.2,31],[8.0,43],[5.4,37],[2.9,42],[4.6,32],[5.1,46],[7.2,38]]
              }
            ]
          };
        this.ageChartData = JSON.parse(JSON.stringify(res));
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