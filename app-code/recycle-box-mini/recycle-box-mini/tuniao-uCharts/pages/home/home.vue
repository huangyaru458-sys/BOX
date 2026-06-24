<template>
  <view class="template-home tn-safe-area-inset-bottom">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed :isBack="false" :bottomShadow="false" backgroundColor="#FFFFFF00">
      <view id="navbar" class="custom-nav tn-flex tn-flex-col-center tn-flex-row-left">
        <!-- 图标logo -->
        <view class="custom-nav__back">
          <view class="logo-pic tn-shadow-blur" style="background-image:url('https://resource.tuniaokj.com/images/logo/logo2.png')">
            <view class="logo-image">
            </view>
          </view> 
          <!-- <view class="tn-icon-left"></view> -->
        </view>
        <!-- 字 -->
        <!-- <view class="custom-nav__search tn-flex tn-flex-col-center tn-flex-row-center ">
          <view class="custom-nav__search__box tn-flex tn-flex-col-center tn-flex-row-center tn-color-white">
            <text class="tn-text-bold tn-text-xxl">北北壁纸库</text>
          </view>
        </view> -->
        <!-- 搜索框 -->
        <!-- <view class="custom-nav__search tn-flex tn-flex-col-center tn-flex-row-center">
          <view class="custom-nav__search__box tn-flex tn-flex-col-center tn-flex-row-left">
            <view class="custom-nav__search__text tn-padding-left tn-margin-left tn-text-bold tn-text-xl">图鸟 & uCharts</view>
          </view>
        </view> -->
      </view>
    </tn-nav-bar>

    <swiper class="card-swiper" :circular="true" style="background-color: #02B075;"
      :autoplay="false" duration="500" interval="28000" @change="cardSwiper"> 
      <swiper-item v-for="(item,index) in swiperList" :key="index" :class="cardCur==index?'cur':''">
        <view class="swiper-item image-banner">
          <image :src="item.url" mode="aspectFill" v-if="item.type=='image'"></image>
        </view>
      </swiper-item>
    </swiper>
    <view class="indication">
        <block v-for="(item,index) in swiperList" :key="index">
            <view class="spot" :class="cardCur==index?'active':''"></view>
        </block>
    </view>
    
    <!-- 方式15 start-->
    <view class="tn-flex tn-margin-xs tn-padding-top-sm tn-color-white icon-function">
      <view class="tn-flex-1 tn-padding-sm tn-margin-xs" @click="copyManual">
        <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
          <view class="icon15__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur ">
            <view class="tn-icon-image-text"></view>
          </view>  
          <view class="tn-text-center">
            <text class="tn-text-ellipsis">应用手册</text>
          </view>
        </view>
      </view>
      <view class="tn-flex-1 tn-padding-sm tn-margin-xs tn-radius" @click="showModal">
        <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
          <view class="icon15__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur">
            <view class="tn-icon-honor"></view>
          </view>  
          <view class="tn-text-center">
            <text class="tn-text-ellipsis">服务条款</text>
          </view>
        </view>
      </view>
      <view class="tn-flex-1 tn-padding-sm tn-margin-xs tn-radius" @click="showModal2">
        <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
          <view class="icon15__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur">
            <view class="tn-icon-level"></view>
          </view>  
          <view class="tn-text-center">
            <text class="tn-text-ellipsis">关于应用</text>
          </view>
        </view>
      </view>
      <view class="tn-flex-1 tn-padding-sm tn-margin-xs">
        <button class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center tn-button--clear-style" open-type="contact" @click="vibrateShort">
          <view class="icon15__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur">
            <view class="tn-icon-message"></view>
          </view>  
          <view class="tn-text-center">
            <text class="tn-text-ellipsis">问题反馈</text>
          </view>
        </button>
      </view>
    </view>
    <!-- 方式15 end-->
    
    
    <!-- 更多信息-->
    <view class="health-shadow tn-margin tn-color-black tn-bg-white" style="position: relative;z-index: 1;padding: 20rpx 6rpx;">
      
      <tn-notice-bar :list="list" mode="vertical"></tn-notice-bar>
      
      
      <!-- 方式9 start-->
      <view class="tn-flex">
        <view class="tn-flex-1 tn-margin-xs" @click="navTuniaoUI">
          <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
            <view class="icon9__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-bg-orange tn-color-white">
              <view class="tn-icon-qr-code-circle"></view>
            </view>  
            <view class="tn-color-gray--dark tn-text-sm tn-text-center">
              <text class="tn-text-ellipsis">图鸟vue2</text>
            </view>
          </view>
        </view>
        <view class="tn-flex-1 tn-margin-xs" @click="navTuniaoVUE3">
          <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
            <view class="icon9__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-bg-red tn-color-white">
              <view class="tn-icon-qr-code-circle"></view>
            </view>  
            <view class="tn-color-gray--dark tn-text-sm tn-text-center">
              <text class="tn-text-ellipsis">图鸟vue3</text>
            </view>
          </view>
        </view>
        <view class="tn-flex-1 tn-margin-xs" @click="navTuniaoTbys">
          <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
            <view class="icon9__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-bg-cyan tn-color-white">
              <view class="tn-icon-qr-code-circle"></view>
            </view>  
            <view class="tn-color-gray--dark tn-text-sm tn-text-center">
              <text class="tn-text-ellipsis">图鸟图表原生</text>
            </view>
          </view>
        </view>
        <view class="tn-flex-1 tn-margin-xs" @click="navTuniaoTbvue3">
          <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
            <view class="icon9__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-shadow-blur tn-bg-blue tn-color-white">
              <view class="tn-icon-qr-code-circle"></view>
            </view>  
            <view class="tn-color-gray--dark tn-text-sm tn-text-center">
              <text class="tn-text-ellipsis">图鸟图表vue3</text>
            </view>
          </view>
        </view>
      </view>
    </view>
    
    
    <!-- banner start-->
    <view class="tn-flex tn-flex-wrap tn-padding-xs" style="margin-top: -30rpx;"  @click="navTuniaoUI">
      <view class="" style="width: 100%;">
        <view class="image-piccapsule tn-shadow-blur" style="background-image:url('https://cdn.nlark.com/yuque/0/2023/png/280373/1690025870393-assets/web-upload/6f35f6a6-2935-4aca-9f2d-146d1bbf1d58.png');">
           <view class="image-capsule">
           </view>
         </view>  
      </view>  
    </view>
    <!-- banner end-->
    
    <!-- 方式7 start-->
    <view class="tn-flex tn-flex-wrap">
      <block v-for="(item, index) in icons" :key="index">
        <view class=" " style="width: 25%;" @click="tn(item.path)">
          <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center  tn-padding-xl">
            <view class="icon7__item--icon tn-flex tn-flex-row-center tn-flex-col-center" :class="{'punch-no': item.status==false}" :style="'background-image:url('+ item.url +');background-size:100% 100%;background-size: cover;'">
            </view>
            <view class="tn-color-black tn-text-df tn-text-center">
              <text class="tn-text-ellipsis">{{item.title}}</text>
            </view>
          </view>
        </view>
      </block>
    </view>
    <!-- 方式16 end-->
    
    <!-- <view class="tn-flex tn-flex-row-between">
      <view class="justify-content-item tn-margin tn-text-bold tn-text-xxl">
        推荐博主
      </view>
      <view class="justify-content-item tn-margin tn-text-lg tn-color-gray--disabled">
        <text class="tn-padding-xs">全部</text>
        <text class="tn-icon-topics"></text>
      </view>
    </view>
    
    <swiper class="card-swiper2 tn-margin-top-sm" :circular="true"
      :autoplay="false" :duration="500" @change="resume"> 
      <swiper-item v-for="(item,index) in resumeList" :key="index" :class="cardCur2==index?'cur':''">
        <view class="swiper-item" :style="'background-image:url('+ item.url + ');width: 660rpx;height: 100%;background-size: cover;border-radius: 15rpx;'">
        </view>
        <view class="swiper-item2 image-banner tn-shadow-blur" :style="'background-image:url('+ item.avatar +');width: 120rpx;height: 120rpx;background-size: cover;'">
        </view>
        <view class="swiper-item-text tn-text-shadow-indigo">
          <view class="tn-text-bold tn-color-blue--dark" style="font-size: 45rpx;">{{item.title}}</view>
          <view class="tn-color-blue--dark tn-padding-top-sm">{{item.name}}</view>
          <view class="tn-flex tn-padding-top-xl" style="margin-left: -50rpx;">
            <view class="tn-flex-1 tn-padding-sm tn-margin-right">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
                <view class="">
                  <view class="tn-text-xxl tn-color-blue">{{item.hot}}</view>
                </view>
                <view class="tn-margin-top-xs tn-color-grey tn-text-df tn-text-center">
                  <text class="tn-icon-fire"></text>
                  <text class="tn-padding-left-xs">人气</text>
                </view>
              </view>
            </view>
            <view class="tn-flex-1 tn-padding-sm tn-margin-left tn-margin-right">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
                <view class="">
                  <view class="tn-text-xxl tn-color-orange">{{item.share}}</view>
                </view>
                <view class="tn-margin-top-xs tn-color-grey tn-text-df tn-text-center">
                  <text class="tn-icon-share-circle"></text>
                  <text class="tn-padding-left-xs">分享</text>
                </view>
              </view>
            </view>
            <view class="tn-flex-1 tn-padding-sm tn-margin-left">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center">
                <view class="">
                  <view class="tn-text-xxl tn-color-red">{{item.love}}</view>
                </view>
                <view class="tn-margin-top-xs tn-color-grey tn-text-df tn-text-center">
                  <text class="tn-icon-like"></text>
                  <text class="tn-padding-left-xs">爱心</text>
                </view>
              </view>
            </view>
          </view>
        </view>
      </swiper-item>
    </swiper> -->
