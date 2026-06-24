<template>
  <view class="template-content bg-black">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed customBack :bottomShadow="false" backgroundColor="#0D0B30">
      <view slot="back" class='tn-custom-nav-bar__back'
        @click="goBack">
        <text class='icon tn-icon-left'></text>
        <text class='icon tn-icon-home-capsule-fill'></text>
      </view>
      <view class="tn-flex tn-flex-col-center tn-flex-row-center ">
        <text class="tn-text-bold tn-text-xl tn-color-white">酷炫移动端看板</text>
      </view>
    </tn-nav-bar>
    
    <!-- 模拟器上，图表是显示在最上层挡住很多东西，真机是没有问题的，因为加了canvas2d处理 -->
    <!-- 如因一次性加载太多太多，所以会慢，也因懒得写延时加载，所以实际应用中自行延时处理 -->
    
    <view class="tn-color-white tn-padding-bottom-xl" :style="{paddingTop: vuex_custom_bar_height + 30 +'px'}">
      
      <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          业务数据
        </view>
        <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
      
      <view class="tn-flex tn-flex-wrap tn-padding-bottom" style="margin: 15rpx;">
        <view v-for="(item, index) in tuniaoData" :key="index" style="width: 50%;">
          <view class="tn-flex tn-flex-row-between tn-flex-col-center" style="margin: 15rpx;padding: 30rpx 20rpx;border-radius: 15rpx;background-color: #1B193C;">
            <view class="justify-content-item ">
              <view class="tn-flex tn-flex-col-center tn-flex-row-left">
                <view class="icon12__item--icon tn-flex tn-flex-row-center tn-flex-col-center tn-color-white" :style="'background-color:'+ item.color +';'">
                  <view :class="[`tn-icon-${item.icon}`]"></view>
                </view>  
                <view class="">
                  <view class="tn-padding-right tn-padding-left-sm">
                    <text style="font-size: 42rpx;">{{ item.title }}</text>
                    <text class="tn-text-sm tn-padding-left-xs" style="opacity: 0.7;">万</text>
                  </view>
                  <view class="tn-padding-right tn-padding-top-xs tn-text-sm tn-padding-left-sm tn-text-ellipsis tn-color-gray">
                    
                    <text class="tn-padding-right-xs">较上年</text>
                    <text :style="'color:'+ item.updown +';'">{{ item.number }}</text>
                  </view>
                </view>
              </view>
            </view>
          </view>
        </view>  
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            流量来源
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="bubble" :opts="flowOpts" :chartData="flowChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            营收占比
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            集团成员
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="pie" :opts="memberOpts" :chartData="memberChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            用户终端
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="rose" :opts="terminalOpts" :chartData="terminalChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            用户转化
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="funnel" :opts="convertOpts" :chartData="convertChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            贸易数量
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="mount" :opts="saleOpts" :chartData="saleChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            公司盈利
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            员工年龄
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="scatter" :opts="ageOpts" :chartData="ageChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            月度盈利
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="column" :opts="monthOpts" :chartData="monthChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            月度盈利
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="column" :opts="monthOpts1" :chartData="monthChartData1" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            区域业绩
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="bar" :opts="firmOpts" :chartData="firmChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            区域业绩
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="bar" :opts="firmOpts1" :chartData="firmChartData1" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            公司营收
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="line" :opts="revenueOpts" :chartData="revenueChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            公司营收
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="line" :opts="revenueOpts1" :chartData="revenueChartData1" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            员工能力
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="radar" :opts="abilityOpts" :chartData="abilityChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            员工能力
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="radar" :opts="abilityOpts1" :chartData="abilityChartData1" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            年度词云
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="word" :opts="wordOpts" :chartData="wordChartData" background="#0D0B30" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            员工分布
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
        <view class="" style="min-height: 500rpx;padding-top: 40rpx;">
          <qiun-data-charts canvas2d type="map" :opts="placeOpts" :chartData="placeChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            出勤请假
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="arcbar" :opts="workOpts" :chartData="workChartData" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            出勤请假
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="arcbar" :opts="workOpts1" :chartData="workChartData1" />
        </view>
      </view>
      
      <view class="tn-strip-bottom-min"></view>
      
      <view class="tn-padding-top-xl tn-padding-bottom-xl">
        <view class="tn-flex tn-flex-row-between tn-flex-col-center">
          <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
            公司股价
          </view>
          <view class="tn-flex tn-flex-col-center justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-radius tn-color-gray--dark" style="background-color: #1B193C;">
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
          <qiun-data-charts canvas2d type="candle" :opts="stockOpts" :chartData="stockChartData" background="#0D0B30" :disableScroll="true" :ontouch="true" :onzoom="true" />
        </view>
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
    data(){
      return {
        date: '2023-07',
        date1: '2024-03',
        
        tuniaoData: [
          {
            title: '1,209',
            icon: 'cube-fill',
            color: '#FB6A67',
            number: '+21%',
            updown: '#00D05E',
          },
          {
            title: '609',
            icon: 'cube-fill',
            color: '#FFAC00',
            number: '+18%',
            updown: '#00D05E',
          },
          {
            title: '9,613',
            icon: 'cube-fill',
            color: '#957BFE',
            number: '-12%',
            updown: '#FB6A67',
          },
          {
            title: '3,822',
            icon: 'cube-fill',
            color: '#4B98FE',
            number: '+16%',
            updown: '#00D05E',
          },
          {
            title: '2068',
            icon: 'cube-fill',
            color: '#00C8B0',
            number: '+22%',
            updown: '#00D05E',
          },
          {
            title: '522',
            icon: 'cube-fill',
            color: '#FE871B',
            number: '+9%',
            updown: '#00D05E',
          }
        ],
        
        // 流量来源
        flowChartData: {},
        flowOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: true,
          xAxis: {
            disableGrid: true,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
            splitNumber: 4,
            min: 0,
            max: 260
          },
          yAxis: {
            gridColor: "rgba(230,230,230,0.1)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              fontColor: "#868598",
              axisLineColor: "#1B193C",
            }, ],
          },
          legend: {
            show: false,
            position: "top",
            float: "right",
          },
          extra: {
            bubble: {
              border: 0.4,
              opacity: 0.5
            }
          }
        },
        
        // 营收占比
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
              centerColor: "#0D0B30",
              ringWidth: 30,
              activeOpacity: 0.5,
              activeRadius: 10,
              offsetAngle: 0,
              labelWidth: 15,
              border: true,
              borderWidth: 2,
              borderColor: "#0D0B30",
              // linearType: "custom",
              // customColor: ["#24F083"],
            }
          }
        },
        
        // 集团成员
        memberChartData: {},
        memberOpts: {
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
            pie: {
              activeOpacity: 0.5,
              activeRadius: 10,
              offsetAngle: 0,
              labelWidth: 15,
              border: true,
              borderWidth: 2,
              borderColor: "#0D0B30",
            }
          }
        },
        
        // 用户终端
        terminalChartData: {},
        terminalOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15,10,15,10],
          dataLabel: true,
          enableScroll: false,
          legend: {
            show: true,
            position: "left",
            lineHeight: 32
          },
          extra: {
            rose: {
              type: "radius",
              minRadius: 50,
              activeOpacity: 0.5,
              activeRadius: 10,
              offsetAngle: 0,
              labelWidth: 15,
              border: true,
              borderWidth: 2,
              borderColor: "#0D0B30"
            }
          }
        },
        
        // 用户转化
        convertChartData: {},
        convertOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15,15,0,15],
          dataLabel: true,
          enableScroll: false,
          // legend: {
          //   show: true,
          //   position: "left",
          //   lineHeight: 32
          // },
          extra: {
            funnel: {
              activeOpacity: 0.5,
              activeWidth: 10,
              border: true,
              borderWidth: 2,
              borderColor: "#0D0B30",
              fillOpacity: 1,
              labelAlign: "right",
              // minSize: 12
            }
          }
        },
        
        // 贸易数量
        saleChartData: {},
        saleOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
          },
          yAxis: {
            gridColor: "rgba(255,255,255,0.1)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              fontColor: "#868598",
              axisLineColor: "#1B193C",
            }, ],
          },
          legend: {
            show: false,
            position: "top",
            float: "right",
          },
          extra: {
            mount: {
              type: "sharp",
              widthRatio: 1.2,
            }
          }
        },
        
        // 公司盈利
        incomeChartData: {},
        incomeOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          dataPointShape: false,
          xAxis: {
            disableGrid: true,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
          },
          yAxis: {
            gridColor: "rgba(255,255,255,0.1)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              fontColor: "#868598",
              axisLineColor: "#1B193C",
              min: 1500,
              max: 2000
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
              opacity: 0.2,
              addLine: true,
              width: 2,
              gradient: false,
            },
          },
        },
        
        // 员工年龄
        ageChartData: {},
        ageOpts: {
          color: ["#4B98FE","#FB6A67","#FFAC00","#00D05E","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15,15,0,15],
          dataLabel: false,
          enableScroll: false,
          xAxis: {
            disableGrid: true,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
          },
          yAxis: {
            gridColor: "rgba(255,255,255,0.1)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              fontColor: "#868598",
              axisLineColor: "#1B193C",
            }, ],
          },
          legend: {
            show: true,
            position: "bottom",
            // float: "right",
          },
          extra: {
            scatter: {}
          }
        },
        
        // 月度盈利
        monthChartData: {},
        monthOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
          },
          yAxis: {
            gridColor: "rgba(255,255,255,0.1)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              fontColor: "#868598",
              axisLineColor: "#1B193C",
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
              width: 5,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
              barBorderCircle: true,
              linearType: "custom",
              customColor: ["#24F083"],
            }
          },
        },
        
        // 月度盈利
        monthChartData1: {},
        monthOpts1: {
          color: ["#FB6A67","#00D05E","#FFAC00","#4B98FE","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: true,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
          },
          yAxis: {
            gridColor: "rgba(255,255,255,0.1)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              fontColor: "#868598",
              axisLineColor: "#1B193C",
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
              width: 5,
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
              barBorderCircle: true,
              linearType: "custom",
              customColor: ["#FFAC00"],
            }
          },
        },
        
        // 区域业绩
        firmChartData: {},
        firmOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: false,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
            gridColor: "rgba(255,255,255,0.1)",
            gridType: 'dash',
          },
          yAxis: {
            gridColor: "rgba(255,255,255,0.1)",
            disabled: false,
            disableGrid: true,
            gridType: 'dash',
            dashLength: '4',
            gridColor: "rgba(255,255,255,0.1)",
            data: [{
              type: 'categories',
              axisLineColor: "#1B193C",
              fontColor: "#868598",
            }, ],
          },
          
          legend: {
            show: false,
            position: "top",
            float: "right",
          },
          extra: {
            bar: {
              type: "group",
              width: 5,
              meterBorde: 1,
              meterFillColor: "#FFFFFF",
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
              categoryGap: 2,
              linearType: "custom",
              customColor: ["#24F083"],
              barBorderCircle: true,
            }
          }
        },
        
        // 区域业绩
        firmChartData1: {},
        firmOpts1: {
          color: ["#FB6A67","#00D05E","#FFAC00","#4B98FE","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          xAxis: {
            disableGrid: false,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
            gridColor: "rgba(255,255,255,0.1)",
            gridType: 'dash',
          },
          yAxis: {
            gridColor: "rgba(255,255,255,0.1)",
            disabled: false,
            disableGrid: true,
            gridType: 'dash',
            dashLength: '4',
            gridColor: "rgba(255,255,255,0.1)",
            data: [{
              type: 'categories',
              axisLineColor: "#1B193C",
              fontColor: "#868598",
            }, ],
          },
          
          legend: {
            show: false,
            position: "top",
            float: "right",
          },
          extra: {
            bar: {
              type: "group",
              width: 5,
              meterBorde: 1,
              meterFillColor: "#FFFFFF",
              activeBgColor: "#000000",
              activeBgOpacity: 0.04,
              categoryGap: 2,
              linearType: "custom",
              customColor: ["#FFAC00"],
              barBorderCircle: true,
            }
          }
        },
        
        // 公司营收
        revenueChartData: {},
        revenueOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          dataPointShape: false,
          xAxis: {
            disableGrid: true,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
          },
          yAxis: {
            gridColor: "rgba(255,255,255,0.1)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              fontColor: "#868598",
              axisLineColor: "#1B193C",
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
        
        // 公司营收
        revenueChartData1: {},
        revenueOpts1: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15, 15, 0, 15],
          dataLabel: false,
          dataPointShape: false,
          xAxis: {
            disableGrid: true,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
          },
          yAxis: {
            gridColor: "rgba(255,255,255,0.1)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              fontColor: "#868598",
              axisLineColor: "#1B193C",
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
        
        // 员工能力
        abilityChartData: {},
        abilityOpts: {
          color: ["#24F083","#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
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
              gridType: "radar",
              gridColor: "#1B193C",
              gridCount: 2,
              opacity: 0.2,
              max: 100,
              labelShow: true,
              border: true
            }
          }
        },
        
        // 员工能力
        abilityChartData1: {},
        abilityOpts1: {
          color: ["#FFAC00","#4B98FE","#00D05E","#24F083","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
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
              gridType: "radar",
              gridColor: "#1B193C",
              gridCount: 2,
              opacity: 0.2,
              max: 100,
              labelShow: true,
              border: true
            }
          }
        },
        
        // 年度词云
        wordChartData: {},
        wordOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: undefined,
          dataLabel: true,
          enableScroll: false,
          extra: {
            word: {
              type: "normal",
              autoColors: false
            }
          }
        },
        
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
              borderColor: "#868598",
              fillOpacity: 0.5,
              activeBorderColor: "#FFFFFF",
              activeFillColor: "#4B98FE",
              activeFillOpacity: 1
            }
          }
        },
        
        // 出勤请假
        workChartData: {},
        workOpts: {
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: undefined,
          title: {
            name: "62.46%",
            fontSize: 22,
            color: "#FFFFFF"
          },
          subtitle: {
            name: "全勤率",
            fontSize: 12,
            color: "#868598",
            offsetY: 12
          },
          extra: {
            arcbar: {
              type: "circle",
              width: 8,
              backgroundColor: "#1B193C",
              startAngle: 1.5,
              endAngle: 0.25,
              gap: 2,
              direction: "ccw",
              linearType: "custom",
              customColor: ["#24F083"],
            }
          }
        },
        
        // 出勤请假
        workChartData1: {},
        workOpts1: {
          color: ["#FB6A67","#00D05E","#FFAC00","#4B98FE","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: undefined,
          title: {
            name: "62.46%",
            fontSize: 22,
            color: "#FFFFFF"
          },
          subtitle: {
            name: "全勤率",
            fontSize: 12,
            color: "#868598",
            offsetY: 12
          },
          extra: {
            arcbar: {
              type: "circle",
              width: 8,
              backgroundColor: "#1B193C",
              startAngle: 1.5,
              endAngle: 0.25,
              gap: 2,
              direction: "ccw",
              linearType: "custom",
              customColor: ["#FFAC00"],
            }
          }
        },
        
        // 公司股价
        stockChartData: {},
        stockOpts: {
          rotate: false,
          rotateLock: false,
          color: ["#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
          padding: [15,15,0,15],
          dataLabel: false,
          touchMoveLimit: 24,
          enableScroll: true,
          enableMarkLine: true,
          xAxis: {
            disableGrid: true,
            fontColor: "#868598",
            axisLineColor: "#1B193C",
            labelCount: 6,
            itemCount: 36,
            scrollShow: true,
            scrollAlign: "left",
            scrollColor: "#868598",
            scrollBackgroundColor: "#1B193C"
          },
          yAxis: {
            gridColor: "rgba(255,255,255,0.1)",
            disabled: false,
            disableGrid: false,
            gridType: 'dash',
            dashLength: '4',
            data: [{
              fontColor: "#868598",
              axisLineColor: "#1B193C",
            }, ],
          },
          legend: {
            show: false,
            position: "top",
            float: "right",
          },
          extra: {
            candle: {
              color: {
                upLine: "#FB6A67",
                upFill: "#FB6A67",
                downLine: "#00D05E",
                downFill: "#00D05E"
              },
              average: {
                show: true,
                name: [
                  "TN01",
                  "TN02",
                  "TN09"
                ],
                day: [
                  5,
                  10,
                  20
                ],
                color: [
                  "#4B98FE",
                  "#00C8B0",
                  "#FFAC00"
                ]
              }
            },
            markLine: {
              type: "dash",
              dashLength: 5,
              data: [
                {
                  value: 2150,
                  lineColor: "rgba(254,135,27,0)",
                  showLabel: false
                },
                {
                  value: 2350,
                  lineColor: "rgba(254,135,27,0)",
                  showLabel: false
                }
              ]
            },
            tooltip: {
              showCategory: true
            }
          }
        },
        
      }
    },
    onReady() {
      this.drawFlowCharts();  //流量来源
      this.drawMakeupCharts();  //营收占比
      this.drawMemberCharts();  //集团成员
      this.drawTerminalCharts();  //用户终端
      this.drawConvertCharts();  //用户转化
      this.drawSaleCharts();  //贸易数量
      this.drawIncomeCharts();  //公司盈利
      this.drawAgeCharts();  //员工年龄
      this.drawMonthCharts();  //月度盈利
      this.drawMonthCharts1();  //月度盈利
      this.drawFirmCharts();  //区域业绩
      this.drawFirmCharts1();  //区域业绩
      this.drawRevenueCharts();  //公司营收
      this.drawRevenueCharts1();  //公司营收
      this.drawAbilityCharts();  //员工能力
      this.drawAbilityCharts1();  //员工能力
      this.drawWordCharts();  //年度词云
      this.drawPlaceCharts();  //员工分布
      this.drawWorkCharts();  //出勤请假
      this.drawWorkCharts1();  //出勤请假
      this.drawStockCharts();  //公司股价
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
      
      // 流量来源 绘制
      drawFlowCharts() {
        let res = {
            series: [
              {
                name: "抖音",
                data: [[210,100,50,"抖音"]]
              },
              {
                name: "微信",
                data: [[180,40,45,"微信"]]
              },
              {
                name: "快手",
                data: [[110,40,40,"快手"]]
              },
              {
                name: "小红书",
                data: [[60,80,30,"小红书"]]
              },
              {
                name: "其他",
                data: [[30,20,20,"其他"]]
              }
            ]
          };
        this.flowChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 营收占比 绘制
      drawMakeupCharts() {
        let res = {
          series: [
            {
              data: [{"name":"前端","value":5000},{"name":"设计","value":3000},{"name":"赞赏","value":2000},{"name":"原型","value":1800},{"name":"运维","value":900}]
            }
          ]
        };
        this.makeupChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 集团成员 绘制
      drawMemberCharts() {
        let res = {
          series: [
            {
              data: [{"name":"生产","value":3000},{"name":"运维","value":2600},{"name":"销售","value":2200},{"name":"研发","value":900},{"name":"管理","value":600}]
            }
          ]
        };
        this.memberChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 用户终端 绘制
      drawTerminalCharts() {
        let res = {
            series: [
              {
                data: [{"name":"Android","value":652},{"name":"iPhone","value":508},{"name":"Win PC","value":422},{"name":"Mac PC","value":346},{"name":"其他","value":262},{"name":"未知","value":129}]
              }
            ]
          };
        this.terminalChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 用户转化 绘制
      drawConvertCharts() {
        let res = {
            series: [
              {
                data: [{"name":"访问","value":56,},{"name":"登录","value":31},{"name":"下单","value":18},{"name":"付款","value":12},{"name":"完成交易","value":8}]
              }
            ]
          };
        this.convertChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 贸易数量 绘制
      drawSaleCharts() {
        let res = {
            series: [
              {
                data: [
                  {"name":"广东","value":82,legendShape: "circle"},
                  {"name":"湖北","value":63,legendShape: "circle"},
                  {"name":"河南","value":86,legendShape: "circle"},
                  {"name":"其他","value":79,legendShape: "circle"},
                ],
              }
            ],
            
          };
        this.saleChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 公司盈利 绘制
      drawIncomeCharts() {
        let res = {
          categories: [
            "7月",
            "8月",
            "9月",
            "10月",
            "11月",
            "12月",
            "1月",
            "2月",
            "3月",
          ],
          series: [{
              name: "收入",
              data: [1600, 1568, 1808, 1680, 1788, 1680, 1800, 1777, 1860],
              legendShape: "circle",
              color: "#4B98FE",
            }
          ],
        };
        this.incomeChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 员工年龄 绘制
      drawAgeCharts() {
        let res = {
            series: [
              {
                name: "男员工年龄工龄",
                data: [[1.5,24],[3.9,36],[6.3,52],[3.3,36],[1.7,26],[7.2,42],[5.0,38],[8.3,51],[1.2,39],[0.6,28],[9.1,48]]
              },
              {
                name: "女员工年龄工龄",
                data: [[4.3,26],[2.4,26],[5.2,43],[0.5,24],[6.6,54],[3.2,31],[8.0,43],[5.4,37],[2.9,42],[4.6,32],[5.1,46],[7.2,38]]
              }
            ]
          };
        this.ageChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 月度盈利 绘制
      drawMonthCharts() {
        let res = {
          categories: [
            "7月",
            "8月",
            "9月",
            "10月",
            "11月",
            "12月",
            "1月",
            "2月",
            "3月",
          ],
          series: [{
              name: "月度盈利",
              data: [300, 1340, 2578, 3700, 6688, 8980, 5800, 4677, 3700],
              legendShape: "circle",
            }
          ],
        };
        this.monthChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 月度盈利 绘制
      drawMonthCharts1() {
        let res = {
          categories: [
            "7月",
            "8月",
            "9月",
            "10月",
            "11月",
            "12月",
            "1月",
            "2月",
            "3月",
          ],
          series: [{
              name: "月度盈利",
              data: [300, 1340, 2578, 3700, 6688, 8980, 5800, 4677, 3700],
              legendShape: "circle",
            }
          ],
        };
        this.monthChartData1 = JSON.parse(JSON.stringify(res));
      },
      
      // 区域业绩 绘制
      drawFirmCharts() {
        let res = {
            categories: ["广东","上海","福建","江苏","江西","其他"],
            series: [
              {
                name: "区域业绩",
                data: [36,24,18,12,9,6],
                legendShape: "circle",
              }
            ]
          };
        this.firmChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 区域业绩 绘制
      drawFirmCharts1() {
        let res = {
            categories: ["广东","上海","福建","江苏","江西","其他"],
            series: [
              {
                name: "区域业绩",
                data: [36,24,18,12,9,6],
                legendShape: "circle",
              }
            ]
          };
        this.firmChartData1 = JSON.parse(JSON.stringify(res));
      },
      
      // 公司营收 绘制
      drawRevenueCharts() {
        let res = {
          categories: [
            "7月",
            "8月",
            "9月",
            "10月",
            "11月",
            "12月",
            "1月",
            "2月",
            "3月",
          ],
          series: [{
              name: "投资理财",
              data: [990, 1293, 1062, 1457, 1232, 1443, 1321, 1438, 1689],
              legendShape: "circle",
              setShadow: [4,4,20,"#31C9E84D"],
              linearColor: [[0,"#24F083"],[0.25,"#2DE8BD"],[0.5,"#31C9E8"],[0.75,"#3D7EFF"],[1,"#3646FF"]],
            },
          ],
        };
        this.revenueChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 公司营收 绘制
      drawRevenueCharts1() {
        let res = {
          categories: [
            "7月",
            "8月",
            "9月",
            "10月",
            "11月",
            "12月",
            "1月",
            "2月",
            "3月",
          ],
          series: [{
              name: "投资理财",
              data: [990, 1293, 1062, 1457, 1232, 1443, 1321, 1438, 1689],
              legendShape: "circle",
              setShadow: [4,4,20,"#FB6A674D"],
              linearColor: [[0,"#FFAC00"],[0.25,"#FE871B"],[0.5,"#FB6A67"],[0.75,"#F674D6"],[1,"#957BFE"]],
            },
          ],
        };
        this.revenueChartData1 = JSON.parse(JSON.stringify(res));
      },
      
      // 员工能力 绘制
      drawAbilityCharts() {
        let res = {
            categories: ["处事","学习","工作","沟通","决策"],
            series: [
              {
                name: "打杂总监",
                data: [86,39,66,46,6]
              }
            ]
          };
        this.abilityChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 员工能力 绘制
      drawAbilityCharts1() {
        let res = {
            categories: ["处事","学习","工作","沟通","决策"],
            series: [
              {
                name: "打杂总监",
                data: [86,39,66,46,6]
              }
            ]
          };
        this.abilityChartData1 = JSON.parse(JSON.stringify(res));
      },
      
      // 年度词云 绘制
      drawWordCharts() {
        let res = {
            series: [
              {
                name: "图鸟UI",
                textSize: 25,
                data: undefined
              },
              {
                name: "uniapp",
                textSize: 20,
                data: undefined
              },
              {
                name: "微信小程序",
                textSize: 20,
                data: undefined
              },
              {
                name: "H5",
                textSize: 20,
                data: undefined
              },
              {
                name: "APP",
                textSize: 20,
                data: undefined
              },
              {
                name: "vue2",
                textSize: 20,
                data: undefined
              },
              {
                name: "vue3",
                textSize: 20,
                data: undefined
              },
              {
                name: "组件库",
                textSize: 20,
                data: undefined
              },
              {
                name: "UI框架",
                textSize: 10,
                data: undefined
              },
              {
                name: "简约",
                textSize: 12,
                data: undefined
              },
              {
                name: "酷炫",
                textSize: 10,
                data: undefined
              },
              {
                name: "开源",
                textSize: 12,
                data: undefined
              },
              {
                name: "生态",
                textSize: 10,
                data: undefined
              },
              {
                name: "前端",
                textSize: 12,
                data: undefined
              },
              {
                name: "共赢",
                textSize: 12,
                data: undefined
              },
              {
                name: "合作",
                textSize: 12,
                data: undefined
              },
              {
                name: "uCharts",
                textSize: 16,
                data: undefined
              },
              {
                name: "图表",
                textSize: 12,
                data: undefined
              }
            ]
          };
        this.wordChartData = JSON.parse(JSON.stringify(res));
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
      
      // 出勤请假 绘制
      drawWorkCharts() {
        let res = {
            series: [
              {
                name: "全勤率",
                data: 0.6246
              }
            ]
          };
        this.workChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 出勤请假 绘制
      drawWorkCharts1() {
        let res = {
            series: [
              {
                name: "全勤率",
                data: 0.6246
              }
            ]
          };
        this.workChartData1 = JSON.parse(JSON.stringify(res));
      },
      
      // 公司股价 绘制
      drawStockCharts() {
        let res = {
          categories: ["1/24","1/25","1/28","1/29","1/30","1/31","2/1","2/4","2/5","2/6","2/7","2/8","2/18","2/19","2/20","2/21","2/22","2/25","2/26","2/27","2/28","3/1","3/4","3/5","3/6","3/7","3/8","3/11","3/12","3/13","3/14","3/15","3/18","3/19","3/20","3/21","3/22","3/25","3/26","3/27","3/28","3/29","4/1","4/2","4/3","4/8","4/9","4/10","4/11","4/12","4/15","4/16","4/17","4/18","4/19","4/22","4/23","4/24","4/25","4/26","5/2","5/3","5/6","5/7","5/8","5/9","5/10","5/13","5/14","5/15","5/16","5/17","5/20","5/21","5/22","5/23","5/24","5/27","5/28","5/29","5/30","5/31","6/3","6/4","6/5","6/6","6/7","6/13"],
          series: [
            {
              name: "上证指数",
              data: [[2320.26,2302.6,2287.3,2362.94],[2300,2291.3,2288.26,2308.38],[2295.35,2346.5,2295.35,2346.92],[2347.22,2358.98,2337.35,2363.8],[2360.75,2382.48,2347.89,2383.76],[2383.43,2385.42,2371.23,2391.82],[2377.41,2419.02,2369.57,2421.15],[2425.92,2428.15,2417.58,2440.38],[2411,2433.13,2403.3,2437.42],[2432.68,2434.48,2427.7,2441.73],[2430.69,2418.53,2394.22,2433.89],[2416.62,2432.4,2414.4,2443.03],[2441.91,2421.56,2415.43,2444.8],[2420.26,2382.91,2373.53,2427.07],[2383.49,2397.18,2370.61,2397.94],[2378.82,2325.95,2309.17,2378.82],[2322.94,2314.16,2308.76,2330.88],[2320.62,2325.82,2315.01,2338.78],[2313.74,2293.34,2289.89,2340.71],[2297.77,2313.22,2292.03,2324.63],[2322.32,2365.59,2308.92,2366.16],[2364.54,2359.51,2330.86,2369.65],[2332.08,2273.4,2259.25,2333.54],[2274.81,2326.31,2270.1,2328.14],[2333.61,2347.18,2321.6,2351.44],[2340.44,2324.29,2304.27,2352.02],[2326.42,2318.61,2314.59,2333.67],[2314.68,2310.59,2296.58,2320.96],[2309.16,2286.6,2264.83,2333.29],[2282.17,2263.97,2253.25,2286.33],[2255.77,2270.28,2253.31,2276.22],[2269.31,2278.4,2250,2312.08],[2267.29,2240.02,2239.21,2276.05],[2244.26,2257.43,2232.02,2261.31],[2257.74,2317.37,2257.42,2317.86],[2318.21,2324.24,2311.6,2330.81],[2321.4,2328.28,2314.97,2332],[2334.74,2326.72,2319.91,2344.89],[2318.58,2297.67,2281.12,2319.99],[2299.38,2301.26,2289,2323.48],[2273.55,2236.3,2232.91,2273.55],[2238.49,2236.62,2228.81,2246.87],[2229.46,2234.4,2227.31,2243.95],[2234.9,2227.74,2220.44,2253.42],[2232.69,2225.29,2217.25,2241.34],[2196.24,2211.59,2180.67,2212.59],[2215.47,2225.77,2215.47,2234.73],[2224.93,2226.13,2212.56,2233.04],[2236.98,2219.55,2217.26,2242.48],[2218.09,2206.78,2204.44,2226.26],[2199.91,2181.94,2177.39,2204.99],[2169.63,2194.85,2165.78,2196.43],[2195.03,2193.8,2178.47,2197.51],[2181.82,2197.6,2175.44,2206.03],[2201.12,2244.64,2200.58,2250.11],[2236.4,2242.17,2232.26,2245.12],[2242.62,2184.54,2182.81,2242.62],[2187.35,2218.32,2184.11,2226.12],[2213.19,2199.31,2191.85,2224.63],[2203.89,2177.91,2173.86,2210.58],[2170.78,2174.12,2161.14,2179.65],[2179.05,2205.5,2179.05,2222.81],[2212.5,2231.17,2212.5,2236.07],[2227.86,2235.57,2219.44,2240.26],[2242.39,2246.3,2235.42,2255.21],[2246.96,2232.97,2221.38,2247.86],[2228.82,2246.83,2225.81,2247.67],[2247.68,2241.92,2231.36,2250.85],[2238.9,2217.01,2205.87,2239.93],[2217.09,2224.8,2213.58,2225.19],[2221.34,2251.81,2210.77,2252.87],[2249.81,2282.87,2248.41,2288.09],[2286.33,2299.99,2281.9,2309.39],[2297.11,2305.11,2290.12,2305.3],[2303.75,2302.4,2292.43,2314.18],[2293.81,2275.67,2274.1,2304.95],[2281.45,2288.53,2270.25,2292.59],[2286.66,2293.08,2283.94,2301.7],[2293.4,2321.32,2281.47,2322.1],[2323.54,2324.02,2321.17,2334.33],[2316.25,2317.75,2310.49,2325.72],[2320.74,2300.59,2299.37,2325.53],[2300.21,2299.25,2294.11,2313.43],[2297.1,2272.42,2264.76,2297.1],[2270.71,2270.93,2260.87,2276.86],[2264.43,2242.11,2240.07,2266.69],[2242.26,2210.9,2205.07,2250.63],[2190.1,2148.35,2126.22,2190.1]]
            }
          ]
        };
        this.stockChartData = JSON.parse(JSON.stringify(res));
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
  .tn-strip-bottom {
    width: 100%;
    border-bottom: 20rpx solid #1B193C;
  }
  
  /* 间隔线小 start*/
  .tn-strip-bottom-min {
    width: 100%;
    border-bottom: 1rpx solid #1B193C;
  }
  
  .bg-black{
    background-color: #0D0B30;
    min-height: 100vh;
  }
  
  /* 业务数据 start */
  .icon12 {
    &__item {
      transform: scale(1);
      transition: transform 0.3s linear;
      transform-origin: center center;
      
      &--icon {
        width: 90rpx;
        height: 90rpx;
        font-size: 50rpx;
        border-radius: 50%;
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
          // background-image: url(https://resource.tuniaokj.com/images/cool_bg_image/icon_bg2.png);
        }
      }
    }
  }
  
</style>
