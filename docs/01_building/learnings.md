# Learnings

Document new concepts, techniques, and knowledge gained. Reference this file to build on past learning and find resources for deeper understanding.

## Format

### YYYY-MM-DD - Learning Title

**What Was New:**
- Core concept or technique learned
- Context of when it came up

**Key Points:**
- Important details to remember
- How it works or why it matters

**Sources:**
- Documentation links
- Articles or tutorials referenced
- Code examples or repositories

**Where to Learn More:**
- Advanced resources
- Related topics to explore
- Practice exercises or projects

**Applied In:**
- Where/how this was used in practice (optional)

---

<!-- Add new entries below this line, newest first -->

### 2026-05-23 - C++ Structs, Nullability & File Includes in Arduino

**What Was New:**
- Translating TypeScript interfaces and optional properties to C++ structs
- Using nullptr for optional pointer values in structs
- Understanding include path behavior in Arduino IDE vs PlatformIO

**Key Points:**
- `struct` is the C++ equivalent of a TypeScript interface for grouped data
- All fields in a C++ struct are mandatory — no optional properties like TypeScript's `?`
- `nullptr` is the C++ equivalent of `null` — valid for pointer types like `uint16_t*`
- Always check `if (ptr != nullptr)` before using a nullable pointer — no compiler protection in C++, crashes are your responsibility
- Relative paths (`../`, `../../`) work in C++ includes but Arduino IDE is unreliable with deep relative paths
- PlatformIO handles relative paths correctly — one more reason to migrate eventually
- Safest structure with Arduino IDE: all `.h` files at root or one level deep maximum

**Recommended file structure:**
plant-visual-voice/
├── plant-visual-voice.ino
├── PlantProfile.h
├── states.h
├── display.h
└── plants/
    ├── monstera_images.h
    └── cactus_images.h

**Where to Learn More:**
- What is the difference between a pointer and a value type in C++?
- What happens at runtime when you dereference a nullptr?
- How does PlatformIO resolve include paths differently than the Arduino IDE?

**Applied In:**
- moisture.h — MoistureThreshold struct with nullable number
- plant-visual-voice project file structure

### 2026-05-17 - Project File Architecture for Multi-Plant Support

**What Was New:**
- Thinking about file structure as a scalability decision, not just an organization preference

**Key Points:**
- A folder-per-plant structure is the most extensible approach — each plant is self-contained
- Recommended structure:
  plants/
  ├── monstera/
  │   ├── profile.h    ← thresholds, name
  │   └── images.h     ← 4 bitmaps
  ├── cactus/
  │   ├── profile.h
  │   └── images.h
- A single `plants.h` works for a small number of plants but becomes hard to navigate quickly
- One file per plant at the root level is cleaner than one big file but less organized than folders
- Choosing the right structure early avoids painful refactoring later

**Where to Learn More:**
- How does `#include` handle files in subfolders in Arduino/C++?
- What is a forward declaration and when is it needed?

**Applied In:**
- plant-visual-voice project structure — organizing Monstera and future plant variants

### 2026-05-17 - Multi-File Structure in Arduino Projects

**What Was New:**
- Splitting an Arduino project across multiple files instead of one monolithic `.ino`

**Key Points:**
- Arduino supports multiple files via tabs in the IDE — each tab is a file in the same folder
- `.h` header files contain definitions (enums, structs, functions, bitmaps)
- Files are included in the main `.ino` with `#include "filename.h"`
- Recommended structure for this project:
    - `plant-visual-voice.ino` — `setup()` and `loop()` only
    - `states.h` — `enum State` and `getState()`
    - `display.h` — all screen-related logic
    - `images.h` — generated bitmap arrays

