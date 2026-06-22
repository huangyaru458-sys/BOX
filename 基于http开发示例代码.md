/*
 * 示例程序 6-11：ESP32 HTTP GET请求
 * 功能：从服务器获取数据并通过串口输出
 * 核心逻辑：连接WiFi -> 构造GET请求 -> 发送并接收响应 -> 解析状态码和内容
 */
 #include <WiFi.h>
 #include <HTTPClient.h>
 #include "log_config.h"            // 引入分级日志宏定义

#define TAG "HTTP_GET"             // 日志标签

const char* ssid     = "Wokwi-GUEST";
const char* password = "";

// 以开放的测试API为例（实际使用需替换为有效API地址）
const char* apiUrl = "http://www.httpbin.org/get?devid=1&type=5";

// 定时配置
unsigned long lastRequestTime = 0;      // 记录上一次执行的时间
const unsigned long requestInterval = 10000; // 请求间隔 10,000ms (10秒)

// 状态标志
volatile bool isConnected = false;

// WiFi 事件回调
void WiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi连接成功, IP: %s", WiFi.localIP().toString().c_str());
            isConnected = true;
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOG_W(TAG, "WiFi断开（原因码: %d），正在重连...", info.wifi_sta_disconnected.reason);
            isConnected = false;
            break;
    }
}

void setup() {
    Serial.begin(115200);

​    WiFi.onEvent(WiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true);  //设置自动重连
​    WiFi.begin(ssid, password);
​    LOG_I(TAG, "系统启动...");
}

void loop() {
    unsigned long currentMillis = millis();

​    // 条件：网络必须连接 && 距离上次请求已超过间隔时间
​    if (isConnected && (currentMillis - lastRequestTime >= requestInterval)) {
​        lastRequestTime = currentMillis; 
​        // 执行HTTP-GET
​        performHttpGet();
​    }
}

void performHttpGet() {
    HTTPClient http;
    // http.begin 返回 bool 值，需判断 URL 格式是否合法
    if (http.begin(apiUrl)) {
        http.setTimeout(5000);
        
        int httpCode = http.GET();
        
        if (httpCode > 0) {
            if (httpCode == HTTP_CODE_OK) {  // HTTP_CODE_OK = 200
                String response = http.getString();
                LOG_I(TAG, "成功! 长度: %d", response.length());
                LOG_D(TAG, "内容: \n%s", response.c_str());
            } else {
                LOG_W(TAG, "服务器响应异常，状态码: %d", httpCode);
            }
        } else {  // 负值表示连接或发送错误（非HTTP协议错误）
             LOG_E(TAG, "请求失败: %s", http.errorToString(httpCode).c_str());
        }
        http.end(); // 释放资源
    } else {
        LOG_E(TAG, "无法解析 API 地址，请检查 apiUrl 字符串");
    }
}

/*
 * 示例程序 6-12：ESP32 HTTP POST 请求 (事件驱动版)
 * 功能：利用 WiFi 事件回调管理链路，实现非阻塞 JSON 数据上报
 */

#include <WiFi.h>
#include <HTTPClient.h>
#include "log_config.h"

#define TAG "HTTP_POST"

// --- 配置参数 ---
const char* ssid      = "Wokwi-GUEST";
const char* password  = "";
const char* serverUrl = "http://www.httpbin.org/post";

// --- 状态与计时变量 ---
volatile bool isConnected = false;     // 网络状态标志位
unsigned long lastPostTime = 0;        // 上一次发送的时间
const unsigned long postInterval = 10000; // 上报间隔 (10秒)

/**
 * WiFi 事件回调函数
 * 逻辑：仅负责维护连接标志位，不在此处执行耗时的网络请求
 */
 void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi 已就绪，IP: %s", WiFi.localIP().toString().c_str());
            isConnected = true;
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOG_W(TAG, "WiFi 已断开（原因: %d），正在尝试后台重连...", info.wifi_sta_disconnected.reason);
            isConnected = false;
            break;
        default:
            break;
    }
 }

