<template>
  <view class="template-mine tn-safe-area-inset-bottom">
    
    <view class="container about-bg" style="background-image:url('https://resource.tuniaokj.com/images/about/about-charts.png')">
    </view>
    
    <button class='' open-type="contact">
      <view class="wechat tnxuanfu">
        <view class="bg0 pa">
          <view class="bg1">
            <image src="https://resource.tuniaokj.com/images/my/my7.png" class="button-shop shadow"></image>
          </view>
        </view>
        <view class="hx-box pa">
          <view class="pr">
            <view class="hx-k1 pa0">
              <view class="span"></view>
            </view>
            <view class="hx-k2 pa0">
              <view class="span"></view>
            </view>
            <view class="hx-k3 pa0">
              <view class="span"></view>
            </view>
            <view class="hx-k4 pa0">
              <view class="span"></view>
            </view>
            <view class="hx-k5 pa0">
              <view class="span"></view>
            </view>
            <view class="hx-k6 pa0">
              <view class="span"></view>
            </view>
          </view>
        </view>
      </view>
    </button>
  </view>
</template>

<script>
  export default {
    name: 'Mine',
    data() {
      return {
        
      }
    },
    
    methods: {
      
    }
  }
</script>

<style lang="scss" scoped>
  .template-mine {
    margin: 0;
    width: 100%;
    height: 100vh;
    max-height: 100vh;
    color: #fff;
    background: linear-gradient(-120deg, #F15BB5, #9A5CE5, #01BEFF, #00F5D4);
    /* background: linear-gradient(-120deg,  #9A5CE5, #01BEFF, #00F5D4, #43e97b); */
    /* background: linear-gradient(-120deg,#c471f5, #ec008c, #ff4e50,#f9d423); */
    /* background: linear-gradient(-120deg, #0976ea, #c471f5, #f956b6, #ea7e0a); */
    background-size: 500% 500%;
    animation: gradientBG 15s ease infinite;
    
    position: relative;
    
    .bubble {
      position: fixed;
      bottom: -10vh;
      right: 0;
      z-index: 1024;
      pointer-events: none;
      // background-color: red;
    }
  }
  
  
  .about-bg {
    background-size: cover;
    width: 100vw;
    height: 100vh;
    justify-content: center;
    flex-direction: column;
    color: #fff;
  }
  
  
  
  
  @keyframes gradientBG {
    0% {
      background-position: 0% 50%;
    }
  
    50% {
      background-position: 100% 50%;
    }
  
    100% {
      background-position: 0% 50%;
    }
  }
  
  .container {
    width: 100%;
    position: absolute;
    text-align: center;
  }
  
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
  
  /* 悬浮 */
  .tnxuanfu{
    animation: suspension 3s ease-in-out infinite;
  }
  
  @keyframes suspension {
    0%, 100% {
      transform: translateY(0);
    }
    50% {
      transform: translateY(-0.8rem);
    }
  }
  /* 悬浮按钮 */
  .button-shop {
    width: 90rpx;
    height: 90rpx;
    display: flex;
    flex-direction: row;
    position: fixed;
    /* bottom:200rpx;
      right: 20rpx; */
    left: 5rpx;
    top: 5rpx;
    z-index: 1001;
    border-radius: 100px;
    opacity: 0.9;
  }
  
  
  /* 按钮 */
  .wechat {
    bottom: 300rpx;
    right: 75rpx;
    position: fixed;
    z-index: 9999;
  }
  
  
  .pa,
  .pa0 {
    position: absolute
  }
  
  .pa0 {
    left: 0;
    top: 0
  }
  
  
  .bg0 {
    width: 100rpx;
    height: 100rpx;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
  }
  
  .bg1 {
    width: 100%;
    height: 100%;
  }
  
  
  
  
  .hx-box {
    top: 50%;
    left: 50%;
    width: 100rpx;
    height: 100rpx;
    transform-style: preserve-3d;
    transform: translate(-50%, -50%) rotateY(75deg) rotateZ(10deg);
  }
  
  .hx-box .pr {
    width: 100rpx;
    height: 100rpx;
    transform-style: preserve-3d;
    animation: hxz 20s linear infinite;
  }
  
  @keyframes hxz {
    0% {
      transform: rotateX(0deg);
    }
  
    100% {
      transform: rotateX(-360deg);
    }
  }
  
  
  
  .hx-box .pr .pa0 {
    width: 100rpx;
    height: 100rpx;
    /* border: 4px solid #5ec0ff; */
    border-radius: 1000px;
  }
  
  .hx-box .pr .pa0 .span {
    display: block;
    width: 100%;
    height: 100%;
    background: url(https://resource.tuniaokj.com/images/cool_bg_image/arc4.png) no-repeat center center;
    background-size: 100% 100%;
    animation: hx 4s linear infinite;
  }
  
  @keyframes hx {
    to {
      transform: rotate(360deg);
    }
  }
  
  .hx-k1 {
    transform: rotateX(-60deg) rotateZ(-60deg)
  }
  
  .hx-k2 {
    transform: rotateX(-30deg) rotateZ(-30deg)
  }
  
  .hx-k3 {
    transform: rotateX(0deg) rotateZ(0deg)
  }
  
  .hx-k4 {
    transform: rotateX(30deg) rotateZ(30deg)
  }
  
  .hx-k5 {
    transform: rotateX(60deg) rotateZ(60deg)
  }
  
  .hx-k6 {
    transform: rotateX(90deg) rotateZ(90deg)
  }
</style>