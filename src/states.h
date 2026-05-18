#define OVERWATER_MOISTURE_THRESHOLD 80
#define PERFECT_MOISTURE_THRESHOLD 50
#define THIRSTY_MOISTURE_THRESHOLD 20

enum State {
  DYING,
  THIRSTY,
  PERFECT,
  OVERWATER
};

State getState(int percentage) {
  State currentState = DYING;

  if (percentage >= OVERWATER_MOISTURE_THRESHOLD) {
    currentState = OVERWATER;
  }
  else if (percentage >= PERFECT_MOISTURE_THRESHOLD) {
    currentState = PERFECT;
  }
  else if (percentage >= THIRSTY_MOISTURE_THRESHOLD) {
    currentState = THIRSTY;
  }

  return currentState;
}
