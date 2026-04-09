# USB to ESP-01 Programmer Adapter (CH340G)

Product: USB to ESP8266 ESP-01 Wireless WiFi Adapter Module (CH340G driver)

## Overview

USB programmer for ESP-01/ESP-01S form-factor modules. The CH340G IC provides USB-to-UART bridging. The module under test or programming plugs directly into the onboard 8-pin socket — no jumper wires required. An onboard toggle switch selects between UART debugging mode and PROG (firmware programming) mode.

## Electrical Specs

| Parameter | Value |
|-----------|-------|
| USB supply input | 4.5V – 5.5V |
| Module socket VCC output | **3.3V** (onboard LDO regulator) |
| LDO max current | 300mA |
| Logic level | 3.3V |
| USB-to-UART IC | CH340G |

## Mode Switch

| Switch position | Behavior |
|-----------------|----------|
| UART | Normal boot — use for AT command debugging |
| PROG | Download mode — use for firmware flashing |

The switch drives the **IO9** pin on the socket (see pinout below). On the bundled XH-C2X (ESP8684H4/ESP32-C3) module, IO9 is the strapping pin for boot mode. **See compatibility note below for ESP8285.**

## 8-Pin Socket Pinout

| Pin | Name | Direction | Description |
|-----|------|-----------|-------------|
| 1 | RXD0 | I/O | GPIO19 / U0RXD — UART receive |
| 2 | IO9 | I/O | High: normal boot; Low: UART download mode |
| 3 | IO8 | I/O | GPIO8, internal pull-up |
| 4 | GND | PWR | Ground |
| 5 | VCC | PWR | 3.3V supply (LDO output, 300mA max) |
| 6 | RST | I/O | EN (chip enable) — do not leave floating |
| 7 | RST | I/O | EN (chip enable) — do not leave floating |
| 8 | TXD0 | I/O | GPIO20 / U0TXD — UART transmit |

## Compatibility with ESP8285 ESP-01M

**Two differences require attention when using this programmer with the ESP8285 ESP-01M IR transceiver module:**

### 1. Flash mode pin mismatch

This programmer drives **IO9** low to enter download mode. The ESP8285 ESP-01M uses **GPIO0 (IO0)** as its boot-mode strapping pin — IO9 on ESP8285 is connected to the internal SPI flash and must not be held low during boot.

The PROG switch will not automatically trigger download mode on the ESP8285. To flash manually:
1. Manually short **IO0 to GND** before power-on
2. Set the switch to UART (to avoid pulling IO9 low)
3. Flash firmware
4. Remove the IO0–GND short and power-cycle to run

### 2. Supply voltage

This programmer outputs **3.3V** on VCC. The ESP8285 ESP-01M specifies **5V** input to its onboard regulator. Supplying 3.3V directly may work if 3.3V lands on the ESP8285's VCC rail past the regulator, but is not guaranteed. If the module fails to boot or behaves erratically, use a 5V source instead (e.g., the FT232RL adapter referenced in `setup.md`).

## Bundled Module: XH-C2X (ESP8684H4)

The programmer ships with an ESP8684H4 module. This is **not** an ESP8285 — it is an ESP32-C3 based module. It is not used in this project, but its specs are noted for reference.

| Parameter | Value |
|-----------|-------|
| Chip | ESP8684H4 (ESP32-C3 family) |
| Flash | 4MB |
| Operating voltage | 3.0V – 3.6V |
| WiFi | 802.11b/g/n, 2.4GHz |
| Bluetooth | BLE 5.0, Bluetooth mesh |
| Package | 16mm × 24mm × 3mm |
| Boot mode pin | IO9 (matches this programmer's PROG switch) |
