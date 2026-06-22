/*
 * **示例程序 6-1：ESP32 STA模式连接WiFi**
 * **功能：连接到指定WiFi路由器，输出IP地址和信号强度**
 * **核心逻辑：发起连接 -> 阻塞等待结果 -> 成功获取网络参数 -> 轮询状态并重连**
 ***/**
 #include <WiFi.h>
 #include "log_config.h"  // 引入通用日志配置

#define TAG "WIFI"

const char* ssid     = "Wokwi-GUEST";      // 替换为实际WiFi名称
const char* password = "";      // 替换为实际WiFi密码

void setup() {
    Serial.begin(115200);

​    WiFi.mode(WIFI_STA);   // 设置为STA模式
​    LOG_I(TAG, "正在连接WiFi: %s", ssid);
​    
​    // 发起连接请求（非阻塞，底层WiFi任务在后台异步处理）
​    WiFi.begin(ssid, password);

​    // 阻塞等待连接成功，每500ms检查一次，最多等待约10秒
​    int retry = 0;
​    while (WiFi.status() != WL_CONNECTED && retry < 20) {
​        delay(500);
​        Serial.print(".");
​        retry++;
​    }
​    Serial.println();
​    // 连接结果判定
​    if (WiFi.status() == WL_CONNECTED) {
​        LOG_I(TAG, "WiFi连接成功，IP: %s",
​              WiFi.localIP().toString().c_str());
​        LOG_I(TAG, "MAC地址: %s", WiFi.macAddress().c_str());
​        LOG_I(TAG, "信号强度: %d dBm", WiFi.RSSI());
​    } else {
​        LOG_E(TAG, "WiFi连接失败，请检查SSID和密码");
​    }
}

void loop() {
    // 周期性检查连接状态，断开时尝试重连
  static unsigned long lastRetry = 0;
    if (WiFi.status() != WL_CONNECTED && (millis() - lastRetry > 10000)) {
        lastRetry = millis();
        LOG_W(TAG, "WiFi 断开，正在尝试静默重连...");
        WiFi.begin(ssid, password); // 重新发起连接请求
    }
}



**/***
 * **示例程序 6-2：ESP32 AP模式创建热点**
 * **功能：创建名为"ESP32_Config"的热点，显示连接设备数量**
 * **核心逻辑：定义热点参数 -> 开启AP模式 -> 输出网络信息 -> 循环监测接入设备**
 ***/**
 #include "log_config.h"
 #include <WiFi.h>

#define TAG "AP"

const char* ap_ssid     = "ESP32_Config";
const char* ap_password = "esp32setup";  // 密码至少8位

void setup() {
    Serial.begin(115200);
    // 设置模式为 WIFI_AP
    WiFi.mode(WIFI_AP);
    // 启动热点
    WiFi.softAP(ap_ssid, ap_password);
    // 输出网络信息
    LOG_I(TAG, "AP热点已启动，SSID: %s", ap_ssid);
    LOG_I(TAG, "AP IP地址: %s", WiFi.softAPIP().toString().c_str());
    LOG_I(TAG, "AP MAC地址: %s", WiFi.softAPmacAddress().c_str());
}

void loop() {
    // 实时监控接入设备数量
    int stationCount = WiFi.softAPgetStationNum();
    LOG_I(TAG, "当前连接设备数: %d", stationCount);
    delay(5000);
}

/*
 * **示例程序 6-3：ESP32 STA+AP混合模式**
 * **功能：同时连接路由器并创建本地热点**
 * **核心逻辑：设置混合模式 -> STA连接路由器 -> 启动AP热点 -> 循环监控状态**
 ***/**
 #include "log_config.h"
 #include <WiFi.h>

#define TAG "WIFI"

const char* sta_ssid     = "Wokwi-GUEST";       // 路由器SSID
const char* sta_password = "";       // 路由器密码
const char* ap_ssid      = "ESP32_Config";
const char* ap_password  = "esp32setup";

void setup() {
    Serial.begin(115200);
    // 设置为混合模式
    WiFi.mode(WIFI_AP_STA);  

​    // 作为STA连接路由器
​    WiFi.begin(sta_ssid, sta_password);
​    LOG_I(TAG, "正在连接路由器: %s", sta_ssid);
​    while (WiFi.status() != WL_CONNECTED) {
​        delay(500);
​        Serial.print(".");
​    }
​    Serial.println();
​    LOG_I(TAG, "STA已连接，IP: %s", WiFi.localIP().toString().c_str());

​    // 启动AP热点
​    WiFi.softAP(ap_ssid, ap_password);
​    LOG_I(TAG, "AP已启动，IP: %s", WiFi.softAPIP().toString().c_str());
}

void loop() {
    LOG_I(TAG, "STA RSSI: %d dBm，AP连接设备数: %d",
          WiFi.RSSI(), WiFi.softAPgetStationNum());
    delay(5000);
}

**/***

 * **示例程序 6-4：WiFi网络扫描**
 * **功能：扫描附近WiFi网络并输出详细信息**
 * **核心逻辑：设为 STA -> 断开现有连接 -> 同步扫描 -> 遍历结果 -> 内存回收**
 ***/**
 #include "log_config.h"
 #include <WiFi.h>

#define TAG "SCAN"

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();  // 确保没有活动连接
    delay(100);

​    LOG_I(TAG, "正在扫描网络...");
​    // 同步扫描是阻塞式的，直到遍历完所有信道
​    int n = WiFi.scanNetworks();  // 返回发现的网络数量

