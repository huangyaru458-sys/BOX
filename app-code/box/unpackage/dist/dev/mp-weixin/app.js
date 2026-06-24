"use strict";
Object.defineProperty(exports, Symbol.toStringTag, { value: "Module" });
const common_vendor = require("./common/vendor.js");
require("./test-main-console.js");
const uni_modules_uniStat_plugin = require("./uni_modules/uni-stat/plugin.js");
const store_index = require("./store/index.js");
const uni_modules_uniStat_utssdk_index = require("./uni_modules/uni-stat/utssdk/index.js");
const uni_modules_uniStat_utssdk_interface = require("./uni_modules/uni-stat/utssdk/interface.js");
if (!Math) {
  "./pages/index/index.js";
  "./pages/control/control.js";
  "./pages/history/history.js";
  "./workers/helloWorkerTask.js";
  "./workers/sendableTransferWorker.js";
}
const _sfc_main = /* @__PURE__ */ common_vendor.defineComponent({
  __name: "App",
  setup(__props, _a) {
    var __expose = _a.expose;
    common_vendor.onLaunch((res) => {
      store_index.updateGlobalData("launchOptions", res);
      store_index.setLifeCycleNum(store_index.state.lifeCycleNum + 1e3);
      common_vendor.index.__f__("log", "at App.uvue:13", "App Launch");
      uni_modules_uniStat_utssdk_index.report(new uni_modules_uniStat_utssdk_interface.ReportOptions({
        name: "uni-app-launch",
        options: res,
        success(res_data) {
          common_vendor.index.__f__("log", "at App.uvue:31", res_data);
        },
        fail(err) {
          common_vendor.index.__f__("log", "at App.uvue:33", err);
        }
      }));
      store_index.checkSystemTheme();
    });
    const getRedirectUrl = (scheme = null, ulink = null) => {
      let url = null;
      if (null != scheme && scheme.length > 0) {
        const PATHPRE = "redirect";
        let parts = null;
        let pos = scheme.search("//");
        if (pos > 0) {
          parts = scheme.substring(pos + 2);
        }
        if (null != parts && parts.startsWith(PATHPRE)) {
          url = parts.substring(PATHPRE.length);
        }
      } else if (null != ulink && ulink.length > 0) {
        const PATH = "ulink/redirect.html";
        let parts = ulink.split("?");
        if (parts.length > 1 && parts[0].endsWith(PATH) && parts[1].length > 0) {
          parts[1].split("&").forEach((e) => {
            let params = e.split("=");
            if (params.length > 1 && params[0].length > 0 && params[1].length > 0) {
              if ("url" == params[0]) {
                if (null == url) {
                  url = decodeURIComponent(params[1]);
                }
              }
            }
          });
        }
      }
      return url;
    };
    onAppShow((res) => {
      store_index.updateGlobalData("showOptions", res);
      let url = getRedirectUrl(res.appScheme, res.appLink);
      if (null != url) {
        common_vendor.index.navigateTo({
          url
        });
      }
      store_index.setLifeCycleNum(store_index.state.lifeCycleNum + 100);
      common_vendor.index.__f__("log", "at App.uvue:106", "App Show");
      uni_modules_uniStat_utssdk_index.report(new uni_modules_uniStat_utssdk_interface.ReportOptions({
        name: "uni-app-show",
        success(res_data) {
          common_vendor.index.__f__("log", "at App.uvue:113", res_data);
        },
        fail(err) {
          common_vendor.index.__f__("log", "at App.uvue:115", err);
        }
      }));
    });
    onAppHide(() => {
      store_index.setLifeCycleNum(store_index.state.lifeCycleNum - 100);
      common_vendor.index.__f__("log", "at App.uvue:123", "App Hide");
      uni_modules_uniStat_utssdk_index.report(new uni_modules_uniStat_utssdk_interface.ReportOptions({
        name: "uni-app-hide",
        success(res) {
          common_vendor.index.__f__("log", "at App.uvue:130", res);
        },
        fail(err) {
          common_vendor.index.__f__("log", "at App.uvue:132", err);
        }
      }));
    });
    common_vendor.onError((err = null) => {
      common_vendor.index.__f__("log", "at App.uvue:161", "App Error", err);
      store_index.setLifeCycleNum(store_index.state.lifeCycleNum + 100);
      uni_modules_uniStat_utssdk_index.report(new uni_modules_uniStat_utssdk_interface.ReportOptions({
        name: "uni-app-error",
        options: err,
        success(res) {
          common_vendor.index.__f__("log", "at App.uvue:169", res);
        },
        fail(err2) {
          common_vendor.index.__f__("log", "at App.uvue:171", err2);
        }
      }));
    });
    const increaseLifeCycleNum = () => {
      store_index.setLifeCycleNum(store_index.state.lifeCycleNum + 100);
      common_vendor.index.__f__("log", "at App.uvue:178", "App increaseLifeCycleNum");
    };
    __expose({
      increaseLifeCycleNum
    });
    return () => {
    };
  }
});
const uniStatcollectItems = new UTSJSONObject({
  uniStatPageLog: true
});
const uniStatOptions = new UTSJSONObject({
  enable: false,
  debug: false,
  collectItems: uniStatcollectItems
});
function createApp() {
  const app = common_vendor.createSSRApp(_sfc_main);
  app.use(uni_modules_uniStat_plugin.uniStat, uniStatOptions);
  return {
    app
  };
}
createApp().app.mount("#app");
exports.createApp = createApp;
//# sourceMappingURL=../.sourcemap/mp-weixin/app.js.map
