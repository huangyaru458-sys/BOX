"use strict";
const common_vendor = require("../../common/vendor.js");
const api_device = require("../../api/device.js");
const _sfc_main = /* @__PURE__ */ common_vendor.defineComponent({
  __name: "history",
  setup(__props) {
    const activeTab = common_vendor.ref("telemetry");
    const dateRange = common_vendor.ref("全部");
    const telemetryData = common_vendor.ref([]);
    const alertsData = common_vendor.ref([]);
    const page = common_vendor.ref(1);
    const hasMore = common_vendor.ref(true);
    const switchTab = (tab) => {
      activeTab.value = tab;
      page.value = 1;
      hasMore.value = true;
      if (tab === "telemetry") {
        telemetryData.value = [];
        fetchTelemetry();
      } else {
        alertsData.value = [];
        fetchAlerts();
      }
    };
    const showDatePicker = () => {
      const options = ["全部", "今日", "本周", "本月"];
      common_vendor.index.showActionSheet({
        itemList: options,
        success: (res) => {
          dateRange.value = options[res.tapIndex];
          switchTab(activeTab.value);
        }
      });
    };
    const fetchTelemetry = () => {
      return common_vendor.__awaiter(this, void 0, void 0, function* () {
        try {
          const data = yield api_device.api.getHistory({
            limit: 20
          });
          if (data.length > 0) {
            telemetryData.value = [...telemetryData.value, ...data];
            if (data.length < 20) {
              hasMore.value = false;
            }
          } else {
            hasMore.value = false;
          }
        } catch (e) {
          common_vendor.index.__f__("error", "at pages/history/history.uvue:117", "Failed to fetch telemetry:", e);
        }
      });
    };
    const fetchAlerts = () => {
      return common_vendor.__awaiter(this, void 0, void 0, function* () {
        try {
          const data = yield api_device.api.getAlerts({
            limit: 20
          });
          if (data.length > 0) {
            alertsData.value = [...alertsData.value, ...data];
            if (data.length < 20) {
              hasMore.value = false;
            }
          } else {
            hasMore.value = false;
          }
        } catch (e) {
          common_vendor.index.__f__("error", "at pages/history/history.uvue:135", "Failed to fetch alerts:", e);
        }
      });
    };
    const loadMore = () => {
      page.value++;
      if (activeTab.value === "telemetry") {
        fetchTelemetry();
      } else {
        fetchAlerts();
      }
    };
    const formatTime = (ts) => {
      if (!ts)
        return "--";
      const date = new Date(ts);
      return `${date.getMonth() + 1}/${date.getDate()} ${date.getHours().toString().padStart(2, "0")}:${date.getMinutes().toString().padStart(2, "0")}`;
    };
    const getAlertClass = (type) => {
      if (type.includes("TILT") || type.includes("倾斜"))
        return "tilt";
      if (type.includes("FAULT") || type.includes("故障"))
        return "fault";
      if (type.includes("FULL") || type.includes("满"))
        return "full";
      return "other";
    };
    const getAlertIcon = (type) => {
      if (type.includes("TILT") || type.includes("倾斜"))
        return "⚠️";
      if (type.includes("FAULT") || type.includes("故障"))
        return "❌";
      if (type.includes("FULL") || type.includes("满"))
        return "📦";
      return "🔔";
    };
    common_vendor.onMounted(() => {
      fetchTelemetry();
    });
    common_vendor.onPullDownRefresh(() => {
      switchTab(activeTab.value);
      setTimeout(() => {
        common_vendor.index.stopPullDownRefresh();
      }, 1e3);
    });
    return (_ctx, _cache) => {
      "raw js";
      const __returned__ = common_vendor.e({
        a: activeTab.value === "telemetry" ? 1 : "",
        b: common_vendor.o(($event) => {
          return switchTab("telemetry");
        }),
        c: activeTab.value === "alerts" ? 1 : "",
        d: common_vendor.o(($event) => {
          return switchTab("alerts");
        }),
        e: common_vendor.t(dateRange.value),
        f: common_vendor.o(showDatePicker),
        g: activeTab.value === "telemetry"
      }, activeTab.value === "telemetry" ? common_vendor.e({
        h: common_vendor.f(telemetryData.value, (item, k0, i0) => {
          return {
            a: common_vendor.t(formatTime(item.ts)),
            b: common_vendor.t(item.temperature.toFixed(1)),
            c: common_vendor.t(item.humidity.toFixed(1)),
            d: common_vendor.t(item.capacity.toFixed(1)),
            e: common_vendor.t(item.fan_status === 1 ? "开" : "关"),
            f: item.fan_status === 1 ? 1 : "",
            g: item.id
          };
        }),
        i: telemetryData.value.length === 0
      }, telemetryData.value.length === 0 ? {} : {}) : {}, {
        j: activeTab.value === "alerts"
      }, activeTab.value === "alerts" ? common_vendor.e({
        k: common_vendor.f(alertsData.value, (item, k0, i0) => {
          return {
            a: common_vendor.t(getAlertIcon(item.alert_type)),
            b: common_vendor.n(getAlertClass(item.alert_type)),
            c: common_vendor.t(item.alert_msg),
            d: common_vendor.t(formatTime(item.ts)),
            e: common_vendor.t(item.is_ack === 1 ? "已处理" : "待处理"),
            f: item.is_ack === 1 ? 1 : "",
            g: item.id
          };
        }),
        l: alertsData.value.length === 0
      }, alertsData.value.length === 0 ? {} : {}) : {}, {
        m: hasMore.value
      }, hasMore.value ? {
        n: common_vendor.o(loadMore)
      } : {}, {
        o: common_vendor.sei(common_vendor.gei(_ctx, ""), "view")
      });
      return __returned__;
    };
  }
});
wx.createPage(_sfc_main);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages/history/history.js.map
