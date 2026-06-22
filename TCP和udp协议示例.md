**/***
 * **示例程序 6-7：ESP32 TCP服务器（事件驱动方式）**
 * **功能：监听TCP端口，接收客户端数据并回复确认**
 * **核心逻辑：事件回调管理WiFi -> WiFi就绪后启动TCP服务器 -> 主循环非阻塞处理客户端** 
 * **说明：客户端发送的消息需以换行符'\n'结尾**
 ***/**
 #include <WiFi.h>
 #include "log_config.h"

#define TAG "TCP_SVR"

const char* ssid     = "Wokwi-GUEST";
const char* password = "";

const uint16_t port  = 2002;     //端口号

// 全局对象
NetworkServer tcpServer(port);
NetworkClient currentClient;  // 当前连接的客户端

//  状态标志
volatile bool isConnected = false;   // 连接标志
bool serverStarted   = false;  // TCP服务器是否已启动

// WiFi事件回调
void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi连接成功，IP: %s", WiFi.localIP().toString().c_str());
            isConnected = true;       
            break;

​        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
​            LOG_W(TAG, "WiFi断开（原因码: %d），正在重连...", info.wifi_sta_disconnected.reason);
​            isConnected = false;        
​            break;

​        default:
​            break;
​    }
}

void setup() {
    Serial.begin(115200);

​    WiFi.onEvent(onWiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true);  
​    WiFi.begin(ssid, password);

​    LOG_I(TAG, "正在连接WiFi: %s ...", ssid);
}

