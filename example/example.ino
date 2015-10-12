// Arduino Threshold Library Example - Convert an input domain to a custom quantile output range
// Copyright 2015 Alex Taujenis
// MIT License

#include <RBD_Threshold.h>

RBD::Threshold threshold(3); // 3 levels

void setup() {
  threshold.setLevel(1,0);    // low
  threshold.setLevel(2,10.5); // medium
  threshold.setLevel(3,20);   // high
  threshold.setMaxLevel(30);
}

void loop() {
  Serial.println(threshold.computeLevel(-1));
  Serial.println(threshold.computeLevel(8));
  Serial.println(threshold.computeLevel(10.6));
  Serial.println(threshold.computeLevel(30));
  Serial.println(threshold.computeLevel(31));
}