// Arduino Threshold Library Example - Convert an input domain to a custom quantile output range
// Copyright 2015 Alex Taujenis
// MIT License

#include <Threshold.h>

#define BAUD 115200

Threshold threshold(3);

void setup() {
  Serial.begin(BAUD);
  threshold.setLevel(1,0);   // [0 - 9]       low
  threshold.setLevel(2,10);  // [10 - 19]     medium
  threshold.setLevel(3,20);  // [20 - max]    high
  threshold.setMaxLevel(30); // max = 30      high
}

void loop() {
  compute(-1);  // => 0   under
  compute(0);   // => 1   low
  compute(1);   // => 1   low
  compute(9);   // => 1   low
  compute(10);  // => 2   med
  compute(11);  // => 2   med
  compute(15);  // => 2   med
  compute(20);  // => 3   high
  compute(30);  // => 3   high
  compute(99);  // => 4   over
  compute(999); // => 4   over
}

void compute(int value) {
  Serial.print("value: ");
  Serial.print(value);
  Serial.print(" level: ");
  Serial.println(threshold.computeLevel(value));
  delay(500); // delay sucks but it helps see serial output here
}