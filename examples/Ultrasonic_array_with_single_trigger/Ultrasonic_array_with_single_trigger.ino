#include "Ultrasonic.h"

int trigPin = 2;
int echoPins[] = {3, 4, 5};
int numSensors = 3;
Ultrasonic ultrasonic(trigPin, echoPins, numSensors);

void setup() {
  Serial.begin(115200);
}

void loop() {
  int distances[numSensors];
  ultrasonic.measureDistances(distances);
  for (int i = 0; i < numSensors; i++) {
    char msgString[128];
    if (distances[i] < 0) {
      sprintf(msgString, "Sensor@Pin%d:  FAIL | ", echoPins[i]);
    } else if (distances[i] >= 1000) {
      sprintf(msgString, "Sensor@Pin%d:  OoR  | ", echoPins[i]);
    } else {
      sprintf(msgString, "Sensor@Pin%d: %3dcm | ", echoPins[i], distances[i]);
    }
    Serial.print(msgString);
  }
  Serial.println();

  delay(1000);
}
