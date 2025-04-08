# Contrlz Hardware

Welcome to the **Contrlz Hardware** repository! This project includes various hardware modules designed to enable smart control and automation of electrical devices using microcontrollers. From relay-based control to IR remote interfaces and custom LED displays, this repo hosts all the essential hardware designs and wiring guides.

## 📂 Table of Contents

- [Overview](#overview)
- [Modules & Wiring Schemes](#modules--wiring-schemes)
  - [Bulb Relay Module](#bulb-relay-module)
  - [IR Bulb Relay Module](#ir-bulb-relay-module)
  - [7-Segment Display Using LEDs](#7-segment-display-using-leds)
- [Setup Instructions](#setup-instructions)
- [Contributing](#contributing)
- [License](#license)

---

## 🧩 Overview

The Contrlz Hardware project contains modular hardware setups compatible with platforms like Arduino or ESP8266. Each module in this repo is purpose-built for home or DIY automation projects and includes schematics, wiring instructions, and integration examples.

---

## ⚡ Modules & Wiring Schemes

### 🔌 Bulb Relay Module

Control a 220V/110V light bulb using a relay and microcontroller.

#### Components:
- Relay Module (5V or 3.3V)
- Light Bulb
- Microcontroller (ESP8266/Arduino)
- Power Supply

#### Wiring:
- **Relay Module**
  - `VCC` → Microcontroller 5V/3.3V
  - `GND` → Microcontroller GND
  - `IN` → Digital Pin (e.g., D1)

- **AC Bulb Wiring**
  - Live wire → Relay **Common (COM)**
  - Relay **Normally Open (NO)** → Bulb live input
  - Bulb neutral → AC Neutral

> ⚠️ **Caution:** Use proper insulation and a relay rated for your AC voltage.

---

### 📡 IR Bulb Relay Module

Same as the basic relay module, but adds IR remote control.

#### Components:
- Relay Module
- IR Receiver (e.g., TSOP1838)
- Microcontroller
- Light Bulb
- Power Supply

#### Wiring:
- **IR Receiver**
  - `VCC` → 3.3V/5V
  - `GND` → GND
  - `OUT` → Digital Pin (e.g., D2)

- **Relay Module**
  - Same as above

- **AC Wiring**
  - Same as Bulb Relay Module

#### Logic:
- Microcontroller reads IR signals and maps them to specific relay actions (e.g., toggle bulb ON/OFF).

---

### 🔢 7-Segment Display Using LEDs

Create a custom 7-segment style numeric display using individual LEDs.

#### Components:
- 7 LEDs (Red or White)
- 7 Resistors (220Ω)
- Microcontroller
- Breadboard or Custom PCB

#### Wiring:
- Each LED:
  - Anode → Resistor → Microcontroller Digital Pin (D3 to D9)
  - Cathode → GND

#### Segment Mapping Example:

| Segment | Micro Pin |
|---------|-----------|
| A       | D3        |
| B       | D4        |
| C       | D5        |
| D       | D6        |
| E       | D7        |
| F       | D8        |
| G       | D9        |

Program logic handles lighting combinations to show digits 0–9.

---

## 🛠️ Setup Instructions

1. **Clone the Repo**

```bash
git clone https://github.com/DG-Devil/contrlz-hardware.git
cd contrlz-hardware