/**
 * 执行 POST 业务逻辑
 */
 void sendSensorData(float temperature, float humidity) {
    HTTPClient http;
    
    // 1. 初始化并设置超时
    if (!http.begin(serverUrl)) {
        LOG_E(TAG, "无法初始化 HTTP 连接");
        return;
    }
    http.setTimeout(5000);

    // 2. 设置请求头
    http.addHeader("Content-Type", "application/json");

    // 3. 构造 JSON 请求体
    String requestBody = String("{") +
                         "\"device_id\":\"esp32_002\"," +
                         "\"temperature\":" + temperature + "," +
                         "\"humidity\":" + humidity +
                         "}";

    // 4. 发送 POST
    int httpCode = http.POST(requestBody);

    // 5. 结果解析
    if (httpCode > 0) {
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_CREATED) {
            LOG_I(TAG, "数据上报成功: \n%s", http.getString().c_str());
        } else {
            LOG_W(TAG, "服务器响应异常，状态码: %d", httpCode);
        }
    } else {
        LOG_E(TAG, "发送失败: %s", http.errorToString(httpCode).c_str());
    }

    // 6. 释放资源
    http.end();
 }

void setup() {
    Serial.begin(115200);

​    // 配置 WiFi 事件监听
​    WiFi.onEvent(onWiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true); // 启用底层自动重连逻辑
​    WiFi.begin(ssid, password);

​    LOG_I(TAG, "系统启动，等待网络连接...");
}

void loop() {
    unsigned long currentMillis = millis();

​    // 核心逻辑：只有在网络就绪且到达时间周期时才执行
​    if (isConnected && (currentMillis - lastPostTime >= postInterval)) {
​        lastPostTime = currentMillis;

​        // 模拟传感器采集
​        float t = 24.5 + (random(-5, 6) * 0.1);
​        float h = 55.0 + (random(-10, 11) * 0.1);

​        sendSensorData(t, h);
​    }
}

/*
 * 示例程序 6-13：ESP32 HTTPS 请求
 * 功能：通过 TLS 加密连接访问安全服务器，并验证服务器证书的合法性
 * 核心逻辑：
 * 1. 证书管理：加载 Root CA 根证书，确保不被中间人攻击。
 * 2. 安全客户端：使用 NetworkClientSecure 处理复杂的加密握手。
 * 3. 异步链路：利用 WiFi 事件回调维护连接状态。
 * 4. 容错处理：针对 HTTPS 握手耗时较长的特性，优化超时机制。
 */
 #include <WiFi.h>
 #include <HTTPClient.h>
 #include <NetworkClientSecure.h>// HTTPS 专用库
 #include "log_config.h"

#define TAG "HTTPS"

const char* ssid     = "Wokwi-GUEST";
const char* password = "";

// 服务器的根CA证书（需根据实际服务器获取）
// 可通过浏览器访问服务器，导出根CA证书（PEM格式），将内容复制到此处
const char* rootCACertificate =  R"string_literal(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)string_literal";

// --- 状态与计时变量 ---
volatile bool isConnected = false;
unsigned long lastHttpsTime = 0;
const unsigned long httpsInterval = 60000; // 演示：每分钟请求一次

void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi 已就绪，IP: %s", WiFi.localIP().toString().c_str());
            isConnected = true;
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOG_W(TAG, "WiFi 已断开（原因: %d），正在尝试后台重连...", info.wifi_sta_disconnected.reason);
            isConnected = false;
            break;
        default:
            break;
    }
}

// 执行 HTTPS 安全请求
void performHttpsGet() {
    // 1. 创建安全客户端。注意：HTTPS 比 HTTP 更消耗内存
    NetworkClientSecure client; 
    
    // 2. 配置安全策略
    if (rootCACertificate != NULL && strlen(rootCACertificate) > 100) {
        client.setCACert(rootCACertificate); // 验证服务器证书，防止伪造服务器
    } else {
        // [警告]：如果未提供证书，可以使用 setInsecure 跳过验证，但极不安全。
        // client.setInsecure(); 
        LOG_W(TAG, "未检测到有效证书，连接可能被拦截");
    }

​    HTTPClient https;
​    LOG_I(TAG, "发起 TLS 握手并建立安全连接...");

​    // 3. 初始化连接。HTTPS 端口默认为 443
​    if (https.begin(client, "https://www.howsmyssl.com/a/check")) {
​        // HTTPS 握手过程包含：非对称密钥交换、证书解析等，5-10秒超时是合理的
​        https.setTimeout(10000); 

​        // 4. 发起请求
​        int httpCode = https.GET();

​        // 5. 解析响应
​        if (httpCode > 0) {
​            if (httpCode == HTTP_CODE_OK) {
​                LOG_I(TAG, "安全请求成功！");
​                LOG_D(TAG, "加密测试响应: %s", https.getString().c_str());
​            } else {
​                LOG_W(TAG, "服务器返回代码: %d", httpCode);
​            }
​        } else {
​            // 常见错误：-1 (超时), -0x7200 (证书验证失败)
​            LOG_E(TAG, "TLS 握手或请求失败: %s", https.errorToString(httpCode).c_str());
​        }
​        
​        // 6. 释放资源
​        https.end();
​    }
}

