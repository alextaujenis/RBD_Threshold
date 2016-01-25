// Arduino RBD Threshold Library v1.0.2 - Set and check numeric quantile scales.
// https://github.com/alextaujenis/RBD_Threshold
// Copyright 2016 Alex Taujenis
// MIT License

#ifndef RBD_THRESHOLD
#define RBD_THRESHOLD

#include <Arduino.h>

namespace RBD {
  class Threshold {
    public:
      Threshold(int level_count);
      void setLevel(int index, int value);     // overloaded: set a threshold value for a level
      void setLevel(int index, double value);  // same as above
      double getLevel(int index);              // get the threshold value for a level
      void setMaxLevel(int value);             // overloaded: set the maximum threshold value
      void setMaxLevel(double value);          // same as above
      double getMaxLevel();                    // get the maximum threshold value
      int computeLevel(int value);             // overloaded: convert an input domain value to the output range
      int computeLevel(double value);          // same as above
    private:
      int _total_levels;                       // total number of levels for this threshold
      double* _levels;                         // dynamically allocated array for the levels
      int _i;                                  // temp variable to loop through the levels
      void _setLevel(int index, double value); // set a threshold value for a level
      void _setMaxLevel(double value);         // set the maximum threshold value
      int _computeLevel(double value);         // convert an input domain value to the output range
  };
}
#endif
