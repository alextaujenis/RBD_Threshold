// Arduino Threshold Library - Quickly set and check an arbitrary number of thresholds
// Copyright 2015 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <Threshold.h>

Threshold::Threshold(int total_levels) {
  _total_levels = total_levels;
  // leave a space for the over-bounds level
  _levels = new int [_total_levels + 1];
}

void Threshold::setLevel(int index, int value) {
  // check the bounds
  if(index > 0 && index <= _total_levels) {
    // store the level in the 0-based array
    _levels[index - 1] = value;
  }
}

int Threshold::getLevel(int index) {
  // get the level from the 0-based array
  return _levels[index - 1];
}

void Threshold::setMaxLevel(int value) {
  _levels[_total_levels] = value;
}

int Threshold::getMaxLevel() {
  return _levels[_total_levels];
}

// convert the domain into the range
int Threshold::computeLevel(int value) {
  // it's under
  if(value < _levels[0]) {
    return 0;
  }
  // it's exactly at the maxLevel
  else if(value == _levels[_total_levels]) {
    // return the last level
    return _total_levels;
  }
  // it's over the maxLevel
  else if (value > _levels[_total_levels]) {
    // return a number only one greater than the number of levels
    return _total_levels + 1;
  }
  // it's in-between
  else {
    // scroll through all levels
    for(i = 0; i < _total_levels; i++) {
      // see if the value falls within the range
      if(value >= _levels[i] && value < _levels[i+1]) {
        // return the level number
        return i + 1;
      }
    }
    // catch mistakes in the input domain
    return -1;
  }
}