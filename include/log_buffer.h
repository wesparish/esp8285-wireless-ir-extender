#pragma once
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <Arduino.h>

// Entry layout: "[HH:MM:SS] <message>" — 11-char prefix + message.
#define LOG_BUF_ENTRIES   30u
#define LOG_BUF_ENTRY_LEN 96u
#define LOG_TIMESTAMP_LEN 11u  // "[HH:MM:SS] "

// Circular ring buffer — s_logHead points to the next write slot.
// When full the oldest entry is overwritten.
static char     s_logBuf[LOG_BUF_ENTRIES][LOG_BUF_ENTRY_LEN];
static uint8_t  s_logHead  = 0;
static uint32_t s_logTotal = 0;  // monotonic count of entries ever pushed

// Prepend "[HH:MM:SS] " uptime timestamp, then store msg (truncated to fit).
inline void logPush(const char* msg) {
    uint32_t s = millis() / 1000;
    uint32_t h = s / 3600; s %= 3600;
    uint32_t m = s / 60;   s %= 60;
    snprintf(s_logBuf[s_logHead], LOG_BUF_ENTRY_LEN,
        "[%02u:%02u:%02u] %s", h, m, s, msg);
    s_logHead = (s_logHead + 1) % LOG_BUF_ENTRIES;
    s_logTotal++;
}

// Formatted push — message portion is capped at (LOG_BUF_ENTRY_LEN - LOG_TIMESTAMP_LEN - 1) chars.
inline void logPushf(const char* fmt, ...) {
    char buf[LOG_BUF_ENTRY_LEN - LOG_TIMESTAMP_LEN];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    logPush(buf);
}
