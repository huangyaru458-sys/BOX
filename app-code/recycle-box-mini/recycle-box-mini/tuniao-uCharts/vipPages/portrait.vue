<template>
  <view class="template-content bg-gray">
    <!-- 顶部自定义导航 -->
    <!-- <tn-nav-bar fixed customBack :bottomShadow="false" backgroundColor="#FFFFFF00">
      <view slot="back" class='tn-custom-nav-bar__back'
        @click="goBack">
        <text class='icon tn-icon-left-arrow'></text>
      </view>
      <view class="tn-flex tn-flex-col-center tn-flex-row-center ">
        <text class="tn-text-xl tn-color-black">用户画像</text>
      </view>
    </tn-nav-bar> -->
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed customBack :bottomShadow="false" :backgroundColor="navBarBackgroundColor" id="navbar">
      <view slot="back" class='tn-custom-nav-bar__back' @click="goBack" :style="[navBarStyle]">
        <text class='icon tn-icon-left-arrow'></text>
      </view>
      <view class="tn-flex tn-flex-col-center tn-flex-row-center" :style="[navBarStyle2]">
        <view class="tn-text-bold tn-text-xl">付衣衣</view>
      </view>
    </tn-nav-bar>
    
    <view class="home-fixed">
    </view>
    
    <view class="tn-padding-bottom-lg" :style="{paddingTop: vuex_custom_bar_height + 10 + 'px'}" style="position: relative;z-index: 1;">
    
      <view class="tn-margin" style="position: relative;background-color: #FFFFFFCC;border-radius: 20rpx;">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center" style="padding: 30rpx 30rpx 0 30rpx;">
          <view class="justify-content-item">
            <view class="tn-text-bold">
              <text class="tn-text-xxl">付衣衣</text>
              <text class="tn-padding-left-sm tn-text-lg">Fu Yiyi</text>
            </view>
            <view class="tn-padding-top-xs tn-color-gray--dark">
              <text>打杂UI设计</text>
            </view>
          </view>
          <view class="justify-content-item tn-text-lg tn-color-grey">
            <view class="user-pic">
              <view class="user-image">
                <view class="" style="background-image:url('https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1692940242409-assets/web-upload/fcc4eab6-b2ce-44eb-9165-c49b51f5f830.jpeg');width: 110rpx;height: 110rpx;background-size: cover;">
                </view>
              </view>
            </view>
          </view>
        </view>
        <view class="" style="padding: 30rpx 30rpx 15rpx 30rpx;">
          <view class="tn-flex  tn-flex-col-center tn-padding-bottom-sm tn-text-sm" @click="callPhoneNumber">
            <view class="icon1__item--icon tn-flex tn-flex-row-center tn-flex-col-center">
              <view class="tn-icon-tel-circle-fill"></view>
            </view>
            <view class="tn-margin-left-sm tn-flex-1 tn-color-gray--dark">182 1912 9999</view>
          </view>
          <view class="tn-flex tn-flex-col-center tn-padding-bottom-sm tn-text-sm" @click="copyCompany">
            <view class="icon1__item--icon tn-flex tn-flex-row-center tn-flex-col-center">
              <view class="tn-icon-company-fill"></view>
            </view>
            <view class="tn-margin-left-sm tn-flex-1 tn-color-gray--dark">抓住那只猪科技有限公司</view>
          </view>
          <view class="tn-flex tn-flex-col-center tn-padding-bottom-sm tn-text-sm" @click="copyMap">
            <view class="icon1__item--icon tn-flex tn-flex-row-center tn-flex-col-center">
              <view class="tn-icon-location-fill"></view>
            </view>
            <view class="tn-margin-left-sm tn-flex-1 tn-color-gray--dark">广东省广州市番禺区祈福新邨129号</view>
          </view>
        </view>
      </view>
      
      <!-- 有id用于判断滚动-->
      <view class="tn-flex tn-padding-top" id="page_tips">
        <view class="tn-flex-1 justify-content-item tn-margin-left tn-margin-right-xs tn-text-center tn-bg-white" style="border-radius: 10rpx;">
          <tn-button backgroundColor="#00B9FE " padding="39rpx 0" width="100%" :fontSize="28" :plain="true" fontColor="#00B9FE" open-type="share">
            <text class="tn-icon-wechat tn-padding-right-xs"></text>
            <text class="">分享名片</text>
          </tn-button>
        </view>
        <view class="tn-flex-1 justify-content-item tn-margin-right tn-margin-left-xs tn-text-center">
          <tn-button backgroundColor="#00B9FE " padding="40rpx 0" width="100%" :fontSize="28" fontColor="#FFFFFF" @click="tn('')">
            <text class="tn-icon-my-add tn-padding-right-xs"></text>
            <text class="">跟进客户</text>
          </tn-button>
        </view>
      </view>
      
      <view class="tn-padding-top tn-padding-bottom">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            用户标签
            <text class="tn-padding-left-xs tn-text-xs tn-color-gray--dark">/ 共29个</text>
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-white tn-color-blue" style="border-radius: 12rpx;">
            <view class="tn-icon-add tn-padding-left-xs tn-padding-right-xs"></view>
            <view class="tn-padding-right-xs">添加标签</view>
          </view>
        </view>
        <view class="" style="margin: 0rpx 30rpx 0rpx 30rpx;padding:30rpx 30rpx 0 30rpx;border-radius: 20rpx;overflow: hidden;background-color: #FFFFFF;">
          <view class="tn-tag-content tn-text-justify">
            <view v-for="(item, index) in tagList" :key="index" class="tn-tag-content__item tn-margin-right tn-round tn-text-sm tn-text-bold" :class="[`tn-bg-${item.color}--light tn-color-${item.color}`]">
              <text class="tn-tag-content__item--prefix">#</text> {{ item.title }}
            </view>
          </view>
        </view>
      </view>
      
      <view class="tn-padding-top tn-padding-bottom">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            活跃时长
            <text class="tn-padding-left-xs tn-text-xs tn-color-gray--dark">/ 时间分</text>
          </view>
          <picker @change="bindPickerChange" :value="index" :range="array">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-white tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{array[index]}}</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="margin: 0rpx 30rpx 0rpx 30rpx;padding:30rpx 0;border-radius: 20rpx;overflow: hidden;background-color: #FFFFFF;">
          <qiun-data-charts canvas2d type="line" :opts="investOpts" :chartData="investChartData" background="#FFFFFF" />
        </view>
      </view>
      
      <view class="tn-padding-top tn-padding-bottom">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            消费统计
            <text class="tn-padding-left-xs tn-text-xs tn-color-gray--dark">/ 金额元</text>
          </view>
          <picker @change="bindPickerChange" :value="index" :range="array">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-white tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{array[index]}}</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="margin: 0rpx 30rpx 0rpx 30rpx;border-radius: 20rpx;overflow: hidden;background-color: #FFFFFF;">
          <qiun-data-charts canvas2d type="column" :opts="totalOpts" :chartData="totalChartData" background="#FFFFFF" />
        </view>
      </view>
      
      <view class="tn-padding-top tn-padding-bottom">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            雷达图谱
            <text class="tn-padding-left-xs tn-text-xs tn-color-gray--dark">/ 百分比</text>
          </view>
          <picker @change="bindPickerChange" :value="index" :range="array">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-white tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{array[index]}}</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="margin: 0rpx 30rpx 0rpx 30rpx;padding:30rpx 0;border-radius: 20rpx;overflow: hidden;background-color: #FFFFFF;">
          <qiun-data-charts canvas2d type="radar" :opts="abilityOpts" :chartData="abilityChartData" background="#FFFFFF" />
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
        /* 导航*/
        navBarRectInfo: {},
        navBarChangebaseLineHeight: 0,
        navBarStyle: {
          color:'#FFFFFF',
          opacity: 1,
          display: 'flex'
        },
        navBarStyle2: {
          color:'rgba(255,255,255,0)',
          opacity: 1,
          display: 'flex'
        },
        navBarBackgroundColor: 'rgba(255, 255, 255, 0)',
        
        /* 时间*/
        index: 2,
        array: ['今日', '近七天', '本月'],
        
        /* 标签*/
        tagList: [
          {
            color: 'red',
            title: "萌新求带",
          },
          {
            color: 'cyan',
            title: "简约美",
          },
          {
            color: 'blue',
            title: "开心吃货",
          },
          {
            color: 'green',
            title: "爱花草",
          },
          {
            color: 'orange',
            title: "产品经理",
          },
          {
            color: 'purplered',
            title: "健身女王",
          },
          {
            color: 'purple',
            title: "创意设计",
          },
          {
            color: 'brown',
            title: "腹黑",
          },
          {
            color: 'yellowgreen',
            title: "水果控",
          },
          {
            color: 'lime',
            title: "bug多多",
          },
          {
            color: 'grey',
            title: "蠢萌蠢萌",
          }
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
            axisLineColor: "#FFFFFF",
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
        
        // 访问来源
        totalChartData: {},
        totalOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [30, 10, 20, 20],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
            axisLineColor: "#FFFFFF",
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.6)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              axisLineColor: "#FFFFFF",
              min: 0,
              max: 200
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
              width: 24,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
              barBorderRadius: [16,16,16,16]
            }
          },
        },
        
        // 员工能力
        abilityChartData: {},
        abilityOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
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
        
        
      }
    },
    onReady() {
      /* 导航*/
      this.$nextTick(() => {
        this.initNavBarRectInfo()
      });
      
      this.drawInvestCharts();  //投资理财
      this.drawTotalCharts();  //访问来源
      this.drawAbilityCharts();  //员工能力
    },
    
    onPageScroll() {
      this.updateNavBarRectInfo()
    },
    methods: {
      // 初始化导航栏信息
      async initNavBarRectInfo() {
        const navBarRectInfo = await this._tGetRect('#navbar')
        const pageTipsRectInfo = await this._tGetRect('#page_tips')
        // console.log(navBarRectInfo, pageTipsRectInfo, navBarRectInfo?.top, pageTipsRectInfo?.top);
        if (!navBarRectInfo.hasOwnProperty('top') || !pageTipsRectInfo.hasOwnProperty('top')) {
          setTimeout(() => {
            this.initNavBarRectInfo()
          }, 10)
          return
        }
        this.navBarRectInfo = {
          top: navBarRectInfo.top
        }
        this.navBarChangebaseLineHeight = pageTipsRectInfo.top - navBarRectInfo.top
      },
      // 更新导航栏信息
      updateNavBarRectInfo() {
        this._tGetRect('#page_tips').then((res) => {
          const top = res?.top || 0
          if (!top) {
            return
          }
          const differHeight = top - this.navBarRectInfo.top
          const opacity = differHeight / this.navBarChangebaseLineHeight
          if (opacity < 0) {
            // this.navBarStyle.opacity = 1
            // this.navBarStyle.display = 'flex'
            this.navBarStyle.color = 'rgba(0, 0, 0, ${opacity})'
            this.navBarStyle2.color = 'rgba(0, 0, 0, ${opacity})'
            this.navBarBackgroundColor = `rgba(255, 255, 255, 1)`
          } else {
            // this.navBarStyle.opacity = 1 - opacity
            // this.navBarStyle.display = 'flex'
            this.navBarStyle.color = 'rgba(255, 255, 255, 1)'
            this.navBarStyle2.color = 'rgba(255, 255, 255, 0)'
            this.navBarBackgroundColor = `rgba(255, 255, 255, ${1 - opacity})`
          }
          
          // console.log(top, differHeight, opacity);
        })
      },
      
      bindPickerChange: function(e) {
        this.index = e.detail.value
      },
      
      // 投资理财 绘制
      drawInvestCharts() {
        let res = {
          categories: [
            "10月",
            "11月",
            "12月",
            "1月",
            "2月",
            "3月",
          ],
          series: [{
              name: "访问时长",
              data: [99, 129, 106, 145, 123, 144],
              legendShape: "circle",
              linearColor: [[0,"#FFAC00"],[0.25,"#FE871B"],[0.5,"#FB6A67"],[0.75,"#F674D6"],[1,"#957BFE"]],
            },
          ],
        };
        this.investChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 访问来源 绘制
      drawTotalCharts() {
        let res = {
          categories: [
            "餐饮",
            "护肤",
            "日用",
            "其他",
          ],
          series: [{
              name: "访问来源",
              data: [{"value":129,"color":"#00D05E"}, {"value":168,"color":"#FFAC00"},{"value":116,"color":"#FB6A67"}, {"value":46,"color":"#957BFE"}],
              legendShape: "circle",
            },
          ],
        };
        this.totalChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 员工能力 绘制
      drawAbilityCharts() {
        let res = {
            categories: ["处事","学习","工作","沟通","领导","决策"],
            series: [
              {
                name: "分值",
                data: [90,86,79,66,15,63],
                color: "#FFAC00"
              },
            ]
          };
        this.abilityChartData = JSON.parse(JSON.stringify(res));
      },
      
    }
  }
</script>

<style lang="scss" scoped>
  /* 胶囊*/
  .tn-custom-nav-bar__back {
    width: 60%;
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
    font-size: 32rpx;
    
    .icon {
      display: block;
      flex: 1;
      margin: auto;
      text-align: center;
    }
    
  }
  
  .bg-gray{
    background-color: #F9F9F9;
    min-height: 100vh;
  }
  
  // 四个角渐变底色
  .home-fixed{
    position: fixed;
    background: linear-gradient(90deg, #C5FADC , #DBF2FE, #D7EAFA);
    top: 0;
    width: 100%;
    transition: all 0.25s ease-out;
    z-index: 0;
    min-height: 30vh;
  }
  .home-fixed:before{
    content: "";
    position: absolute;
    top: 0;
    left: 0;
    bottom: 0;
    right: 0;
    z-index: 0;
    mask-image: linear-gradient(to bottom, transparent, black);
    background: linear-gradient(90deg, #F9F9F9, #F9F9F9);	
  
  }
  
  /* 用户头像 start */
  .user-image {
    width: 110rpx;
    height: 110rpx;
    position: relative;
  }
  
  .user-pic {
    background-size: cover;
    background-repeat: no-repeat;
    // background-attachment:fixed;
    background-position: top;
    border: 6rpx solid rgba(249,249,249,0.65);
    box-shadow: 0rpx 0rpx 80rpx 0rpx rgba(0, 0, 0, 0.1);
    border-radius: 50%;
    overflow: hidden;
    // background-color: #FFFFFF;
  }
  
  /* 标签内容 start*/
  .tn-tag-content {
    &__item {
      display: inline-block;
      line-height: 45rpx;
      padding: 10rpx 30rpx;
      margin: 0rpx 20rpx 25rpx 0rpx;
      
      &--prefix {
        padding-right: 10rpx;
      }  
    }
  }
  /* 标签内容 end*/
  
</style>
