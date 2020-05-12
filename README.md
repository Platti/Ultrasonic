# Ultrasonic
Arduino library designed to simultaneously measure the distances with multiple ultrasonic distance sensors (HC-SR04) with interconnected trigger pins.

With this library multiple HC-SR04 sensors can be triggered at the same time and the distance is measured with each of them. Keep in mind that those sensors use the same frequency and hence can interfere with each other. Thus, the sensors must NOT point towards each other!

The advantage of this library is that multiple sensors are read simultaneously and therefor a measurement of all sensors only takes about 150ms at max, if a sensor is disconnected or does not receive an echo (without errors even faster). Compared to a time multiplex approach of many sensors, where a single sensor might need the same time for a measurement, this library is designed for time critical applications with many sensors pointing into different directions. 
