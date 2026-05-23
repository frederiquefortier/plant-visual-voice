enum MoistureState {
  DYING,
  THIRSTY,
  PERFECT,
  OVERWATER
};

struct MoistureThreshold {
  int thirsty;
  int perfect;
  int overwater;
};

const MoistureThreshold ARID = { 5, 10, 30 };
const MoistureThreshold TEMPERATE = { 20, 40, 60 };
const MoistureThreshold HUMID = { 30, 60, 80 };

MoistureState getMoistureState(int percentage) {
  MoistureState state = DYING;

  if (percentage >= OVERWATER_MOISTURE_THRESHOLD) {
    state = OVERWATER;
  }
  else if (percentage >= PERFECT_MOISTURE_THRESHOLD) {
    state = PERFECT;
  }
  else if (percentage >= THIRSTY_MOISTURE_THRESHOLD) {
    state = THIRSTY;
  }

  return state;
}
