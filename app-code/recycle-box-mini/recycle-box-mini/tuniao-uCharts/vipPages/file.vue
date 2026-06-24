<template>
  <view class="template-content">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed alpha customBack>
      <view slot="back" class='tn-custom-nav-bar__back'
        @click="goBack">
        <text class='icon tn-icon-left'></text>
        <text class='icon tn-icon-home-capsule-fill'></text>
      </view>
    </tn-nav-bar>
    
    
    <view class="tn-margin" :style="{paddingTop: vuex_custom_bar_height + 'px'}">
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <!-- <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            存储空间
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">清理加速</text>
            <text class="tn-icon-clear tn-padding-right-xs"></text>
          </view>
        </view> -->
        <view class="" style="min-height: 500rpx;">
          <qiun-data-charts canvas2d type="ring" :opts="makeupOpts" :chartData="makeupChartData" />
        </view>

        <view class="tn-flex tn-flex-row-between tn-strip-bottom-min tn-padding tn-margin-top-xs" v-for="(item, index) in fileList" :key="index" @click="tn('')">
          <view class="justify-content-item">
            <view class="tn-text-lg">
              <text class="tn-icon-circle-fill tn-padding-right-xs" :style="'color:'+ item.color +';'"></text>
              {{ item.title }}
            </view>
          </view>
          <view class="justify-content-item tn-color-gray">
            <view class="">{{ item.name }} GB</view>
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
        // 营收占比
        makeupChartData: {},
        makeupOpts: {
          rotate: false,
          rotateLock: false,
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#F8F7F8"],
          padding: [15,10,15,10],
          dataLabel: false,
          enableScroll: false,
          legend: {
            show: false,
            position: "left",
            lineHeight: 32
          },
          title: {
            name: "46%",
            fontSize: 32,
            color: "#000"
          },
          subtitle: {
            name: "已使用 235GB / 512GB",
            fontSize: 10,
            color: "#AAAAAA",
            offsetY: 10
          },
          extra: {
            ring: {
              ringWidth: 30,
              activeOpacity: 0.5,
              activeRadius: 10,
              offsetAngle: -90,
              labelWidth: 15,
              border: true,
              borderWidth: 0,
              borderColor: "#FFFFFF",
              // linearType: "custom"
            }
          }
        },
        
        fileList: [
        	{
        		title: "图片",
            name: "11.57",
            icon: 'location-fill',
            color: '#4B98FE',
            url: ""
        	},
        	{
        		title: "视频",
            name: "30.68",
            icon: 'location-fill',
            color: '#00D05E',
            url: ""
        	},
        	{
        		title: "音频",
            name: "2.32",
            icon: 'location-fill',
            color: '#FFAC00',
            url: ""
        	},
          {
          	title: "文档",
            name: "9.57",
            icon: 'location-fill',
            color: '#FB6A67',
            url: ""
          },
        	{
        		title: "压缩包",
            name: "6.87",
            icon: 'location-fill',
            color: '#957BFE',
            url: ""
        	},
          {
          	title: "安装包",
            name: "8.08",
            icon: 'location-fill',
            color: '#00B9FE',
            url: ""
          },
          {
          	title: "应用",
            name: "62.23",
            icon: 'location-fill',
            color: '#FE871B',
            url: ""
          }
        ]
        
      }
    },
    onReady() {
      this.drawMakeupCharts();  //营收占比
    },
    methods: {
      // 跳转
      tn(e) {
      	uni.navigateTo({
      		url: e,
      	});
      },
      
      // 营收占比 绘制
      drawMakeupCharts() {
        let res = {
          series: [
            {
              data: [{"name":"图片","value":11.57},{"name":"视频","value":30.68},{"name":"音频","value":2.32},{"name":"文档","value":9.57},{"name":"压缩包","value":6.87},{"name":"安装包","value":8.08},{"name":"应用","value":62.23},{"name":"剩余","value":180}]
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
  
  /* 间隔线 start*/
  .tn-strip-bottom-min {
    width: 100%;
    border-bottom: 1rpx solid #F8F9FB;
  }
  
  .tn-strip-bottom {
   width: 100%;
   border-top: 20rpx solid rgba(241, 241, 241, 0.8);
  }
   /* 间隔线 end*/
</style>