<!--    <view class="indication">
        <block v-for="(item,index) in resumeList" :key="index">
            <view class="spot" :class="cardCur==index?'active':''"></view>
        </block>
    </view> -->
    
    
    <!-- <view class="">
      <view class="tn-flex tn-flex-row-between">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-xxl">
          热门项目
        </view>
        <view class="justify-content-item tn-margin tn-text-lg tn-color-gray--disabled">
          <text class="tn-padding-xs">全部</text>
          <text class="tn-icon-topics"></text>
        </view>
      </view>
      
      <view class="tn-flex tn-margin-left tn-margin-right tn-margin-top-sm">
        <view class="tn-flex-2">
          
          <view class="image-pic tn-margin-right" style="background-image:url('https://resource.tuniaokj.com/images/shop/card.jpg')">
            <view class="image-tuniao1">
            </view>
          </view> 
          
        </view>
        <view class="tn-flex-1">
          <view class="image-pic" style="background-image:url('https://resource.tuniaokj.com/images/shop/phonecase1.jpg')">
            <view class="image-tuniao2">
            </view>
          </view> 
          <view class="image-pic tn-margin-top" style="background-image:url('https://resource.tuniaokj.com/images/shop/banner1.jpg')">
            <view class="image-tuniao2">
            </view>
          </view> 
        </view>
      </view>
      
      
      <view class="tn-flex tn-flex-row-between tn-margin-top">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-xxl">
          业务范围
        </view>
        <view class="justify-content-item tn-margin tn-text-xxl tn-color-gray--disabled">
          <text class="tn-padding-xs">全部</text>
          <text class="tn-icon-topics"></text>
        </view>
      </view>
      
      -->
      

    <tn-modal v-model="show1" :custom="true" :showCloseBtn="true">
      <view class="custom-modal-content">
        <view class="">
          <view class="tn-text-justify tn-color-blue tn-text-lg" style="padding: 40rpx 0rpx;">
            <view class="tn-padding-bottom tn-text-center">免费版本足够白嫖，酷炫模板需知识付费，不喜勿喷</view>
            <view class="">图鸟图表，699元/终身（含原生、vue2、vue3），不喜勿喷</view>
          </view>  
        </view>
        <!-- <view class="tn-flex-1 justify-content-item tn-margin-sm tn-text-center tn-padding-top">
          <tn-button backgroundColor="#3668FC" padding="40rpx 0" width="100%" shadow fontBold >
            <text class="tn-color-white">关闭弹窗</text>
          </tn-button>
        </view> -->
      </view>
    </tn-modal>
    
    <tn-modal v-model="show2" :custom="true" :showCloseBtn="true">
      <view class="custom-modal-content">
        <view class="tn-text-justify">
          <view class="tn-color-blue tn-text-lg" style="padding: 40rpx 0rpx;">
            <view class="tn-padding-bottom">图鸟图表上线于2023年7月23日</view>
            <view class="tn-padding-bottom"> uCharts一直是图鸟最大的支持者，从图鸟UI刚出生，uCharts就在默默支持</view>
            <view class=""> 推出 【图鸟图表】，更多是为了感谢uCharts、感谢粉丝们的支持，也感恩一起成长的小伙伴们</view>
          </view>  
        </view>
        <!-- <view class="tn-flex-1 justify-content-item tn-margin-sm tn-text-center tn-padding-top">
          <tn-button backgroundColor="#3668FC" padding="40rpx 0" width="100%" shadow fontBold >
            <text class="tn-color-white">关闭弹窗</text>
          </tn-button>
        </view> -->
      </view>
    </tn-modal>
      
    
    <view class="tn-tabbar-height"></view>
    
    
  </view>
