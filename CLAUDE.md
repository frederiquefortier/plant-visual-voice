# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## What this is

An Arduino Uno (ATmega328P) sketch that reads a capacitive soil moisture sensor, maps it to a humidity percentage, picks one of four `MoistureState`s against the active plant's thresholds, and draws the matching hand-drawn illustration on an ILI9341 SPI TFT (240×320, RGB565). It is designed to scale to many plant types, each with its own thresholds and four illustrations.

## This is a learning project — guide, don't write the code

The owner is learning C++ and embedded development from a TypeScript background. The standing contract (see `docs/01_building/sessions.md`) is **"learn, don't receive code."** Act as a professor: explain concepts, ask guiding questions, point to references, and review code the owner wrote — do **not** hand over finished implementations unless explicitly asked. The owner often brings questions as inline `//` comments in the code; answer those in place. When you spot an AI mistake or correct one, it belongs in the journal (below).

## Writing tone (README, docs, journal, commit messages)

Write all prose in a plain, human engineering voice. Avoid the AI tells the owner has repeatedly flagged:

- No "X — Y" em-dash tic ending sentences and bullets. Use "so", "because", "and", or a period.
- Cut filler intensifiers ("genuinely", "simply", "seamlessly", "robust", "powerful") and "not just X but Y" parallelism.
- Don't stack buzzwords ("data-driven", "scalable", "modular", "source of truth") — once each is plenty.
- State facts plainly; if something is unfinished or untested, say so.
- Prefer consequence over description ("As a result…", "This means…").

The `update-readme` skill holds the fuller version of these rules and the portfolio README structure. Apply this tone to anything new; don't rewrite dated journal entries just to retune them.

## Build & run

There is **no CLI build** — this compiles and uploads through the **Arduino IDE v2** (Sketch → Verify/Upload). `src/main.ino` is the sketch entry point; `.h` files are picked up as sibling tabs / includes.

- Required libraries (Tools → Manage Libraries): **Adafruit ILI9341**, **Adafruit GFX Library**.
- Wiring (TFT over SPI): CS→10, RESET→9, DC→8, MOSI→11, SCK→13, LED→3.3V. Sensor AOUT→A0.
- Debugging is via the **Serial Monitor at 9600 baud** — the primary feedback tool until/while hardware behavior is verified.
- No automated tests; verification is manual (Serial output, on-screen render). Wokwi is used to simulate before hardware is present.

## Architecture

Data-driven and split across shallow headers so the Arduino IDE resolves includes reliably (deep relative paths are unreliable in the IDE — keep headers at most one or two levels deep).

- `src/moisture.h` — `enum MoistureState` (DYING/THIRSTY/PERFECT/OVERWATER), the `MoistureThreshold` struct, three reusable threshold presets (`ARID`, `TEMPERATE`, `HUMID`), and `getMoistureState(int percentage)`. Thresholds are **per-plant, never global** — the enum is shared but a cactus and a fern fire states at different percentages.
- `src/plants/profile.h` — `PlantProfile` struct: `name`, a `MoistureThreshold`, and four `const uint16_t*` image pointers (one per state).
- `src/plants/<plant>/profile.h` — one `const PlantProfile` per plant (e.g. `MONSTERA`, `SUNFLOWER`), picking a threshold preset and wiring its four images.
- `src/plants/<plant>/images.h` — the four RGB565 `PROGMEM` bitmaps for that plant.
- `src/assets/<plant>/{dying,thirsty,perfect,overwater}.png` — source 240×320 PNGs (the single source of truth for the art).

**Adding a plant:** create `plants/<plant>/`, define a `PlantProfile`, drop the four PNGs in `assets/<plant>/`, convert them to `images.h`.

## Hard constraints & conventions

- **Flash budget is the dominant constraint.** A full 240×320 RGB565 image is ~150 KB; the Uno has 32 KB flash. Full-screen color art for all four states will not fit — expect downscaling, palette indexing, or a board upgrade (ESP32) before the image pipeline is complete. Surface this before any image work.
- **Image pipeline:** PNG → RGB565 `PROGMEM` array via [FileToCArray](https://notisrac.github.io/FileToCArray/) (output preset: *Arduino code (Adafruit GFX, TFT_eSPI)*, *16bit RGB (565)*, PROGMEM on). This was a deliberate choice over image2cpp — see ADR-001 in `docs/01_building/decisions.md`. Do not reintroduce image2cpp for color art.
- Image pointers in a `PlantProfile` may be `nullptr` (states not yet illustrated). C++ gives no null protection — guard `if (img != nullptr)` before drawing.
- `map(raw, 0, 1023, 0, 100)` then `constrain(..., 0, 100)`: 1023 is the 10-bit ADC max; `constrain` is defensive against real sensors over/undershooting.

## Known in-progress gaps (don't mistake for finished code)

- `getMoistureState()` in `moisture.h` still compares against `OVERWATER_/PERFECT_/THIRSTY_MOISTURE_THRESHOLD` — **constants that are defined nowhere**. The refactor to read from a `PlantProfile`'s `MoistureThreshold` struct is not finished; this won't compile as-is.
- `main.ino` only reads the sensor and prints to Serial. It does **not** include any plant profile or the TFT libraries yet, and `// do the display stuff` is an unwritten TODO. The previous-state tracking to avoid redraw flicker is stubbed.

## Development journal (keep it current)

This repo maintains a structured journal under `docs/` (set up via the `dev-journal` skill). Append to the relevant file after meaningful work — newest entries first, below the `<!-- Add new entries below this line -->` marker, using each file's documented format:

- `docs/01_building/decisions.md` — architectural decisions (ADR format); check it before proposing changes that might conflict.
- `docs/02_fixing/bugs.md` — bugs with root cause + prevention.
- `docs/01_building/learnings.md` — concepts learned (this is a teaching log; bias toward explanation and sources).
- `docs/01_building/sessions.md` — AI-session retrospectives.
- `docs/03_planning/improvements.md` — future feature ideas.
- `docs/00_briefing/plan.md` — the 6-module learning roadmap the project follows.

Convert relative dates to absolute when logging. Current focus: Module 0 (pre-hardware) — architecture and Monstera/Sunflower illustrations are in place; awaiting hardware for first real readings.
