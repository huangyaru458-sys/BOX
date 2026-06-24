<template>
  <view class="template-vip tn-safe-area-inset-bottom">
    
    <!-- 轮播banner-->
    <swiper class="card-swiper" @click="tn('/vipPages/black')" :circular="true" 
      :autoplay="true" duration="500" interval="8000" @change="cardSwiper"> 
      <swiper-item v-for="(item,index) in swiperList" :key="index" :class="cardCur==index?'cur':''">
        <view class="swiper-item image-banner">
          <image :src="item.url" mode="aspectFill" v-if="item.type=='image'"></image>
        </view>
        <view class="swiper-item-text">
          <view class="tn-text-bold tn-color-white" style="font-size: 70rpx;">{{item.title}}</view>
          <view class="tn-color-white tn-padding-top-sm" style="font-size: 30rpx;">{{item.name}}</view>
          <view class="tn-text-sm tn-text-bold tn-color-white tn-padding-top-sm tn-padding-bottom-sm">{{item.text}}</view>
        </view>
        <!-- 按钮 -->
        <view class="tn-flex go">
          <view class="tn-flex-1 justify-content-item tn-margin-sm tn-text-center">
            <tn-button :plain="true" shape="round" backgroundColor="#FFFFFF" fontColor="#FFFFFF" width="220rpx"
              height="60rpx" @click="tn('/productPages/details')">
              前往探索
              <text class="tn-icon-right-arrow tn-padding-left-xs"></text>
            </tn-button>
          </view>
        </view>
      </swiper-item>
    </swiper>
    <view class="indication">
        <block v-for="(item,index) in swiperList" :key="index">
            <view class="spot" :class="cardCur==index?'active':''"></view>
        </block>
    </view>
    
    <!-- 功能入口-->
    <view class="charts-type__container tn-flex tn-flex-wrap tn-flex-col-center tn-flex-row-between tn-margin-left tn-margin-right">
      <block v-for="(item, index) in navList" :key="index">
        
        <!-- <view class="tn-color-blue tn-text-bold tn-text-xl tn-padding-bottom tn-padding-top">{{ item.title }}</view> -->
        
        <block v-for="(content_item, content_index) in item.list" :key="content_index">
          <navigator open-type="navigate" hover-class='none' :url="content_item.url" class="charts-type__item tn-flex tn-flex-direction-row tn-flex-col-center tn-flex-row-between tn-shadow-blur" :class="'tn-bg-'+ content_item.color + '--light; tn-color-'+ content_item.color + ';' ">
            <view class="charts-type__item__left tn-flex tn-flex-direction-row tn-flex-col-center tn-flex-row-left">
              <view class="">
                <view class="tn-text-bold" style="font-size: 32rpx;">{{ content_item.title }}</view>
              </view>
            </view>
            <view class="charts-type__item__bottom">
              <view class='name tn-text-sm tn-color-gray' style="margin-left: -10rpx;">
                <text class="tn-icon-code tn-padding-right-xs" style="opacity: 0;"></text>
              </view>
            </view>
          </navigator>
        </block>
        
      </block>
    </view>
    
    <view class="tn-tabbar-height"></view>
    
    
  </view>
</template>

<script>
  import vipListData from '@/libs/navigation/navigation.js'
  export default {
    name: 'Vip',
    data() {
      return {
        // nav菜单列表
        navList: vipListData.data,
        
        cardCur: 0,
        swiperList: [{
          id: 0,
          type: 'image',
          title: '暗黑图表',
          name: '酷炫可视化移动端看板',
          text: '',
          url: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1700289261187-assets/web-upload/ed9c78bf-9d7a-4c2a-a800-80860b56fa6b.jpeg',
        }, 
        /* {
          id: 1,
          type: 'image',
          title: '合作勾搭',
          name: '作者微信 tnkewo',
          text: '',
          url: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1700289261191-assets/web-upload/97fb8008-110e-45dd-a5f8-a95467224111.jpeg',
        }, 
        {
          id: 2,
          type: 'image',
          title: '海量分享',
          name: '总有你想不到的创意',
          text: '',
          url: 'https://cdn.nlark.com/yuque/0/2023/jpeg/280373/1700289261185-assets/web-upload/128758cf-3029-44df-830e-99510133ec9d.jpeg',
        } */],
      }
    },

    methods: {
      // 跳转
      tn(e) {
        uni.navigateTo({
          url: e,
        });
      },
      
      // cardSwiper
      cardSwiper(e) {
        this.cardCur = e.detail.current
      },
    }
  }
</script>

<style lang="scss" scoped>
  .template-vip {
    max-height: 100vh;
  }
  /* 底部安全边距 start*/
  .tn-tabbar-height {
    min-height: 120rpx;
    height: calc(140rpx + env(safe-area-inset-bottom) / 2);
    height: calc(140rpx + constant(safe-area-inset-bottom));
  }
  /* 分类展示 start */
  .charts-type {
    
    &__container {
      margin-top: 10rpx;
      margin-bottom: 50rpx;
    }
    
    &__item {
      width: 100%;
      margin: 15rpx 0rpx 30rpx 0rpx;
      padding: 40rpx 30rpx;
      border-radius: 10rpx;
      
  
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
  
      &__bottom {
        box-shadow: 0rpx 0rpx 30rpx 0rpx rgba(0, 0, 0, 0.12);
        border-radius: 0 0 10rpx 10rpx;
        position: absolute;
        width: 85%;
        line-height: 15rpx;
        left: 50%;
        bottom: -15rpx;
        transform: translateX(-50%);
        z-index: -1;
        text-align: center;
      }
    }
  }
  /* 分类展示 end */
  
  /* 轮播视觉差 start */
  .card-swiper {
    height: 500rpx !important;
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
    will-change: transform;
    overflow: hidden;
  }
    
  .card-swiper swiper-item.cur .swiper-item {
    transform: none;
    transition: all 0.2s ease-in 0s;
    will-change: transform;
  }
    
  .card-swiper swiper-item .swiper-item-text {
    margin-top: -380rpx;
    text-align: center;
    width: 100%;
    display: block;
    height: 50%;
    border-radius: 10rpx;
    transform: translate(100rpx, 0rpx) scale(0.9, 0.9);
    transition: all 0.6s ease 0s;
    will-change: transform;
    overflow: hidden;
  }
    
  .card-swiper swiper-item.cur .swiper-item-text {
    margin-top: -380rpx;
    width: 100%;
    transform: translate(0rpx, 0rpx) scale(0.9, 0.9);
    transition: all 0.6s ease 0s;
    will-change: transform;
  }
  
  /* 按钮 start*/
  .card-swiper swiper-item .go {
    z-index: 9999;
    width: 100%;
    position: fixed;
    margin: 0 auto;
    bottom: 90rpx;
  }
  
  .card-swiper swiper-item.cur .go {
    z-index: 9999;
    width: 100%;
    position: fixed;
    margin: 0 auto;
    bottom: 90rpx;
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
  }
  
  .spot{
    background-color: #00000010;
    opacity: 0.4;
    width: 10rpx;
    height: 10rpx;
    border-radius: 20rpx;
    top: -60rpx;
    margin: 0 8rpx !important;
    position: relative;
  }
  
  .spot.active{
    opacity: 0.6;
    width: 30rpx;
    background-color: #00000010;
  }
  
</style>