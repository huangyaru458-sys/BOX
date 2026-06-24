<template>
  <view class="template-content tn-safe-area-inset-bottom">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed alpha customBack>
      <view slot="back" class='tn-custom-nav-bar__back'
        @click="goBack">
        <text class='icon tn-icon-left'></text>
        <text class='icon tn-icon-home-capsule-fill'></text>
      </view>
    </tn-nav-bar>
    
    <!-- 模拟器上，图表是显示在最上层挡住很多东西，真机是没有问题的，因为加了canvas2d处理 -->
    <!-- 如因一次性加载太多太多，所以会慢，也因懒得写延时加载，所以实际应用中自行延时处理 -->
    
    <view class="top-fixed" :style="{paddingTop: vuex_custom_bar_height + 20 + 'px'}">
      <view class="tn-text-center" style="position: absolute;top: 60rpx;right:0;font-size: 400rpx;opacity: 0.06;">
        <view class="tn-icon-rocket-fill tn-color-white"></view>
      </view>
      <view class="" style="z-index: 9999;">
        <tn-tabs :list="fixedList" :current="current" :isScroll="false" activeColor="#FFFFFF" inactiveColor="#FFFFFF80" :bold="true" :fontSize="32" :badgeOffset="[20, 50]" @change="tabChange"></tn-tabs>
      </view>
    </view>
    
    <view class="tn-padding-bottom-xl" v-if="current==0" :style="{paddingTop: vuex_custom_bar_height + 70 + 'px'}">
      
      <view class="tn-margin" style="background-color: #3724BE;border-radius: 15rpx">
        <view class="tn-padding-left-sm tn-padding-bottom tn-padding-top-xl tn-text-center tn-color-white">
          <view class="">账户总金额</view>
          <view class="tn-padding-top">
            <text class="tn-padding-right-sm" style="margin-left: -20rpx;">￥</text>
            <text class="tn-text-bold" style="font-size:70rpx">12,812.08</text>
          </view>
          <view class="tn-padding-top tn-text-center">
            <view class="tn-flex tn-flex-row-between tn-flex-col-center">
              <view class="justify-content-item tn-flex-1">
                <view class="tn-text-sm">交易笔数</view>
                <view class="tn-text-xl tn-text-bold tn-padding-top-xs">20,362</view>
              </view>
              <view class="justify-content-item tn-flex-1">
                <view class="tn-text-sm">交易人数</view>
                <view class="tn-text-xl tn-text-bold tn-padding-top-xs">206</view>
              </view>
            </view>
          </view>
          <!-- <view class="tn-margin-top-sm tn-text-sm" style="opacity: 0.5;">
            <text>收款记录</text>
            <text class="tn-icon-right tn-padding-left-xs"></text>
          </view> -->
        </view>
      </view>
    
      
      <view class="tn-flex tn-flex-row-between tn-flex-col-center tn-padding-top">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          账单记录
        </view>
        <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <text class="tn-padding-left-xs tn-padding-right-xs">23年7月 - 24年3月</text>
          <text class="tn-icon-down tn-padding-right-xs"></text>
        </view>
      </view>
      
      
      <view class="tn-flex tn-flex-col-center" style="margin: 50rpx 30rpx;" v-for="(item,index) in 12" :key="index" @click="tn('')">
        <view class="logo-pic" style="background-image:url('https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1693830798032-assets/web-upload/aa49b472-f60a-45cc-83cb-d56255e21a96.jpeg');width: 80rpx;height: 80rpx;background-size: cover;">
          <view class="logo-image">
          </view>
        </view>
        <view class="tn-padding-left-sm" style="width: 67vw">
          <view class="tn-flex tn-flex-row-between tn-flex-col-between">
            <view class="justify-content-item">
              <text class="tn-text-lg tn-text-bold">不许凶我吖</text>
            </view>
          </view>
          <view class="tn-padding-top-xs tn-text-ellipsis tn-text-sm">
            <text class="tn-color-gray">2024-09-23 12:26</text>
          </view>
        </view>
        <view class="" style="width: 35vw;">
          <view class="tn-flex tn-flex-row-right tn-margin-bottom-xs">
            <text class="tn-text-lg tn-text-bold">+ 129.68</text>
          </view>
          <view class="tn-flex tn-flex-row-right tn-color-gray tn-text-sm">
            余额 12,812.08
          </view>
        </view>
      </view>
      
      <view class="tn-flex tn-flex-col-center" style="margin: 50rpx 30rpx;" @click="tn('')">
        <view class="">
          <view class="icon15__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-color-white" style="background-color: #3724BE;">
            <view class="tn-icon-money"></view>
          </view>
        </view>
        <view class="tn-padding-left-sm" style="width: 67vw">
          <view class="tn-flex tn-flex-row-between tn-flex-col-between">
            <view class="justify-content-item">
              <text class="tn-text-lg tn-text-bold">未知用户</text>
            </view>
          </view>
          <view class="tn-padding-top-xs tn-text-ellipsis tn-text-sm">
            <text class="tn-color-gray">2023-09-22 20:06</text>
          </view>
        </view>
        <view class="" style="width: 35vw;">
          <view class="tn-flex tn-flex-row-right tn-margin-bottom-xs" style="color: #FB6A67;">
            <text class="tn-text-lg tn-text-bold">- 3,189.29</text>
          </view>
          <view class="tn-flex tn-flex-row-right tn-color-gray tn-text-sm">
            余额 12,812.08
          </view>
        </view>
      </view>
      
      
    </view>
    
    <view class="" v-if="current==1" :style="{paddingTop: vuex_custom_bar_height + 50 + 'px'}">
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            投资理财
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">23年7月 - 24年3月</text>
            <text class="tn-icon-down tn-padding-right-xs"></text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="line" :opts="investOpts" :chartData="investChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            收支数据
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">23年7月 - 24年3月</text>
            <text class="tn-icon-down tn-padding-right-xs"></text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="line" :opts="economyOpts" :chartData="economyChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            收支对比
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">23年7月 - 24年6月</text>
            <text class="tn-icon-down tn-padding-right-xs"></text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="ring" :opts="makeupOpts" :chartData="makeupChartData" />
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
        current: 0,
        fixedList: [
          {name: '账单明细'},
          {name: '资产统计'},
        ],
        
        // 投资理财
        investChartData: {},
        investOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          dataPointShape: false,
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
            show: false,
            position: "top",
            float: "right",
          },
          extra: {
            line: {
              type: "curve",
              width: 2,
              activeType: "hollow",
              linearType: "custom",
              onShadow: true,
            },
          },
        },
        
        // 经济情况
        economyChartData: {},
        economyOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          dataPointShape: false,
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
            show: false,
            position: "top",
            float: "right",
          },
          extra: {
            line: {
              type: "curve",
              width: 2,
              activeType: "hollow"
            },
          },
        },
        
        // 收支对比
        makeupChartData: {},
        makeupOpts: {
          rotate: false,
          rotateLock: false,
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15,10,15,10],
          dataLabel: true,
          enableScroll: false,
          legend: {
            show: false,
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
            fontSize: 22,
            color: "#666666"
          },
          extra: {
            tooltip: {
              showBox: false
            },
            ring: {
              ringWidth: 30,
              activeOpacity: 0.5,
              activeRadius: 10,
              offsetAngle: -30,
              labelWidth: 15,
              border: true,
              borderWidth: 2,
              borderColor: "#FFFFFF",
              // linearType: "custom"
            }
          }
        },
        
      }
    },
    onReady() {
      this.drawInvestCharts();  //投资理财
      this.drawEconomyCharts();  //收支数据
      this.drawMakeupCharts();  //收支对比
    },
    methods: {
      // tab选项卡切换
      tabChange(index) {
        this.current = index
      },
      
      // 跳转
      tn(e) {
      	uni.navigateTo({
      		url: e,
      	});
      },
      
      // 投资理财 绘制
      drawInvestCharts() {
        let res = {
          categories: [
            "7月",
            "8月",
            "9月",
            "10月",
            "11月",
            "12月",
            "1月",
            "2月",
            "3月",
          ],
          series: [{
              name: "投资理财",
              data: [990, 1293, 1062, 1457, 1232, 1443, 1321, 1438, 1689],
              legendShape: "circle",
              linearColor: [[0,"#FFAC00"],[0.25,"#FE871B"],[0.5,"#FB6A67"],[0.75,"#F674D6"],[1,"#957BFE"]],
            },
          ],
        };
        this.investChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 经济情况 绘制
      drawEconomyCharts() {
        let res = {
          categories: [
            "7月",
            "8月",
            "9月",
            "10月",
            "11月",
            "12月",
            "1月",
            "2月",
            "3月",
          ],
          series: [{
              name: "收入",
              data: [1800, 1668, 1508, 1900, 1588, 1880, 1700, 1777, 1760],
              legendShape: "circle",
              color: "#4B98FE",
            },
            {
              name: "支出",
              data: [1290, 1293, 1262, 1557, 1689, 1432, 1643, 1321, 1438],
              legendShape: "circle",
              color: "#FFAC00",
            },
          ],
        };
        this.economyChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 收支对比 绘制
      drawMakeupCharts() {
        let res = {
          series: [
            {
              data: [{"name":"支出","value":12.9,"color":"#FFD374","labelText":"支出 12.9万元"},{"name":"收入","value":36,"color":"#FFAC00","labelText":"收入 36万元"}]
            }
          ]
        };
        this.makeupChartData = JSON.parse(JSON.stringify(res));
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
    position: fixed;
    background: linear-gradient(90deg, #3724BE, #3724BE);
    box-shadow: 0rpx 0rpx 30rpx 0rpx rgba(0, 0, 0, 0.07);
    top: 0;
    width: 100%;
    transition: all 0.25s ease-out;
    z-index: 100;
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
  
  /* 图标容器15 start */
  .icon15 {
    &__item {
      width: 30%;
      background-color: #FFFFFF;
      padding: 30rpx;
      margin: 20rpx 10rpx;
      transform: scale(1);
      transition: transform 0.3s linear;
      transform-origin: center center;
      
      &--icon {
        width: 80rpx;
        height: 80rpx;
        font-size: 50rpx;
        border-radius: 50%;
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
        }
      }
    }
  }
  
  /* 用户头像 start */
  .logo-image{
    width: 80rpx;
    height: 80rpx;
    position: relative;
  }
  
  .logo-pic{
    background-size: cover;
    background-repeat:no-repeat;
    background-position: center;
    border-radius: 100rpx;
  }
  
</style>
