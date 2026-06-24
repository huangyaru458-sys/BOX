const fs = require('fs');
const path = require('path');

const file = path.join(__dirname, 'flows.json');
const flows = JSON.parse(fs.readFileSync(file, 'utf8'));

const map = new Map([
  ['tab_core', '数据采集'],
  ['tab_api', '接口服务'],
  ['tab_dash', '仪表盘'],
  ['mqtt_broker_local', '本地MQTT'],
  ['ui_tab_main', '智能衣物回收箱'],
  ['ui_group_metrics', '实时监控'],
  ['ui_group_control', '控制面板'],
  ['ui_group_alerts', '告警信息'],
  ['fn_init_schema', '初始化建表'],
  ['fn_cleanup', '清理旧数据'],
  ['mqtt_in_telemetry', '遥测输入'],
  ['json_telemetry', '解析JSON'],
  ['fn_telemetry', '遥测处理'],
  ['mqtt_in_alert', '告警输入'],
  ['json_alert', '解析JSON'],
  ['fn_alert', '告警处理'],
  ['mqtt_in_ack', '控制应答'],
  ['json_ack', '解析JSON'],
  ['fn_ack', '应答记录'],
  ['inj_refresh', '刷新状态'],
  ['fn_refresh', '刷新摘要'],
  ['http_status', '状态接口'],
  ['fn_api_status', '状态JSON'],
  ['http_history', '历史接口'],
  ['fn_history_query', '历史查询SQL'],
  ['fn_history_fmt', '历史返回'],
  ['http_devices', '设备接口'],
  ['fn_devices_query', '设备查询SQL'],
  ['fn_devices_fmt', '设备返回'],
  ['http_alerts', '告警接口'],
  ['fn_alerts_query', '告警查询SQL'],
  ['fn_alerts_fmt', '告警返回'],
  ['http_commands', '指令接口'],
  ['fn_commands_query', '指令查询SQL'],
  ['fn_commands_fmt', '指令返回'],
  ['http_health', '健康检查'],
  ['fn_health', '健康JSON'],
  ['http_control', '控制接口'],
  ['fn_control', '控制下发'],
  ['http_config', '配置接口'],
  ['fn_config', '配置下发'],
  ['http_alerts_read', '告警已读'],
  ['fn_alerts_read', '告警已读SQL'],
  ['fn_db_router', '结果分发'],
  ['fn_dash_control', '面板控制'],
  ['http_compat_latest', '兼容最新'],
  ['http_compat_history', '兼容历史'],
  ['fn_compat_history', '兼容历史参数'],
  ['http_compat_control', '兼容控制'],
  ['http_compat_devices', '兼容设备'],
  ['catch_all', '错误捕获'],
  ['status_mqtt', '节点状态'],
  ['fn_status_log', '状态日志'],
  ['debug_error', '错误输出'],
  ['debug_status', '状态输出'],
  ['debug_telemetry', '遥测调试'],
  ['db_core', 'SQLite执行'],
  ['debug_db_core', '数据库调试'],
  ['db_dash', 'SQLite执行'],
  ['debug_db_dash', '仪表盘数据库调试']
]);

for (const node of flows) {
  if (node.type === 'tab' && map.has(node.id)) node.label = map.get(node.id);
  if (map.has(node.id) && node.name !== undefined) node.name = map.get(node.id);
}

fs.writeFileSync(file, JSON.stringify(flows, null, 2), 'utf8');
console.log('Node-RED names rewritten.');