**Sources:**
- [Multiple files in Arduino — Arduino Docs](https://docs.arduino.cc/learn/programming/sketches/)

**Where to Learn More:**
- What is the difference between a `.h` and a `.cpp` file in C++?
- When should a function definition live in a `.h` vs a `.cpp`?
- What are include guards and why are they needed in header files?

**Applied In:**
- Project structure for plant-visual-voice — separating state logic, display logic, and bitmap assets

### 2026-05-17 - Arduino State Management & Plant Profile Architecture

**What Was New:**
- Using enums to represent discrete states instead of strings or magic numbers
- Understanding why JSON is not viable on Arduino and what replaces it

**Key Points:**
- `#define` is a compile-time constant — it cannot change at runtime; use variables for state
- `enum` is the right tool for a fixed set of named states — safer and more readable than strings or integers
- JSON parsing is too memory-intensive for Arduino; `struct` is the C++ equivalent for grouped data per plant profile
- Function parameters must be explicitly typed in C++ — `getState(percentage)` is invalid, `getState(int percentage)` is correct

**Sources:**
- [enum reference — Arduino/C++](https://www.arduino.cc/reference/en/language/variables/data-types/enum/)
- [struct reference — Arduino/C++](https://www.arduino.cc/reference/en/language/variables/compound-types/struct/)

**Where to Learn More:**
- How does `enum` compare to `const int` in C++?
- When should you use a `struct` vs a class in C++?
- What is a lookup table and when is it better than if/else chains?

**Applied In:**
- Module 2 — refactoring threshold logic and state management in the soil moisture sketch

### 2026-05-17 - First Arduino Sketch — Soil Moisture Sensor

**What Was New:**
- Writing a first real Arduino sketch to read a capacitive soil moisture sensor
- Understanding the difference between analog and digital pins
- Using the Serial Monitor as a debugging tool

**Key Points:**
- `#define` creates an alias — the value must be a valid pin identifier like `A0`, not `5V`
- Analog pins (A0–A5) read a variable voltage (0–5V); digital pins only read 0 or 1
- The Arduino ADC is 10-bit: 2¹⁰ = 1024 possible values, so the max raw value is **1023**
- Multiple components can share the 5V pin — what matters is total current draw (~500mA max via USB)
- `map()` should stay within range in theory, but physical sensors can exceed 0 or 1023 in real conditions — `constrain()` is defensive best practice
- `Serial.print()` stays on the same line; `Serial.println()` adds a line break — mix them to format output correctly

**Sources:**
- [analogRead() reference](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)
- [Serial.print() reference](https://www.arduino.cc/reference/en/language/functions/communication/serial/print/)
- [map() reference](https://www.arduino.cc/reference/en/language/functions/math/map/)
- [constrain() reference](https://www.arduino.cc/reference/en/language/functions/math/constrain/)

**Where to Learn More:**
- What is an ADC (analog-to-digital converter) and how does it work?
- What happens if total current draw exceeds the Arduino's limit?
- Explore `Serial.print()` vs `Serial.println()` formatting patterns

**Applied In:**
- Module 2 — first sketch reading soil moisture sensor on A0 and printing to Serial Monitor

### 2026-05-15 - Building a Plant Humidity Sensor with Arduino

**What Was New:**
- Creating a soil moisture sensor connected to a color TFT display
- Using an Arduino Uno as the central microcontroller with no soldering required
- Displaying different images based on the humidity level

**Key Points:**
- An OLED SSD1306 screen is monochrome (black and white) — not suitable for colored drawings
- The TFT ILI9341 2.4" SPI display supports 65,000 colors and is fully compatible with Arduino Uno
- A capacitive soil moisture sensor (e.g. Stemedu v1.2) is preferable to resistive — it doesn't oxidize
- Everything connects without soldering via a breadboard and Dupont cables
- The ILI9341 connects over SPI: CS→10, RESET→9, DC→8, MOSI→11, SCK→13, LED→3.3V
- `analogRead(A0)` reads the raw sensor value (0–1023)
- `map()` converts that raw value into a percentage (0–100)

**Sources:**
- [Adafruit ILI9341 documentation](https://learn.adafruit.com/adafruit-2-4-tft-lcd-touchscreen/overview)
- [Adafruit GFX Library — drawing functions](https://learn.adafruit.com/adafruit-gfx-graphics-library/overview)
- [analogRead() reference — Arduino](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)
- [map() reference — Arduino](https://www.arduino.cc/reference/en/language/functions/math/map/)
- [image2cpp — image to C++ array converter](https://javl.github.io/image2cpp/)

**Where to Learn More:**
- [Official Arduino tutorials](https://docs.arduino.cc/built-in-examples/basics/Blink/) — start with Blink
- [Full Arduino reference](https://www.arduino.cc/reference/en/)
- [Arduino forum](https://forum.arduino.cc)
- [r/arduino](https://www.reddit.com/r/arduino/)
- Understand the SPI protocol and why it is used for displays
- Understand the RGB565 bitmap format (16-bit) vs standard RGB (24-bit)

**Applied In:**
- Plant sensor project — hardware purchased on Amazon.ca (~$87.91 CAD)
    - ELEGOO Uno R3 — $21.99
    - TFT ILI9341 2.4" SPI display — $24.96
    - Stemedu capacitive sensor (x5) — $14.98
    - ELEGOO 830-point breadboard (x3) — $12.99
    - USB A-B cable (x2) — $12.99

---

### 2026-05-15 - Image Formats for Arduino TFT Displays

**What Was New:**
- GIFs are not natively supported on Arduino — not enough RAM to decode animations
- Images must be converted into C++ arrays (`uint16_t`) before use
- The source image format affects the quality of the conversion

**Key Points:**
- **PNG** is the ideal source format: lossless, supports transparency, clean edges
- **BMP** is also acceptable: no compression, pixel-perfect color accuracy
- **JPG** should be avoided: its compression introduces color artifacts around edges
- **GIF** is limited to 256 colors — color loss happens before even converting
- The **image2cpp** tool converts any image into a C++ array for Arduino
- Once converted, the original format no longer exists — only the pixel array matters
- For this project: 4 PNG images representing *overwatered*, *perfect*, *a little thirsty*, *very thirsty*

**Sources:**
- [image2cpp — image to C++ array converter](https://javl.github.io/image2cpp/)
- [Adafruit GFX — loading images](https://learn.adafruit.com/adafruit-gfx-graphics-library/loading-images)

**Where to Learn More:**
- Understand the RGB565 format (16-bit) and why Arduino uses it
- Explore `drawBitmap()` vs `drawRGBBitmap()` in the Adafruit GFX docs
- Practice with a small image (e.g. 50x50px) before creating all 4 project images

---

### 2026-05-15 - Git & GitHub for Arduino Projects

**What Was New:**
- An Arduino project (.ino) can be version-controlled on GitHub like any other code
- Best practice is to commit early, before the code gets complex

**Key Points:**
- An Arduino project = a `main.ino` file + ideally a `README.md`
- Consider a `.gitignore` to exclude temporary files generated by the Arduino IDE
- Document the hardware and project goal in `README.md` from the very start
- The Arduino community shares a huge number of projects on GitHub — great source of inspiration

**Sources:**
- [Git in 15 minutes](https://rogerdudler.github.io/git-guide/)
- [Creating a GitHub repo](https://docs.github.com/en/get-started/quickstart/create-a-repo)

**Where to Learn More:**
- Best practices for writing commit messages
- How to structure a hardware project repo (code + schematics + photos)
