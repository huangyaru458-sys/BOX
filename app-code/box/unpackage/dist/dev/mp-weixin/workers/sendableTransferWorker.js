require('uni-worker.js')
"use strict";
class SendableTransferWorker extends WorkerTaskImpl {
  //constructor
  constructor() {
    super();
    console.log("[WorkerTask] HelloWorkerTask 构造器初始化");
  }
  //实现入口函数
  entry() {
    console.log("[WorkerTask] HelloWorkerTask 启动完成，等待主线程消息");
  }
  //接收主线程发送的消息
  onMessage(message = null) {
    console.log("[WorkerTask] 收到主线程消息: ", UTS.JSON.stringify(message));
    this.sendReply(message);
  }
  // 发送回复消息
  sendReply(message = null) {
    console.log("[WorkerTask] 发送回复消息");
    this.postMessage(message);
  }
}
new SendableTransferWorker().entry();
//# sourceMappingURL=../../.sourcemap/mp-weixin/workers/sendableTransferWorker.js.map
