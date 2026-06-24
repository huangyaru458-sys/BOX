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
            年度词云
          </view>
          <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="year">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{date}}年</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="word" :opts="wordOpts" :chartData="wordChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            年度词云
          </view>
          <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="year">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{date}}年</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="word" :opts="wordOpts1" :chartData="wordChartData1" />
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
        date: '2024',
        
        // 年度词云
        wordChartData: {},
        wordOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: undefined,
          dataLabel: true,
          enableScroll: false,
          extra: {
            word: {
              type: "normal",
              autoColors: false
            }
          }
        },
        
        // 年度词云
        wordChartData1: {},
        wordOpts1: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: undefined,
          dataLabel: true,
          enableScroll: false,
          extra: {
            word: {
              type: "vertical",
              autoColors: false
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
      this.drawWordCharts();  //年度词云
      this.drawWordCharts1();  //年度词云
    },
    mounted() {
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
      
      // 年度词云 绘制
      drawWordCharts() {
        let res = {
            series: [
              {
                name: "图鸟UI",
                textSize: 25,
                data: undefined
              },
              {
                name: "uniapp",
                textSize: 20,
                data: undefined
              },
              {
                name: "微信小程序",
                textSize: 20,
                data: undefined
              },
              {
                name: "H5",
                textSize: 20,
                data: undefined
              },
              {
                name: "APP",
                textSize: 20,
                data: undefined
              },
              {
                name: "vue2",
                textSize: 20,
                data: undefined
              },
              {
                name: "vue3",
                textSize: 20,
                data: undefined
              },
              {
                name: "组件库",
                textSize: 20,
                data: undefined
              },
              {
                name: "UI框架",
                textSize: 10,
                data: undefined
              },
              {
                name: "简约",
                textSize: 12,
                data: undefined
              },
              {
                name: "酷炫",
                textSize: 10,
                data: undefined
              },
              {
                name: "开源",
                textSize: 12,
                data: undefined
              },
              {
                name: "生态",
                textSize: 10,
                data: undefined
              },
              {
                name: "前端",
                textSize: 12,
                data: undefined
              },
              {
                name: "共赢",
                textSize: 12,
                data: undefined
              },
              {
                name: "合作",
                textSize: 12,
                data: undefined
              },
              {
                name: "uCharts",
                textSize: 16,
                data: undefined
              },
              {
                name: "图表",
                textSize: 12,
                data: undefined
              }
            ]
          };
        this.wordChartData = JSON.parse(JSON.stringify(res));
      },
      
      
      // 年度词云 绘制
      drawWordCharts1() {
        let res = {
            series: [
              {
                name: "图鸟UI",
                textSize: 25,
                data: undefined
              },
              {
                name: "uniapp",
                textSize: 20,
                data: undefined
              },
              {
                name: "微信小程序",
                textSize: 20,
                data: undefined
              },
              {
                name: "H5",
                textSize: 20,
                data: undefined
              },
              {
                name: "APP",
                textSize: 20,
                data: undefined
              },
              {
                name: "vue2",
                textSize: 20,
                data: undefined
              },
              {
                name: "vue3",
                textSize: 20,
                data: undefined
              },
              {
                name: "组件库",
                textSize: 20,
                data: undefined
              },
              {
                name: "UI框架",
                textSize: 10,
                data: undefined
              },
              {
                name: "简约",
                textSize: 12,
                data: undefined
              },
              {
                name: "酷炫",
                textSize: 10,
                data: undefined
              },
              {
                name: "开源",
                textSize: 12,
                data: undefined
              },
              {
                name: "生态",
                textSize: 10,
                data: undefined
              },
              {
                name: "前端",
                textSize: 12,
                data: undefined
              },
              {
                name: "共赢",
                textSize: 12,
                data: undefined
              },
              {
                name: "合作",
                textSize: 12,
                data: undefined
              },
              {
                name: "uCharts",
                textSize: 16,
                data: undefined
              },
              {
                name: "图表",
                textSize: 12,
                data: undefined
              }
            ]
          };
        this.wordChartData1 = JSON.parse(JSON.stringify(res));
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