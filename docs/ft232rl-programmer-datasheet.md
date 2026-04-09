# DSD TECH SH-U09G USB-to-Serial Adapter (FT232RL)

Product: [DSD TECH SH-U09G USB to TTL Serial Adapter (FT232RL)](https://www.amazon.com/dp/B083HVM7VZ)

## Overview

USB-to-UART adapter using the FTDI FT232RL IC. Used to flash firmware onto the ESP8285 ESP-01M IR transceiver modules via jumper wires. Requires manual IO0→GND wiring to enter download mode (no auto-PROG switch).

## Electrical Specs

| Parameter | Value |
|-----------|-------|
| USB-to-UART IC | FT232RL |
| Output voltage | **3.3V or 5V** — selectable via onboard jumper |
| Logic level | matches selected voltage |

> **Set the voltage jumper to 5V** before connecting to the ESP8285 ESP-01M. The module has an onboard 5V-to-3.3V regulator and requires 5V input. Supplying 3.3V will undervolt the ESP8285 through the regulator's dropout.

## Pins Used for ESP8285 Programming

| FT232RL pin | Direction | ESP8285 ESP-01M pin |
|-------------|-----------|---------------------|
| 5V | → | 5V (VCC) |
| GND | → | GND |
| TXD | → | RXD (IO19) |
| RXD | ← | TXD (IO20) |
| GND | → | IO0 *(flash mode only — see below)* |

## Wiring Diagram

```
FT232RL adapter          ESP8285 ESP-01M
┌─────────────┐          ┌──────────────┐
│          5V ├──────────┤ 5V           │
│         GND ├────┬─────┤ GND          │
│         TXD ├────┼────►│ RXD (IO19)   │
│         RXD │◄───┼─────┤ TXD (IO20)   │
└─────────────┘    │     │              │
                   └─────┤ IO0 (GPIO0)  │  ← flash mode only;
                         └──────────────┘    remove after flashing
```

## Flash Mode Procedure

1. Connect IO0 to GND (add the jumper shown above)
2. Power-cycle the module (disconnect and reconnect USB)
3. Flash firmware: `./bin/flash <media-node|server-node> [port]`
4. Remove the IO0–GND jumper
5. Power-cycle again — module boots normally

## Finding the Serial Port

```bash
pio device list
```

Typical ports:
- Linux: `/dev/ttyUSB0`
- macOS: `/dev/cu.usbserial-XXXXXX`
