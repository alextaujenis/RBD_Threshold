#Arduino Threshold Library
Quickly set and check an arbitrary number of thresholds. Provide an input domain and this library will convert it to a quantile output range.

##Example Setup
This takes an input domain of [under 0, 0-9, 10-19, 20-29, over 29] and converts it to a quantile output range of [under, low, medium, high, over]

0. Install this library and load the example sketch on to an Arduino
0. Open a serial connection at 115200 BAUD
0. Watch as values are converted into the output range

##[example.ino](https://github.com/alextaujenis/RBD_Threshold/blob/master/example/example.ino)

    #include <RBD_Threshold.h>

    RBD::Threshold threshold(3);

    void setup() {
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

#Documentation
##Public Methods

* [constructor(level\_count)](#constructorlevel_count)
* [setLevel(index, value)](#setlevelindex-value)
* [getLevel(index)](#getlevelindex)
* [setMaxLevel(value)](#setmaxlevelvalue)
* [getMaxLevel()](#getmaxlevel)
* [computeLevel(value)](#computelevelvalue)

##constructor(level\_count)
Create a new instance and provide an integer for the maximum number of levels of this threshold. For example; set the level\_count to 3 if you have levels of low, medium, and high.

If you need more than 3 levels, this library will dynamically allocate an array large enough to accommodate the size you provide the constructor.

    RBD::Threshold threshold(3);

##setLevel(index, value)
Provide integers for the index and value to set an individual level. This is not zero based, the first level starts at 1. You must also call [setMaxLevel()](#setmaxlevelvalue) at the end to set an upper bounds of your last level.

    threshold.setLevel(1,0);   // [0 - 9]       low
    threshold.setLevel(2,10);  // [10 - 19]     medium
    threshold.setLevel(3,20);  // [20 - max]    high
    threshold.setMaxLevel(30); // max = 30      high

##getLevel(index)
Provide an integer for a level index and this returns the value set for that level.

    threshold.getLevel(3) // => 20

##setMaxLevel(value)
Set the upper-bounds threshold of the last level.

    threshold.setMaxLevel(30);

##getMaxLevel()
Returns the upper-bounds threshold of the last level.

    threshold.getMaxLevel() // => 30

##computeLevel(value)
Provide an integer for the input domain and this returns an integer threshold level.

* it returns 0 for values that are under the first level
* 1 for your first level
* 2 for your second level
* n for your nth level
* sizeof(n) + 1 for any value greater than [getMaxLevel()](#getmaxlevel)
* -1 if an error was found in the input domain (non-contiguous range)

Example:

    threshold.computeLevel(17); // => 2 medium

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).