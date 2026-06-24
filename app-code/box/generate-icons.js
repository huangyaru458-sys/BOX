const fs = require('fs');
const path = require('path');

const iconsDir = path.join(__dirname, 'static', 'icons');
if (!fs.existsSync(iconsDir)) {
    fs.mkdirSync(iconsDir, { recursive: true });
}

const createPngIcon = (color) => {
    const size = 48;
    const png = Buffer.alloc(8 + 25 + size * size * 4 + 12);
    let offset = 0;
    
    const signature = Buffer.from([0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A]);
    signature.copy(png, offset);
    offset += 8;
    
    const ihdr = Buffer.alloc(13);
    ihdr.writeUInt32BE(size, 0);
    ihdr.writeUInt32BE(size, 4);
    ihdr[8] = 8;
    ihdr[9] = 6;
    ihdr[10] = 0;
    ihdr[11] = 0;
    ihdr[12] = 0;
    
    const ihdrChunk = createChunk('IHDR', ihdr);
    ihdrChunk.copy(png, offset);
    offset += ihdrChunk.length;
    
    const rawData = Buffer.alloc(size * size * 4);
    for (let y = 0; y < size; y++) {
        for (let x = 0; x < size; x++) {
            const idx = (y * size + x) * 4;
            rawData[idx] = color.r;
            rawData[idx + 1] = color.g;
            rawData[idx + 2] = color.b;
            rawData[idx + 3] = color.a;
        }
    }
    
    const zlib = require('zlib');
    const compressed = zlib.deflateSync(rawData);
    const idatChunk = createChunk('IDAT', compressed);
    
    const finalPng = Buffer.alloc(8 + ihdrChunk.length + idatChunk.length + 12);
    offset = 0;
    signature.copy(finalPng, offset);
    offset += 8;
    ihdrChunk.copy(finalPng, offset);
    offset += ihdrChunk.length;
    idatChunk.copy(finalPng, offset);
    offset += idatChunk.length;
    
    const iendChunk = createChunk('IEND', Buffer.alloc(0));
    iendChunk.copy(finalPng, offset);
    
    return finalPng;
};

const createChunk = (type, data) => {
    const chunk = Buffer.alloc(4 + 4 + data.length + 4);
    chunk.writeUInt32BE(data.length, 0);
    chunk.write(type, 4);
    data.copy(chunk, 8);
    
    const crcData = Buffer.alloc(4 + data.length);
    crcData.write(type, 0);
    data.copy(crcData, 4);
    
    let crc = crc32(crcData);
    chunk.writeUInt32BE(crc >>> 0, 8 + data.length);
    
    return chunk;
};

const crc32 = (buf) => {
    let crc = 0xFFFFFFFF;
    const table = [];
    for (let i = 0; i < 256; i++) {
        let c = i;
        for (let j = 0; j < 8; j++) {
            c = (c & 1) ? (0xEDB88320 ^ (c >>> 1)) : (c >>> 1);
        }
        table[i] = c;
    }
    for (let i = 0; i < buf.length; i++) {
        crc = table[(crc ^ buf[i]) & 0xFF] ^ (crc >>> 8);
    }
    return crc ^ 0xFFFFFFFF;
};

fs.writeFileSync(path.join(iconsDir, 'home.png'), createPngIcon({r: 138, g: 138, b: 138, a: 255}));
fs.writeFileSync(path.join(iconsDir, 'home-active.png'), createPngIcon({r: 26, g: 115, b: 232, a: 255}));
fs.writeFileSync(path.join(iconsDir, 'control.png'), createPngIcon({r: 138, g: 138, b: 138, a: 255}));
fs.writeFileSync(path.join(iconsDir, 'control-active.png'), createPngIcon({r: 26, g: 115, b: 232, a: 255}));
fs.writeFileSync(path.join(iconsDir, 'history.png'), createPngIcon({r: 138, g: 138, b: 138, a: 255}));
fs.writeFileSync(path.join(iconsDir, 'history-active.png'), createPngIcon({r: 26, g: 115, b: 232, a: 255}));

console.log('Icons generated successfully!');