​    if (n == 0) {
​        LOG_W(TAG, "未发现任何网络");
​    } else {
​        LOG_I(TAG, "发现 %d 个网络:", n);
​        for (int i = 0; i < n; i++) {
​            Serial.printf("  %2d: %-20s  RSSI: %4d dBm  信道: %2d  %s\n",
​                          i + 1,
​                          WiFi.SSID(i).c_str(),
​                          WiFi.RSSI(i),
​                          WiFi.channel(i),
​                          WiFi.encryptionType(i) == WIFI_AUTH_OPEN ?
​                              "开放" : "加密");
​        }
​    }
​    WiFi.scanDelete();  // 删除扫描结果以释放内存
}

void loop() {}

**/***
 * **示例程序 6-5：WiFi事件回调与自动重连**
 * **功能：通过事件回调管理WiFi连接状态，断开后自动重连**
 ***/**
 #include "log_config.h"
 #include <WiFi.h>

#define TAG "WIFI"

volatile bool isConnected = false;          // 连接状态

const char* ssid     = "Wokwi-GUEST";
const char* password = "";

// WiFi 事件回调函数（由系统后台任务自动调用）
void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi 已连接，IP 地址: %s",  WiFi.localIP().toString().c_str());
            isConnected = true ; // 连接成功，清除重连标志      
            break;

​        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
​            LOG_W(TAG, "WiFi断开（原因码: %d）,正在尝试自动重连...", info.wifi_sta_disconnected.reason);
​            isConnected = false; // 标记需要重连
​            break;

​        default:
​            break;
​    }
}

void setup() {
    Serial.begin(115200);

​    // 在begin之前注册事件回调，确保不遗漏早期事件
​    WiFi.onEvent(onWiFiEvent);

​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true);  // 开启底层自动重连
​    WiFi.begin(ssid, password);   // 发起异步连接请求

​    LOG_I(TAG, "正在连接WiFi: %s", ssid);
}

void loop() {
    // WiFi连接由事件回调管理，主循环可专注业务逻辑，例如：心跳日志，监控 WiFi 状态
    static unsigned long heartbeatTick = 0;
    if (millis() - heartbeatTick >= 5000) {
        heartbeatTick = millis();
        if (isConnected) {
            LOG_D(TAG, "系统运行正常 | 信号强度: %d dBm", WiFi.RSSI());
        } else {
            LOG_D(TAG, "系统运行正常 | WiFi 未连接");
        }
    }
}



**/***
 * **示例程序 6-6：设置静态IP（事件驱动方式）**
 * **功能：以静态IP连接WiFi网络，使用事件回调管理连接状态**
 ***/**
 #include <WiFi.h>
 #include "log_config.h"

#define TAG "WIFI"  

const char* ssid     = "Wokwi-GUEST";
const char* password = "";

// 静态IP配置
IPAddress local_IP(192, 168, 1, 100);   // 静态IP（需在路由器网段内且不冲突）
IPAddress gateway(192, 168, 1, 1);      // 网关（通常为路由器IP）
IPAddress subnet(255, 255, 255, 0);     // 子网掩码
IPAddress dns(8, 8, 8, 8);             // DNS服务器

volatile bool isConnected = false;   // 连接标志

// WiFi事件回调 
void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            // 连接成功，验证静态IP是否生效
            LOG_I(TAG, "WiFi连接成功！");
            LOG_I(TAG, "  IP地址: %s（静态配置）",
                  WiFi.localIP().toString().c_str());
            LOG_I(TAG, "  网关:   %s", WiFi.gatewayIP().toString().c_str());
            LOG_I(TAG, "  子网:   %s", WiFi.subnetMask().toString().c_str());
            LOG_I(TAG, "  DNS:    %s", WiFi.dnsIP().toString().c_str());
            LOG_I(TAG, "  RSSI:   %d dBm", WiFi.RSSI());

​            // 验证分配到的IP是否与配置一致
​            if (WiFi.localIP() == local_IP) {
​                LOG_I(TAG, "✓ 静态IP配置已生效");
​            } else {
​                LOG_W(TAG, "✗ IP与预期不符，可能回退到了DHCP");
​            }

​            isConnected = true;
​            break;

​        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
​            LOG_W(TAG, "WiFi断开（原因码: %d），正在重连...",
​                  info.wifi_sta_disconnected.reason);
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
​    WiFi.setAutoReconnect(true);  // 开启底层自动重连

​    // 注入静态IP配置（必须在 begin 之前调用）
​    if (!WiFi.config(local_IP, gateway, subnet, dns)) {
​        LOG_E(TAG, "静态IP配置注入失败，将回退到DHCP");
​    } else {
​        LOG_I(TAG, "静态IP已配置: %s", local_IP.toString().c_str());
​    }

​    // 发起异步连接
​    WiFi.begin(ssid, password);
​    LOG_I(TAG, "正在连接WiFi: %s ...", ssid);
}
void loop() {
​    // 业务逻辑（每5秒输出一次心跳状态）
​    static unsigned long heartbeatTick = 0;
​    if (millis() - heartbeatTick >= 5000) {
​        heartbeatTick = millis();
​        if (isConnected) {
​            LOG_D(TAG, "运行正常 | IP: %s | RSSI: %d dBm",
​                  WiFi.localIP().toString().c_str(), WiFi.RSSI());
​        } else {
​            LOG_D(TAG, "运行正常 | WiFi离线，等待重连...");
​        }
​    }
}



