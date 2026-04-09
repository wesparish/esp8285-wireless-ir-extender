#pragma once
#include <stdint.h>
#include <stddef.h>
#include <string.h>

// Wire format for an IR signal transmitted over ESP-NOW.
// Both nodes must agree on this layout — never reorder or resize fields
// without updating both sides and verifying sizeof() in unit tests.
struct IrPayload {
    uint32_t protocol;  // IRremoteESP8266 decode_type_t cast to uint32_t
    uint16_t bits;      // signal bit length
    uint64_t value;     // decoded IR value
};

// Deserialize raw bytes into an IrPayload.
// Returns false if len != sizeof(IrPayload) — caller should discard the packet.
inline bool ir_payload_decode(const uint8_t* data, size_t len, IrPayload* out) {
    if (len != sizeof(IrPayload)) return false;
    memcpy(out, data, sizeof(IrPayload));
    return true;
}

// Serialize an IrPayload into a byte buffer.
// buf must be at least sizeof(IrPayload) bytes.
inline void ir_payload_encode(const IrPayload* in, uint8_t* buf) {
    memcpy(buf, in, sizeof(IrPayload));
}
