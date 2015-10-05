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
  timer.setTimeout(3000);
  Serial.begin(BAUD);
}

void loop() {
  if(timer.onRestart()) {
    Serial.println(threshold.computeLevel(-1));    // under
    Serial.println(threshold.computeLevel(0));     // low
    Serial.println(threshold.computeLevel(10.51)); // medium
    Serial.println(threshold.computeLevel(21));    // high
    Serial.println(threshold.computeLevel(999));   // over
    Serial.println("---");
  }
}