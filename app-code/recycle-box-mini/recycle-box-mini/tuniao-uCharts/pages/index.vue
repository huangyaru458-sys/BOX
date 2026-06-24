<template>
  <view class="start-index">
    <view v-if="tabberPageLoadFlag[0]" :style="{display: currentIndex === 0 ? '' : 'none'}">
      <scroll-view class="custom-tabbar-page" scroll-y enable-back-to-top @scrolltolower="tabbarPageScrollLower">
        <Home ref="home"></Home>
      </scroll-view>
    </view>
    <view v-if="tabberPageLoadFlag[1]" :style="{display: currentIndex === 1 ? '' : 'none'}">
      <scroll-view class="custom-tabbar-page" scroll-y enable-back-to-top @scrolltolower="tabbarPageScrollLower">
        <Vip ref="vip"></Vip>
      </scroll-view>
    </view>
    <view v-if="tabberPageLoadFlag[2]" :style="{display: currentIndex === 2 ? '' : 'none'}">
      <scroll-view class="custom-tabbar-page" scroll-y enable-back-to-top @scrolltolower="tabbarPageScrollLower">
        <News ref="news"></News>
      </scroll-view>
    </view>
    <view v-if="tabberPageLoadFlag[3]" :style="{display: currentIndex === 3 ? '' : 'none'}">
      <scroll-view class="custom-tabbar-page" scroll-y enable-back-to-top @scrolltolower="tabbarPageScrollLower">
        <Mine ref="mine"></Mine>
      </scroll-view>
    </view>
    
    <tn-tabbar
      v-model="currentIndex"
      :list="tabbarList"
      activeColor="#3668FC"
      inactiveColor="#C5CAD5"
      activeIconColor="#3668FC"
      inactiveIconColor="#C5CAD5"
      :animation="true"
      :safeAreaInsetBottom="true"
      @change="switchTabbar"
    ></tn-tabbar>
  </view>
</template>

<script>
  import Home from './home/home.vue'
  import Vip from './vip/vip.vue'
  import News from './news/news.vue'
  import Mine from './mine/mine.vue'
  
  export default {
    components: {
      Home,
      Vip,
      News,
      Mine
    },
    data() {
      return {
        // 底部tabbar菜单数据
        tabbarList: [
          {
            title: '免费商用',
            // activeIcon: '/static/tabbar/tn-tabbar0-curnew.png',
            // inactiveIcon: '/static/tabbar/tn-tabbar0.png'
            activeIcon: 'home-fill',
            inactiveIcon: 'home-fill',
            iconSize: 50
          },
          {
            title: '会员模板',
            /* activeIcon: '/static/tabbar/tn-tabbar1-curnew.png',
            inactiveIcon: '/static/tabbar/tn-tabbar1.png' */
            activeIcon: 'vip-diamond-fill',
            inactiveIcon: 'vip-diamond-fill',
            // count: '12',
            iconSize: 50
          },
          {
            title: '免费模板',
            /* activeIcon: '/static/tabbar/tn-tabbar2-curnew.png',
            inactiveIcon: '/static/tabbar/tn-tabbar2.png' */
            activeIcon: 'iot-fill',
            inactiveIcon: 'iot-fill',
            iconSize: 50
          },
          {
            title: '关于我们',
            /* activeIcon: '/static/tabbar/tn-tabbar3-curnew.png',
            inactiveIcon: '/static/tabbar/tn-tabbar3.png' */
            activeIcon: 'my-simple-fill',
            inactiveIcon: 'my-simple-fill',
            iconSize: 50
          }
        ],
        // tabbar当前被选中的序号
        currentIndex: 0,
        // 自定义底栏对应页面的加载情况
        tabberPageLoadFlag: []
      }
    },
    onLoad(options) {
      const index = Number(options.index || 0)
      // 根据底部tabbar菜单列表设置对应页面的加载情况
      this.tabberPageLoadFlag = this.tabbarList.map((item, tabbar_index) => {
        return index === tabbar_index
      })
      this.switchTabbar(index)
    },
    methods: {
      // 切换导航
      switchTabbar(index) {
        this._switchTabbarPage(index)
      },
      
      // 导航页面滚动到底部
      tabbarPageScrollLower(e) {
        // if (this.currentIndex === 2) {
        //   this.$refs.news.getRandomData && this.$refs.news.getRandomData()
        // }
      },

      // 切换导航页面
      _switchTabbarPage(index) {
        wx.vibrateShort();
        const selectPageFlag = this.tabberPageLoadFlag[index]
        if (selectPageFlag === undefined) {
          return
        }
        if (selectPageFlag === false) {
          this.tabberPageLoadFlag[index] = true
        }
        this.currentIndex = index
      }
    }
  }
</script>

<style lang="scss" scoped>
</style>