</template>

<script>
  import template_page_mixin from '@/libs/mixin/template_page_mixin.js'
  export default {
    name: 'Home',
    mixins: [template_page_mixin],
    data() {
      return {
        show1: false,
        show2: false,
        
        list: [
          'uCharts跨全端图表，荣获插件大赛一等奖！',
          '感谢DCloud以及uCharts团队的鼓励和认可！',
          '感谢各位伯乐巨佬们对图鸟图表的慷慨赞赏！'
        ],
        cardCur: 0,
        swiperList: [{
          id: 0,
          type: 'image',
          title: '免费开源',
          name: '商业合作请联系作者',
          text: '微信：tnkewo',
          url: 'https://resource.tuniaokj.com/images/swiper/adno3.jpg',
        }, {
          id: 1,
          type: 'image',
          title: '图鸟南南',
          name: '欢迎加入东东们',
          text: '如果你也有不错的作品',
          url: 'https://resource.tuniaokj.com/images/swiper/adno4.jpg',
        }, {
          id: 2,
          type: 'image',
          title: '图鸟西西',
          name: '一起玩转scss',
          text: '用最少的代码做最骚的效果',
          url: 'https://resource.tuniaokj.com/images/swiper/adno5.jpg',
        }, {
          id: 3,
          type: 'image',
          title: '图鸟北北',
          name: '微信号 tnkewo',
          text: '商业合作请联系作者',
          url: 'https://resource.tuniaokj.com/images/swiper/adno2.jpg',
        }],
        
        
        icons: [
          {
            url: "https://cdn.nlark.com/yuque/0/2023/png/280373/1690020081118-assets/web-upload/2ecc8ed6-d000-4f1e-ae7f-57a9882ac1b3.png",
            title: "柱状图",
            path: '/homePages/column',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2023/png/280373/1690020500501-assets/web-upload/73f25dce-89fe-4693-a2ee-4bbef76569e2.png",
            title: "条形图",
            path: '/homePages/bar',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647140787383-assets/web-upload/61e9cc25-3554-4025-9acc-50ee934af53e.png",
            title: "折线图",
            path: '/homePages/line',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2023/png/280373/1690016872715-assets/web-upload/4e5349ae-2b25-4207-b89a-fafce8326987.png",
            title: "山峰图",
            path: '/homePages/mount',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2023/png/280373/1690015522605-assets/web-upload/3f1d8a0c-78b1-4a15-be4e-8a1d0b034489.png",
            title: "散点图",
            path: '/homePages/scatter',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647142981691-assets/web-upload/831c2d86-2834-4a23-a2ef-e4596051bff5.png",
            title: "圆环图",
            path: '/homePages/ring',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647142894339-assets/web-upload/5a9dd8d0-fda5-4f1e-a596-a90082abfa42.png",
            title: "饼状图",
            path: '/homePages/pie',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647146724667-assets/web-upload/fc2be2b3-eb10-4c99-b12c-c9f6ef1ef648.png",
            title: "玫瑰图",
            path: '/homePages/rose',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2023/png/280373/1690019817274-assets/web-upload/249380ee-cfa9-40ec-a9b4-619bbd563bec.png",
            title: "进度条",
            path: '/homePages/arcbar',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647150734710-assets/web-upload/1eeb9fb3-3f5f-4971-8a19-65867217e5bf.png",
            title: "区域图",
            path: '/homePages/area',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647150966872-assets/web-upload/4009704d-e4e7-4df4-992d-e68d99711997.png",
            title: "混合图",
            path: '/homePages/mix',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2023/png/280373/1690018686955-assets/web-upload/d56c92ef-c53b-49c9-9539-bbe2fdaabe8a.png",
            title: "雷达图",
            path: '/homePages/radar',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647151102859-assets/web-upload/872a9716-3e60-4406-9597-111b4cccaac1.png",
            title: "K线图",
            path: '/homePages/candle',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647153742104-assets/web-upload/770e4a06-481b-489d-ad4f-9c77d4ac04ea.png",
            title: "漏斗图",
            path: '/homePages/funnel',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2023/png/280373/1690017168910-assets/web-upload/394f68e7-2db5-4a84-992b-4f2eabd0dea4.png",
            title: "气泡图",
            path: '/homePages/bubble',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2023/png/280373/1690019618539-assets/web-upload/760d575c-ad8b-4678-a965-58e9d9ef078d.png",
            title: "仪表盘",
            path: '/homePages/gauge',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2023/png/280373/1689866938850-assets/web-upload/6fa173e6-6dbd-498e-a13e-d1aeccb08787.png",
            title: "词云图",
            path: '/homePages/word',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647154285224-assets/web-upload/9bf3bdfc-2f65-4ecc-bfdf-4e3bcf9ad9f1.png",
            title: "地图",
            path: '/homePages/map',
            status: true,
          },
          {
            url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647154447211-assets/web-upload/91b029d1-1088-4ffa-8cf6-80e9388a575c.png",
            title: "大杂烩",
            path: '/homePages/content',
            status: true,
          },
          // {
          //   url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647150225993-assets/web-upload/994fbc32-a193-454a-90b2-be7a3a702b83.png",
          //   title: "圆弧进度条",
          //   path: '/homePages/content',
          //   status: true,
          // },
          // {
          //   url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647141432488-assets/web-upload/a8aa8760-c795-49ed-85cd-69e2365d5f9c.png",
          //   title: "曲线图",
          //   path: '/homePages/content',
          //   status: false,
          // },
          // {
          //   url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647142379943-assets/web-upload/86725be9-5570-470b-9434-6398fb2f16d9.png",
          //   title: "折线滚动条",
          //   path: '/homePages/content',
          //   status: false,
          // },
          // {
          //   url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647142796046-assets/web-upload/d9541d32-3e53-4d3c-8ceb-e4962e532883.png",
          //   title: "曲线横滚动",
          //   path: '/homePages/content',
          //   status: false,
          // },
          // {
          //   url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647139412104-assets/web-upload/0a9b8682-ba75-48c0-93c0-91e7bbd91b55.png",
          //   title: "柱状堆叠图",
          //   path: '/homePages/content',
          //   status: false,
          // },
          // {
          //   url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647139725183-assets/web-upload/c6a007e8-e17f-4b4a-a732-defc758f6b08.png",
          //   title: "柱状温度计",
          //   path: '/homePages/content',
          //   status: false,
          // },
          // {
          //   url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647140327438-assets/web-upload/103ea652-be67-44e8-9487-b0c19d309076.png",
          //   title: "柱状滚动条",
          //   path: '/homePages/content',
          //   status: false,
          // },
          // {
          //   url: "https://cdn.nlark.com/yuque/0/2022/png/280373/1647140690779-assets/web-upload/45ad31b3-34a6-4c69-afce-b42345211596.png",
          //   title: "柱状标记线",
          //   path: '/homePages/content',
          //   status: false,
          // },
        ],
        
      }
    },

    methods: {
      
      // 弹出模态框
      showModal(event) {
        wx.vibrateShort();
        this.openModal()
      },
      // 打开模态框
      openModal() {
        this.show1 = true
      },
      
      // 弹出模态框
      showModal2(event) {
        wx.vibrateShort();
        this.openModal2()
      },
      // 打开模态框
      openModal2() {
        this.show2 = true
      },
      
      // 复制应用手册
      copyManual() {
        wx.vibrateShort();
        uni.setClipboardData({
          data: "https://www.ucharts.cn/v2/#/document/index",
        })
      },
      
      // 短震动
      vibrateShort(e) {
        wx.vibrateShort();
      },
      
      // 跳转
      tn(e) {
        wx.vibrateShort();
        uni.navigateTo({
          url: e,
        });
      },
      
      // cardSwiper
      cardSwiper(e) {
        this.cardCur = e.detail.current
      },
      // resume
      resume(e) {
        this.cardCur2 = e.detail.current
      },
     
      // 跳转到图鸟UI
      navTuniaoUI() {
        wx.vibrateShort();
        uni.navigateToMiniProgram({
          appId: 'wxf3d81a452b88ff4b'
        })
      },
      // 跳转到图鸟vue3
      navTuniaoVUE3() {
        wx.vibrateShort();
        uni.navigateToMiniProgram({
          appId: 'wxd4296f570b8b39c9'
        })
      },
      // 跳转到图鸟图表原生
      navTuniaoTbys() {
        wx.vibrateShort();
        uni.navigateToMiniProgram({
          appId: 'xxxxxxxxxxx'
        })
      },
      // 跳转到图鸟图表vue3
      navTuniaoTbvue3() {
        wx.vibrateShort();
        uni.navigateToMiniProgram({
          appId: 'yyyyyyyyy'
        })
      },
    }
  }
