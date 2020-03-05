/*
  Ultrasonic.h - Library for ultrasonic distance sensor (HC-SR04) arrays
  with connected trigger pins.
  Caution! Trigger pins of the sensors must be connected, sensors must NOT point
  towards each other.
  Created by Michael Plattner, March 4, 2020.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Ultrasonic.h"

Ultrasonic::Ultrasonic(int trigPin, int* echoPins, int numSensors)
{
  _trigPin = trigPin;
  _echoPins = echoPins;
  _numSensors = numSensors;
  pinMode(_trigPin, OUTPUT);
  for (int i = 0; i < _numSensors; i++) {
    pinMode(_echoPins[i], INPUT);
  }
}

void Ultrasonic::measureDistances(int distances[])
{
  // Setup measurement
  long durations[_numSensors];
  long sensorsReady[_numSensors];
  for (int i = 0; i < _numSensors; i++) {
    durations[i] = 0;
    sensorsReady[i] = 0;
  }

  // Clear the trigger
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);

  // Set the trigPin on HIGH state for 10 micro seconds
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  // Perform measurements
  long tsStart = micros();
  int numResults = 0;
  while (numResults < _numSensors) {
    for (int i = 0; i < _numSensors; i++) {
      if (digitalRead(_echoPins[i]) == HIGH && sensorsReady[i] == 0) {
        // Ultrasonic bursts sent by sensor i
        sensorsReady[i] = micros();
      } else if (digitalRead(_echoPins[i]) == LOW && sensorsReady[i] > 0 && durations[i] == 0) {
        // Echo received by sensor i
        durations[i] = micros() - sensorsReady[i];
        numResults++;
      }
    }
    if (micros() - tsStart > 150000) {
      // Abort after 150ms
      break;
    }
  }

  // Interpret measurements
  for (int i = 0; i < _numSensors; i++) {
    if (sensorsReady[i] > 0) {
      // Calculate distance from duration
      distances[i] = durations[i] * 0.034 / 2;
    } else {
      // Measurement failed
      distances[i] = -1;
    }
  }
}
