# 🌱 Visual Plant Communication

A soil moisture sensor that reads hydration levels and displays one of 4 status images on a color TFT screen — built with Arduino Uno.

![Project photo](docs/04_results/demo.gif)
> My Monstera is no longer at risk of dying!

---

## How It Works

The capacitive soil moisture sensor outputs an analog signal that the Arduino reads and converts into a humidity percentage. Based on four thresholds, the ILI9341 TFT screen displays a different image representing the plant's current state.

| State | Humidity |
|---|---|
| 💧 Overwatered | > 80% |
| ✅ Perfect | 50–80% |
| 🌤 A little thirsty | 20–50% |
| 🔥 Very thirsty | < 20% |

Every status image was hand-drawn on iPad using Procreate. The 4 states are designed as a reusable visual system. I've already illustrated two plant variants as of today, May 15, 2026.

---

## Hardware

| Component | Model |
|---|---|
| Microcontroller | ELEGOO Uno R3 (ATmega328P) |
| Display | TFT LCD 2.4" ILI9341 SPI — 240×320, 65K colors |
| Sensor | Stemedu Capacitive Soil Moisture Sensor v1.2 |
| Breadboard | ELEGOO 830-point breadboard |
| Cables | Dupont male-female jumper wires |

**No soldering required.** Everything connects via breadboard and Dupont cables.

### Wiring

| TFT Pin | Arduino Pin |
|---|---|
| VCC | 5V |
| GND | GND |
| CS | 10 |
| RESET | 9 |
| DC | 8 |
| MOSI | 11 |
| SCK | 13 |
| LED | 3.3V |

Sensor: VCC → 5V, GND → GND, AOUT → A0

---

## Libraries

- [Adafruit ILI9341](https://github.com/adafruit/Adafruit_ILI9341)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)

Install via **Arduino IDE → Tools → Manage Libraries**.

---

## What I Learned

This is a learning project — my first time working with:

- SPI communication between Arduino and a TFT display
- Analog sensor reading and value mapping (`analogRead`, `map`, `constrain`)
- Bitmap image conversion to C++ arrays using [image2cpp](https://javl.github.io/image2cpp/)
- Storing image data in flash memory with `PROGMEM`
- Conditional display logic to avoid unnecessary screen redraws
- Version controlling a hardware project with Git

See [`plan.md`](docs/00_briefing/plan.md) for the full learning roadmap and [`learnings.md`](docs/01_building/learnings.md) for notes taken along the way.

---

## Project Status

🚧 In progress — currently on Module 0 (waiting for all the components to arrive :)).

--- 

## A Note on AI Assistance

This project was scoped and planned with the help of Claude (Anthropic). Claude helped me identify the right hardware, understand the learning path, and answer my questions along the way — but the learning, the wiring, and the code were mine to figure out.

I wouldn't have known where to begin without it. That felt worth being transparent about.