void setup() {
    Serial.begin(115200);

​    WiFi.onEvent(onWiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true);
​    WiFi.begin(ssid, password);

​    LOG_I(TAG, "系统启动，正在尝试建立安全网络环境...");
}

void loop() {
    unsigned long currentMillis = millis();

​    // 仅在网络稳定且到达周期时执行
​    if (isConnected && (currentMillis - lastHttpsTime >= httpsInterval)) {
​        lastHttpsTime = currentMillis;
​        performHttpsGet();
​    }
}

/*
 * 示例程序 6-14：ArduinoJson 7.x 序列化示例
 * 功能：构造传感器数据JSON字符串
 */
 #include <ArduinoJson.h>
 #include "log_config.h"

#define TAG "JSON"

// 函数：构造传感器数据JSON字符串
// 返回值：JSON字符串（如 {"device_id":"esp32_001","temperature":25.6,...}）
String buildSensorJson(float temperature,
                       float humidity,
                       int   light) {
    // ArduinoJson 7.x：直接使用JsonDocument，无需指定容量
    JsonDocument doc;

​    // 添加标准字段
​    doc["device_id"]   = "esp32_living_room";
​    doc["timestamp"]   = 1700000000;  // 实际应用中从NTP或RTC获取
​    doc["temperature"] = temperature;
​    doc["humidity"]    = humidity;
​    doc["light"]       = light;

​    // 序列化为字符串
​    String output;
​    serializeJson(doc, output);

​    return output;
}

void setup() {
    Serial.begin(115200);

​    // 构造JSON字符串
​    String json = buildSensorJson(25.6, 60.2, 350);
​    LOG_I(TAG, "构造的JSON: %s", json.c_str());
​    // 输出：[INFO ][JSON] 构造的JSON:
​    //   {"device_id":"esp32_living_room","timestamp":1700000000,
​    //    "temperature":25.6,"humidity":60.2,"light":350}
}

void loop() {}

/*
 * 示例程序 6-15：ArduinoJson 7.x 反序列化示例
 * 功能：解析服务器下发的控制指令JSON
 */
 #include <ArduinoJson.h>
 #include "log_config.h"

#define TAG "JSON"

// 函数：解析并执行控制指令
// 参数：JSON字符串（如 {"command":"relay","value":1}）
void parseControlCommand(const String& jsonStr) {
    // ArduinoJson 7.x：直接使用JsonDocument
    JsonDocument doc;

​    // 反序列化，检查是否有错误
​    DeserializationError error = deserializeJson(doc, jsonStr);

​    if (error) {
​        LOG_E(TAG, "JSON解析失败: %s", error.c_str());
​        return;
​    }

​    // 使用 | 运算符安全读取字段（键不存在时返回默认值）
​    const char* command = doc["command"] | "unknown";
​    int value           = doc["value"]   | 0;

​    LOG_I(TAG, "指令: %s, 值: %d", command, value);

​    // 根据指令执行相应操作
​    if (strcmp(command, "relay") == 0) {
​        LOG_I(TAG, "继电器控制: %s", value == 1 ? "开" : "关");
​        // digitalWrite(RELAY_PIN, value);
​    }
}

void setup() {
    Serial.begin(115200);

​    // 模拟接收到的控制指令
​    String receivedJson = "{\"command\":\"relay\",\"value\":1,"
​                          "\"timestamp\":1700000001}";
​    parseControlCommand(receivedJson);
}

void loop() {}

/*
 * 示例程序 6-16：ArduinoJson 7.x 嵌套结构示例
 * 功能：构造带嵌套对象和数组的JSON，演示显式引用与链式调用两种写法
 */
 #include <ArduinoJson.h>
 #include "log_config.h"

#define TAG "JSON"

