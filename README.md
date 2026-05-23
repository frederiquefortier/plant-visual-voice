# 🌱 Visual Plant Communication

A soil moisture sensor that reads hydration levels and displays one of 4 hand-drawn status images on a color TFT screen — built with Arduino Uno, designed to support multiple plant types with their own moisture preferences and illustrations.

---

## How It Works

The capacitive soil moisture sensor outputs an analog signal that the Arduino reads and maps to a humidity percentage. That percentage is compared against the active plant's thresholds to pick one of four moisture states. The ILI9341 TFT screen then displays the matching illustration for that plant.

| State | Meaning |
|---|---|
| 💧 `OVERWATER` | Too much water |
| ✅ `PERFECT` | Happy plant |
| 🌤 `THIRSTY` | Needs a drink soon |
| 🔥 `DYING` | Critically dry |

Thresholds are not global — each plant carries its own. The project ships with three reusable presets (`ARID`, `TEMPERATE`, `HUMID`) that plant profiles can pick from, so a cactus and a fern can share the same enum but trigger states at very different humidity levels.

Every illustration is hand-drawn on iPad in Procreate. Each plant has its own folder with all four states, designed as a consistent visual system that scales as new plants are added.

---

## Project Structure

```
src/
├── main.ino              # entry point — reads sensor, drives display
├── moisture.h            # MoistureState enum + MoistureThreshold presets
├── plants/
│   ├── profile.h         # PlantProfile struct (name + thresholds + images)
│   ├── monstera/
│   │   ├── profile.h     # MONSTERA profile (TEMPERATE thresholds)
│   │   └── images.h      # RGB565 bitmaps for the 4 states
│   └── ...
└── assets/               # source PNGs (240×320) per plant, per state
    ├── monstera/
    └── ...
```

Adding a new plant = create a folder under `plants/`, define a `PlantProfile`, drop the 4 PNGs into `assets/<plant>/`, and convert them to `images.h`.

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

## Image Pipeline

PNGs in `src/assets/<plant>/` are converted to RGB565 `PROGMEM` arrays using [FileToCArray](https://notisrac.github.io/FileToCArray/) and pasted into the plant's `images.h`. The 16-bit color format and flash storage are non-negotiable on the Uno — a full 24-bit 240×320 image wouldn't fit in 32 KB of flash.

---

## What I'm Learning

This is a learning project — my first time working with:

- SPI communication between Arduino and a TFT display
- Analog sensor reading and value mapping (`analogRead`, `map`, `constrain`)
- Bitmap conversion to C++ arrays and storage in flash with `PROGMEM`
- C++ structs and `enum`s, applied from a TypeScript background
- Designing a scalable file structure for a hardware project
- Version controlling a hardware project with Git

See [`docs/00_briefing/plan.md`](docs/00_briefing/plan.md) for the full learning roadmap and [`docs/01_building/learnings.md`](docs/01_building/learnings.md) for notes taken along the way.

---

## Project Status

🚧 In progress — code architecture and illustrations for Monstera and Sunflower are in place. Currently on Module 0, waiting for hardware to arrive before wiring and the first real sensor readings.

---

## A Note on AI Assistance

This project was scoped and planned with the help of Claude (Anthropic). Claude helped me identify the right hardware, understand the learning path, and answer my questions along the way — but the learning, the wiring, and the code were mine to figure out. You can see my process under [docs](docs).
