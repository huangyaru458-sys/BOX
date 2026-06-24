<template>
  <view class="template-content">
    <!-- 顶部自定义导航 -->
    <tn-nav-bar fixed alpha customBack>
      <view slot="back" class='tn-custom-nav-bar__back'
        @click="goBack">
        <text class='icon tn-icon-left'></text>
        <text class='icon tn-icon-home-capsule-fill'></text>
      </view>
    </tn-nav-bar>
    
    <view class="top-info" :style="{paddingTop: vuex_custom_bar_height + 'px'}">
      <!-- <view class="tn-text-center" style="position: absolute;top: 20rpx;right:20rpx;font-size: 200rpx;opacity: 0.1;">
        <view class="tn-icon-trophy-fill tn-color-white"></view>
      </view> -->
      <view class="tn-margin tn-padding-left-sm tn-padding-bottom-xl tn-padding-top tn-color-white tn-text-center">
        <view class="">
          <text>参考总市值 (元)</text>
          <text class="tn-icon-eye" style="opacity: 0.8;margin-left: 10rpx;"></text>
        </view>
        <view class="tn-text-bold tn-padding-top-xs" style="font-size:70rpx">129,086.82</view>
      </view>
      <view class="tn-color-white">
        <view class="tn-flex tn-flex-col-center tn-text-center">
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm" style="opacity: 0.6;">持仓盈亏 (元)</view>
            <view class="tn-text-lg tn-text-bold tn-padding-top-xs">+ 608.62</view>
          </view>
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm" style="opacity: 0.6;">持仓份额 (份)</view>
            <view class="tn-text-lg tn-text-bold tn-padding-top-xs">+ 26.09%</view>
          </view>
          <view class="justify-content-item tn-flex-1">
            <view class="tn-text-sm" style="opacity: 0.6;">累计盈亏 (元)</view>
            <view class="tn-text-lg tn-text-bold tn-padding-top-xs">1,506.22</view>
          </view>
        </view>
      </view>
    </view>
    
    <view class="tn-padding-top-xl tn-padding-bottom-xl">
      <view class="tn-flex tn-flex-row-between tn-flex-col-center">
        <view class="justify-content-item tn-margin tn-text-bold tn-text-lg">
          那只猪科技
        </view>
        <view class="justify-content-item tn-margin-right tn-padding-xs tn-text-sm tn-bg-gray--light tn-radius tn-color-gray--dark">
          <text class="tn-padding-left-xs tn-padding-right-xs">23年1月 - 至今</text>
          <text class="tn-icon-down tn-padding-right-xs"></text>
        </view>
      </view>
      <view class="" style="min-height: 500rpx;">
        <qiun-data-charts canvas2d type="candle" :opts="stockOpts" :chartData="stockChartData" :disableScroll="true" :ontouch="true" :onzoom="true" />
      </view>
    </view>
      
      
      
  </view>
</template>

<script>
  import template_page_mixin from '@/libs/mixin/template_page_mixin.js'
  export default {
    name: 'TemplateContent',
    mixins: [template_page_mixin],
    data() {
      return {
        
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
            labelCount: 6,
            itemCount: 36,
            disableGrid: true,
            scrollShow: true,
            scrollAlign: "left",
            scrollColor: "#E5E5E5",
            scrollBackgroundColor: "#F8F7F8"
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
            show: true,
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
        
      };
    },
    onReady() {
      this.drawStockCharts();  //公司股价
    },
    methods: {
      
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
  
  .top-info{
    position: relative;
    background: linear-gradient(90deg, #395ACD, #395ACD);
    top: 0;
    width: 100%;
    height: 580rpx;
    transition: all 0.25s ease-out;
    z-index: -1;
  }
  .top-info:before{
    content: "";
    position: absolute;
    top: 0;
    left: 0;
    bottom: 0;
    right: 0;
    z-index: -1;
    mask-image: linear-gradient(to bottom, transparent, black);
    background: linear-gradient(90deg, #395ACD, #395ACD);	
  
  }
</style>
