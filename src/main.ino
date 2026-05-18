#include "states.h"

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 320

#define SOIL_MOISTURE_SENSOR A0

State previousState = DYING;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int moistureValue = analogRead(SOIL_MOISTURE_SENSOR);
  int percentage = map(moistureValue, 0, 1023, 0, 100);
  percentage = constrain(percentage, 0, 100);

  Serial.print("Sensor value: ");
  Serial.print(moistureValue);
  Serial.print(", in percent: ");
  Serial.print(percentage);
  Serial.println("%");

  State currentState = getState(percentage);
  if (currentState != previousState) {
    //do the display stuff

    previousState = currentState;
  }

  delay(1000);
}