/*
 * 主循环采用三阶段状态机，每次迭代快速执行一轮后立即返回：
 *   阶段0：WiFi 断线 → 清理资源  → return
 *   阶段1：WiFi 就绪但服务器未启动 → 启动服务器
 * 阶段2：服务器运行中 → 非阻塞处理客户端（接受/收发/清理）
     */
    void loop() {
    // ============ 阶段0：WiFi断线处理 ============
    if (!isConnected) {
        // 如果 WiFi 掉了，清理现有的 Socket 连接，防止占用内存
        if (currentClient) {
            currentClient.stop();
            LOG_I(TAG, "因 WiFi 断开，清理客户端连接");
        }
        // 停止TCP服务器, 等待网络恢复后重新启动
        if (serverStarted) {
            tcpServer.end();
            serverStarted = false;
            LOG_I(TAG, "TCP服务器已停止");
        }
        return;  // WiFi未就绪，跳过后续所有阶段
    }

    // ============ 阶段1：网络恢复后, 启动TCP服务器 ============
    if (isConnected && !serverStarted) {
        tcpServer.begin();
        tcpServer.setNoDelay(true);  // 禁用Nagle算法，降低小包延迟
        serverStarted = true;
        LOG_I(TAG, "TCP服务器已启动，监听端口: %d", port);
    }
    if (!serverStarted) return;  // 服务器未就绪，跳过客户端处理

    // ============ 阶段2：非阻塞客户端管理 ============
    // 本阶段分三步顺序执行，每步仅做一次快速检查

    // ---- 步骤A：处理客户端主动断开的情况，释放资源 ----
    if (currentClient && !currentClient.connected()) {
        currentClient.stop();  // 关闭socket
        LOG_I(TAG, "客户端已断开");
    }

    // ---- 步骤B：无活跃客户端时，尝试接受新连接 ----
    if (!currentClient) {
        currentClient = tcpServer.accept();
        // accept() 无连接时返回空对象
        if (currentClient) {
            LOG_I(TAG, "新客户端连接: %s:%d",
                  currentClient.remoteIP().toString().c_str(),
                  currentClient.remotePort());
        }
    }

    // ---- 步骤C：数据收发处理（非阻塞读取）----
    if (currentClient && currentClient.connected() && currentClient.available()) {
        String message = currentClient.readStringUntil('\n');// 读取数据直到换行符
        LOG_I(TAG, "收到数据: %s", message.c_str());

    ​    // 构造回显信息并回复
    ​    String response = "Server ACK:" + message + "\n";
    ​    currentClient.print(response);
    }
    }

    **/***
     * **示例程序 6-8：ESP32 TCP客户端（事件驱动方式）**
     * **功能：连接TCP服务器，实现串口与TCP之间的双向数据透传**
     * **状态机：**
     *   **WiFi断线 ──(事件回调)──> WiFi就绪 ──(loop)──> TCP连接中 ──> 透传工作**
     *      **↑                                             │**
     *      **└──────────────── WiFi断开事件 ────────────────┘**
     ***/**
    #include <WiFi.h>
    #include "log_config.h"

    #define TAG "TCP_CLI"

    const char* ssid     = "Wokwi-GUEST";
    const char* password = "";

    const IPAddress serverIP(192, 168, 1, 100);  // 目标服务器IP
    const uint16_t  serverPort = 2002;           // 目标服务器端口

    // 全局对象
    NetworkClient tcpClient;  // TCP客户端

    // 状态标志
    volatile bool isConnected = false;   // 连接标志

    // WiFi事件回调
    void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
        switch (event) {
            case ARDUINO_EVENT_WIFI_STA_GOT_IP:
                LOG_I(TAG, "WiFi连接成功, IP: %s", WiFi.localIP().toString().c_str());
                isConnected = true;
                break;

    ​        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
    ​            LOG_W(TAG, "WiFi断开（原因码: %d），正在重连...", info.wifi_sta_disconnected.reason);
    ​            isConnected = false;
    ​            break;

    ​        default:
    ​            break;
    ​    }
    }

    void setup() {
        Serial.begin(115200);

    ​    WiFi.onEvent(onWiFiEvent);
    ​    WiFi.mode(WIFI_STA);
    ​    WiFi.setAutoReconnect(true);  
    ​    WiFi.begin(ssid, password);

    ​    LOG_I(TAG, "正在连接WiFi: %s ...", ssid);
    ​    LOG_I(TAG, "目标TCP服务器: %s:%d", serverIP.toString().c_str(), serverPort);
    }

    /*
     * 主循环采用三阶段状态机，每次迭代快速执行后立即返回：
     *   阶段0：WiFi 断线 → 清理TCP连接 + 定时重连WiFi → return
     *   阶段1：WiFi 就绪但TCP未连接 → 定时尝试连接服务器 → return
     * 阶段2：TCP 已连接 → 非阻塞双向透传
         */
        void loop() {
        // ============ 阶段0：WiFi断线处理 ============
        if (!isConnected) {
            // WiFi断开时，TCP连接必然不可用，主动清理
            if (tcpClient.connected()) {
                tcpClient.stop();
                LOG_I(TAG, "WiFi断开, 已关闭TCP连接");
            }
            return;  // WiFi未就绪，跳过后续所有阶段
        }

        // ============ 阶段1：TCP连接管理 ============
        if (isConnected && !tcpClient.connected()) {
            // 非阻塞定时重连TCP服务器
            static unsigned long lastTcpRetry = 0;
            if (millis() - lastTcpRetry >= 5000) {   // 每5秒尝试一次
                lastTcpRetry = millis();
                LOG_I(TAG, "连接TCP服务器 %s:%d ...",
                      serverIP.toString().c_str(), serverPort);

        ​        // connect() 的第三个参数为超时时间（毫秒）
        ​        // 超时期间会阻塞，但最多阻塞 3 秒，不会无限等待
        ​        if (tcpClient.connect(serverIP, serverPort, 3000)) {
        ​            LOG_I(TAG, "TCP连接成功!");
        ​            tcpClient.setNoDelay(true);  // 禁用Nagle算法
        ​        } else {
        ​            LOG_E(TAG, "TCP连接失败, 请检查服务器状态");
        ​            tcpClient.stop();  // 清理socket资源
        ​        }
        ​    }
        ​    return;  // TCP未就绪，跳过透传阶段
        }

        // ============ 阶段2：双向数据透传 ============
        // ---- 方向1：TCP → 串口（接收服务器数据）----
        if (tcpClient.available()) {
            String received = tcpClient.readStringUntil('\n');
            LOG_I(TAG,"[RECV] 来自 %s:%d: %s\n",
                          tcpClient.remoteIP().toString().c_str(),
                          tcpClient.remotePort(),
                          received.c_str());
        }

        // ---- 方向2：串口 → TCP（发送用户输入）----
        if (Serial.available()) {
            String sendMsg = Serial.readStringUntil('\n');
            tcpClient.println(sendMsg);  // println 自动追加 '\n'
            LOG_I(TAG, "已发送: %s", sendMsg.c_str());
        }
        }

        <span style="font-weight:bold;">/*</span>

         * <span style="font-weight:bold;">示例程序 6-9：ESP32 UDP通用通信（事件驱动方式）</span>
         * <span style="font-weight:bold;">功能：通过UDP发送和接收数据，支持串口动态指定目标地址</span>
         * <span style="font-weight:bold;">核心逻辑：事件回调管理WiFi -> WiFi就绪后初始化UDP -> 主循环非阻塞收发 -> WiFi断线时暂停通信并自动重连</span>
         * <span style="font-weight:bold;">状态机：</span>
         *   <span style="font-weight:bold;">WiFi断线 ──(事件)──> WiFi就绪 ──(loop)──> UDP就绪 ──> 收发工作</span>
         *      <span style="font-weight:bold;">↑                                                    │</span>
         * <span style="font-weight:bold;">└──────────────── WiFi断开事件 ───────────────────────┘</span>

           **** *
         * <span style="font-weight:bold;">说明：串口输入格式为 <目标IP>,<目标端口>,<消息></span>
         *       <span style="font-weight:bold;">例如: 192.168.1.100,2001,Hello</span>
         *       <span style="font-weight:bold;">使用广播地址 255.255.255.255 可实现局域网广播</span>
        <span style="font-weight:bold;"> */</span>
        #include <WiFi.h>
        #include <NetworkUdp.h>
        #include "log_config.h"

        #define TAG "UDP"

        const char* ssid     = "Wokwi-GUEST";
        const char* password = "";
        const uint16_t localPort = 2001;  // 本地监听端口

        //  全局对象 
        NetworkUDP udp;

        //  状态标志 
        volatile bool isConnected = false;   // 连接标志
        bool udpStarted      = false;  // UDP是否已初始化

        //  WiFi事件回调 
        void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
            switch (event) {
                case ARDUINO_EVENT_WIFI_STA_GOT_IP:
                    LOG_I(TAG, "WiFi连接成功, IP: %s", WiFi.localIP().toString().c_str());
                    isConnected = true;
                    break;

        ​        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        ​            LOG_W(TAG, "WiFi断开（原因码: %d），正在重连...", info.wifi_sta_disconnected.reason);
        ​            isConnected = false;
        ​            break;

        ​        default:
        ​            break;
        ​    }
        }

        //  串口解析与UDP发送 
        // 解析用户输入的 "<IP>,<端口>,<消息>" 格式并发送UDP数据报
        void parseAndSend(String input) {
            // 查找两个逗号分隔符的位置
            int firstComma  = input.indexOf(',');
            int secondComma = input.indexOf(',', firstComma + 1);

        ​    if (firstComma == -1 || secondComma == -1) {
        ​        LOG_E(TAG, "格式错误，请使用: <IP>,<端口>,<消息>");
        ​        return;
        ​    }

        ​    // 提取并验证目标IP
        ​    String ipStr = input.substring(0, firstComma);
        ​    IPAddress targetIP;
        ​    if (!targetIP.fromString(ipStr)) {
        ​        LOG_E(TAG, "无效的IP地址: %s", ipStr.c_str());
        ​        return;
        ​    }

        ​    // 提取并验证目标端口
        ​    uint16_t targetPort = input.substring(firstComma + 1,
        ​                                          secondComma).toInt();
        ​    if (targetPort == 0) {
        ​        LOG_E(TAG, "无效的端口号");
        ​        return;
        ​    }

        ​    // 提取消息内容
        ​    String message = input.substring(secondComma + 1);
        ​    if (message.length() == 0) {
        ​        LOG_E(TAG, "消息不能为空");
        ​        return;
        ​    }

        ​    // 三步发送UDP数据报
        ​    udp.beginPacket(targetIP, targetPort);  // 步骤1：指定目标
        ​    udp.print(message);                     // 步骤2：写入数据
        ​    if (udp.endPacket()) {                  // 步骤3：完成发送
        ​        LOG_I(TAG, "已发送到 %s:%d: %s",
        ​              targetIP.toString().c_str(), targetPort,
        ​              message.c_str());
        ​    } else {
        ​        LOG_E(TAG, "发送失败");
        ​    }
        }

        void setup() {
            Serial.begin(115200);

        ​    WiFi.onEvent(onWiFiEvent);
        ​    WiFi.mode(WIFI_STA);
        ​    WiFi.setAutoReconnect(true);  
        ​    WiFi.begin(ssid, password);

        ​    LOG_I(TAG, "正在连接WiFi: %s ...", ssid);
        }

        /*
         * 主循环采用三阶段状态机，每次迭代快速执行后立即返回：
         *   阶段0：WiFi 断线 → 停止UDP  → return
         *   阶段1：WiFi 就绪但UDP未启动 → 初始化UDP
         * 阶段2：UDP 就绪 → 非阻塞收发数据
             */
            void loop() {
            // ============ 阶段0：WiFi断线处理 ============
            if (!isConnected) {
                // WiFi断开时，UDP通信不可用，停止UDP
                if (udpStarted) {
                    udp.stop();
                    udpStarted = false;
                    LOG_I(TAG, "WiFi断开，UDP已停止");
                }
                return;  // WiFi未就绪，跳过后续所有阶段
            }

            // ============ 阶段1：初始化UDP ============
            if (isConnected && !udpStarted) {
                // 绑定到STA接口的IP和端口
                udp.begin(WiFi.localIP(), localPort);
                udpStarted = true;
                LOG_I(TAG, "UDP已就绪，绑定到 %s:%d",
                      WiFi.localIP().toString().c_str(), localPort);
                LOG_I(TAG, "串口输入格式: <IP>,<端口>,<消息>");
                LOG_I(TAG, "广播示例: 255.255.255.255,%d,Hello", localPort);
            }
            if (!udpStarted) return;  // UDP未就绪，跳过收发

            // ============ 阶段2：非阻塞收发数据 ============
            // ---- 发送：解析串口输入 ----
            if (Serial.available()) {
                String input = Serial.readStringUntil('\n');
                parseAndSend(input);
            }

            // ---- 接收：检查并读取UDP数据报 ----
            int packetSize = udp.parsePacket();
            if (packetSize > 0) {
                char rxBuffer[256] = {0};
                int len = udp.read(rxBuffer, sizeof(rxBuffer) - 1);
                LOG_I(TAG, "收到来自 %s:%d 的数据(%d字节): %s",
                      udp.remoteIP().toString().c_str(),
                      udp.remotePort(),
                      len,
                      rxBuffer);
            }
            }

            /*
             * **示例程序 6-10：TCP客户端——传感器数据定时上报（事件驱动方式）**
             * **功能：定期通过TCP长连接向服务器发送传感器数据，接收服务器应答**
             * **核心逻辑：事件回调管理WiFi -> WiFi就绪后连接TCP服务器 ->**
             *           **定时采集并上报数据 -> 非阻塞接收应答 -> 多级断线自动恢复**
             * **状态机（三层级联恢复）：**
             *   **WiFi断线 ──(事件)──> WiFi就绪 ──(loop)──> TCP连接 ──> 定时上报**
             *      **↑                    ↑                    │          │**
             *      **│                    │           TCP断开───┘          │**
             *      **└──────────────── WiFi断开事件 ───────────────────────┘**
             * **任何层级断开，都会级联影响下游：**
             *   **WiFi断开 → TCP必然不可用 → 上报暂停**
             *   **TCP断开（服务器重启等） → 上报暂停，但WiFi仍在线，仅需重连TCP**
             ***/**
            #include "log_config.h"
            #include <WiFi.h>

            #define TAG "SENSOR"

            const char* ssid     = "Wokwi-GUEST";
            const char* password = "";

            const IPAddress serverIP(192, 168, 1, 100);  // 目标服务器IP
            const uint16_t  serverPort = 8080;           // 目标服务器端口
            const unsigned long sendInterval = 2000;     // 数据上报间隔：2秒

            //  全局对象 
            NetworkClient tcpClient;  // TCP客户端（全局持有，跨 loop() 迭代保持连接）

            //  状态标志 
            volatile bool isConnected = false;   // 连接标志

            //  上报统计 
            unsigned long lastSendTime  = 0;   // 上次发送时间戳
            uint32_t      sendCount     = 0;   // 累计发送帧数（用于监控）
            uint32_t      failCount     = 0;   // 累计发送失败次数

            //  WiFi事件回调 
            void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
                switch (event) {
                    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
                        LOG_I(TAG, "WiFi连接成功, IP: %s", WiFi.localIP().toString().c_str());
                        isConnected = true;
                        break;

            ​        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            ​            LOG_W(TAG, "WiFi断开（原因码: %d），正在重连...", info.wifi_sta_disconnected.reason);
            ​            isConnected = false;
            ​            break;

            ​        default:
            ​            break;
            ​    }
            }

            //  传感器数据采集 
            // 模拟采集函数（实际应用中替换为真实传感器读数）
            void readSensors(float &temperature, float &humidity) {
                // 模拟带有微小波动的传感器数据
                temperature = 25.6 + random(-10, 11) * 0.1;
                humidity    = 60.2 + random(-5, 6) * 0.1;
            }

            void setup() {
                Serial.begin(115200);

            ​    WiFi.onEvent(onWiFiEvent);
            ​    WiFi.mode(WIFI_STA);
            ​    WiFi.setAutoReconnect(true);  
            ​    WiFi.begin(ssid, password);

            ​    LOG_I(TAG, "正在连接WiFi: %s ...", ssid);
            ​    LOG_I(TAG, "目标服务器: %s:%d，上报间隔: %lu ms",
            ​          serverIP.toString().c_str(), serverPort, sendInterval);
            }

            /*
             * 主循环采用三阶段状态机，每次迭代快速执行后立即返回：
             *   阶段0：WiFi 断线 → 清理TCP → return
             *   阶段1：WiFi 就绪但TCP未连接 → 定时连接服务器 → return
             *   阶段2：TCP 已连接 → 定时上报数据 + 非阻塞接收应答
             */
            void loop() {
                // ============ 阶段0：WiFi断线处理 ============
                if (!isConnected) {
                    // WiFi断开 → TCP必然不可用，主动清理
                    if (tcpClient.connected()) {
                        tcpClient.stop();
                        LOG_I(TAG, "WiFi断开，已关闭TCP连接");
                    }
                    return;  // WiFi未就绪，跳过后续所有阶段
                }

                // ============ 阶段1：TCP连接管理 ============
                // 触发场景：① WiFi刚恢复  ② 服务器主动断开  ③ 网络抖动导致TCP断开
                if (isConnected && !tcpClient.connected()) {
                    // 非阻塞定时重连TCP服务器
                    static unsigned long lastTcpRetry = 0;
                    if (millis() - lastTcpRetry >= 5000) {  // 每5秒尝试一次
                        lastTcpRetry = millis();
                        LOG_I(TAG, "连接服务器 %s:%d ...",
                              serverIP.toString().c_str(), serverPort);

                ​        if (tcpClient.connect(serverIP, serverPort, 3000)) {
                ​            LOG_I(TAG, "TCP连接成功！（累计已发送 %u 帧）", sendCount);
                ​            tcpClient.setNoDelay(true);  // 禁用Nagle算法
                ​        } else {
                ​            LOG_E(TAG, "TCP连接失败，请检查服务器状态");
                ​            tcpClient.stop();  // 清理socket资源
                ​        }
                ​    }
                ​    return;  // TCP未就绪，跳过上报阶段
                }

                // ============ 阶段2：定时数据上报 + 接收应答 ============
                // ---- 定时采集并上报传感器数据 ----
                if (millis() - lastSendTime >= sendInterval) {
                    lastSendTime = millis();

                ​    // 采集传感器数据
                ​    float temperature, humidity;
                ​    readSensors(temperature, humidity);

                ​    // 构造数据帧
                ​    char data[64];
                ​    snprintf(data, sizeof(data), "T:%.1f,H:%.1f\n",
                ​             temperature, humidity);

                ​    // 发送数据并检查结果
                ​    size_t written = tcpClient.print(data);
                ​    if (written > 0) {
                ​        sendCount++;
                ​        LOG_I(TAG, "帧#%u 已发送: T=%.1f, H=%.1f",
                ​              sendCount, temperature, humidity);
                ​    } else {
                ​        failCount++;
                ​        LOG_E(TAG, "发送失败（累计失败 %u 次）", failCount);
                ​        // 发送失败通常意味着TCP连接已断开
                ​        // 下一次 loop() 迭代会检测到 !tcpClient.connected()
                ​        // 自动回到阶段1进行重连
                ​    }
                }

                // ---- 非阻塞接收服务器应答 ----
                if (tcpClient.available()) {
                    String response = tcpClient.readStringUntil('\n');
                    LOG_I(TAG, "服务器回复: %s", response.c_str());
                }
            }