void setup() {
    Serial.begin(115200);

​    JsonDocument doc;

​    // 基础字段
​    doc["device_id"] = "esp32_001";
​    doc["timestamp"] = 1700000000;

​    // ============ 嵌套对象处理 ============
​    
​    // 【写法一：显式创建引用】
​    // 适用场景：需要多次操作同一个子对象，代码更清晰，避免重复键值查找
​    // JsonObject sensors = doc["sensors"].to<JsonObject>();
​    // sensors["temperature"] = 25.6;
​    // sensors["humidity"]    = 60.2;

​    // 【写法二：链式调用（ArduinoJson 7.x 推荐）】
​    // 适用场景：操作简单，代码更简洁，库会自动创建中间节点
​    // 下面这行代码可替代上面的3行，效果相同：
​    doc["sensors"]["temperature"] = 25.6;
​    doc["sensors"]["humidity"] = 60.2; 
​    // ============ 嵌套数组处理 ============
​    
​    // 【写法一：显式创建数组引用】
​    // JsonArray alerts = doc["alerts"].to<JsonArray>();
​    // alerts.add("high_temp");
​    // alerts.add("low_humidity");

​    // 【写法二：链式调用写法示例】：
​    doc["alerts"].add("high_temp");
​    doc["alerts"].add("low_humidity");

​    // ============ 序列化输出 ============
​    
​    // 格式化输出（调试用）
​    String output;
​    serializeJsonPretty(doc, output);
​    LOG_I(TAG, "嵌套JSON:\n%s", output.c_str());
​    
​    /* 输出结果：
​    {
​      "device_id": "esp32_001",
​      "timestamp": 1700000000,
​      "sensors": {
​        "temperature": 25.6,
​        "humidity": 60.2
​      },
​      "alerts": [
​        "high_temp",
​        "low_humidity"
​      ]
​    }
​    */
}

void loop() {}

/*
 * 示例程序 6-17：ESP32 简单Web服务器（WiFi事件驱动版）
 * 功能：搭建HTTP服务器，返回JSON格式模拟传感器数据
 * 接口：GET / -> 返回温湿度JSON
 * 特点：使用WiFi事件管理连接，自动重连，连接成功后自动启动Web服务
 */
 #include <WiFi.h>
 #include <WebServer.h>
 #include <ArduinoJson.h>
 #include "log_config.h"

#define TAG "WEB_SVR"

const char* ssid     = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);
volatile bool isConnected = false;  // WiFi连接状态

// 模拟传感器数据，返回JSON字符串
String getSensorJson() {
    JsonDocument doc;
    // 模拟数据赋值
    doc["temperature"] = random(200, 305) / 10.0;   // 20.0~30.4
    doc["humidity"]    = random(40, 81);            // 40~80
    // 序列化为字符串
    String jsonStr;
    serializeJson(doc, jsonStr);
    return jsonStr;
}

// 根路径请求处理
void handleRoot() {
    String json  = getSensorJson();
    server.send(200, "application/json", json );
    LOG_D(TAG, "客户端请求 -> 响应: %s", json.c_str());
}

// 404 处理
void handleNotFound() {
    server.send(404, "text/plain", "404 Not Found");
    LOG_W(TAG, "404 路径: %s", server.uri().c_str());
}

// WiFi 事件回调函数
void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        // 获取IP → 连接成功 → 启动Web服务器
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi 已连接，IP: %s", WiFi.localIP().toString().c_str());
            // 启动Web服务器
            server.begin();
            isConnected = true;
            LOG_I(TAG, "Web 服务器已启动，访问: http://%s/", WiFi.localIP().toString().c_str());
            break;

​        // WiFi 断开 → 停止服务器
​        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
​            LOG_W(TAG, "WiFi 断开，原因码: %d", info.wifi_sta_disconnected.reason);
​            isConnected = false;

​            // 断开后关闭服务器，避免异常
​            server.stop();
​            LOG_W(TAG, "Web 服务器已停止，等待网络恢复...");
​            break;

​        default:
​            break;
​    }
}

// ===================== 初始化 =====================
void setup() {
    Serial.begin(115200);

​    WiFi.onEvent(onWiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true);  // 开启自动重连
​    WiFi.begin(ssid, password);   
​    //注册路由
​    server.on("/", handleRoot);
​    server.onNotFound(handleNotFound);
​    LOG_I(TAG, "正在连接 WiFi: %s ...", ssid);
}

// ===================== 主循环 =====================
void loop() {
    // 仅在WiFi连接时处理客户端请求
    if (isConnected) {
        server.handleClient();
    }
}

