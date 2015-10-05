#Arduino Threshold Library
Quickly set and check an arbitrary number of thresholds. Provide an input domain and this library will convert it to a quantile output range.

##Example Setup
This takes an input domain of [under 0, 0-10.4, 10.5-19.9, 20-30, over 30] and converts it to a quantile output range of [under, low, medium, high, over]

0. Install this threshold library (and the [dependency](https://github.com/alextaujenis/RBD_Timer) for the example)
0. Load the example sketch on to an Arduino
0. Open a serial connection at 115200 BAUD
0. Watch as values are converted into the output range

##[example.ino](https://github.com/alextaujenis/RBD_Threshold/blob/master/example/example.ino)
The [RBD Timer Library](https://github.com/alextaujenis/RBD_Timer) is a dependency for only the example code below, and is not a requirement while using this threshold library by itself.

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
Provide an integer for the index, then provide either an integer or a float for the value. This is not zero based, the first level index starts at 1. You must also call [setMaxLevel()](#setmaxlevelvalue) at the end to set an upper bounds of your last level.

    threshold.setLevel(1,0);    // [0 - 10.4]    low
    threshold.setLevel(2,10.5); // [10.5 - 19.9] medium
    threshold.setLevel(3,20);   // [20 - max]    high
    threshold.setMaxLevel(30);  // max = 30      high

##getLevel(index)
Returns the value previously set for the level at that index.

    threshold.getLevel(3) // => 20

##setMaxLevel(value)
Set the upper threshold of the last level. This can be either an integer or a float.

    threshold.setMaxLevel(30);

##getMaxLevel()
Returns the upper threshold of the last level.

    threshold.getMaxLevel() // => 30

##computeLevel(value)
Provide an integer or float for the input domain and this returns the computed threshold level.

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