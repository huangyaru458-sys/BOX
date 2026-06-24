<template>
  <view class="template-content">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed customBack :bottomShadow="false" backgroundColor="#05C160">
      <view slot="back" class='tn-custom-nav-bar__back'
        @click="goBack">
        <text class='icon tn-icon-left'></text>
        <text class='icon tn-icon-home-capsule-fill'></text>
      </view>
      <view class="tn-flex tn-flex-col-center tn-flex-row-center ">
        <text class="tn-text-bold tn-text-xl tn-color-white">微信群成员统计</text>
      </view>
    </tn-nav-bar>
    
    <view class="top-fixed" :style="{paddingTop: vuex_custom_bar_height + 'px'}">
      <view class="tn-text-center" style="position: absolute;top: 220rpx;right:30rpx;font-size: 200rpx;opacity: 0.1;">
        <view class="tn-icon-team-fill tn-color-white"></view>
      </view>
      <view class="tn-margin tn-padding-left-sm tn-padding-bottom-xl tn-padding-top tn-color-white">
        <view class="tn-text-sm">
          <text style="opacity: 0.6;">总人数（人）</text>
        </view>
        <view class="tn-text-bold tn-padding-top-xs" style="font-size:70rpx">486</view>
      </view>
      <view class="tn-margin tn-padding-left-sm tn-color-white">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm" style="opacity: 0.6;">日活跃</view>
            <view class="tn-text-lg tn-text-bold tn-padding-top-xs">+68.62%</view>
          </view>
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm" style="opacity: 0.6;">周活跃</view>
            <view class="tn-text-lg tn-text-bold tn-padding-top-xs">+26.09%</view>
          </view>
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm" style="opacity: 0.6;">总活跃</view>
            <view class="tn-text-lg tn-text-bold tn-padding-top-xs">+37.62%</view>
          </view>
        </view>
      </view>
    </view>
    
    <view class="tn-padding-top-xl tn-padding-bottom-xl">
      <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          活跃成员
        </view>
        <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="month">
            <text class="tn-padding-left-xs tn-padding-right-xs">{{date}}</text>
          </picker>
          <view class="tn-icon-sequence">
          </view>
          <picker @change="bindDateChange1" mode="date" :value="date1" :start="startDate1" :end="endDate1" fields="month">
            <text class="tn-padding-left-xs tn-padding-right-xs">{{date1}}</text>
          </picker>
        </view>
      </view>
      <view class="tn-flex tn-flex-row-between tn-flex-col-center tn-margin">
        <view class="justify-content-item">
          <text class="">活跃榜 前十</text>
        </view>
        <view class="justify-content-item">
          <tn-avatar-group :lists="latestUserAvatar" size="df"></tn-avatar-group>
        </view>
      </view>
    </view>
    
    <view class="tn-strip-bottom"></view>
    
    <view class="tn-padding-top-xl tn-padding-bottom-xl">
      <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          性别比例
        </view>
        <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="month">
            <text class="tn-padding-left-xs tn-padding-right-xs">{{date}}</text>
          </picker>
          <view class="tn-icon-sequence">
          </view>
          <picker @change="bindDateChange1" mode="date" :value="date1" :start="startDate1" :end="endDate1" fields="month">
            <text class="tn-padding-left-xs tn-padding-right-xs">{{date1}}</text>
          </picker>
        </view>
      </view>
      <view class="" style="min-height: 500rpx;">
        <qiun-data-charts canvas2d type="ring" :opts="makeupOpts" :chartData="makeupChartData" />
      </view>
    </view>
    
    <view class="tn-strip-bottom"></view>
    
    <view class="tn-padding-top-xl tn-padding-bottom-xl">
      <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          群友年龄
        </view>
        <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="month">
            <text class="tn-padding-left-xs tn-padding-right-xs">{{date}}</text>
          </picker>
          <view class="tn-icon-sequence">
          </view>
          <picker @change="bindDateChange1" mode="date" :value="date1" :start="startDate1" :end="endDate1" fields="month">
            <text class="tn-padding-left-xs tn-padding-right-xs">{{date1}}</text>
          </picker>
        </view>
      </view>
      <view class="" style="min-height: 500rpx;">
        <qiun-data-charts canvas2d type="column" :opts="totalOpts" :chartData="totalChartData" />
      </view>
    </view>
    
    <view class="tn-strip-bottom"></view>
    
    <view class="tn-padding-top-xl tn-padding-bottom-xl">
      <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          群友数量
        </view>
        <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="month">
            <text class="tn-padding-left-xs tn-padding-right-xs">{{date}}</text>
          </picker>
          <view class="tn-icon-sequence">
          </view>
          <picker @change="bindDateChange1" mode="date" :value="date1" :start="startDate1" :end="endDate1" fields="month">
            <text class="tn-padding-left-xs tn-padding-right-xs">{{date1}}</text>
          </picker>
        </view>
      </view>
      <view class="" style="min-height: 500rpx;">
        <qiun-data-charts canvas2d type="area" :opts="incomeOpts" :chartData="incomeChartData" />
      </view>
    </view>
    
    <view class="tn-strip-bottom"></view>
    
    <view class="tn-padding-top-xl tn-padding-bottom-xl">
      <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          群友分布
        </view>
        <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <picker @change="bindDateChange" mode="date" :value="date" :start="startDate" :end="endDate" fields="month">
            <text class="tn-padding-left-xs tn-padding-right-xs">{{date}}</text>
          </picker>
          <view class="tn-icon-sequence">
          </view>
          <picker @change="bindDateChange1" mode="date" :value="date1" :start="startDate1" :end="endDate1" fields="month">
            <text class="tn-padding-left-xs tn-padding-right-xs">{{date1}}</text>
          </picker>
        </view>
      </view>
      <view class="" style="min-height: 500rpx;padding-top: 40rpx">
        <qiun-data-charts canvas2d type="map" :opts="placeOpts" :chartData="placeChartData" />
      </view>
    </view>
      
  </view>
