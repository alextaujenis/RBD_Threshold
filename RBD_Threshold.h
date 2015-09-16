// Arduino Threshold Library - Quickly set and check an arbitrary number of thresholds
// Copyright 2015 Alex Taujenis
// MIT License

#ifndef RBD_THRESHOLD
#define RBD_THRESHOLD

#include <Arduino.h>

namespace RBD {
  class Threshold {
    public:
      Threshold(int level_count);
      void setLevel(int index, int value);  // set a threshold value for a level
      int getLevel(int index);              // get the threshold value for a level
      void setMaxLevel(int value);          // set the maximum threshold value
      int getMaxLevel();                    // get the maximum threshold value
      int computeLevel(int value);          // convert an input domain value to the output range
    private:
      int _total_levels;                    // total number of levels for this threshold
      int* _levels;                         // dynamically allocated array for the levels
      int i;                                // temp variable to loop through the levels
  };
}
#endif