/*
 * 示例程序 6-18：WebServer 参数解析（事件驱动版）  
 * 功能：处理 GET/POST 请求参数，演示参数遍历与特定键值提取
 * 测试方法：
 * GET:  http://<IP>/get?temp=25.5&humidity=60
 * POST: 使用 Postman 或 curl 发送 POST 请求，Body 选 x-www-form-urlencoded
 */

#include <WiFi.h>
#include <WebServer.h>
#include "log_config.h"

#define TAG "WEB_PARAM"

const char* ssid     = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);
volatile bool isConnected = false;

// 通用参数解析函数：遍历所有请求参数并构造响应字符串
String parseAllParams() {
    String response = "接收到的参数明细:\n";
    response += "------------------------\n";

​    // 1. 遍历所有参数
​    for (int i = 0; i < server.args(); i++) {
​        response += server.argName(i) + ": " + server.arg(i) + "\n";
​        LOG_D(TAG, "参数索引[%d] -> %s: %s", i, 
​              server.argName(i).c_str(), server.arg(i).c_str());
​    }

​    // 2. 特定参数精准提取与类型转换
​    if (server.hasArg("temp")) {
​        float temp = server.arg("temp").toFloat();
​        response += "温度解析结果: " + String(temp, 1) + " ℃\n";
​        LOG_I(TAG, "温度参数: %.1f℃", temp);
​    }
​    
​    if (server.hasArg("humidity")) {
​        int hum = server.arg("humidity").toInt();
​        response += "湿度解析结果: " + String(hum) + " %\n";
​        LOG_I(TAG, "湿度参数: %d%%", hum);
​    }

​    return response;
}

// 处理 GET /get 请求
void handleGet() {
    String response = parseAllParams();
    // 使用 charset=utf-8 确保浏览器正确显示中文/符号
    server.send(200, "text/plain; charset=utf-8", response);
}

// 处理 POST /post 请求
void handlePost() {
    String response = parseAllParams();
    server.send(200, "text/plain; charset=utf-8", response);
}

void handleNotFound() {
    server.send(404, "text/plain", "404 Not Found");
}

/**
 * WiFi 事件回调
 */
 void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "网络就绪，IP: %s", WiFi.localIP().toString().c_str());
            server.begin();
            isConnected = true;
            LOG_I(TAG, "Web 服务器已启动，访问: http://%s/", WiFi.localIP().toString().c_str());
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOG_W(TAG, "网络断开");
            isConnected = false;
            server.stop();
            LOG_W(TAG, "Web 服务器已停止，等待网络恢复...");
            break;
    }
 }

void setup() {
    Serial.begin(115200);

​    WiFi.onEvent(onWiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true);
​    WiFi.begin(ssid, password);

​    // 路由注册：明确指定请求方法
​    server.on("/get",  HTTP_GET,  handleGet);
​    server.on("/post", HTTP_POST, handlePost);
​    server.onNotFound(handleNotFound);

​    LOG_I(TAG, "系统初始化，等待网络连接...");
}

void loop() {
    if (isConnected) {
        server.handleClient();
    }
}

/*
 * 示例程序 6-19：ESP32 Web控制与数据监控系统（网页内嵌+事件驱动）
 * 功能：RESTful API控制LED、获取传感器数据，并提供可视化Dashboard
 */
 #include <WiFi.h>
 #include <WebServer.h>
 #include <ArduinoJson.h>
 #include "log_config.h"

#define TAG      "WEB_CTRL"
#define LED_PIN  2

const char* ssid     = "Wokwi-GUEST";
const char* password = "";

// --- 全局变量与实例 ---
WebServer server(80);
volatile bool isConnected = false;
int ledState = LOW;


// ---- CORS响应头 ----
// 允许浏览器从Dashboard页面跨域访问API接口
// 虽然本示例中Dashboard与API同源，无需CORS即可访问，
// 但设置此头允许从其他Web应用或本地文件直接跨域调用API。
void sendCorsHeaders() {
    server.sendHeader("Access-Control-Allow-Origin", "*");
    server.sendHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
    server.sendHeader("Access-Control-Allow-Headers", "Content-Type");
}

// 处理 LED 开启
void handleLedOn() {
    ledState = HIGH;
    digitalWrite(LED_PIN, ledState);

​    JsonDocument doc;
​    doc["status"] = "success";
​    doc["led"] = "ON";

​    String json;
​    serializeJson(doc, json);
​    sendCorsHeaders();
​    server.send(200, "application/json", json);
​    LOG_I(TAG, "LED 已打开");
}

