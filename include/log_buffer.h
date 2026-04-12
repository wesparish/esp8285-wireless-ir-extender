#pragma once
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define LOG_BUF_ENTRIES   30u
#define LOG_BUF_ENTRY_LEN 80u

// Circular ring buffer — s_logHead points to the next write slot.
// When full the oldest entry is overwritten.
static char     s_logBuf[LOG_BUF_ENTRIES][LOG_BUF_ENTRY_LEN];
static uint8_t  s_logHead  = 0;
static uint32_t s_logTotal = 0;  // monotonic count of entries ever pushed

inline void logPush(const char* msg) {
    strncpy(s_logBuf[s_logHead], msg, LOG_BUF_ENTRY_LEN - 1);
    s_logBuf[s_logHead][LOG_BUF_ENTRY_LEN - 1] = '\0';
    s_logHead = (s_logHead + 1) % LOG_BUF_ENTRIES;
    s_logTotal++;
}

inline void logPushf(const char* fmt, ...) {
    char buf[LOG_BUF_ENTRY_LEN];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    logPush(buf);
}
