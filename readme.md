# STC8G ADC with Potentiometer & SSD1306 Display

## 📌 Project Overview
This project demonstrates the ADC (Analog-to-Digital Converter) functionality of the STC8G series microcontroller (like STC8G1K17 - STC8G1K08)  using a 10K potentiometer and SSD1306 OLED display. The analog voltage from the potentiometer is converted to digital values and displayed in numerical form on the OLED screen.

## 🎯 Features
- Read analog voltage from 10K potentiometer via ADC
- Display raw ADC value (0-1023)
- Compatible with STC8G1K17 (8051 core)
- Uses I²C communication for SSD1306 OLED

## 🛠 Hardware Requirements
| Component | Specification |
|-----------|--------------|
| MCU | STC8G1K17 (8051 architecture) |
| Display | SSD1306 OLED (128x64, I²C) |
| Potentiometer | 10K linear |
| Power Supply | 3.3V or 5V |

## 🔌 Circuit Connections

### STC8G1K17 ↔ SSD1306 OLED

| STC8G1K17   | SSD1306 |
| :---------- | :------ |
|  P3.3 (SDA) |  SDA    |
|  P3.2 (SCL) |  SCL    |
|  VCC        |  VCC    |
|  GND        |  GND    |


### STC8G1K17 ↔ Potentiometer

| STC8G1K17 | 10K Potentiometer |
| :------- | :----------------- |
|  VCC     |  Pin-1             |
|  P1.0    |  Pin-2 (middle pin)|
|  GND     |  Pin-3             |


## 📋 8051 Architecture Notes for STC8G
The STC8G series is based on enhanced 8051 architecture with:
- Single-cycle 8051 core (faster than traditional 8051)
- Integrated 12-bit ADC (up to 12-bit resolution)
- Multiple power modes
- Enhanced peripherals while maintaining 8051 instruction set compatibility

### ADC Features in STC8G:
- 10-bit resolution
- Multiple channel support
- Internal reference voltage option
- High conversion speed

## 🚀 Getting Started

### 1. Prerequisites
- [Compiler: SDCC](https://sdcc.sourceforge.net/) (Small Device C Compiler) for 8051
- [IDE: Code::Blocks](https://www.codeblocks.org)
- [ISP: STC-ISP](https://www.stcmicro.com/rjxz.html)

Note: This project is specifically designed for 8051-architecture STC8G microcontrollers. The code may need adjustments for other 8051 variants or different architectures.

<img width="1920" height="1080" alt="vlcsnap-2026-01-03-03h11m32s297" src="https://github.com/user-attachments/assets/3dfae00b-ddde-46b0-98ff-cfc631078c77" />

Video: https://www.youtube.com/watch?v=wYS1EDPwsuQ


