# Arduino Plant Humidity Sensor — Course Plan

> **Project goal:** Build a soil moisture sensor that displays one of 4 images on a color TFT screen depending on the plant's hydration level: *Overwatered*, *Perfect*, *A little thirsty*, *Very thirsty*.

---

## Module 0 — While Waiting for Hardware

**Goal:** Make meaningful progress before the package arrives.

Everything in this module requires zero hardware.

### 0a — Set Up Your GitHub Repo

1. Install [Git](https://git-scm.com/downloads)
2. Create your GitHub repository
3. Commit your documentation files

### 0b — Draw Your Illustrations in Procreate

Your 4 status images are the creative heart of the project — give yourself time here.

1. Draw your 4 states for each plant variant (Procreate, PNG export, 240×320px):
    - Overwatered
    - Perfect
    - A little thirsty
    - Very thirsty
2. Export each as PNG at full resolution
3. Experiment with [image2cpp](https://javl.github.io/image2cpp/) to understand how conversion works — no Arduino needed to explore the tool

**Think about:**
- How do you design expressions that are readable at 240×320px on a small screen?
- How do you keep the style consistent across plant variants so the system feels reusable?

### 0c — Simulate with Wokwi

[Wokwi](https://wokwi.com) is a free in-browser Arduino simulator. You can wire a virtual Arduino, add a virtual soil sensor, and write real code — no hardware needed.

1. Go to [wokwi.com](https://wokwi.com) and create a new Arduino Uno project
2. Add a potentiometer to simulate the analog signal of your soil sensor (A0)
3. Write a sketch that reads the value and prints it to the Serial Monitor
4. Try converting it to a percentage using `map()` and `constrain()`

This gets you through Module 2 before your hardware arrives.

**Read:**
- [Wokwi documentation](https://docs.wokwi.com)

### 0d — Install the Arduino IDE & Read the Language Reference

1. Download and install the [Arduino IDE v2](https://www.arduino.cc/en/software)
2. Browse the [Arduino language reference](https://www.arduino.cc/reference/en/) — focus on: `analogRead()`, `map()`, `constrain()`, `if/else`, `Serial.println()`
3. Read the [Blink tutorial](https://docs.arduino.cc/built-in-examples/basics/Blink/) fully even if you can't upload yet

**Think about:**
- What is the difference between `setup()` and `loop()`?
- What does it mean for code to run in a loop forever?

---

## Module 1 — Set Up Your Environment

**Goal:** Get a blinking LED working on your Arduino.

Before touching the screen or sensor, get comfortable with your tools. Everything else builds on this.

1. Download and install the [Arduino IDE v2](https://www.arduino.cc/en/software)
2. Plug in your ELEGOO Uno R3 via USB
3. Select the correct board and port under **Tools → Board** and **Tools → Port**
4. Open the built-in Blink example: **File → Examples → 01.Basics → Blink**
5. Upload it and confirm the onboard LED blinks

**Read:**
- [Installing the Arduino IDE v2](https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing/)
- [Your first sketch: Blink](https://docs.arduino.cc/built-in-examples/basics/Blink/)

**Think about:**
- What happens if you put all your code in `setup()` instead of `loop()`?
- What is the difference between `setup()` and `loop()`? Why do both exist?

---

## Module 2 — Read Your Sensor

**Goal:** Print the raw soil moisture value to the Serial Monitor.

Before adding a screen, learn to "see" what your sensor is saying through the Serial Monitor — your best debugging tool throughout the project.

1. Wire your capacitive soil moisture sensor: VCC→5V, GND→GND, AOUT→A0
2. Open a new sketch and use `analogRead(A0)` to read the sensor
3. Use `Serial.begin(9600)` and `Serial.println()` to print the value
4. Open **Tools → Serial Monitor** and observe values changing when you insert the sensor in dry vs wet soil
5. Use the `map()` function to convert the raw value (0–1023) into a percentage (0–100)
6. Use `constrain()` to make sure the percentage never goes below 0 or above 100

**Read:**
- [analogRead() reference](https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/)
- [Serial Monitor guide](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-serial-monitor/)
- [map() reference](https://www.arduino.cc/reference/en/language/functions/math/map/)
- [constrain() reference](https://www.arduino.cc/reference/en/language/functions/math/constrain/)

**Think about:**
- Why doesn't the sensor return a percentage directly?
- What raw values correspond to "dry" and "wet" for your specific sensor? How do you find out?

---

## Module 3 — Drive the TFT Display

**Goal:** Display text and colored shapes on the ILI9341 screen.

1. Wire the ILI9341 screen to your Arduino Uno:

   | Screen pin | Arduino pin |
      |---|---|
   | VCC | 5V |
   | GND | GND |
   | CS | 10 |
   | RESET | 9 |
   | DC/RS | 8 |
   | MOSI | 11 |
   | SCK | 13 |
   | LED | 3.3V |

2. Install the required libraries via **Tools → Manage Libraries**:
    - `Adafruit ILI9341`
    - `Adafruit GFX Library`

3. Open the built-in example: **File → Examples → Adafruit ILI9341 → graphicstest**
4. Upload it and confirm shapes and colors appear on screen
5. Write a simple sketch that displays the humidity percentage as text on screen

**Read:**
- [Installing a library in Arduino IDE](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library/)
- [Adafruit ILI9341 overview](https://learn.adafruit.com/adafruit-2-4-tft-lcd-touchscreen/overview)
- [Adafruit GFX Library — all drawing functions](https://learn.adafruit.com/adafruit-gfx-graphics-library/overview)

**Think about:**
- What is SPI? How does the screen know which Arduino pins to listen to?
- What does the `display.fillScreen()` function do, and when would you use it?

---

## Module 4 — Convert Your Images to Bitmap

**Goal:** Display one static image on the TFT screen.

This is where your 4 drawings become Arduino-compatible. You'll create images in any drawing tool, convert them, and embed them directly in your code.

1. Create 4 simple drawings (PNG format, recommended size: 240×320px to fill the screen):
    - `overwatered.png`
    - `perfect.png`
    - `thirsty.png`
    - `very_thirsty.png`

2. Go to [image2cpp](https://javl.github.io/image2cpp/) and convert each PNG:
    - Set canvas size to match your image dimensions
    - Set color format to **RGB565 16-bit**
    - Copy the generated C++ array

3. Paste each array into your sketch as a `const uint16_t` variable stored in `PROGMEM`
4. Use `tft.drawRGBBitmap()` to display one image on screen
5. Confirm it renders correctly before moving on

**Read:**
- [image2cpp tool](https://javl.github.io/image2cpp/)
- [Adafruit GFX — loading images](https://learn.adafruit.com/adafruit-gfx-graphics-library/loading-images)
- [PROGMEM reference — storing data in flash memory](https://www.arduino.cc/reference/en/language/variables/utilities/progmem/)

**Think about:**
- Why does Arduino use RGB565 (16-bit color) instead of standard RGB (24-bit)?
- What is `PROGMEM` and why is it important when storing images?
- What is the difference between `drawBitmap()` and `drawRGBBitmap()`?

---

## Module 5 — Assemble the Final Project

**Goal:** Display the correct image based on the live humidity reading.

You now have all the pieces. This module is about connecting them with logic.

1. Define your 4 humidity thresholds — for example:
    - Above 80% → Overwatered
    - 50–80% → Perfect
    - 20–50% → A little thirsty
    - Below 20% → Very thirsty

2. Use `if / else if / else` to select which image to display based on the current humidity
3. Track the *previous* state so you only redraw the screen when the level changes (avoid unnecessary flickering)
4. Test with your sensor in different conditions: dry soil, moist soil, submerged in water
5. Adjust your thresholds based on real readings from Module 2
6. Commit your final code to GitHub with a clear commit message

**Read:**
- [if / else reference — Arduino](https://www.arduino.cc/reference/en/language/structure/control-structure/if/)

**Think about:**
- Why is redrawing on every `loop()` cycle a bad idea, even if the image hasn't changed?
- How would you handle a sensor reading that fluctuates between two thresholds rapidly?
- What would you add if you wanted to support multiple plants?

---

## Reference Resources

Keep these bookmarked throughout the project.

| Resource | Purpose |
|---|---|
| [wokwi.com](https://wokwi.com) | Free in-browser Arduino simulator — no hardware needed |
| [arduino.cc/reference](https://www.arduino.cc/reference/en/) | Complete Arduino function reference |
| [Adafruit Learning System](https://learn.adafruit.com) | In-depth guides for Adafruit libraries |
| [image2cpp](https://javl.github.io/image2cpp/) | Convert images to C++ arrays |
| [forum.arduino.cc](https://forum.arduino.cc) | Community — someone has likely had your problem |
| [r/arduino](https://www.reddit.com/r/arduino/) | Active and welcoming community |
| [GitHub — arduino/arduino-examples](https://github.com/arduino/arduino-examples) | Official example sketches |
