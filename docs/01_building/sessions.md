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

# AI Session Records

Track AI-assisted development sessions with summaries, successes, challenges, and friction points. Review this before similar sessions to learn from past experiences.

---

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
