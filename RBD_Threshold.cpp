// Arduino Threshold Library - Quickly set and check an arbitrary number of thresholds
// Copyright 2015 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Threshold.h>

namespace RBD {
  Threshold::Threshold(int total_levels) {
    _total_levels = total_levels;
    // leave a space for the over-bounds level
    _levels = new float [_total_levels + 1];
  }

  // overloaded function
  void Threshold::setLevel(int index, int value) {
    _setLevel(index, float(value));
  }

  // overloaded function
  void Threshold::setLevel(int index, float value) {
    _setLevel(index, value);
  }

  int Threshold::getLevel(int index) {
    // get the level from the 0-based array
    return _levels[index - 1];
  }

  // overloaded function
  void Threshold::setMaxLevel(int value) {
    _setMaxLevel(float(value));
  }

  // overloaded function
  void Threshold::setMaxLevel(float value) {
    _setMaxLevel(value);
  }

  int Threshold::getMaxLevel() {
    return _levels[_total_levels];
  }

  // overloaded function
  int Threshold::computeLevel(int value) {
    return _computeLevel(float(value));
  }

  // overloaded function
  int Threshold::computeLevel(float value) {
    return _computeLevel(value);
  }


  // private

  // convert the domain into the range
  int Threshold::_computeLevel(float value) {
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
      for(_i = 0; _i < _total_levels; _i++) {
        // see if the value falls within the range
        if(value >= _levels[_i] && value < _levels[_i+1]) {
          // return the level number
          return _i + 1;
        }
      }
      // catch mistakes in the input domain
      return -1;
    }
  }

  void Threshold::_setLevel(int index, float value) {
    // check the bounds
    if(index > 0 && index <= _total_levels) {
      // store the level in the 0-based array
      _levels[index - 1] = value;
    }
  }

  void Threshold::_setMaxLevel(float value) {
    _levels[_total_levels] = value;
  }
}