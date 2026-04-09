# HiLetgo ESP8285 ESP-01M IR Transceiver Module

Product: [HiLetgo ESP8285 ESP-01M Digital Infrared Transceiver Sensor Module](https://www.amazon.com/dp/B09KGXNZ2Q)

## Overview

The ESP-01M uses an **ESP8285** as its core controller. The ESP8285 is pin- and software-compatible with the ESP8266; any ESP8266 firmware or toolchain works as-is. The module board integrates an IR receiver and IR transmitter, plus a dedicated programming port on a separate header.

## Pin Assignments (on-module PCB)

| GPIO | Function | Direction |
|------|----------|-----------|
| IO14 | IR receiver | Input |
| IO4  | IR transmitter | Output |
| IO0  | Boot mode select (flash = GND, run = float/high) | Input |

IO14 and IO4 are hardwired on the PCB — they are not reconfigurable without hardware modification.

## Power

| Parameter | Value |
|-----------|-------|
| Supply voltage | **5V** (onboard regulator steps down to 3.3V for the ESP8285) |
| Supply pin | VCC |
| Ground pin | GND |

**No reverse-polarity protection** — incorrect VCC/GND orientation may destroy the chip.

## Programming (UART)

Connect a USB-to-UART adapter (3.3V logic level, 5V power rail):

| Adapter | Module |
|---------|--------|
| GND | GND |
| 5V | 5V |
| TX | RX |
| RX | TX |

Flash mode procedure:
1. Short **IO0 to GND**
2. Power-cycle the module
3. Flash firmware
4. Remove the IO0–GND short
5. Power-cycle again to boot normally

## Compatible Programmer

Use the **[DSD TECH SH-U09G FT232RL adapter](https://www.amazon.com/dp/B083HVM7VZ)** with the voltage jumper set to **5V**. See `docs/ft232rl-programmer-datasheet.md` for the full wiring diagram and flash mode procedure.

> Do not use a programmer that supplies only 3.3V to VCC. The onboard regulator requires more than 3.3V input headroom and will undervolt the ESP8285.

## Notes

- The ESP8285 integrates 1 MB of flash on-chip (no external flash chip)
- Programming is identical to ESP8266; use the `esp8266` platform in PlatformIO
- The module can decode and re-emit IR key values and raw codes via the `IRremoteESP8266` library
