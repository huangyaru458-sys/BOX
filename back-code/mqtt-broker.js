const net = require('net');

const PORT = Number(process.env.MQTT_PORT || 1883);
const clients = new Set();

function encodeLength(len) {
  const out = [];
  do {
    let digit = len % 128;
    len = Math.floor(len / 128);
    if (len > 0) digit |= 0x80;
    out.push(digit);
  } while (len > 0);
  return Buffer.from(out);
}

function packet(type, body = Buffer.alloc(0)) {
  return Buffer.concat([Buffer.from([type]), encodeLength(body.length), body]);
}

function str(text) {
  const b = Buffer.from(String(text));
  const h = Buffer.alloc(2);
  h.writeUInt16BE(b.length);
  return Buffer.concat([h, b]);
}

function readLength(buf, offset) {
  let multiplier = 1;
  let value = 0;
  let digit = 0;
  let pos = offset;
  do {
    digit = buf[pos++];
    value += (digit & 127) * multiplier;
    multiplier *= 128;
  } while ((digit & 128) !== 0 && pos < buf.length);
  return { value, pos };
}

function readString(buf, offset) {
  const len = buf.readUInt16BE(offset);
  const start = offset + 2;
  return { value: buf.slice(start, start + len).toString(), pos: start + len };
}

function matches(filter, topic) {
  if (filter === '#') return true;
  if (filter.endsWith('/#')) return topic.startsWith(filter.slice(0, -1));
  return filter === topic;
}

function publish(topic, payload, except = null) {
  const body = Buffer.concat([str(topic), Buffer.from(payload)]);
  const pkt = packet(0x30, body);
  for (const client of clients) {
    if (client === except) continue;
    if (client.subs.some((sub) => matches(sub, topic))) {
      client.socket.write(pkt);
    }
  }
}

const server = net.createServer((socket) => {
  const client = { socket, subs: [], id: 'unknown' };
  clients.add(client);
  let buffer = Buffer.alloc(0);

  socket.on('data', (chunk) => {
    buffer = Buffer.concat([buffer, chunk]);
    while (buffer.length >= 2) {
      const len = readLength(buffer, 1);
      const total = len.pos + len.value;
      if (buffer.length < total) break;
      const type = buffer[0] >> 4;
      const body = buffer.slice(len.pos, total);
      buffer = buffer.slice(total);

      try {
        if (type === 1) {
          let pos = 0;
          const proto = readString(body, pos);
          pos = proto.pos + 4;
          const cid = readString(body, pos);
          client.id = cid.value || `client_${Date.now()}`;
          socket.write(packet(0x20, Buffer.from([0x00, 0x00])));
          console.log('[mqtt] connect', client.id);
        } else if (type === 3) {
          const t = readString(body, 0);
          const payload = body.slice(t.pos);
          console.log('[mqtt] publish', t.value, payload.toString());
          publish(t.value, payload, client);
        } else if (type === 8) {
          let pos = 0;
          const pid = body.readUInt16BE(pos); pos += 2;
          const granted = [];
          while (pos < body.length) {
            const t = readString(body, pos);
            pos = t.pos + 1;
            client.subs.push(t.value);
            granted.push(0);
            console.log('[mqtt] sub', client.id, t.value);
          }
          socket.write(packet(0x90, Buffer.from([pid >> 8, pid & 255, ...granted])));
        } else if (type === 12) {
          socket.write(packet(0xD0));
        } else if (type === 14) {
          socket.end();
        }
      } catch (err) {
        console.error('[mqtt] packet error', err.message);
      }
    }
  });

  socket.on('close', () => {
    clients.delete(client);
    console.log('[mqtt] disconnect', client.id);
  });
});

server.listen(PORT, '0.0.0.0', () => {
  console.log(`[mqtt] broker listening on 0.0.0.0:${PORT}`);
});
