const BASE_URL = 'http://10.94.163.228:1880';

export interface TelemetryData {
  deviceId: string;
  temperature: number;
  humidity: number;
  capacity: number;
  airQuality: number;
  humanDetect: boolean;
  fanStatus: boolean;
  frontDoor: boolean;
  backDoor: boolean;
  tiltAngle: number;
  sensorFaults: string[];
  buzzerMode: string;
  netMode: string;
  systemState: string;
  lastSeen: number;
}

export interface ControlResult {
  code: number;
  msg: string;
  data?: {
    sent: boolean;
    topic: string;
    command: unknown;
    offlineWarning: boolean;
  };
}

export interface HistoryRecord {
  id: number;
  device_id: string;
  ts: number;
  temperature: number;
  humidity: number;
  capacity: number;
  air_quality: number;
  human_detect: number;
  fan_status: number;
  front_door: number;
  back_door: number;
  tilt_angle: number;
  sensor_faults: string;
  buzzer_mode: string;
}

export interface AlertRecord {
  id: number;
  device_id: string;
  ts: number;
  alert_type: string;
  alert_msg: string;
  is_ack: number;
}

function request<T>(options: {
  url: string;
  method?: 'GET' | 'POST' | 'PUT' | 'DELETE';
  data?: Record<string, unknown>;
  params?: Record<string, string | number>;
}): Promise<T> {
  return new Promise((resolve, reject) => {
    let fullUrl = BASE_URL + options.url;
    
    if (options.params) {
      const query = new URLSearchParams(options.params as Record<string, string>).toString();
      if (query) {
        fullUrl += '?' + query;
      }
    }
    
    uni.request({
      url: fullUrl,
      method: options.method || 'GET',
      data: options.data,
      header: {
        'Content-Type': 'application/json'
      },
      success: (res) => {
        if (res.statusCode === 200) {
          resolve(res.data as T);
        } else {
          reject(new Error('Request failed: ' + res.statusCode));
        }
      },
      fail: (err) => {
        reject(err);
      }
    });
  });
}

export const api = {
  getLatestStatus: (deviceId?: string): Promise<TelemetryData> => {
    return request({
      url: '/api/v1/box/latest',
      params: deviceId ? { deviceId } : undefined
    });
  },

  sendControl: (action: string, deviceId?: string): Promise<ControlResult> => {
    return request({
      url: '/api/v1/box/control',
      method: 'POST',
      data: {
        action,
        deviceId: deviceId || 'ESP32_BOX_001',
        adminToken: 'admin_auth_secret01'
      }
    });
  },

  getHistory: (params: {
    deviceId?: string;
    limit?: number;
    startTs?: number;
    endTs?: number;
  }): Promise<HistoryRecord[]> => {
    return request({
      url: '/api/v1/box/history',
      params: params
    });
  },

  getAlerts: (params: {
    deviceId?: string;
    limit?: number;
    isAck?: number;
  }): Promise<AlertRecord[]> => {
    return request({
      url: '/api/v1/box/alerts',
      params: params
    });
  },

  acknowledgeAlert: (alertId: number): Promise<{ code: number; msg: string }> => {
    return request({
      url: '/api/v1/box/alerts/' + alertId + '/ack',
      method: 'POST'
    });
  }
};

export const CONTROL_COMMANDS = {
  FRONT_DOOR_OPEN: 'FRONT_DOOR_OPEN',
  FRONT_DOOR_CLOSE: 'FRONT_DOOR_CLOSE',
  BACK_DOOR_OPEN: 'BACK_DOOR_OPEN',
  BACK_DOOR_CLOSE: 'BACK_DOOR_CLOSE',
  FAN_ON: 'FAN_ON',
  FAN_OFF: 'FAN_OFF',
  ALARM_STOP: 'ALARM_STOP',
  BUZZER_ON: 'BUZZER_ON',
  BUZZER_OFF: 'BUZZER_OFF'
} as const;
