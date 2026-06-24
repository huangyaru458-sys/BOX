<template>
  <view class="template-content bg-black">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed customBack :bottomShadow="false" backgroundColor="#17171C">
      <view slot="back" class='tn-custom-nav-bar__back'
        @click="goBack">
        <text class='icon tn-icon-left'></text>
        <text class='icon tn-icon-home-capsule-fill'></text>
      </view>
      <view class="tn-flex tn-flex-col-center tn-flex-row-center ">
        <text class="tn-text-bold tn-text-xl tn-color-white">充电统计</text>
      </view>
    </tn-nav-bar>
    
    <!-- 模拟器上，图表是显示在最上层挡住很多东西，真机是没有问题的，因为加了canvas2d处理 -->
    <!-- 如因一次性加载太多太多，所以会慢，也因懒得写延时加载，所以实际应用中自行延时处理 -->
    
    <view class="" :style="{paddingTop: vuex_custom_bar_height + 10 + 'px'}">
      
      <view class="tn-color-gray tn-padding-top" style="margin: 30rpx 30rpx 60rpx 30rpx;">
        <tn-tabs :list="fixedList" :current="current" :isScroll="false" barHeight="6" barWidth="28" :showBar="true"
          :activeItemStyle="activeItemStyle" :inactiveItemStyle="inactiveItemStyle" :barStyle="barStyle" inactiveColor="#E5E8EF" activeColor="#E5E8EF" :bold="true" :fontSize="30" :badgeOffset="[10, 30]"
          @change="tabChange" backgroundColor="#FFFFFF00" :height="80"></tn-tabs>
      </view>
      
      <!-- 周 -->
      <view v-if="current==0" class="">
        <view class="tn-padding-bottom-xl">
          <view class="" style="min-height: 500rpx;max-height: 500rpx;">
            <qiun-data-charts canvas2d type="column" :opts="weekOpts" :chartData="weekChartData" />
          </view>
        </view>
        
        <view class="tn-padding-top tn-padding-bottom-xl">
          <view class="tn-flex tn-flex-row-between tn-flex-col-center tn-margin tn-padding-bottom-sm">
            <view class="justify-content-item tn-text-bold tn-text-lg tn-color-gray">
              周度统计
            </view>
            <view class="tn-color-gray">
              累计充电次数 2 次
            </view>
          </view>
          
          <view class="tn-flex tn-flex-wrap" style="margin: 15rpx;" @click="showModal">
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">88</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">累计充电总量 KWh</text>
                </view>
              </view>
            </view>
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">76</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">累计支付费用 元</text>
                </view>
              </view>
            </view>
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">4</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">累计充电时间 H</text>
                </view>
              </view>
            </view>
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">22</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">预估节省费用 元</text>
                </view>
              </view>
            </view>
          </view>
        </view>
      </view>
      
      <!-- 月-->
      <view v-if="current==1" class="">
        <view class="tn-padding-bottom-xl">
          <view class="" style="min-height: 500rpx;max-height: 500rpx;">
            <qiun-data-charts canvas2d type="column" :opts="monthOpts" :chartData="monthChartData" />
          </view>
        </view>
      
        <view class="tn-padding-top tn-padding-bottom-xl">
          <view class="tn-flex tn-flex-row-between tn-flex-col-center tn-margin tn-padding-bottom-sm">
            <view class="justify-content-item tn-text-bold tn-text-lg tn-color-gray">
              月度统计
            </view>
            <view class="tn-color-gray">
              累计充电次数 12 次
            </view>
          </view>
          
          <view class="tn-flex tn-flex-wrap" style="margin: 15rpx;" @click="showModal">
            
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">327</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">累计充电总量 KWh</text>
                </view>
              </view>
            </view>
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">402</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">累计支付费用 元</text>
                </view>
              </view>
            </view>
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">26</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">累计充电时间 H</text>
                </view>
              </view>
            </view>
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">106</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">预估节省费用 元</text>
                </view>
              </view>
            </view>
          </view>
        </view>
      </view>
      
      <!-- 年-->
      <view v-if="current==2" class="">
        <view class="tn-padding-bottom-xl">
          <view class="" style="min-height: 500rpx;max-height: 500rpx;">
            <qiun-data-charts canvas2d type="column" :opts="yearOpts" :chartData="yearChartData" />
          </view>
        </view>
        <view class="tn-padding-top tn-padding-bottom-xl">
          <view class="tn-flex tn-flex-row-between tn-flex-col-center tn-margin tn-padding-bottom-sm">
            <view class="justify-content-item tn-text-bold tn-text-lg tn-color-gray">
              年度统计
            </view>
            <view class="tn-color-gray">
              累计充电次数 129 次
            </view>
          </view>
          
          <view class="tn-flex tn-flex-wrap" style="margin: 15rpx;" @click="showModal">
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">2,168</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">累计充电总量 KWh</text>
                </view>
              </view>
            </view>
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">3,628</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">累计支付费用 元</text>
                </view>
              </view>
            </view>
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">229</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">累计充电时间 H</text>
                </view>
              </view>
            </view>
            <view class="" style="width: 50%;padding: 15rpx;" @click="tn('')">
              <view class="tn-flex tn-flex-direction-column tn-flex-row-center tn-flex-col-center" style="background-color: #1D1F24;color: #E5E8EF;border-radius: 8rpx;">
                <view class="tn-text-center tn-text-bold tn-padding-top-lg" style="font-size: 50rpx;">
                  <text class="tn-text-ellipsis">1,053</text>
                </view>
                <view class="tn-text-center tn-text-xs tn-padding-bottom-lg tn-padding-top-sm" style="opacity: 0.4;">
                  <text class="tn-text-ellipsis">预估节省费用 元</text>
                </view>
              </view>
            </view>
          </view>
        </view>
      </view>
      
      <tn-modal v-model="show" :custom="true" :showCloseBtn="true">
        <view class="custom-modal-content">
          <view class="">
            <view class="tn-text-justify tn-color-blue tn-text-lg" style="padding: 20rpx 0rpx;">
              <view class="tn-padding-bottom">图鸟弹窗，tn-modal</view>
              <view class="tn-padding-bottom">在图表之上，忽略渣渣模拟器，请在真机看效果</view>
              <view class="tn-padding-bottom">一堆瞎逼逼的文案，别喷</view>
            </view>  
          </view>
          <!-- <view class="tn-flex-1 justify-content-item tn-margin-sm tn-text-center tn-padding-top">
            <tn-button backgroundColor="#3668FC" padding="40rpx 0" width="100%" shadow fontBold >
              <text class="tn-color-white">关闭弹窗</text>
            </tn-button>
          </view> -->
        </view>
      </tn-modal>
      
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
        show: false,
        
        barStyle: {
          borderRadius: '100rpx',
          backgroundColor: '#FF1C40'
        },
        activeItemStyle: {
          // borderRadius: '8rpx',
          border: "1rpx solid #1D1F24",
          backgroundColor: '#1D1F24',
        },
        inactiveItemStyle: {
          // borderRadius: '8rpx',
          border: "1rpx solid #1D1F24",
        },
        current: 2,
        fixedList: [
          {name: '周'},
          {name: '月'},
          {name: '年'}
        ],
        
        // 周度统计
        weekChartData: {},
        weekOpts: {
          color: ["#FFFFFF","#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
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
            showTitle: true,
            data: [{
              fontColor: "#868598",
              axisLineColor: "#17171C",
              max: 100,
              title: "KWh",
              position: "left",
              titleOffsetX: 60,
              titleOffsetY: 12,
              titleFontColor: "#868598",
              titleFontSize: 10
              
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
              width: 10,
              activeBgColor: "#000000",
              activeBgOpacity: 0.4,
              // barBorderCircle: true,
              linearType: "custom",
              customColor: ["#FF1C40"],
              colorStop: 1 //通过这个自定义程度，改变提示点和图例颜色不一样，即提示点白色，柱状图红色
            },
            tooltip: {
              showArrow: false,
              borderRadius: 12,
              bgOpacity: 0.1,
              bgColor: "#FFFFFF",
              boxPadding: 5
            },
          },
        },
        
        // 月度统计
        monthChartData: {},
        monthOpts: {
          color: ["#FFFFFF","#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
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
            showTitle: true,
            data: [{
              fontColor: "#868598",
              axisLineColor: "#17171C",
              max: 200,
              title: "KWh",
              position: "left",
              titleOffsetX: 60,
              titleOffsetY: 12,
              titleFontColor: "#868598",
              titleFontSize: 10
              
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
              width: 10,
              activeBgColor: "#000000",
              activeBgOpacity: 0.4,
              // barBorderCircle: true,
              linearType: "custom",
              customColor: ["#FF1C40"],
              colorStop: 1 //通过这个自定义程度，改变提示点和图例颜色不一样，即提示点白色，柱状图红色
            },
            tooltip: {
              showArrow: false,
              borderRadius: 12,
              bgOpacity: 0.1,
              bgColor: "#FFFFFF",
              boxPadding: 5
            },
          },
        },
        
        // 年度统计
        yearChartData: {},
        yearOpts: {
          color: ["#FFFFFF","#4B98FE","#00D05E","#FFAC00","#FB6A67","#957BFE","#00B9FE","#FE871B","#00C8B0","#F674D6"],
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
            showTitle: true,
            data: [{
              fontColor: "#868598",
              axisLineColor: "#17171C",
              max: 400,
              title: "KWh",
              position: "left",
              titleOffsetX: 60,
              titleOffsetY: 12,
              titleFontColor: "#868598",
              titleFontSize: 10
              
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
              width: 10,
              activeBgColor: "#000000",
              activeBgOpacity: 0.4,
              // barBorderCircle: true,
              linearType: "custom",
              customColor: ["#FF1C40"],
              colorStop: 1 //通过这个自定义程度，改变提示点和图例颜色不一样，即提示点白色，柱状图红色
            },
            tooltip: {
              showArrow: false,
              borderRadius: 12,
              bgOpacity: 0.1,
              bgColor: "#FFFFFF",
              boxPadding: 5
            },
          },
        },
        
      }
    },
    onReady() {
      this.drawWeekCharts();  //周度统计
      this.drawMonthCharts();  //月度统计
      this.drawYearCharts();  //年度统计
    },
    methods: {
      // 弹出模态框
      showModal(event) {
        wx.vibrateShort();
        this.openModal()
      },
      // 打开模态框
      openModal() {
        this.show = true
      },
      
      // tab选项卡切换
      tabChange(index) {
        this.current = index
      },
      
      // 周度统计 绘制
      drawWeekCharts() {
        let res = {
          categories: [
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
          ],
          series: [{
              name: "日",
              data: [0, 0, 32, 0, 56, 0, 0],
              legendShape: "circle",
            }
          ],
        };
        this.weekChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 月度统计 绘制
      drawMonthCharts() {
        let res = {
          categories: [
            "1-7",
            "8-14",
            "15-21",
            "22-28",
            "29-月尾",
          ],
          series: [{
              name: "",
              data: [126, 60, 58, 46, 37],
              legendShape: "circle",
            }
          ],
        };
        this.monthChartData = JSON.parse(JSON.stringify(res));
      },
      
      // 年度统计 绘制
      drawYearCharts() {
        let res = {
          categories: [
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
          ],
          series: [{
              name: "月",
              data: [30, 134, 278, 370, 188, 180, 158, 146, 20, 58, 46, 37],
              legendShape: "circle",
            }
          ],
        };
        this.yearChartData = JSON.parse(JSON.stringify(res));
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
  
  .bg-black{
    background-color: #17171C;
    min-height: 100vh;
  }
  
</style>
