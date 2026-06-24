"use strict";
const common_vendor = require("../../common/vendor.js");
const api_device = require("../../api/device.js");
const _sfc_main = /* @__PURE__ */ common_vendor.defineComponent({
  __name: "control",
  setup(__props) {
    const fanState = common_vendor.ref(false);
    const history = common_vendor.ref([]);
    const sendCommand = (action) => {
      return common_vendor.__awaiter(this, void 0, void 0, function* () {
        var _a;
        try {
          const result = yield api_device.api.sendControl(action);
          const now = /* @__PURE__ */ new Date();
          const timeStr = `${now.getHours().toString().padStart(2, "0")}:${now.getMinutes().toString().padStart(2, "0")}:${now.getSeconds().toString().padStart(2, "0")}`;
          const actionMap = {
            [api_device.CONTROL_COMMANDS.FRONT_DOOR_OPEN]: "打开前门",
            [api_device.CONTROL_COMMANDS.FRONT_DOOR_CLOSE]: "关闭前门",
            [api_device.CONTROL_COMMANDS.BACK_DOOR_OPEN]: "打开后门",
            [api_device.CONTROL_COMMANDS.BACK_DOOR_CLOSE]: "关闭后门",
            [api_device.CONTROL_COMMANDS.FAN_ON]: "开启风扇",
            [api_device.CONTROL_COMMANDS.FAN_OFF]: "关闭风扇",
            [api_device.CONTROL_COMMANDS.BUZZER_ON]: "开启蜂鸣器",
            [api_device.CONTROL_COMMANDS.BUZZER_OFF]: "关闭蜂鸣器",
            [api_device.CONTROL_COMMANDS.ALARM_STOP]: "停止告警"
          };
          history.value.unshift({
            action: actionMap[action] || action,
            time: timeStr,
            success: result.code === 200
          });
          if (history.value.length > 20) {
            history.value = history.value.slice(0, 20);
          }
          if (action === api_device.CONTROL_COMMANDS.FAN_ON) {
            fanState.value = true;
          } else if (action === api_device.CONTROL_COMMANDS.FAN_OFF) {
            fanState.value = false;
          }
          if ((_a = result.data) === null || _a === void 0 ? null : _a.offlineWarning) {
            common_vendor.index.showToast({
              title: "设备离线，指令已缓存",
              icon: "none",
              duration: 2e3
            });
          } else {
            common_vendor.index.showToast({
              title: "指令发送成功",
              icon: "success",
              duration: 1500
            });
          }
        } catch (e) {
          common_vendor.index.showToast({
            title: "发送失败",
            icon: "error",
            duration: 1500
          });
        }
      });
    };
    const toggleFan = () => {
      if (fanState.value) {
        sendCommand(api_device.CONTROL_COMMANDS.FAN_OFF);
      } else {
        sendCommand(api_device.CONTROL_COMMANDS.FAN_ON);
      }
    };
    return (_ctx, _cache) => {
      "raw js";
      const __returned__ = common_vendor.e({
        a: common_vendor.o(($event) => {
          return sendCommand("FRONT_DOOR_OPEN");
        }),
        b: common_vendor.o(($event) => {
          return sendCommand("FRONT_DOOR_CLOSE");
        }),
        c: common_vendor.o(($event) => {
          return sendCommand("BACK_DOOR_OPEN");
        }),
        d: common_vendor.o(($event) => {
          return sendCommand("BACK_DOOR_CLOSE");
        }),
        e: fanState.value ? 1 : "",
        f: common_vendor.o(toggleFan),
        g: common_vendor.t(fanState.value ? "开启" : "关闭"),
        h: common_vendor.o(($event) => {
          return sendCommand("BUZZER_ON");
        }),
        i: common_vendor.o(($event) => {
          return sendCommand("BUZZER_OFF");
        }),
        j: common_vendor.o(($event) => {
          return sendCommand("ALARM_STOP");
        }),
        k: common_vendor.o(($event) => {
          return sendCommand("FAN_ON");
        }),
        l: common_vendor.o(($event) => {
          return sendCommand("FAN_OFF");
        }),
        m: common_vendor.o(($event) => {
          return sendCommand("FRONT_DOOR_OPEN");
        }),
        n: common_vendor.o(($event) => {
          return sendCommand("BACK_DOOR_OPEN");
        }),
        o: common_vendor.f(history.value, (record, index, i0) => {
          return {
            a: common_vendor.n(record.success ? "success" : "failed"),
            b: common_vendor.t(record.action),
            c: common_vendor.t(record.time),
            d: index
          };
        }),
        p: history.value.length === 0
      }, history.value.length === 0 ? {} : {}, {
        q: common_vendor.sei(common_vendor.gei(_ctx, ""), "view")
      });
      return __returned__;
    };
  }
});
wx.createPage(_sfc_main);
//# sourceMappingURL=../../../.sourcemap/mp-weixin/pages/control/control.js.map
