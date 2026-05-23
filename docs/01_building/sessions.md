# AI Session Records

Track AI-assisted development sessions with summaries, successes, challenges, and friction points. Review this before similar sessions to learn from past experiences.

## Format

### YYYY-MM-DD - Session Title

**What We Worked On:**
- Main objectives and tasks completed
- Features implemented or problems solved

**What Went Well:**
- Successful approaches and techniques
- Effective collaboration patterns
- Quick wins

**What Could We Do Better:**
- Areas for improvement
- Misunderstandings or miscommunications
- Process inefficiencies

**Friction Points:**
- Technical blockers encountered
- Communication challenges
- Tool or workflow limitations

**Key Takeaways:**
- Lessons learned for future sessions
- Best practices identified

---

<!-- Add new entries below this line, newest first -->

### 2026-05-23 - C++ Architecture & File Structure

**What We Worked On:**
- Defined `MoistureThreshold` and `PlantProfile` structs inspired by TypeScript interfaces
- Discussed nullable pointers using `nullptr`
- Clarified include path behavior in Arduino IDE vs PlatformIO
- Established folder-per-plant file structure for scalability
- Decided on `plantProfile.h` over `index.h` by C++ naming convention

**What Went Well:**
- TypeScript background translated naturally to C++ struct concepts
- The "learn, don't receive code" contract was respected throughout

**What Could We Do Better:**
- Nothing notable

**Friction Points:**
- Arduino IDE has limitations with deep relative include paths that PlatformIO does not

**Key Takeaways:**
- Paste code with inline comment questions — it's the most efficient format for a review session
- TypeScript knowledge is a strong foundation for C++ struct and type thinking
- Architecture decisions (file structure, nullable pointers, threshold types) are worth making early

**Questions Asked:**
- Is a struct the right way to organize moisture threshold types (arid, temperate, humid)?
- Can I use null values for optional image pointers in a C++ struct?
- Do include paths work the same way in Arduino as usual?
- By convention, should the struct file be called `index.h` or `plantProfile.h`?

### 2026-05-17 - Sketch Architecture & State Management

**What We Worked On:**
- Reviewed a sketch with threshold definitions and state management questions asked as inline comments
- Discussed JSON vs struct for plant profiles
- Identified the right tool for state tracking (enum vs #define vs string)

**What Went Well:**
- Inline comment questions are an efficient review format — covers a lot of ground quickly
- Student is already thinking about multi-plant architecture before it's needed

**What Could We Do Better:**
- Nothing notable

**Friction Points:**
- None

**Key Takeaways:**
- Inline comment questions in code are a great format to bring to AI sessions
- Thinking about architecture early (profiles, state management) saves refactoring later

**Questions Asked:**
- Could thresholds and images be kept in a JSON per plant type?
- Should I track the previous state to avoid redrawing on every loop?
- Can an Arduino project have more than one file?
- Should I have one file per plant or one file that groups all plant definitions?

### 2026-05-17 - First Arduino Sketch Review

**What We Worked On:**
- Reviewed a first Arduino sketch reading a capacitive soil moisture sensor
- Answered inline code questions and corrected a compilation error
- Identified a Serial output formatting bug

**What Went Well:**
- Questions were asked directly in the code as comments — very efficient format
- Covered 4 distinct concepts in one pass (pins, ADC, power sharing, constrain)

**What Could We Do Better:**
- Nothing notable — inline comment format is a great way to structure code reviews

**Friction Points:**
- None

**Key Takeaways:**
- Inline code comments are an effective way to ask questions during a session
- One sketch review can cover a surprising amount of ground

**Questions Asked:**
- Why A0 and not another pin for the sensor?
- Why 5V specifically — and is it a problem if the screen also uses 5V?
- Where does 1023 come from in `map()`?
- Is `constrain()` really necessary if `map()` already returns 0–100?
- What is the 9600 value in `Serial.begin()` — baud rate or max bits per second?

### 2026-05-15 - Image Constraints & Display Research

**What We Worked On:**
- Discussed image sizing (48×64px) and ratio math for the 240×320 screen
- Identified memory constraints on Arduino Uno (32 KB flash vs ~150 KB for a full RGB565 image)
- Evaluated ESP32 as a future upgrade path
- Discovered image2cpp is monochrome only — LVGL Image Converter is the correct tool for RGB565

**What Went Well:**
- Ratio and pixel math was caught and corrected collaboratively

**What Could We Do Better:**
- image2cpp was incorrectly recommended as supporting color — caught by the student
- An incorrect ratio claim (3:4 for both screen and drawings) was made and had to be corrected

**Friction Points:**
- image2cpp color support was a source of confusion — LVGL Image Converter is the correct tool for RGB565

**Key Takeaways:**
- Always verify tool capabilities before recommending them (image2cpp = monochrome only)
- Flag AI errors immediately when spotted — it keeps the learnings file accurate

**Questions Asked:**
- Could I use `display.fillScreen()` to handle the image size problem?
- Should I have taken the ESP32 instead of the Arduino Uno?
- What is the ratio of a 240×320 screen?
- How many pixels do I need to add to my drawings to get a 3:4 ratio?

### 2026-05-15 - Project Kickoff & Learning Plan

**What We Worked On:**
- Identified the right hardware for a no-solder Arduino plant sensor (Arduino Uno, ILI9341 TFT, capacitive soil sensor)
- Validated and reviewed an Amazon.ca shopping cart (~$87.91 CAD)
- Discovered that OLED screens are monochrome and switched to a color TFT display
- Clarified that GIF is not a viable format for Arduino — switched to PNG → C++ bitmap conversion
- Built a 6-module step-by-step learning plan with tutorials, documentation, and guiding questions
- Established the full GitHub repo structure and file naming conventions
- Wrote README.md and filled out docs
- Documented 3 future improvement ideas: sunlight sensor, temperature sensor, animated images

**What Went Well:**
- The iterative, question-by-question approach felt natural — each answer led organically to the next topic
- Validating the Amazon cart item by item avoided a bad purchase (the Waveshare screen was flagged and replaced)
- The decision to learn rather than receive code kept the session focused on the right outcome
- The professor role worked well — guiding without doing
- Producing all documentation files progressively meant the repo is ready to commit immediately after the session
- Transparency about AI usage was handled thoughtfully and added value to the public repo

**What Could We Do Better:**
- Some product links couldn't be fetched (Amazon blocks direct access) — pasting cart content as text was a good workaround worth doing from the start

**Friction Points:**
- Amazon product pages are inaccessible via direct fetch — product details had to be inferred from URL titles and user-pasted cart content
- File already exists errors required str_replace edits instead of clean rewrites — minor but added steps

**Key Takeaways:**
- Start sessions by pasting cart or product content as text rather than sharing URLs for e-commerce sites
- Establish the "learn, don't do" contract at the start of any learning-focused session — it shapes every answer that follows
- Build the repo structure and documentation in parallel with the technical decisions, not after — it's much easier while context is fresh
- A professor framing (guiding questions, resources, no direct answers) is highly effective for learning-oriented projects
- Transparency about AI tooling in a public repo is a differentiator, not a weakness
