# Architectural Decision Records

Document architectural choices with context, alternatives considered, and trade-offs. Check this file before proposing changes that might conflict with past decisions.

## Format

### ADR-XXX: Decision Title (YYYY-MM-DD)

**Context:**
- Why the decision was needed
- What problem it solves

**Decision:**
- What was chosen

**Alternatives Considered:**
- Option 1 -> Why rejected
- Option 2 -> Why rejected

**Consequences:**
- Benefits
- Trade-offs

---

<!-- Add new entries below this line, newest first -->

### ADR-001: Use FileToCArray instead of image2cpp for image conversion (2026-05-17)

**Context:**
- Module 4 of the plan requires converting four 240×320 PNG illustrations into C++ arrays the Arduino can render on the ILI9341 TFT.
- The plant status illustrations are drawn in color in Procreate — preserving color is essential to the project's creative intent.
- The plan originally referenced [image2cpp](https://javl.github.io/image2cpp/), but that tool is primarily designed for monochrome (1-bit) bitmaps and does not produce true color output suitable for `tft.drawRGBBitmap()`.

**Decision:**
- Use [FileToCArray](https://github.com/notisrac/FileToCArray) ([web app](https://notisrac.github.io/FileToCArray/)) to convert each PNG to a `const uint16_t ... PROGMEM` array in **16-bit RGB (RGB565)** format, using the **Arduino code (Adafruit GFX, TFT_eSPI)** output preset.

**Alternatives Considered:**
- **image2cpp** → Rejected: monochrome-oriented; color output workflow is awkward and not aligned with `drawRGBBitmap()`.
- **LCD Image Converter (desktop)** → Rejected: heavier desktop install for what is a one-shot conversion per asset; web tool is sufficient.
- **SD card + `drawBitmap` from file** → Rejected: adds an SD card module to the BOM and extra wiring; embedding in `PROGMEM` keeps the hardware simple for a learning project.

**Consequences:**
- Benefits: true color rendering matching the Procreate originals; one-click web workflow; output drops directly into the sketch with the right type and `PROGMEM` qualifier.
- Trade-offs: each 240×320 RGB565 image is ~150 KB, which exceeds the Arduino Uno R3's 32 KB flash. The Uno can only hold one or two reduced-size images at most; full-screen color art will require either downscaling, palette indexing, or moving to a board with more flash (e.g., ESP32). This constraint should be surfaced before Module 4.