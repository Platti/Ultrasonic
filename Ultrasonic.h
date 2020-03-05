/*
  Ultrasonic.h - Library for ultrasonic distance sensor (HC-SR04) arrays
  with connected trigger pins.
  Caution! Trigger pins of the sensors must be connected, sensors must NOT point
  towards each other.
  Created by Michael Plattner, March 4, 2020.
  Released into the public domain.
*/

#ifndef Ultrasonic_h
#define Ultrasonic_h

#include "Arduino.h"

class Ultrasonic
{
  public:
    Ultrasonic(int trigPin, int* echoPins, int numSensors);
    void measureDistances(int distances[]);
  private:
    int _trigPin;
    int _numSensors;
    int* _echoPins;
};

#endif
