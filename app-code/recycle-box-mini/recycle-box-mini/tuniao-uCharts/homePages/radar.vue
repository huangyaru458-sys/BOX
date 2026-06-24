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
            员工能力
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">技术总监 vs 财务总监</text>
            <text class="tn-icon-down tn-padding-right-xs"></text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="radar" :opts="abilityOpts" :chartData="abilityChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            员工能力
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">技术总监 vs 财务总监</text>
            <text class="tn-icon-down tn-padding-right-xs"></text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="radar" :opts="abilityOpts1" :chartData="abilityChartData1" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            员工能力
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">打杂总监</text>
            <text class="tn-icon-down tn-padding-right-xs"></text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="radar" :opts="abilityOpts2" :chartData="abilityChartData2" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            员工能力
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">打杂总监</text>
            <text class="tn-icon-down tn-padding-right-xs"></text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="radar" :opts="abilityOpts3" :chartData="abilityChartData3" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            员工能力
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">打杂总监</text>
            <text class="tn-icon-down tn-padding-right-xs"></text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="radar" :opts="abilityOpts4" :chartData="abilityChartData4" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            员工能力
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">打杂总监</text>
            <text class="tn-icon-down tn-padding-right-xs"></text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="radar" :opts="abilityOpts5" :chartData="abilityChartData5" />
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
        
        // 员工能力
        abilityChartData: {},
        abilityOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15,10,15,10],
          dataLabel: false,
          enableScroll: false,
          legend: {
            show: true,
            position: "left",
            lineHeight: 32
          },
          extra: {
            radar: {
              gridType: "circle",
              gridColor: "#E6E6E6",
              gridCount: 2,
              opacity: 0.2,
              max: 100,
              labelShow: true
            }
          }
        },
        
        // 员工能力
        abilityChartData1: {},
        abilityOpts1: {
          color: ["#FB6A67","#957BFE","#4B98FE","#00D05E","#FFAC00","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15,10,15,10],
          dataLabel: false,
          enableScroll: false,
          legend: {
            show: true,
            position: "left",
            lineHeight: 32
          },
          extra: {
            radar: {
              gridType: "radar",
              gridColor: "#E6E6E6",
              gridCount: 2,
              opacity: 0.2,
              max: 100,
              labelShow: true
            }
          }
        },
        
        // 员工能力
        abilityChartData2: {},
        abilityOpts2: {
          color: ["#00D05E","#957BFE","#4B98FE","#00C8B0","#FFAC00","#00B9FE","#FE871B","#FB6A67","#F674D6"],
          padding: [15,10,15,10],
          dataLabel: false,
          dataPointShape: false,
          enableScroll: false,
          legend: {
            show: false,
            position: "top",
            lineHeight: 32
          },
          extra: {
            radar: {
              gridType: "circle",
              gridColor: "#E6E6E6",
              gridCount: 4,
              opacity: 0.08,
              max: 100,
              labelShow: true,
              border: true
            }
          }
        },
        
        // 员工能力
        abilityChartData3: {},
        abilityOpts3: {
          color: ["#FE871B","#957BFE","#4B98FE","#00D05E","#FFAC00","#00B9FE","#00C8B0","#FB6A67","#F674D6"],
          padding: [15,10,15,10],
          dataLabel: false,
          dataPointShape: false,
          enableScroll: false,
          legend: {
            show: false,
            position: "top",
            lineHeight: 32
          },
          extra: {
            radar: {
              gridType: "radar",
              gridColor: "#E6E6E6",
              gridCount: 4,
              opacity: 0.08,
              max: 100,
              labelShow: true,
              border: true
            }
          }
        },
        
        // 员工能力
        abilityChartData4: {},
        abilityOpts4: {
          color: ["#00B9FE","#957BFE","#4B98FE","#00D05E","#FFAC00","#FE871B","#00C8B0","#FB6A67","#F674D6"],
          padding: [15,10,15,10],
          dataLabel: false,
          dataPointShape: false,
          enableScroll: false,
          legend: {
            show: false,
            position: "top",
            lineHeight: 32
          },
          extra: {
            radar: {
              gridType: "circle",
              gridColor: "#E6E6E6",
              gridCount: 4,
              opacity: 0.08,
              max: 100,
              labelShow: true,
              border: true
            }
          }
        },
        
        // 员工能力
        abilityChartData5: {},
        abilityOpts5: {
          color: ["#FB6A67","#957BFE","#4B98FE","#00D05E","#FFAC00","#00B9FE","#00C8B0","#FE871B","#F674D6"],
          padding: [15,10,15,10],
          dataLabel: false,
          dataPointShape: false,
          enableScroll: false,
          legend: {
            show: false,
            position: "top",
            lineHeight: 32
          },
          extra: {
            radar: {
              gridType: "radar",
              gridColor: "#E6E6E6",
              gridCount: 4,
              opacity: 0.08,
              max: 100,
              labelShow: true,
              border: true
            }
          }
        },
        
      };
    },
    onShow() {
    },
    onLoad() {
    },
    onReady() {
      this.drawAbilityCharts();  //员工能力
      this.drawAbilityCharts1();  //员工能力
      this.drawAbilityCharts2();  //员工能力
      this.drawAbilityCharts3();  //员工能力
      this.drawAbilityCharts4();  //员工能力
      this.drawAbilityCharts5();  //员工能力
    },
    mounted() {
    },
    methods: {
      
      // 员工能力 绘制
      drawAbilityCharts() {
        let res = {
            categories: ["处事","学习","工作","沟通","领导","决策"],
            series: [
              {
                name: "技术总监",
                data: [90,86,99,66,95,93]
              },
              {
                name: "财务总监",
                data: [70,56,99,89,57,69]
              },
              // {
              //   name: "市场总监",
              //   data: [88,76,82,85,71,89]
              // }
            ]
          };
        this.abilityChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 员工能力 绘制
      drawAbilityCharts1() {
        let res = {
            categories: ["处事","学习","工作","沟通","领导","决策"],
            series: [
              {
                name: "技术总监",
                data: [90,86,99,66,95,93]
              },
              {
                name: "财务总监",
                data: [70,56,99,89,57,69]
              },
              // {
              //   name: "市场总监",
              //   data: [88,76,82,85,71,89]
              // }
            ]
          };
        this.abilityChartData1 = JSON.parse(JSON.stringify(res));
      },
      
      // 员工能力 绘制
      drawAbilityCharts2() {
        let res = {
            categories: ["处事","学习","工作","沟通","决策"],
            series: [
              {
                name: "打杂总监",
                data: [66,36,69,26,5]
              }
            ]
          };
        this.abilityChartData2 = JSON.parse(JSON.stringify(res));
      },
      
      // 员工能力 绘制
      drawAbilityCharts3() {
        let res = {
            categories: ["处事","学习","工作","沟通","决策"],
            series: [
              {
                name: "打杂总监",
                data: [66,36,69,26,5]
              }
            ]
          };
        this.abilityChartData3 = JSON.parse(JSON.stringify(res));
      },
      
      // 员工能力 绘制
      drawAbilityCharts4() {
        let res = {
            categories: ["处事","学习","工作","沟通"],
            series: [
              {
                name: "打杂总监",
                data: [40,66,69,66]
              }
            ]
          };
        this.abilityChartData4 = JSON.parse(JSON.stringify(res));
      },
      
      // 员工能力 绘制
      drawAbilityCharts5() {
        let res = {
            categories: ["处事","学习","工作","沟通"],
            series: [
              {
                name: "打杂总监",
                data: [40,66,69,66]
              }
            ]
          };
        this.abilityChartData5 = JSON.parse(JSON.stringify(res));
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