// 处理 LED 关闭
void handleLedOff() {
    ledState = LOW;
    digitalWrite(LED_PIN, ledState);

​    JsonDocument doc;
​    doc["status"] = "success";
​    doc["led"] = "OFF";

​    String json;
​    serializeJson(doc, json);
​    sendCorsHeaders();
​    server.send(200, "application/json", json);
​    LOG_I(TAG, "LED 已关闭");
}

// 处理数据请求
void handleData() {
    float temperature = 20.0 + random(0, 100) / 10.0;

​    JsonDocument doc;
​    doc["led"] = ledState ? "ON" : "OFF";
​    doc["temperature"] = temperature;

​    String json;
​    serializeJson(doc, json);
​    sendCorsHeaders();
​    server.send(200, "application/json", json);
​    
​    LOG_D(TAG, "数据响应: %s", json.c_str());
}

// 处理根路径跳转
void handleRoot() {
    server.sendHeader("Location", "/dashboard",true);
    server.send(301, "text/plain", "Redirecting to /dashboard");
}

// 发送 Dashboard 页面
void handleDashboard() {
    server.send(200, "text/html; charset=UTF-8", getDashboardHTML());
    LOG_I(TAG, "Dashboard页面已发送");
}

// ---- Dashboard HTML页面生成 ----
// 使用 R"rawliteral()" 原始字符串字面量嵌入HTML/JS代码
String getDashboardHTML() {
    String html PROGMEM= R"rawliteral(
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 数据监控</title>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px;
               background: #f5f5f5; }
        .container { max-width: 800px; margin: 0 auto;
                     background: white; padding: 20px;
                     border-radius: 8px; box-shadow: 0 2px 8px #ddd; }
        h1 { color: #333; text-align: center; }
        .status { font-size: 1.1em; margin: 10px 0; }
        .btn { padding: 10px 24px; margin: 5px; font-size: 1em;
               border: none; border-radius: 4px; cursor: pointer; }
        .btn-on  { background: #4CAF50; color: white; }
        .btn-off { background: #f44336; color: white; }
        .chart-box { margin-top: 20px; height: 320px; }
    </style>
</head>
<body>
<div class="container">
    <h1>ESP32 实时监控面板</h1>
    <div class="status" id="led-status">LED 状态: 加载中...</div>
    <div class="status" id="temp-status">温度: 加载中...</div>
    <button class="btn btn-on"  onclick="controlLed('on')">打开 LED</button>
    <button class="btn btn-off" onclick="controlLed('off')">关闭 LED</button>
    <div class="chart-box">
        <canvas id="tempChart"></canvas>
    </div>
</div>
<script>
    // 初始化 Chart.js 折线图
    const ctx = document.getElementById('tempChart').getContext('2d');
    const chart = new Chart(ctx, {
        type: 'line',
        data: {
            labels: [],
            datasets: [{
                label: '温度 (°C)',
                data: [],
                borderColor: 'rgb(75, 192, 192)',
                backgroundColor: 'rgba(75, 192, 192, 0.1)',
                tension: 0.3,
                fill: true
            }]
        },
        options: {
            responsive: true,
            maintainAspectRatio: false,
            scales: { y: { beginAtZero: false, min: 15, max: 35 } },
            animation: { duration: 300 }
        }
    });

​    // 更新图表，保留最近30个数据点
​    function updateChart(temperature) {
​        if (chart.data.labels.length >= 30) {
​            chart.data.labels.shift();
​            chart.data.datasets[0].data.shift();
​        }
​        chart.data.labels.push(new Date().toLocaleTimeString());
​        chart.data.datasets[0].data.push(temperature);
​        chart.update();
​    }

​    // LED控制请求
​    function controlLed(action) {
​        fetch('/led/' + action , { method: 'POST' })
​            .then(r => r.json())
​            .then(data => {
​                document.getElementById('led-status').textContent =
​                    'LED 状态: ' + data.led;
​            })
​            .catch(e => console.error('LED控制失败:', e));
​    }

​    // 定时获取数据并更新页面
​    function fetchData() {
​        fetch('/data')
​            .then(r => r.json())
​            .then(data => {
​                document.getElementById('led-status').textContent =
​                    'LED 状态: ' + data.led;
​                document.getElementById('temp-status').textContent =
​                    '温度: ' + data.temperature + ' °C';
​                updateChart(parseFloat(data.temperature));
​            })
​            .catch(e => console.error('数据获取失败:', e));
​    }

​    // 页面加载后立即获取一次，之后每2秒刷新
​    fetchData();
​    setInterval(fetchData, 2000);
</script>
</body>
</html>
)rawliteral";
​    return html;
}

// WiFi 事件回调
void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "WiFi 已就绪，IP: %s", WiFi.localIP().toString().c_str());
            server.begin();
            isConnected = true;
            LOG_I(TAG, "Web 服务器启动成功");
            break;

​        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
​            LOG_W(TAG, "网络连接断开，停止 Web 服务");
​            isConnected = false;
​            server.stop(); 
​            break;
​            
​        default: break;
​    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, ledState);

​    // 静态路由配置
​    server.on("/",          HTTP_GET, handleRoot);
​    server.on("/dashboard", HTTP_GET, handleDashboard);
​    server.on("/data",      HTTP_GET, handleData);
​    server.on("/led/on",    HTTP_POST, handleLedOn);
​    server.on("/led/off",   HTTP_POST, handleLedOff);

​    // 网络与事件配置
​    WiFi.onEvent(onWiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true);
​    WiFi.begin(ssid, password);
}

