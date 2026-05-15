# Improvements

Track future enhancements and feature ideas. Review this file during planning sessions to prioritize next steps.

## Format

### YYYY-MM-DD - Improvement Title

**Description:**
- What the improvement would do
- Problem it would solve or value it would add

**Motivation:**
- Why this would be beneficial
- Use cases or scenarios

**Potential Approach:**
- Initial thoughts on implementation
- Technologies or patterns to consider

**Priority:**
- [ ] High - Critical improvement
- [ ] Medium - Nice to have
- [ ] Low - Future consideration

**Dependencies:**
- Prerequisites or related work needed
- Blockers or considerations

**Status:**
- [ ] Proposed
- [ ] In Progress
- [ ] Completed
- [ ] Deferred

---

<!-- Add new entries below this line, newest first -->

### 2026-05-15 - Per-Plant Humidity Thresholds

**Description:**
- Define custom humidity thresholds for each plant type instead of using a single global set
- Example: a cactus needs much less water than a fern — the "perfect" range should reflect that

**Motivation:**
- A single set of thresholds makes the sensor inaccurate for plants with very different needs
- Makes the project genuinely useful across multiple plant types, not just one
- Natural extension once the multi-plant illustration system is in place
  
**Potential Approach:**
- Define a `struct` per plant type containing its name and 4 threshold values
- Store plant profiles in an array and select the active one at startup (or via a button)
- Thresholds could eventually be stored in EEPROM so they persist after power-off
  
**Priority:**
- [ ] High - Critical improvement
- [x] Medium - Nice to have
- [ ] Low - Future consideration
  
**Dependencies:**
- Base project (Modules 1–6) completed
- Multi-plant illustration system already designed
- Would pair well with a physical button or menu to switch between plant profiles
  
**Status:**
- [x] Proposed
- [ ] In Progress
- [ ] Completed
- [ ] Deferred

---

### 2026-05-15 - Ambient Temperature & Humidity Sensor

**Description:**
- Add a DHT22 sensor to read ambient air temperature and humidity
- Extend the visual system with a ambient air status indicator on screen

**Motivation:**
- Plants are highly sensitive to temperature and air humidity, not just soil moisture
- Would make the device a more complete plant health monitor
- DHT22 reads both values simultaneously with a single sensor

**Potential Approach:**
- Wire DHT22 to a digital pin
- Use the `DHT sensor library` by Adafruit
- Add a secondary screen state or overlay showing temperature and air humidity

**Priority:**
- [ ] High - Critical improvement
- [x] Medium - Nice to have
- [ ] Low - Future consideration

**Dependencies:**
- Modules 1–6 of the current learning plan completed
- Would need to reconsider screen layout to fit additional data
- DHT22 module (~$5–8 CAD on Amazon)

**Status:**
- [x] Proposed
- [ ] In Progress
- [ ] Completed
- [ ] Deferred

---

### 2026-05-15 - Sunlight Level Sensor

**Description:**
- Add a light intensity sensor (e.g. BH1750 or LDR) to monitor how much sunlight the plant receives
- Extend the visual system with a sunlight status indicator on screen

**Motivation:**
- Sunlight is as critical as water for plant health
- A natural extension of the existing humidity visual system
- BH1750 communicates over I2C — same protocol as the original OLED, easy to learn

**Potential Approach:**
- Wire a BH1750 module to the Arduino I2C pins (SDA/SCL)
- Use the `BH1750` library to read lux values
- Define thresholds for too dark / ideal / too bright
- Reuse the existing 4-state visual expression system with a sun illustration

**Priority:**
- [ ] High - Critical improvement
- [x] Medium - Nice to have
- [ ] Low - Future consideration

**Dependencies:**
- Modules 1–6 of the current learning plan completed
- Visual expression system already designed for reuse across plant types
- BH1750 module (~$3–6 CAD on Amazon)

**Status:**
- [x] Proposed
- [ ] In Progress
- [ ] Completed
- [ ] Deferred

---

### 2026-05-15 - Animated Status Images

**Description:**
- Replace static bitmap images with short animations for each of the 4 humidity states

**Motivation:**
- Would make the device more expressive and visually engaging
- A natural evolution of the hand-drawn illustration system already in place
- Demonstrates progression from basic to advanced embedded graphics

**Potential Approach:**
- **Option A (simple):** Animate basic shapes using Adafruit GFX drawing functions directly in code — no bitmap needed, works on Arduino Uno
- **Option B (full animation):** Migrate to an ESP32 microcontroller which has enough memory to decode and display animated GIFs using the `AnimatedGIF` library — compatible with the same ILI9341 screen
- Store animation frames on a microSD card module if staying on Arduino Uno

**Priority:**
- [ ] High - Critical improvement
- [ ] Medium - Nice to have
- [x] Low - Future consideration

**Dependencies:**
- Static image version must be fully working first
- Option B requires upgrading from Arduino Uno to ESP32
- Procreate animations would need to be exported frame by frame and converted via image2cpp

**Status:**
- [x] Proposed
- [ ] In Progress
- [ ] Completed
- [ ] Deferred
