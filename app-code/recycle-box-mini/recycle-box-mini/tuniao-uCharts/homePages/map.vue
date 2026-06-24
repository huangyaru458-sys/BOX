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
            员工分布
          </view>
          <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="year">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{date}}年</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        
        <!-- 旧展示方式 -->
        <!-- <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin-left tn-color-gray--dark" style="width: 350rpx;">
            <view class="tn-padding-top-sm">广东：129人</view>
            <view class="tn-padding-top-sm">河南：86人</view>
            <view class="tn-padding-top-sm">江西：60人</view>
            <view class="tn-padding-top-sm">湖南：32人</view>
            <view class="tn-padding-top-sm">其他：6人</view>
          </view>
          <view class="justify-content-item tn-margin-right" style="max-height: 350rpx;min-height: 350rpx;width: 400rpx;">
            <qiun-data-charts canvas2d type="map" :opts="placeOpts" :chartData="placeChartData" />
          </view>
        </view> -->
        
        <!-- 新展示方式 -->
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="placeOpts" :chartData="placeChartData" />
        </view>
      
      </view>
      
      <view class="tn-strip-bottom"></view>
      
    </view>
      
  </view>
</template>

<script>
  import template_page_mixin from '@/libs/mixin/template_page_mixin.js'
  import mapdata from '@/mockdata/mapdata.json'
  export default {
    mixins: [template_page_mixin],
    data() {
      return {
        date: '2024',
        
        // 员工分布
        placeChartData: {},
        placeOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [0,15,0,0],
          dataLabel: false,
          enableScroll: false,
          extra: {
            map: {
              mercator: true,
              border: true,
              borderWidth: 0.4,
              borderColor: "#AAAAAA",
              fillOpacity: 0.5,
              activeBorderColor: "#FFFFFF",
              activeFillColor: "#4B98FE",
              activeFillOpacity: 1
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
      this.drawPlaceCharts();  //员工分布
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
      
      // 员工分布 绘制
      drawPlaceCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.placeChartData = {series:mapdata.features};
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