void loop() {
    if (isConnected) {
        server.handleClient();
    }
}

/*
 * 示例程序 6-20：ESPAsyncWebServer + LittleFS 静态文件服务
 * 功能：托管LittleFS中的HTML页面，并提供动态JSON接口
 */
 #include <WiFi.h>
 #include <ESPAsyncWebServer.h>
 #include <LittleFS.h>
 #include <ArduinoJson.h>
 #include "log_config.h"

#define TAG "ASYNC_SVR"
#define LED_PIN 2

const char* ssid     = "MyRouter";
const char* password = "12345678";

// --- 全局实例与状态 ---
AsyncWebServer server(80);
AsyncCorsMiddleware* cors = new AsyncCorsMiddleware();  //跨域中间件
volatile bool isConnected = false;
int ledState = LOW;

// 处理 JSON 数据接口
void handleLedOn(AsyncWebServerRequest* request) {
    ledState = HIGH;
    digitalWrite(LED_PIN, ledState);

​    JsonDocument doc;
​    doc["status"] = "success";
​    doc["led"] = "ON";

​    String json;
​    serializeJson(doc, json);
​    request->send(200, "application/json", json);
​    LOG_I(TAG, "LED 已打开");
}
void handleLedOff(AsyncWebServerRequest* request) {
​    ledState = LOW;
​    digitalWrite(LED_PIN, ledState);

​    JsonDocument doc;
​    doc["status"] = "success";
​    doc["led"] = "OFF";

​    String json;
​    serializeJson(doc, json);
​    request->send(200, "application/json", json);
​    LOG_I(TAG, "LED 已关闭");
}

void handleData(AsyncWebServerRequest* request) {
    float temperature = 20.0 + random(0, 100) / 10.0;
    JsonDocument doc;
    doc["led"] = ledState ? "ON" : "OFF";
    doc["temperature"] = temperature;
    
    String json;
    serializeJson(doc, json);
    request->send(200, "application/json", json);
    LOG_D(TAG, "数据响应: %s", json.c_str());
}

void handleNotFound(AsyncWebServerRequest* request) {
    LOG_W(TAG, "404 - 未找到: %s", request->url().c_str());
    request->send(404, "text/plain", "404 Not Found");
}

// WiFi 事件回调

void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "网络就绪，IP: %s", WiFi.localIP().toString().c_str());
            server.begin();
            isConnected = true;
            LOG_I(TAG, "Web 服务已启动");
            break;
            
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOG_W(TAG, "网络断开，Web 服务已停止");
            isConnected = false;
            server.end(); 
            break;
        default: break;
    }
}


void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);

​    // 挂载文件系统
​    if (!LittleFS.begin(true)) {
​        LOG_E(TAG, "LittleFS 挂载失败！");
​        return;
​    }
​    LOG_I(TAG, "LittleFS 挂载成功");

​    // 配置 CORS：允许所有来源、常见方法和 Header
​    cors->setOrigin("*");
​    cors->setMethods("GET,POST,PUT,OPTIONS");
​    cors->setHeaders("Content-Type, Authorization");

​    // 路由配置
​    server.on("/data",    HTTP_GET, handleData);
​    server.on("/led/on",  HTTP_POST, handleLedOn);
​    server.on("/led/off", HTTP_POST, handleLedOff);
​    server.serveStatic("/", LittleFS, "/").setDefaultFile("index.html"); // 注册静态文件映射
​    server.onNotFound(handleNotFound);

