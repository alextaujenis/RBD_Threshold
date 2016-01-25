// Arduino RBD Threshold Library v1.0.2 - Set and check numeric quantile scales.
// https://github.com/alextaujenis/RBD_Threshold
// Copyright 2016 Alex Taujenis
// MIT License

#include <Arduino.h>
#include <RBD_Threshold.h> // https://github.com/alextaujenis/RBD_Threshold

namespace RBD {
  Threshold::Threshold(int total_levels) {
    _total_levels = total_levels;
    // leave a space for the over-bounds level
    _levels = new double [_total_levels + 1];
  }

  // overloaded function
  void Threshold::setLevel(int index, int value) {
    _setLevel(index, double(value));
  }

  // overloaded function
  void Threshold::setLevel(int index, double value) {
    _setLevel(index, value);
  }

  double Threshold::getLevel(int index) {
    // get the level from the 0-based array
    return _levels[index - 1];
  }

  // overloaded function
  void Threshold::setMaxLevel(int value) {
    _setMaxLevel(double(value));
  }

  // overloaded function
  void Threshold::setMaxLevel(double value) {
    _setMaxLevel(value);
  }

  double Threshold::getMaxLevel() {
    return _levels[_total_levels];
  }

  // overloaded function
  int Threshold::computeLevel(int value) {
    return _computeLevel(double(value));
  }

  // overloaded function
  int Threshold::computeLevel(double value) {
    return _computeLevel(value);
  }


  // private

  // convert the domain into the range
  int Threshold::_computeLevel(double value) {
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

  void Threshold::_setLevel(int index, double value) {
    // check the bounds
    if(index > 0 && index <= _total_levels) {
      // store the level in the 0-based array
      _levels[index - 1] = value;
    }
  }

  void Threshold::_setMaxLevel(double value) {
    _levels[_total_levels] = value;
  }
}