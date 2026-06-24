"use strict";
const common_vendor = require("../common/vendor.js");
const BASE_URL = "http://10.94.163.228:1880";
function request(options) {
  return new Promise((resolve, reject) => {
    let fullUrl = BASE_URL + options.url;
    if (options.params) {
      const query = new URLSearchParams(options.params).toString();
      if (query) {
        fullUrl += "?" + query;
      }
    }
    common_vendor.index.request({
      url: fullUrl,
      method: options.method || "GET",
      data: options.data,
      header: {
        "Content-Type": "application/json"
      },
      success: (res) => {
        if (res.statusCode === 200) {
          resolve(res.data);
        } else {
          reject(new Error("Request failed: " + res.statusCode));
        }
      },
      fail: (err) => {
        reject(err);
      }
    });
  });
}
const api = {
  getLatestStatus: (deviceId) => {
    return request({
      url: "/api/v1/box/latest",
      params: deviceId ? { deviceId } : void 0
    });
  },
  sendControl: (action, deviceId) => {
    return request({
      url: "/api/v1/box/control",
      method: "POST",
      data: {
        action,
        deviceId: deviceId || "ESP32_BOX_001",
        adminToken: "admin_auth_secret01"
      }
    });
  },
  getHistory: (params) => {
    return request({
      url: "/api/v1/box/history",
      params
    });
  },
  getAlerts: (params) => {
    return request({
      url: "/api/v1/box/alerts",
      params
    });
  },
  acknowledgeAlert: (alertId) => {
    return request({
      url: "/api/v1/box/alerts/" + alertId + "/ack",
      method: "POST"
    });
  }
};
const CONTROL_COMMANDS = {
  FRONT_DOOR_OPEN: "FRONT_DOOR_OPEN",
  FRONT_DOOR_CLOSE: "FRONT_DOOR_CLOSE",
  BACK_DOOR_OPEN: "BACK_DOOR_OPEN",
  BACK_DOOR_CLOSE: "BACK_DOOR_CLOSE",
  FAN_ON: "FAN_ON",
  FAN_OFF: "FAN_OFF",
  ALARM_STOP: "ALARM_STOP",
  BUZZER_ON: "BUZZER_ON",
  BUZZER_OFF: "BUZZER_OFF"
};
exports.CONTROL_COMMANDS = CONTROL_COMMANDS;
exports.api = api;
//# sourceMappingURL=../../.sourcemap/mp-weixin/api/device.js.map
