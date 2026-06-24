"use strict";
const common_vendor = require("../common/vendor.js");
class SafeArea extends UTS.UTSType {
  static get$UTSMetadata$() {
    return {
      kind: 2,
      get fields() {
        return {
          top: { type: Number, optional: false },
          right: { type: Number, optional: false },
          bottom: { type: Number, optional: false },
          left: { type: Number, optional: false },
          width: { type: Number, optional: false },
          height: { type: Number, optional: false }
        };
      },
      name: "SafeArea"
    };
  }
  constructor(options, metadata = SafeArea.get$UTSMetadata$(), isJSONParse = false) {
    super();
    this.__props__ = UTS.UTSType.initProps(options, metadata, isJSONParse);
    this.top = this.__props__.top;
    this.right = this.__props__.right;
    this.bottom = this.__props__.bottom;
    this.left = this.__props__.left;
    this.width = this.__props__.width;
    this.height = this.__props__.height;
    delete this.__props__;
  }
}
const AGREE_PRIVACY = "UNI-PRIVACY-AGREE";
class UserInfo extends UTS.UTSType {
  static get$UTSMetadata$() {
    return {
      kind: 2,
      get fields() {
        return {
          nickName: { type: String, optional: false },
          avatarUrl: { type: String, optional: true }
        };
      },
      name: "UserInfo"
    };
  }
  constructor(options, metadata = UserInfo.get$UTSMetadata$(), isJSONParse = false) {
    super();
    this.__props__ = UTS.UTSType.initProps(options, metadata, isJSONParse);
    this.nickName = this.__props__.nickName;
    this.avatarUrl = this.__props__.avatarUrl;
    delete this.__props__;
  }
}
class GlobalData extends UTS.UTSType {
  static get$UTSMetadata$() {
    return {
      kind: 2,
      get fields() {
        return {
          str: { type: String, optional: false },
          num: { type: Number, optional: false },
          bool: { type: Boolean, optional: false },
          obj: { type: "Unknown", optional: false },
          null: { type: String, optional: true },
          arr: { type: UTS.UTSType.withGenerics(Array, [Number]), optional: false },
          set: { type: "Unknown", optional: false },
          map: { type: "Unknown", optional: false },
          fun: { type: "Unknown", optional: false },
          launchOptions: { type: "Unknown", optional: false },
          showOptions: { type: "Unknown", optional: false }
        };
      },
      name: "GlobalData"
    };
  }
  constructor(options, metadata = GlobalData.get$UTSMetadata$(), isJSONParse = false) {
    super();
    this.__props__ = UTS.UTSType.initProps(options, metadata, isJSONParse);
    this.str = this.__props__.str;
    this.num = this.__props__.num;
    this.bool = this.__props__.bool;
    this.obj = this.__props__.obj;
    this.null = this.__props__.null;
    this.arr = this.__props__.arr;
    this.set = this.__props__.set;
    this.map = this.__props__.map;
    this.fun = this.__props__.fun;
    this.launchOptions = this.__props__.launchOptions;
    this.showOptions = this.__props__.showOptions;
    delete this.__props__;
  }
}
class State extends UTS.UTSType {
  static get$UTSMetadata$() {
    return {
      kind: 2,
      get fields() {
        return {
          globalData: { type: GlobalData, optional: false },
          lifeCycleNum: { type: Number, optional: false },
          statusBarHeight: { type: Number, optional: false },
          safeArea: { type: SafeArea, optional: false },
          devicePixelRatio: { type: Number, optional: false },
          eventCallbackNum: { type: Number, optional: false },
          noMatchLeftWindow: { type: Boolean, optional: false },
          active: { type: String, optional: false },
          leftWinActive: { type: String, optional: false },
          agreeToPrivacy: { type: Boolean, optional: true },
          allowCapture: { type: Boolean, optional: false },
          isDarkMode: { type: Boolean, optional: false },
          netless: { type: Boolean, optional: false },
          userInfo: { type: UserInfo, optional: true }
        };
      },
      name: "State"
    };
  }
  constructor(options, metadata = State.get$UTSMetadata$(), isJSONParse = false) {
    super();
    this.__props__ = UTS.UTSType.initProps(options, metadata, isJSONParse);
    this.globalData = this.__props__.globalData;
    this.lifeCycleNum = this.__props__.lifeCycleNum;
    this.statusBarHeight = this.__props__.statusBarHeight;
    this.safeArea = this.__props__.safeArea;
    this.devicePixelRatio = this.__props__.devicePixelRatio;
    this.eventCallbackNum = this.__props__.eventCallbackNum;
    this.noMatchLeftWindow = this.__props__.noMatchLeftWindow;
    this.active = this.__props__.active;
    this.leftWinActive = this.__props__.leftWinActive;
    this.agreeToPrivacy = this.__props__.agreeToPrivacy;
    this.allowCapture = this.__props__.allowCapture;
    this.isDarkMode = this.__props__.isDarkMode;
    this.netless = this.__props__.netless;
    this.userInfo = this.__props__.userInfo;
    delete this.__props__;
  }
}
const getAgreePrivacy = () => {
  const data = common_vendor.index.getStorageSync(AGREE_PRIVACY);
  if (typeof data === "boolean") {
    return data;
  }
  if (data == null) {
    return null;
  }
  return null;
};
const state = common_vendor.reactive(new State({
  globalData: new GlobalData({
    str: "default globalData str",
    num: 0,
    bool: false,
    obj: new UTSJSONObject({
      str: "default globalData obj str",
      num: 0,
      bool: false
    }),
    null: null,
    arr: [],
    set: /* @__PURE__ */ new Set(),
    map: /* @__PURE__ */ new Map(),
    fun: () => {
      return "globalData fun";
    },
    launchOptions: {
      path: ""
    },
    showOptions: {
      path: ""
    }
  }),
  lifeCycleNum: 0,
  statusBarHeight: 0,
  devicePixelRatio: 1,
  eventCallbackNum: 0,
  noMatchLeftWindow: true,
  active: "componentPage",
  leftWinActive: "/pages/component/view/view",
  safeArea: new SafeArea({
    top: 0,
    right: 0,
    bottom: 0,
    left: 0,
    width: 0,
    height: 0
  }),
  agreeToPrivacy: getAgreePrivacy(),
  allowCapture: true,
  isDarkMode: false,
  netless: false,
  userInfo: null
}));
const setLifeCycleNum = (num) => {
  state.lifeCycleNum = num;
};
const checkSystemTheme = () => {
  const info = common_vendor.index.getAppBaseInfo();
  state.isDarkMode = info.hostTheme === "dark";
  common_vendor.index.onHostThemeChange((result) => {
    state.isDarkMode = result.hostTheme === "dark";
  });
};
const updateGlobalData = (key, value = null) => {
  switch (key) {
    case "str":
      state.globalData.str = value;
      break;
    case "num":
      state.globalData.num = value;
      break;
    case "bool":
      state.globalData.bool = value;
      break;
    case "obj":
      state.globalData.obj = value;
      break;
    case "null":
      state.globalData.null = value;
      break;
    case "arr":
      state.globalData.arr = value;
      break;
    case "set":
      state.globalData.set = value;
      break;
    case "map":
      state.globalData.map = value;
      break;
    case "fun":
      state.globalData.fun = value;
      break;
    case "launchOptions":
      state.globalData.launchOptions = value;
      break;
    case "showOptions":
      state.globalData.showOptions = value;
      break;
  }
};
exports.checkSystemTheme = checkSystemTheme;
exports.setLifeCycleNum = setLifeCycleNum;
exports.state = state;
exports.updateGlobalData = updateGlobalData;
//# sourceMappingURL=../../.sourcemap/mp-weixin/store/index.js.map