</template>

<script>
  import template_page_mixin from '@/libs/mixin/template_page_mixin.js'
  import mapdata from '@/mockdata/mapdata.json'
  export default {
    name: 'TemplateContent',
    mixins: [template_page_mixin],
    data() {
      return {
        date: '2023-07',
        date1: '2024-03',
        
        latestUserAvatar: [{
            src: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242362-assets/web-upload/39542345-83ab-456c-b309-e156174d5561.jpeg'
          },
          {
            src: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242318-assets/web-upload/6d5b712d-5996-4a80-bb02-4ddc23e01acf.jpeg'
          },
          {
            src: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242375-assets/web-upload/72155ffc-795c-4cc4-b4b5-171fbb44ab8d.jpeg'
          },
          {
            src: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242423-assets/web-upload/6d82b929-67e4-4919-a826-c931940f5872.jpeg'
          },
          {
            src: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242388-assets/web-upload/471a3e0d-246d-4daa-ab83-43e70011177c.jpeg'
          },
          {
            src: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242360-assets/web-upload/b266911b-f8a6-44ad-9a78-df76d3799b76.jpeg'
          },
          {
            src: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242452-assets/web-upload/cfb64a56-9e2c-42ea-bb49-5b9d1b996898.jpeg'
          },
          {
            src: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242455-assets/web-upload/99e7d65c-10fb-4b3c-bec1-7fa77cb3180c.jpeg'
          },
          {
            src: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242345-assets/web-upload/7c70f145-2c93-423e-a9e0-c8ab00b9c0ae.jpeg'
          },
          {
            src: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242409-assets/web-upload/fcc4eab6-b2ce-44eb-9165-c49b51f5f830.jpeg'
          }
        ],
        
        // 性别比例
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
              ringWidth: 30,
              activeOpacity: 0.5,
              activeRadius: 10,
              offsetAngle: -90,
              labelWidth: 15,
              border: true,
              borderWidth: 2,
              borderColor: "#FFFFFF",
              // linearType: "custom"
            }
          }
        },
        
        // 群友年龄
        totalChartData: {},
        totalOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
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
            column: {
              type: "group",
              width: 18,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
            }
          },
        },
        
        // 群友数量
        incomeChartData: {},
        incomeOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
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
            area: {
              type: "curve",
              opacity: 0.9,
              addLine: true,
              width: 2,
              gradient: true,
            },
          },
        },
        
        // 群友分布
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
              activeFillColor: "#00D05E",
              activeFillOpacity: 1
            }
          }
        },
        
      };
    },
    onReady() {
      this.drawMakeupCharts();  //性别比例
      this.drawTotalCharts();  //群友年龄
      this.drawIncomeCharts();  //群友数量
      this.drawPlaceCharts();  //群友分布
    },
    methods: {
      // 跳转
      tn(e) {
      	uni.navigateTo({
      		url: e,
      	});
      },
      
      // 时间
      startDate() {
        return this.getDate('start');
      },
      endDate() {
        return this.getDate('end');
      },
      
      // 时间
      startDate1() {
        return this.getDate('start');
      },
      endDate1() {
        return this.getDate('end');
      },
      
      bindDateChange: function(e) {
          this.date = e.detail.value
      },
      
      bindDateChange1: function(e) {
          this.date1 = e.detail.value
      },
      
      // 性别比例 绘制
      drawMakeupCharts() {
        let res = {
          series: [
            {
              data: [{"name":"男士","value":5000,color: "#00D05E"},{"name":"女士","value":3000,color: "#FFAC00"},{"name":"未知","value":200,color: "#E6E6E6"}]
            }
          ]
        };
        this.makeupChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 群友年龄 绘制
      drawTotalCharts() {
        let res = {
          categories: [
            "10后",
            "00后",
            "90后",
            "80后",
            "70后",
            "60后",
            "未知",
          ],
          series: [{
              name: "群友年龄",
              data: [{"value":31,"color":"#4B98FE"}, {"value":126,"color":"#FFAC00"}, {"value":196,"color":"#00D05E"}, {"value":79,"color":"#FB6A67"}, {"value":13,"color":"#FE871B"}, {"value":8,"color":"#957BFE"}, {"value":33,"color":"#E6E6E6"}],
              legendShape: "circle",
            },
          ],
        };
        this.totalChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 群友数量 绘制
      drawIncomeCharts() {
        let res = {
          categories: [
            "7月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "8月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "9月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "10月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "11月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "12月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "1月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "2月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
            "3月",
            "",
            "",
            "",
            "",
            "",
            "",
            "",
          ],
          series: [{
            name: "群友数量",
            legendShape: "circle",
            color: "#00D05E",
            pointShape: "none",
            data: [
              40,
              60,
              80,
              70,
              90,
              80,
              90,
              120, // 7
              140,
              140,
              160,
              130,
              120,
              120,
              120,
              150, // 8
              155,
              145,
              155,
              145,
              187,
              275,
              273,
              277, // 9
              328,
              326,
              356,
              456,
              434,
              452,
              456,
              456, // 10
              440,
              424,
              435,
              444,
              455,
              466,
              477,
              488, // 11
              490,
              400,
              410,
              440,
              430,
              440,
              455,
              466, // 12
              477,
              480,
              460,
              450,
              443,
              431,
              420,
              430, // 2024
              440,
              450,
              460,
              437,
              428,
              449,
              411,
              422, // 2
              455,
              433,
              440,
              455,
              446,
              477,
              468,
              488, // 3
            ],
          }],
        };
        this.incomeChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 群友分布 绘制
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
  
  .top-fixed{
    position: relative;
    background: linear-gradient(90deg, #05C160, #05C160);
    top: 0;
    width: 100%;
    height: 580rpx;
    transition: all 0.25s ease-out;
    z-index: -1;
  }
  .top-fixed:before{
    content: "";
    position: absolute;
    top: 0;
    left: 0;
    bottom: 0;
    right: 0;
    z-index: -1;
    mask-image: linear-gradient(to bottom, transparent, black);
    background: linear-gradient(90deg, #05C160, #05C160);	
  
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