</script>

<style lang="scss" scoped>
  .template-home {
    max-height: 100vh;
  }
  
  /* 底部安全边距 start*/
  .tn-tabbar-height {
    min-height: 120rpx;
    height: calc(140rpx + env(safe-area-inset-bottom) / 2);
    height: calc(140rpx + constant(safe-area-inset-bottom));
  }
  
  /* 没有上线*/
  .punch-no {
    filter: grayscale(100%);
    -webkit-filter: grayscale(100%);
    opacity: 0.4;
  }
  
  .icon-function {
       position: relative;
       z-index: 1;
       margin: 20rpx 5rpx;
       margin-top: -420rpx;
   }
  
   /* 轮播视觉差 start */
   .card-swiper {
     height: 600rpx !important;
   }
     
   .card-swiper swiper-item {
     width: 750rpx !important;
     left: 0rpx;
     box-sizing: border-box;
     // padding: 0rpx 30rpx 90rpx 30rpx;
     overflow: initial;
   }
     
   .card-swiper swiper-item .swiper-item {
     width: 100%;
     display: block;
     height: 100%;
     transform: scale(1);
     transition: all 0.2s ease-in 0s;
     overflow: hidden;
   }
     
   .card-swiper swiper-item.cur .swiper-item {
     transform: none;
     transition: all 0.2s ease-in 0s;
   }
   
   .image-banner{
     display: flex;
     align-items: center;
     justify-content: center;
   }
   .image-banner image{
     width: 100%;
     height: 100%;
   }
   
   /* 轮播指示点 start*/
   .indication{
     z-index: 9999;
     width: 100%;
     height: 36rpx;
     position: absolute;
     display:flex;
     flex-direction:row;
     align-items:center;
     justify-content:center;
     opacity: 0;
   }
   
   .spot{
     background-color: #FFFFFF;
     opacity: 0.6;
     width: 10rpx;
     height: 10rpx;
     border-radius: 20rpx;
     top: -60rpx;
     margin: 0 8rpx !important;
     position: relative;
   }
   
   .spot.active{
     opacity: 1;
     width: 30rpx;
     background-color: #FFFFFF;
   }
   
   /* 简历推荐 start */
   .card-swiper2 {
     height: 420rpx !important;
     overflow: hidden;
   }
     
   .card-swiper2 swiper-item {
     width: 680rpx !important;
     left: 30rpx;
     box-sizing: border-box;
     overflow: initial;
     padding: 0 0rpx 40rpx 0;
   }
     
   .card-swiper2 swiper-item .swiper-item {
     width: 100%;
     display: block;
     height: 100%;
     // transform: scale(1);
     // transition: transform 0.2s ease-out 0s;
   }
     
   .card-swiper2 swiper-item.cur .swiper-item {
     // transform: scale(1);
   }
   
   .card-swiper2 swiper-item .swiper-item2 {
     width: 100%;
     display: block;
     height: 50%;
     border-radius: 50%;
     transform: translate(480rpx, -300rpx) scale(0.9);
     transition: transform 0.3s ease-out 0s;
   }
     
   .card-swiper2 swiper-item.cur .swiper-item2 {
     transform: translate(510rpx, -320rpx) scale(0.9);
   }
  
   .card-swiper2 swiper-item .swiper-item-text {
     width: 100%;
     display: block;
     height: 100%;
     border-radius: 10rpx;
     transform: translate(20rpx, -420rpx) scale(0.8);
     transition: transform 0.6s ease-out 0s;
     overflow: hidden;
   }
     
   .card-swiper2 swiper-item.cur .swiper-item-text {
     transform: translate(20rpx, -450rpx) scale(0.9);
   }
   
  
   
   /* 底部tabbar假阴影 start*/
   .bg-tabbar-shadow{
     background-image: repeating-linear-gradient(to top, rgba(0,0,0,0.1) 10rpx, #FFFFFF , #FFFFFF);
     position: fixed;
     bottom: 0;
     height: 450rpx;
     width: 100vw;
     z-index: -1;
   }
   
   /* 图标容器15 start */
  .icon15 {
    &__item {
      width: 30%;
      background-color: #FFFFFF;
      border-radius: 10rpx;
      padding: 30rpx;
      margin: 20rpx 10rpx;
      transform: scale(1);
      transition: transform 0.3s linear;
      transform-origin: center center;
      
      &--icon {
        width: 100rpx;
        height: 100rpx;
        font-size: 60rpx;
        // border-radius: 50%;
        margin-bottom: 0rpx;
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
   
   /* 图标容器7 start */
       .icon7 {
         &__item {
           width: 30%;
           background-color: #FFFFFF;
           border-radius: 10rpx;
           padding: 10rpx;
           margin: 20rpx 10rpx;
           transform: scale(1);
           transition: transform 0.3s linear;
           transform-origin: center center;
           
           &--icon {
             width: 90rpx;
             height: 90rpx;
             font-size: 60rpx;
             border-radius: 0;
             margin-bottom: 18rpx;
             position: relative;
             z-index: 1;
           }
         }
       }
     
   /* 图标容器9 start */
     .icon9 {
       &__item {
         width: 30%;
         background-color: #FFFFFF;
         border-radius: 10rpx;
         transform: scale(1);
         transition: transform 0.3s linear;
         transform-origin: center center;
         
         &--icon {
           width: 80rpx;
           height: 80rpx;
           font-size: 50rpx;
           border-radius: 50%;
           margin-bottom: 18rpx;
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
             background-image: url(https://resource.tuniaokj.com/images/cool_bg_image/icon_bg6.png);
           }
         }
       }
     }
   
   
   /* 阴影 start*/
   .health-shadow {
     border-radius: 15rpx;
     box-shadow: 0rpx 0rpx 50rpx 0rpx rgba(0, 0, 0, 0.07);
   }
   
   /* 自定义导航栏内容 start */
   .custom-nav {
     height: 100%;
     
     &__back {
       margin: auto 5rpx;
       font-size: 40rpx;
       margin-right: 10rpx;
       margin-left: 30rpx;
       flex-basis: 5%;
     }
     
     &__search {
       flex-basis: 80%;
       width: 100%;
       height: 100%;
       
       &__box {
         width: 100%;
         height: 70%;
         padding: 10rpx 0;
         margin: 0 30rpx;
         border-radius: 60rpx 60rpx 0 60rpx;
         font-size: 24rpx;
       }
       
       &__icon {
         padding-right: 10rpx;
         margin-left: 20rpx;
         font-size: 30rpx;
       }
       
       &__text {
         color: #FFFFFF;
       }
     }
   }
   .logo-image{
     width: 60rpx;
     height: 60rpx;
     position: relative;
   }
   .logo-pic{
     background-size: cover;
     background-repeat:no-repeat;
     // background-attachment:fixed;
     background-position:top;
     border-radius: 50%;
   }
   /* 自定义导航栏内容 end */
   
  
   /* 热门图片 start*/
   .image-tuniao1{
     padding: 164rpx 0rpx;
     font-size: 40rpx;
     font-weight: 300;
     position: relative;
   }
   .image-tuniao2{
     padding: 75rpx 0rpx;
     font-size: 40rpx;
     font-weight: 300;
     position: relative;
   }
   .image-tuniao3{
     padding: 90rpx 0rpx;
     font-size: 40rpx;
     font-weight: 300;
     position: relative;
   }
   .image-pic{
     background-size: cover;
     background-repeat:no-repeat;
     // background-attachment:fixed;
     background-position:top;
     border-radius: 10rpx;
   }
   /* 胶囊banner*/
   .image-capsule{
     padding: 100rpx 0rpx;
     font-size: 40rpx;
     font-weight: 300;
     position: relative;
   }
   .image-piccapsule{
     background-size: cover;
     background-repeat:no-repeat;
     // background-attachment:fixed;
     background-position:top;
     border-radius: 20rpx 20rpx 0 0;
   }
   
   
   /* 业务展示 start */
   .tn-info {
     
     &__container {
       margin-top: 10rpx;
       margin-bottom: 50rpx;
     }
     
     &__item {
       width: 48%;
       margin: 15rpx 0rpx;
       padding: 40rpx 30rpx;
       border-radius: 15rpx;
       
   
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
           background-image: url(https://resource.tuniaokj.com/images/cool_bg_image/2.png);
         }
       
       &__left {
         
         &--icon {
           width: 80rpx;
           height: 80rpx;
           border-radius: 50%;
           font-size: 40rpx;
           margin-right: 20rpx;
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
             background-image: url(https://resource.tuniaokj.com/images/cool_bg_image/icon_bg5.png);
           }
         }
         
         &__content {
           font-size: 25rpx;          
           
           &--data {
             color: rgba(255,255,255,0.5);
             margin-top: 5rpx;
             // font-weight: bold;
           }
         }
       }
       
       &__right {
         &--icon {
           position: absolute;
           right: 0rpx;
           top: 50rpx;
           font-size: 100rpx;
           width: 108rpx;
           height: 108rpx;
           text-align: center;
           line-height: 60rpx;
           opacity: 0.15;  
         }
       }
     }
   }
   /* 业务展示 end */
   
</style>