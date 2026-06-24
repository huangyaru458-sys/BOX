require('uni-worker.js')
"use strict";
class HelloWorkerTask extends WorkerTaskImpl {
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
    console.log("[WorkerTask] 收到主线程消息: ", message);
    const messageData = message;
    const msgData = messageData["data"];
    const needReply = messageData["needReply"];
    console.log(`[WorkerTask] 数据: ${msgData}, 需要回复: ${needReply}`);
    if (needReply) {
      this.sendReply(msgData);
    }
  }
  // 发送回复消息
  sendReply(msgData) {
    const response = new UTSJSONObject();
    const inputNumber = parseInt(msgData);
    if (isNaN(inputNumber)) {
      response.data = `输入"${msgData}"不是有效数字`;
    } else {
      const result = inputNumber + 1;
      response.data = result.toString();
    }
    console.log("[WorkerTask] 发送回复消息:", response);
    this.postMessage(response);
  }
}
new HelloWorkerTask().entry();
//# sourceMappingURL=../../.sourcemap/mp-weixin/workers/helloWorkerTask.js.map