​    server.addMiddleware(cors);  //所有路由都支持跨域


​    // 网络配置
​    WiFi.onEvent(onWiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true);
​    WiFi.begin(ssid, password);

​    LOG_I(TAG, "正在连接 WiFi: %s", ssid);
}

void loop() {
    // 异步服务器无需在 loop 中执行 handleClient()
}

/*
 * 示例程序 6-21：ESPAsyncWebServer 请求参数处理
 * 功能：解析GET和POST请求中的控制参数，执行相应操作
 * 测试方法：
 *   GET:  http://<IP>/control?pin=2&state=1
 *   POST: http://<IP>/update，表单体: interval=5000
 */
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "log_config.h"

#define TAG      "ASYNC_PARAM"
#define LED_PIN  2

const char* ssid     = "MyRouter";
const char* password = "12345678";

// --- 全局实例与状态 ---
AsyncWebServer server(80);
int reportInterval = 5000;      // 全局变量：上报间隔
volatile bool isConnected = false;

// --- 辅助校验函数 ---
bool isValidOutputPin(int pin) {
    const int validPins[] = {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33};
    for (int p : validPins) { if (p == pin) return true; }
    return false;
}

// 处理 GET /control?pin=2&state=1
void handleControl(AsyncWebServerRequest* request) {
    if (!request->hasParam("pin") || !request->hasParam("state")) {
        request->send(400, "application/json", "{\"error\":\"缺少必要参数\"}");
        return;
    }

​    int pin   = request->getParam("pin")->value().toInt();
​    int state = request->getParam("state")->value().toInt();

​    if (!isValidOutputPin(pin) || (state != 0 && state != 1)) {
​        request->send(400, "application/json", "{\"error\":\"引脚或状态非法\"}");
​        return;
​    }

​    pinMode(pin, OUTPUT);
​    digitalWrite(pin, state);
​    LOG_I(TAG, "控制成功: GPIO %d 设置为 %d", pin, state);
​    request->send(200, "application/json", "{\"status\":\"success\"}");
}

// 处理 POST /update (参数位于 Body)
void handleUpdateInterval(AsyncWebServerRequest* request) {
    if (!request->hasParam("interval", true)) { // true 表示从 POST 体中获取
        request->send(400, "application/json", "{\"error\":\"缺少 interval 参数\"}");
        return;
    }

​    int val = request->getParam("interval", true)->value().toInt();
​    if (val >= 1000 && val <= 60000) {
​        reportInterval = val;
​        LOG_I(TAG, "上报间隔已更新: %d ms", reportInterval);
​        request->send(200, "application/json", "{\"message\":\"updated\"}");
​    } else {
​        request->send(400, "application/json", "{\"error\":\"间隔需在 1000-60000 之间\"}");
​    }
}

// 处理 404 未找到
void handleNotFound(AsyncWebServerRequest* request) {
    request->send(404, "text/plain", "404 Not Found");
}

// --- WiFi 事件回调 ---
void onWiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    switch (event) {
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            LOG_I(TAG, "网络就绪，IP: %s", WiFi.localIP().toString().c_str());
            server.begin();
            isConnected = true;
            LOG_I(TAG, "Web 服务已启动");
            break;
            
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            LOG_W(TAG, "网络断开，Web 服务已停止");
            isConnected = false;
            server.end(); 
            break;
            
        default: break;
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(LED_PIN, OUTPUT);

​    // 注册路由
​    server.on("/control", HTTP_GET, handleControl);
​    server.on("/update", HTTP_POST, handleUpdateInterval);
​    server.onNotFound(handleNotFound);

​    // 配置 WiFi
​    WiFi.onEvent(onWiFiEvent);
​    WiFi.mode(WIFI_STA);
​    WiFi.setAutoReconnect(true); 
​    WiFi.begin(ssid, password);

​    LOG_I(TAG, "系统初始化，等待网络连接...");
}

void loop() {
    // 基于动态间隔 reportInterval 执行业务逻辑
    static unsigned long lastTime = 0;
    if (millis() - lastTime > reportInterval) {
        lastTime = millis();
        if (isConnected) {
            LOG_D(TAG, "系统心跳: IP=%s, 间隔=%dms", 
                  WiFi.localIP().toString().c_str(), reportInterval);
        }
    }
}