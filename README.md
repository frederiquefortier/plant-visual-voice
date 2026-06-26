# 🌱 Visual Plant Communication

An Arduino Uno reads a capacitive soil moisture sensor and displays hand-drawn illustrations on a color TFT screen to communicate plant health at a glance. It's designed around data-driven plant profiles, allowing each species to define its own moisture thresholds and artwork.

The goal wasn't to display data. It was to communicate plant health visually, so the device feels more like a tiny Tamagotchi than a measuring instrument.

<!-- TODO:
![Demo](docs/media/demo.gif)
![Prototype](docs/media/prototype.jpg)
-->

---

## Highlights

- 🧩 Data-driven plant profiles with per-plant moisture thresholds
- 🎨 RGB565 + `PROGMEM` image pipeline under a 32 KB flash budget
- 🏗️ Modular, multi-file C++ architecture designed to scale
- 📺 SPI-driven ILI9341 TFT (240×320, 65K colors)
- 🌱 Arduino Uno (ATmega328P), no soldering

---

## Overview

The Arduino reads the sensor, maps the value to a humidity percentage, compares it against the active plant's thresholds, and picks one of four moisture states. The ILI9341 TFT then renders the matching illustration for that plant.

| State | Meaning |
|---|---|
| 💧 `OVERWATER` | Too much water |
| ✅ `PERFECT` | Happy plant |
| 🌤 `THIRSTY` | Needs a drink soon |
| 🔥 `DYING` | Critically dry |

Every illustration is hand-drawn on iPad in Procreate. Each plant gets its own folder holding all four states, drawn as a consistent visual system so the device stays coherent as new plants are added.

This project marks my transition from web development into embedded systems. The `docs/` journal tracks the concepts, decisions, and trade-offs along the way.

---

## Problem

A moisture number on a screen doesn't tell you much unless you already know what's good for that specific plant. A cactus at 30% humidity is fine; a fern at 30% is in trouble. So a generic sensor falls short in two ways:

- The same percentage means "perfect" for one plant and "dying" for another, so thresholds can't be universal.
- A raw number takes interpretation. A picture doesn't.

The aim is a device that shows plant health visually and per-plant, instead of just reporting volts or percent.

---

## Goals

- Read a capacitive soil moisture sensor and convert it to a normalized humidity percentage.
- Map that humidity to four visual moisture states using per-plant thresholds.
- Render plant-specific illustrations on the ILI9341 TFT.
- Keep the architecture data-driven and extensible across plant types.
- Learn embedded C++ fundamentals along the way.

---

## Architecture

The project uses a data-driven architecture with one `PlantProfile` per plant. Header files stay intentionally shallow, because the Arduino IDE struggles with deep relative includes.

A reading flows through the system in one direction:

```
Sensor
   │  analogRead()
   ▼
Humidity %
   │  active PlantProfile thresholds
   ▼
MoistureState
   │  matching RGB565 image
   ▼
ILI9341 TFT
```

The files that implement that flow:

```
src/
├── main.ino              # entry point — reads sensor, drives display
├── moisture.h            # MoistureState enum, MoistureThreshold struct,
│                         #   ARID/TEMPERATE/HUMID presets, getMoistureState()
├── plants/
│   ├── profile.h         # PlantProfile struct (name + thresholds + 4 images)
│   ├── monstera/
│   │   ├── profile.h     # MONSTERA profile (TEMPERATE thresholds)
│   │   └── images.h      # RGB565 PROGMEM bitmaps for the 4 states
│   └── sunflower/
│       ├── profile.h     # SUNFLOWER profile
│       └── images.h
└── assets/               # source PNGs (240×320), the single source of truth for the art
    ├── monstera/
    └── sunflower/
```

The `MoistureState` enum is shared across plants, but thresholds live per plant inside a `PlantProfile`. Three reusable presets (`ARID`, `TEMPERATE`, `HUMID`) let a cactus and a fern use the same states while firing them at different humidity levels. Image pointers in a profile can be `nullptr` for states that aren't illustrated yet, so drawing code has to guard with `if (img != nullptr)`.

To add a plant: create a folder under `plants/`, define a `PlantProfile`, drop the four PNGs into `assets/<plant>/`, and convert them to `images.h`. As a result, adding a new plant touches only data and art. The rendering and state logic stay untouched.

### Hardware

| Component | Type |
|---|---|
| Microcontroller | ATmega328P-based Uno (Arduino-compatible) |
| Display | 2.4" ILI9341 SPI TFT — 240×320, 65K colors |
| Sensor | Capacitive soil moisture sensor |
| Cables | Dupont jumper wires |

Specific brands aren't pinned because they're interchangeable. Any ATmega328P Uno and any ILI9341 SPI panel will work.

