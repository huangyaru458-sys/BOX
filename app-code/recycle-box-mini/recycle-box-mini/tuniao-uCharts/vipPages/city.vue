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
    
    <!-- 图表数据源-时间2024年01月01日：http://datav.aliyun.com/tools/atlas/ 或 https://github.com/TangSY/echarts-map-demo/-->
    
    <view class="" :style="{paddingTop: vuex_custom_bar_height + 10 +  'px'}">
      
      <view class="tn-text-center tn-margin">
        因一次性加载全部网络数据会慢，也因懒得写延时加载，所以实际应用中自行延时处理
      </view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            全国
          </view>
          <!-- <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">34个省级行政区</text>
            <text class="tn-padding-left-xs tn-padding-right-xs">包括23个省、5个自治区、4个直辖市、2个特别行政区。</text>
            
          </view> -->
          <picker @change="bindPickerChange" :value="index" :range="array">
            <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-color-gray--dark" style="border-radius: 12rpx;">
              <view class="tn-padding-left-xs tn-padding-right-xs">{{array[index]}}</view>
              <view class="tn-icon-down tn-padding-right-xs"></view>
            </view>
          </picker>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="placeOpts" :chartData="placeChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            广东省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：粤</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="guangdongOpts" :chartData="guangdongChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            北京市
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：京</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="beijingOpts" :chartData="beijingChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            广西壮族自治区
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：桂</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="guangxiOpts" :chartData="guangxiChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            四川省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：川或蜀</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="sichuanOpts" :chartData="sichuanChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            浙江省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：浙</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="zhejiangOpts" :chartData="zhejiangChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            云南省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：云或滇</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="yunnanOpts" :chartData="yunnanChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            黑龙江省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：黑</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="heilongjiangOpts" :chartData="heilongjiangChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            青海省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：青</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="qinghaiOpts" :chartData="qinghaiChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            新疆维吾尔自治区
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：新</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="xinjiangOpts" :chartData="xinjiangChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            西藏自治区
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：藏</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="xizangOpts" :chartData="xizangChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            海南省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：琼</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="hainanOpts" :chartData="hainanChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            江西省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：赣</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="jiangxiOpts" :chartData="jiangxiChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            湖南省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：湘</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="hunanOpts" :chartData="hunanChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            辽宁省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：辽</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="liaoningOpts" :chartData="liaoningChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            上海市
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：沪</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="shanghaiOpts" :chartData="shanghaiChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            江苏省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：苏</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="jiangsuOpts" :chartData="jiangsuChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            内蒙古自治区
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：内蒙古</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="neimengguOpts" :chartData="neimengguChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            河南省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：豫</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="henanOpts" :chartData="henanChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            吉林省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：吉</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="jilinOpts" :chartData="jilinChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            甘肃省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：甘或陇</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="gansuOpts" :chartData="gansuChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            宁夏回族自治区
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：宁</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="ningxiaOpts" :chartData="ningxiaChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            湖北省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：鄂</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="hubeiOpts" :chartData="hubeiChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            陕西省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：陕或秦</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="shaanxiOpts" :chartData="shaanxiChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            河北省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：冀</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="hebeiOpts" :chartData="hebeiChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            山西省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：晋</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="shanxiOpts" :chartData="shanxiChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            天津市
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：津</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="tianjinOpts" :chartData="tianjinChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            山东省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：鲁</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="shandongOpts" :chartData="shandongChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            福建省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：闽</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="fujianOpts" :chartData="fujianChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            贵州省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：贵或黔</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="guizhouOpts" :chartData="guizhouChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            重庆市
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：渝</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="chongqingOpts" :chartData="chongqingChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            安徽省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：皖</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="anhuiOpts" :chartData="anhuiChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            香港特别行政区
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：港</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="xianggangOpts" :chartData="xianggangChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            澳门特别行政区
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：澳</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="aomenOpts" :chartData="aomenChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            台湾省
          </view>
          <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
            <text class="tn-padding-left-xs tn-padding-right-xs">行政区简称：台</text>
          </view>
        </view>
        <view class="" style="min-height: 500rpx;padding-top: 40rpx">
          <qiun-data-charts canvas2d type="map" :opts="taiwanOpts" :chartData="taiwanChartData" />
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
        index: 0,
        array: ['34个省级行政区', '广东省', '北京市', '广西壮族自治区', '四川省', '浙江省', '云南省', '黑龙江省', '青海省', '新疆维吾尔自治区', '西藏自治区藏', '海南省', '江西省', '湖南省', '辽宁省', '上海市', '江苏省', '内蒙古自治区', '河南省', '吉林省', '甘肃省', '宁夏回族自治区', '湖北省', '陕西省', '河北省', '山西省', '天津市', '山东省', '福建省', '贵州省', '重庆市', '安徽省', '香港特别行政区', '澳门特别行政区', '台湾省'],
        
        mapdataguangdong: {},
        mapdatabeijing: {},
        mapdataguangxi: {},
        mapdatasichuan: {},
        mapdatazhejiang: {},
        mapdatayunnan: {},
        mapdataheilongjiang: {},
        mapdataqinghai: {},
        mapdataxizang: {},
        mapdatahainan: {},
        mapdatajiangxi: {},
        mapdatahunan: {},
        mapdataliaoning: {},
        mapdatashanghai: {},
        mapdatajiangsu: {},
        mapdataneimenggu: {},
        mapdatahenan: {},
        mapdatajilin: {},
        mapdatagansu: {},
        mapdataningxia: {},
        mapdatahubei: {},
        mapdatashaanxi: {},
        mapdatahebei: {},
        mapdatashanxi: {},
        mapdatatianjin: {},
        mapdatashandong: {},
        mapdatafujian: {},
        mapdataguizhou: {},
        mapdatachongqing: {},
        mapdataanhui: {},
        mapdataxianggang: {},
        mapdataaomen: {},
        mapdatataiwan: {},
        
        // 全国
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
        
        // 广东省
        guangdongChartData: {},
        guangdongOpts: {
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
        
        // 北京市
        beijingChartData: {},
        beijingOpts: {
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
        
        // 广西壮族自治区
        guangxiChartData: {},
        guangxiOpts: {
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
        
        // 四川省
        sichuanChartData: {},
        sichuanOpts: {
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
        
        // 浙江省
        zhejiangChartData: {},
        zhejiangOpts: {
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
        
        // 云南省
        yunnanChartData: {},
        yunnanOpts: {
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
        
        // 黑龙江省
        heilongjiangChartData: {},
        heilongjiangOpts: {
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
        
        // 青海省
        qinghaiChartData: {},
        qinghaiOpts: {
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
        
        // 新疆维吾尔自治区
        xinjiangChartData: {},
        xinjiangOpts: {
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
        
        // 西藏自治区藏
        xizangChartData: {},
        xizangOpts: {
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
        
        // 海南省
        hainanChartData: {},
        hainanOpts: {
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
        
        // 江西省
        jiangxiChartData: {},
        jiangxiOpts: {
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
        
        // 湖南省
        hunanChartData: {},
        hunanOpts: {
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
        
        // 辽宁省
        liaoningChartData: {},
        liaoningOpts: {
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
        
        // 上海市
        shanghaiChartData: {},
        shanghaiOpts: {
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
        
        // 江苏省
        jiangsuChartData: {},
        jiangsuOpts: {
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
        
        // 内蒙古自治区
        neimengguChartData: {},
        neimengguOpts: {
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
        
        // 河南省
        henanChartData: {},
        henanOpts: {
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
        
        // 吉林省
        jilinChartData: {},
        jilinOpts: {
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
        
        // 甘肃省
        gansuChartData: {},
        gansuOpts: {
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
        
        // 宁夏回族自治区
        ningxiaChartData: {},
        ningxiaOpts: {
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
        
        // 湖北省
        hubeiChartData: {},
        hubeiOpts: {
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
        
        // 陕西省
        shaanxiChartData: {},
        shaanxiOpts: {
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
        
        // 河北省
        hebeiChartData: {},
        hebeiOpts: {
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
        
        // 山西省
        shanxiChartData: {},
        shanxiOpts: {
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
        
        // 天津市
        tianjinChartData: {},
        tianjinOpts: {
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
        
        // 山东省
        shandongChartData: {},
        shandongOpts: {
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
        
        // 福建省
        fujianChartData: {},
        fujianOpts: {
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
        
        // 贵州省
        guizhouChartData: {},
        guizhouOpts: {
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
        
        // 重庆市
        chongqingChartData: {},
        chongqingOpts: {
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
        
        // 安徽省
        anhuiChartData: {},
        anhuiOpts: {
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
        
        // 香港特别行政区
        xianggangChartData: {},
        xianggangOpts: {
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
        
        // 澳门特别行政区
        aomenChartData: {},
        aomenOpts: {
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
        
        // 台湾省
        taiwanChartData: {},
        taiwanOpts: {
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
     uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/440000.json',
        method: 'get',
        success: res => {
        this.mapdataguangdong = res.data
        this.drawGuangdongCharts()  //广东省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/110000.json',
        method: 'get',
        success: res => {
        this.mapdatabeijing = res.data
        this.drawBeijingCharts()  //北京市
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/450000.json',
        method: 'get',
        success: res => {
        this.mapdataguangxi = res.data
        this.drawGuangxiCharts()  //广西壮族自治区
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/510000.json',
        method: 'get',
        success: res => {
        this.mapdatasichuan = res.data
        this.drawSichuanCharts()  //四川省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/330000.json',
        method: 'get',
        success: res => {
        this.mapdatazhejiang = res.data
        this.drawZhejiangCharts()  //浙江省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/530000.json',
        method: 'get',
        success: res => {
        this.mapdatayunnan = res.data
        this.drawYunnanCharts()  //云南省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/230000.json',
        method: 'get',
        success: res => {
        this.mapdataheilongjiang = res.data
        this.drawHeilongjiangCharts()  //黑龙江省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/630000.json',
        method: 'get',
        success: res => {
        this.mapdataqinghai = res.data
        this.drawQinghaiCharts()  //青海省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/650000.json',
        method: 'get',
        success: res => {
        this.mapdataxinjiang = res.data
        this.drawXinjiangCharts()  //新疆维吾尔自治区
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/540000.json',
        method: 'get',
        success: res => {
        this.mapdataxizang = res.data
        this.drawXizangCharts() //西藏自治区藏
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/460000.json',
        method: 'get',
        success: res => {
        this.mapdatahainan = res.data
        this.drawHainanCharts()  //海南省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/360000.json',
        method: 'get',
        success: res => {
        this.mapdatajiangxi = res.data
        this.drawJiangxiCharts()  //江西省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/430000.json',
        method: 'get',
        success: res => {
        this.mapdatahunan = res.data
        this.drawHunanCharts()  //湖南省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/210000.json',
        method: 'get',
        success: res => {
        this.mapdataliaoning = res.data
        this.drawLiaoningCharts()  //辽宁省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/310000.json',
        method: 'get',
        success: res => {
        this.mapdatashanghai = res.data
        this.drawShanghaiCharts()  //上海市
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/320000.json',
        method: 'get',
        success: res => {
        this.mapdatajiangsu = res.data
        this.drawJiangsuCharts()  //江苏省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/150000.json',
        method: 'get',
        success: res => {
        this.mapdataneimenggu = res.data
        this.drawNeimengguCharts()  //内蒙古自治区
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/410000.json',
        method: 'get',
        success: res => {
        this.mapdatahenan = res.data
        this.drawHenanCharts()  //河南省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/220000.json',
        method: 'get',
        success: res => {
        this.mapdatajilin = res.data
        this.drawJilinCharts()  //吉林省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/620000.json',
        method: 'get',
        success: res => {
        this.mapdatagansu = res.data
        this.drawGansuCharts()  //甘肃省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/640000.json',
        method: 'get',
        success: res => {
        this.mapdataningxia = res.data
        this.drawNingxiaCharts()  //宁夏回族自治区
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/420000.json',
        method: 'get',
        success: res => {
        this.mapdatahubei = res.data
        this.drawHubeiCharts()  //湖北省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/610000.json',
        method: 'get',
        success: res => {
        this.mapdatashaanxi = res.data
        this.drawShaanxiCharts()  //陕西省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/130000.json',
        method: 'get',
        success: res => {
        this.mapdatahebei = res.data
        this.drawHebeiCharts()  //河北省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/140000.json',
        method: 'get',
        success: res => {
        this.mapdatashanxi = res.data
        this.drawShanxiCharts()  //山西省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/120000.json',
        method: 'get',
        success: res => {
        this.mapdatatianjin = res.data
        this.drawTianjinCharts()  //天津市
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/370000.json',
        method: 'get',
        success: res => {
        this.mapdatashandong = res.data
        this.drawShandongCharts()  //山东省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/350000.json',
        method: 'get',
        success: res => {
        this.mapdatafujian = res.data
        this.drawFujianCharts()  //福建省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/520000.json',
        method: 'get',
        success: res => {
        this.mapdataguizhou = res.data
        this.drawGuizhouCharts()  //贵州省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/500000.json',
        method: 'get',
        success: res => {
        this.mapdatachongqing = res.data
        this.drawChongqingCharts()  //重庆市
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/340000.json',
        method: 'get',
        success: res => {
        this.mapdataanhui = res.data
        this.drawAnhuiCharts()  //安徽省
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/810000.json',
        method: 'get',
        success: res => {
        this.mapdataxianggang = res.data
        this.drawXianggangCharts()  //香港特别行政区
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/820000.json',
        method: 'get',
        success: res => {
        this.mapdataaomen = res.data
        this.drawAomenCharts()  //澳门特别行政区
        }
      })
      uni.request({
        url: 'https://gitee.com/kewohuixiang/mapjson/raw/master/710000.json',
        method: 'get',
        success: res => {
        this.mapdatataiwan = res.data
        this.drawTaiwanCharts()  //台湾省
        }
      })
      
    },
    onReady() {
      this.drawPlaceCharts();  //全国-本地静态数据
    },
    mounted() {
    },
    
    methods: {
      bindPickerChange: function(e) {
        this.index = e.detail.value
      },
      
      // 全国 绘制
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
      
      // 广东省 绘制
      drawGuangdongCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.guangdongChartData = {series:this.mapdataguangdong.features};
      },
      
      // 北京市 绘制
      drawBeijingCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.beijingChartData = {series:this.mapdatabeijing.features};
      },
      
      // 广西壮族自治区 绘制
      drawGuangxiCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.guangxiChartData = {series:this.mapdataguangxi.features};
      },
      
      // 四川省 绘制
      drawSichuanCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.sichuanChartData = {series:this.mapdatasichuan.features};
      },
      
      // 浙江省 绘制
      drawZhejiangCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.zhejiangChartData = {series:this.mapdatazhejiang.features};
      },
      
      // 云南省 绘制
      drawYunnanCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.yunnanChartData = {series:this.mapdatayunnan.features};
      },
      
      // 黑龙江省 绘制
      drawHeilongjiangCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.heilongjiangChartData = {series:this.mapdataheilongjiang.features};
      },
      
      // 青海省 绘制
      drawQinghaiCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.qinghaiChartData = {series:this.mapdataqinghai.features};
      },
      
      // 新疆维吾尔自治区 绘制
      drawXinjiangCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.xinjiangChartData = {series:this.mapdataxinjiang.features};
      },
      
      // 西藏自治区藏 绘制
      drawXizangCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.xizangChartData = {series:this.mapdataxizang.features};
      },
      
      // 海南省 绘制
      drawHainanCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.hainanChartData = {series:this.mapdatahainan.features};
      },
      
      // 江西省 绘制
      drawJiangxiCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.jiangxiChartData = {series:this.mapdatajiangxi.features};
      },
      
      // 湖南省 绘制
      drawHunanCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.hunanChartData = {series:this.mapdatahunan.features};
      },
      
      // 辽宁省 绘制
      drawLiaoningCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.liaoningChartData = {series:this.mapdataliaoning.features};
      },
      
      // 上海市 绘制
      drawShanghaiCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.shanghaiChartData = {series:this.mapdatashanghai.features};
      },
      
      // 江苏省 绘制
      drawJiangsuCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.jiangsuChartData = {series:this.mapdatajiangsu.features};
      },
      
      // 内蒙古自治区 绘制
      drawNeimengguCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.neimengguChartData = {series:this.mapdataneimenggu.features};
      },
      
      // 河南省 绘制
      drawHenanCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.henanChartData = {series:this.mapdatahenan.features};
      },
      
      // 吉林省 绘制
      drawJilinCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.jilinChartData = {series:this.mapdatajilin.features};
      },
      
      // 甘肃省 绘制
      drawGansuCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.gansuChartData = {series:this.mapdatagansu.features};
      },
      
      // 宁夏回族自治区 绘制
      drawNingxiaCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.ningxiaChartData = {series:this.mapdataningxia.features};
      },
      
      // 湖北省 绘制
      drawHubeiCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.hubeiChartData = {series:this.mapdatahubei.features};
      },
      
      // 陕西省 绘制
      drawShaanxiCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.shaanxiChartData = {series:this.mapdatashaanxi.features};
      },
      
      // 河北省 绘制
      drawHebeiCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.hebeiChartData = {series:this.mapdatahebei.features};
      },
      
      // 山西省 绘制
      drawShanxiCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.shanxiChartData = {series:this.mapdatashanxi.features};
      },
      
      // 天津市 绘制
      drawTianjinCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.tianjinChartData = {series:this.mapdatatianjin.features};
      },
      
      // 山东省 绘制
      drawShandongCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.shandongChartData = {series:this.mapdatashandong.features};
      },
      
      // 福建省 绘制
      drawFujianCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.fujianChartData = {series:this.mapdatafujian.features};
      },
      
      // 贵州省 绘制
      drawGuizhouCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.guizhouChartData = {series:this.mapdataguizhou.features};
      },
      
      // 重庆市 绘制
      drawChongqingCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.chongqingChartData = {series:this.mapdatachongqing.features};
      },
      
      // 安徽省 绘制
      drawAnhuiCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.anhuiChartData = {series:this.mapdataanhui.features};
      },
      
      // 香港特别行政区 绘制
      drawXianggangCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.xianggangChartData = {series:this.mapdataxianggang.features};
      },
      
      // 澳门特别行政区 绘制
      drawAomenCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.aomenChartData = {series:this.mapdataaomen.features};
      },
      
      // 台湾省 绘制
      drawTaiwanCharts() {
        let res = {
          series:{
            说明: "地图数据遵循geoJson地图数据交换格式，引用方式请见插件市场示例项目：https://ext.dcloud.net.cn/plugin?id=271",
            备注: "其他地图数据下载地址：http://datav.aliyun.com/tools/atlas/",
            注意: "如果您引用数据的坐标系是WGS84地球坐标系，会导致图形变形，需要在【扩展配置】中开启【是否进行WGS84转墨卡托投影】功能（开启后因大量的数据运算tooltip可能会不跟手，建议自行转换为墨卡托坐标系，可参照源码内function lonlat2mercator()）"
            },
          };
        this.taiwanChartData = {series:this.mapdatataiwan.features};
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