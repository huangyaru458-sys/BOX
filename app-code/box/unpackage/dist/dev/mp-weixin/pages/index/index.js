"use strict";
const common_vendor = require("../../common/vendor.js");
const api_device = require("../../api/device.js");
const _sfc_main = /* @__PURE__ */ common_vendor.defineComponent({
  __name: "index",
  setup(__props) {
    const status = common_vendor.ref({
      deviceId: "ESP32_BOX_001",
      temperature: 0,
      humidity: 0,
      capacity: 0,
      airQuality: 0,
      humanDetect: false,
      fanStatus: false,
      frontDoor: false,
      backDoor: false,
      tiltAngle: 0,
      sensorFaults: [],
      buzzerMode: "off",
      netMode: "STA",
      systemState: "STANDBY",
      lastSeen: 0
    });
    const updateTime = common_vendor.ref("--:--");
    let timer = null;
    const isOnline = common_vendor.computed(() => {
      if (!status.value.lastSeen)
        return false;
      return Date.now() - status.value.lastSeen < 15e3;
    });
    const fetchData = () => {
      return common_vendor.__awaiter(this, void 0, void 0, function* () {
        try {
          const data = yield api_device.api.getLatestStatus();
          status.value = Object.assign(Object.assign({}, status.value), data);
          const now = /* @__PURE__ */ new Date();
          updateTime.value = `${now.getHours().toString().padStart(2, "0")}:${now.getMinutes().toString().padStart(2, "0")}:${now.getSeconds().toString().padStart(2, "0")}`;
        } catch (e) {
          common_vendor.index.__f__("error", "at pages/index/index.uvue:161", "Failed to fetch data:", e);
        }
      });
    };
    common_vendor.onMounted(() => {
      fetchData();
      timer = setInterval(fetchData, 5e3);
    });
    common_vendor.onUnmounted(() => {
      if (timer) {
        clearInterval(timer);
        timer = null;
      }
    });
    common_vendor.onPullDownRefresh(() => {
      fetchData();
      setTimeout(() => {
        common_vendor.index.stopPullDownRefresh();
      }, 1e3);
    });
    return (_ctx, _cache) => {
      "raw js";
      const __returned__ = common_vendor.e({
        a: isOnline.value ? 1 : "",
        b: !isOnline.value ? 1 : "",
        c: common_vendor.t(isOnline.value ? "设备在线" : "设备离线"),
        d: common_vendor.t(updateTime.value),
        e: common_vendor.t(status.value.temperature.toFixed(1)),
        f: common_vendor.t(status.value.humidity.toFixed(1)),
        g: common_vendor.t(status.value.capacity.toFixed(1)),
        h: status.value.capacity + "%",
        i: status.value.capacity > 80 ? 1 : "",
        j: common_vendor.t(status.value.airQuality),
        k: common_vendor.t(status.value.frontDoor ? "打开" : "关闭"),
        l: status.value.frontDoor ? 1 : "",
        m: common_vendor.t(status.value.backDoor ? "打开" : "关闭"),
        n: status.value.backDoor ? 1 : "",
        o: common_vendor.t(status.value.fanStatus ? "开启" : "关闭"),
        p: status.value.fanStatus ? 1 : "",
        q: common_vendor.t(status.value.humanDetect ? "检测到" : "未检测"),
        r: status.value.humanDetect ? 1 : "",
        s: status.value.boxTiltAlert || status.value.sensorFaults.length > 0
      }, status.value.boxTiltAlert || status.value.sensorFaults.length > 0 ? common_vendor.e({
        t: status.value.boxTiltAlert
      }, status.value.boxTiltAlert ? {} : {}, {
        v: common_vendor.f(status.value.sensorFaults, (fault, k0, i0) => {
          return {
            a: common_vendor.t(fault),
            b: fault
          };
        })
      }) : {}, {
        w: common_vendor.t(status.value.systemState),
        x: common_vendor.t(status.value.netMode),
        y: common_vendor.t(status.value.buzzerMode === "off" ? "关闭" : "开启"),
        z: common_vendor.t(status.value.tiltAngle.toFixed(1)),
        A: common_vendor.sei(common_vendor.gei(_ctx, ""), "view")
      });
      return __returned__;
    };
  }
});
wx.createPage(_sfc_main);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages/index/index.js.map
