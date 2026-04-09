# USB-C Female Breakout Board (Power)

Product: USB-C Female Connector DIP Breakout Board

> **Use a USB-A charger with a USB-A to USB-C cable.** USB-C to USB-C cables require 5.1 kΩ pull-down resistors on the CC pins to negotiate power — this breakout does not include them, so a C-to-C cable will not supply power.

## Overview

Small breakout PCB exposing a USB-C female connector as four through-hole pins. Used in this project for **5V power input only** — D− and D+ pins are left unconnected.

## Pinout

| Pin | Label | Description |
|-----|-------|-------------|
| 1 | V | VBUS — 5V power from USB source |
| 2 | D− | USB data minus — not connected in this project |
| 3 | D+ | USB data plus — not connected in this project |
| 4 | G | Ground |

## Wiring for This Project

Connect only V and G to the ESP8285 ESP-01M module:

| Breakout | ESP8285 ESP-01M |
|----------|-----------------|
| V (VBUS) | 5V |
| G (GND) | GND |

## USB-C Power Delivery Note

USB-C sources fall into two categories, and behavior differs:

**USB-A to USB-C cable (recommended for simplicity)**
The source is a legacy USB-A port or charger. 5V is provided unconditionally — no negotiation required. This is the simplest option.

**USB-C to USB-C cable**
A USB-C source will not supply power without detecting a downstream device via the CC (Configuration Channel) pins. This breakout does not expose CC pins. To make a USB-C charger supply 5V over a C-to-C cable, add **5.1 kΩ pull-down resistors** from CC1 to GND and CC2 to GND on the breakout board's CC pads (if exposed) or directly at the connector. Without these resistors the source will either supply no power or supply an unpredictable voltage.

For this project, a USB-A charger or USB-A-to-C cable avoids the CC resistor requirement entirely.

## Power Budget

The ESP8285 ESP-01M draws up to ~300mA peak during WiFi transmission. Any USB charger rated 500mA or above is sufficient for a single module.