**Wiring (TFT over SPI):** VCC→5V, GND→GND, CS→10, RESET→9, DC→8, MOSI→11, SCK→13, LED→3.3V.
**Sensor:** VCC→5V, GND→GND, AOUT→A0.

### Build & libraries

There's no CLI build. The sketch compiles and uploads through the Arduino IDE v2 (Sketch → Verify/Upload). Install these via Tools → Manage Libraries:

- [Adafruit ILI9341](https://github.com/adafruit/Adafruit_ILI9341)
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)

Debugging happens over the Serial Monitor at 9600 baud, which is the main feedback tool until the hardware behaves predictably. There are no automated tests; verification is manual (Serial output and on-screen render), with [Wokwi](https://wokwi.com) standing in to simulate before the hardware is on the desk.

### Image pipeline

PNGs in `assets/<plant>/` get converted to RGB565 `PROGMEM` arrays with [FileToCArray](https://notisrac.github.io/FileToCArray/) (preset: *Arduino code (Adafruit GFX, TFT_eSPI)*, *16bit RGB (565)*, PROGMEM on), then pasted into the plant's `images.h`. The PNGs stay the source of truth.

---

## Challenges

- **Flash budget.** A full 240×320 RGB565 image is around 150 KB, and the Uno has 32 KB of flash. Full-screen color art for all four states won't fit, so the build will need downscaling, palette indexing, or a board with more flash (an ESP32) before the image pipeline is done.
- **16-bit color.** Images have to live in RGB565 and in `PROGMEM` (flash, not RAM) to stand any chance of fitting. Standard 24-bit RGB is off the table.
- **Noisy analog readings.** Real sensors can run past the theoretical 0–1023 ADC range, so `map()` is paired with `constrain(..., 0, 100)`. Readings also jitter near threshold boundaries, which is why the sketch tracks the previous state and only redraws on a change.
- **No null safety in C++.** Dereferencing a `nullptr` image pointer crashes at runtime with no compiler warning, so every draw needs an explicit guard.
- **Arduino IDE includes.** Deep relative paths (`../../`) aren't reliable in the IDE, which is what keeps the headers shallow.

These constraints shaped nearly every architectural decision in the project.

---

## Key Decisions

- **FileToCArray over image2cpp for color art** ([ADR-001](docs/01_building/decisions.md)). image2cpp is built for monochrome; FileToCArray produces true RGB565 output that drops straight into `tft.drawRGBBitmap()` with the right type and `PROGMEM` qualifier.
- **Embed images in `PROGMEM` rather than on an SD card.** This keeps the parts list and wiring minimal, at the cost of flash pressure.
- **Per-plant thresholds via a `PlantProfile` struct**, with shared `ARID`/`TEMPERATE`/`HUMID` presets, instead of one global threshold set. This is what makes the device work across different plants.
- **`enum` for states, `struct` for grouped data.** JSON parsing is too memory-hungry for the Uno, and enums and structs are the idiomatic, frugal C++ equivalents.
- **Folder-per-plant layout** over one monolithic file, so each plant is self-contained and the structure grows without painful refactors.

---

## Future Work

Tracked in [`docs/03_planning/improvements.md`](docs/03_planning/improvements.md):

- Finish the core loop (`getMoistureState()` reads from the active `PlantProfile`, `main.ino` drives the TFT, redraw only on state change) and take the first real hardware readings to calibrate dry and wet values per sensor.
- Switch the active plant at runtime with a button or menu, and persist the choice to EEPROM.
- Add more sensors: ambient temperature and humidity (DHT22) and sunlight level (BH1750 or LDR), reusing the same four-state visual system.
- Animate the status art, either with basic GFX drawing on the Uno or full animated frames after moving to an ESP32 (which also eases the flash constraint).
- Automate image conversion at build time once the project is on PlatformIO, keeping the PNGs as the only committed asset.

---

## Lessons Learned

From the journal ([`docs/01_building/learnings.md`](docs/01_building/learnings.md)):

- A C++ struct is close to a TypeScript interface, but every field is mandatory; there's no optional `?`. `nullptr` stands in for `null` on pointer types, and you check it yourself.
- Source format matters before conversion. PNG is lossless with clean edges; JPG artifacts and GIF's 256-color limit degrade the art before it ever becomes an array.
- A monochrome OLED was the wrong screen for color illustrations. The ILI9341 TFT (65K colors over SPI) was the right call.
- Hardware assembly surfaced practical concerns that rarely show up in software work, such as connector compatibility, cable management, and part selection.
- File structure is a scalability decision, not just tidiness. Choosing folder-per-plant early saved a later rewrite.

See [`docs/00_briefing/plan.md`](docs/00_briefing/plan.md) for the full six-module learning roadmap.
