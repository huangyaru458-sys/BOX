<template>
  <view class="template-news tn-safe-area-inset-bottom">
    
    
    <!-- 功能入口-->
    <!-- <view class="charts-type__container tn-flex tn-flex-wrap tn-flex-col-center tn-flex-row-between tn-margin-left tn-margin-right" :style="{paddingTop: vuex_custom_bar_height + 10 + 'px'}">
      <block v-for="(item, index) in navList" :key="index">
        <view class="charts-type__item tn-flex tn-flex-direction-row tn-flex-col-center tn-flex-row-between tn-shadow-blur" :class="'tn-bg-'+ item.color + '--light; tn-color-'+ item.color + ';' " @click="tn(item.url)">
          <view class="charts-type__item__left tn-flex tn-flex-direction-row tn-flex-col-center tn-flex-row-left">
            <view class="">
              <view class="tn-text-bold" style="font-size: 32rpx;">{{ item.title }}</view>
            </view>
          </view>
          <view class="charts-type__item__bottom">
            <view class='name tn-text-sm tn-color-gray' style="margin-left: -10rpx;">
              <text class="tn-icon-code tn-padding-right-xs" style="opacity: 0;"></text>
            </view>
          </view>
        </view>
      </block>
    </view> -->
    
    <view class="home-fixed">
    </view>
    
    
    <!-- 功能入口-->
    <view class="charts-type__container tn-flex tn-flex-wrap tn-flex-col-center tn-flex-row-between tn-margin-left tn-margin-right" :style="{paddingTop: vuex_custom_bar_height + 10 + 'px'}">
      <block v-for="(item, index) in navList" :key="index">
        
        <!-- <view class="tn-color-blue tn-text-bold tn-text-xl tn-padding-bottom tn-padding-top">{{ item.title }}</view> -->
        
        <block v-for="(content_item, content_index) in item.list" :key="content_index">
          <navigator open-type="navigate" hover-class='none' :url="content_item.url" class="charts-type__item tn-shadow-blur" :class="'tn-bg-'+ content_item.color + '--light; tn-color-'+ content_item.color + ';' ">
            <view class="tn-text-center">
              <text class="tn-text-bold" style="font-size: 32rpx;">{{ content_item.title }}</text>
            </view>
            <view class="charts-type__item__bottom">
              <view class='name tn-text-sm tn-color-gray' style="margin-left: -10rpx;">
                <text class="tn-icon-code tn-padding-right-xs"></text>
                <text class="tn-text-sm">{{ content_item.author }}</text>
              </view>
            </view>
            
           <!-- <view class="author">
              <view class='name tn-text-sm tn-color-gray' style="margin-left: -10rpx;">
                <text class="tn-icon-code tn-padding-right-xs"></text>
                <text class=""> {{ content_item.author }} </text>
              </view>
            </view> -->
          </navigator>
        </block>
        
      </block>
    </view>
    
    
    <view class="tn-tabbar-height"></view>
    
    
  </view>
</template>

<script>
  import vipListData1 from '@/libs/navigation/navigation1.js'
  export default {
    name: 'News',
    data() {
      return {
        // nav菜单列表
        navList: vipListData1.data,
        
        /* tuniaoData: [
          {
            title: '敬请期待',
            color: 'purplered',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'bluepurple',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'red',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'aquablue',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'orangered',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'blue',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'orange',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'indigo',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'orangeyellow',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'cyan',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'lime',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'teal',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'yellowgreen',
            url: '/newsPages/xxxx'
          },
          {
            title: '敬请期待',
            color: 'green',
            url: '/newsPages/xxxx'
          },
        ], */
      }
    },

    methods: {
      // 跳转
      tn(e) {
        uni.navigateTo({
          url: e,
        });
      },
    }
  }
</script>

<style lang="scss" scoped>
  .template-news {
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
      width: 47.7%;
      margin: 15rpx 0rpx 80rpx 0rpx;
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
        border-radius: 0 0 15rpx 15rpx;
        position: absolute;
        width: 85%;
        line-height: 50rpx;
        left: 50%;
        bottom: -50rpx;
        transform: translateX(-50%);
        z-index: -1;
        text-align: center;
      }
    }
  }
  /* 分类展示 end */
  
  // 四个角渐变底色
  .home-fixed{
    position: fixed;
    background: linear-gradient(90deg, #DBF2FE, #FFE1E1);
    top: 0;
    width: 100%;
    transition: all 0.25s ease-out;
    z-index: -1;
    min-height: 20vh;
  }
  .home-fixed:before{
    content: "";
    position: absolute;
    top: 0;
    left: 0;
    bottom: 0;
    right: 0;
    z-index: -1;
    mask-image: linear-gradient(to bottom, transparent, black);
    background: linear-gradient(90deg, #FFFFFF, #FFFFFF);	
  
  }
  
  
</style>