// Arduino Threshold Library Example - Convert an input domain to a custom quantile output range
// Copyright 2015 Alex Taujenis
// MIT License

#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer
#include <RBD_Threshold.h>

#define BAUD 115200

RBD::Timer timer;
RBD::Threshold threshold(3);

void setup() {
  threshold.setLevel(1,0);    // [0 - 10.4]    low
  threshold.setLevel(2,10.5); // [10.5 - 19.9] medium
  threshold.setLevel(3,20);   // [20 - max]    high
  threshold.setMaxLevel(30);  // max = 30      high
  timer.setTimeout(5000);
  Serial.begin(BAUD);
}

void loop() {
  if(timer.isExpired()) {
    timer.restart();
    computeEverything();
  }
}

void computeEverything() {
  compute(-1);    // => 0   under
  compute(0);     // => 1   low
  compute(10.4);  // => 1   low
  compute(10.5);  // => 2   med
  compute(10.6);  // => 2   med
  compute(21);    // => 3   high
  compute(30);    // => 3   high
  compute(30.01); // => 4   over
  compute(999);   // => 4   over
}

void compute(float value) {
  Serial.print("value: ");
  Serial.print(value);
  Serial.print(" level: ");
  Serial.println(threshold.computeLevel(value));
}