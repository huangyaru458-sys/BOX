# Node-RED 后端说明

本后端按实训要求采用 Node-RED 图形化流程实现，核心文件是 `flows.json`。

## 需要手动安装的节点

在 `D:\finish-tsask\back-code` 目录执行：

```bat
npm install
```

或在 Node-RED 右上角菜单进入“管理调色板”，安装：

- `node-red-node-sqlite`
- `node-red-dashboard`

## 启动顺序

1. 启动 MQTT Broker：

```bat
D:\finish-tsask\back-code\start-mqtt.cmd
```

2. 启动 Node-RED：

```bat
D:\finish-tsask\back-code\start-nodered.cmd
```

3. 打开：

- Node-RED 编辑器：`http://localhost:1880`
- Node-RED Dashboard：`http://localhost:1880/ui`
- 托管前端页面：`http://localhost:1880/web/index.html`

ESP32 MQTT 服务器填写电脑局域网 IP，例如 `192.168.34.228`，端口 `1883`。

## API 路径

设计文档路径：

- `GET /api/v1/box/status`
- `GET /api/v1/box/history?deviceId=ESP32_BOX_001&limit=50`
- `POST /api/v1/box/control`
- `GET /api/v1/box/devices`
- `GET /api/v1/box/alerts?deviceId=ESP32_BOX_001`
- `POST /api/v1/box/alerts/read`
- `GET /api/v1/box/commands`
- `GET /api/v1/box/health`
- `POST /api/v1/box/config`

实训要求示例兼容路径：

- `GET /api/data/latest`
- `GET /api/data/history?device_id=ESP32_BOX_001&limit=50`
- `POST /api/control`
- `GET /api/devices`

## Node-RED 流程覆盖

- MQTT 输入：遥测、告警、控制 ACK。
- MQTT 输出：控制指令、配置下发。
- JSON/Function：解析、校验、类型转换、在线状态、告警抑制。
- SQLite：建表、遥测入库、告警入库、控制记录、历史查询、30 天清理。
- HTTP API：实时数据、历史数据、设备列表、告警列表、控制下发、配置下发。
- Dashboard：温度、湿度、满载率、空气质量、倾斜角、实时曲线、状态摘要、控制按钮、告警列表。
- 运维监控：Catch、Status、Debug 输出。
- 静态托管：`vue-code` 挂载到 `/web`。
