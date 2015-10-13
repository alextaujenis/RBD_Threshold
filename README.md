#Arduino Threshold Library
Quickly set and check an arbitrary number of thresholds. Provide an input domain and this library will convert it to a numeric quantile output range. It is different from the Arduino map() function because this library can handle a non-uniform input range.

##Example Setup
* Install this library and load the example sketch on to an Arduino
* Open a serial connection at 115200 BAUD
* Watch as values are converted into the output range

This example takes an input domain of:

* [under 0]
* [0 - 10.49]
* [10.5 - 19.99]
* [20 - 30]
* [over 30]

and converts it to the quantile output range:

* 0 - UNDER
* 1 - LOW
* 2 - MEDIUM
* 3 - HIGH
* 4 - OVER

**Example:**

    #include <RBD_Threshold.h>

    RBD::Threshold threshold(3); // 3 levels

    void setup() {
      Serial.begin(115200);
      threshold.setLevel(1,0);    // low
      threshold.setLevel(2,10.5); // medium
      threshold.setLevel(3,20);   // high
      threshold.setMaxLevel(30);
    }

    void loop() {
      Serial.println(threshold.computeLevel(-1));   // 0
      Serial.println(threshold.computeLevel(8));    // 1
      Serial.println(threshold.computeLevel(10.6)); // 2
      Serial.println(threshold.computeLevel(30));   // 3
      Serial.println(threshold.computeLevel(31));   // 4
    }

#Documentation
##Public Methods

* [constructor(level\_count)](#constructorlevel_count)
<hr />
* [setLevel(index, value)](#setlevelindex-value)
* [setMaxLevel(value)](#setmaxlevelvalue)
<hr />
* [getLevel(index)](#getlevelindex)
* [getMaxLevel()](#getmaxlevel)
<hr />
* [computeLevel(value)](#computelevelvalue)

##constructor(level\_count)
Create a new instance and provide an integer for the maximum number of threshold levels. For example; set the level_count to 3 if you have levels of low, medium, and high. If you need more levels, this library will dynamically allocate an array to accommodate the size you provide the constructor.

    RBD::Threshold threshold(3) // 3 levels

    void setup() {
      ...
    }

##setLevel(index, value)
Provide an integer for a level index and an integer, float, or double for the threshold value. This is not zero based, the first level starts at 1. You must also call [setMaxLevel()](#setmaxlevelvalue) at the end to set an upper bounds of your last level.

    void setup() {
      threshold.setLevel(1,0);    // [0 - 10.49]
      threshold.setLevel(2,10.5); // [10.5 - 19.99]
      threshold.setLevel(3,20);   // [20 - max]
    }

##setMaxLevel(value)
Provide an integer, float, or double to set the upper-bounds threshold of the last level.

    void setup() {
      threshold.setMaxLevel(30); // [max = 30]
    }

##getLevel(index)
Provide an integer for the level index, and this returns the value originally provided to [setLevel()](#setlevelindex-value).

    void loop() {
      Serial.println(threshold.getLevel(3); // returns 20
    }

##getMaxLevel()
Returns the value originally provided to [setMaxLevel()](#setmaxlevelvalue).

    void loop() {
      Serial.println(threshold.getMaxLevel()); // returns 30
    }

##computeLevel(value)
Provide an integer, float, or double value to compare against the thresholds for setLevel() and setMaxLevel(). This returns an integer for the computed level.

* it returns 0 for values that are under the first level
* 1 for your first level
* 2 for your second level
* n for your nth level
* sizeof(n) + 1 for any value greater than [getMaxLevel()](#getmaxlevel)
* -1 if the value was not found

Example:

    void loop() {
      Serial.println(threshold.computeLevel(17)); // returns 2 (medium)
    }

#License
This code is available under the [MIT License](http://opensource.org/licenses/mit-license.php).