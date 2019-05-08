 /* 
 
 Hardware setup:
 
 MPU9250 Breakout --------- Arduino
 VCC ---------------------- 3.3V
 INT ---------------------- D12
 SDA ----------------------- A4
 SCL ----------------------- A5
 GND ---------------------- GND

 [SDA and SCL should have external pull-up resistors (to 3.3V)]
 */

#include "quaternionFilters.h"
#include "MPU9250.h"

// Pin definitions
int intPin = 12;  // These can be changed, 2 and 3 are the Arduinos ext int pins

MPU9250 myIMU;

//#define X 0
//#define Y 1
//#define Z 2

#define step_threshold 1.5F //3000      // the magnitude of acceleration above which a step is registered

#define pace_period 1000              // the period (in ms) over which steps are counted to calculate pace
#define pace_threshold 0.0005F        // the pace above which a light will switch on

float acceleration[3];

float gyro[3];

float temperature_C;

unsigned long startTime = millis();
unsigned long endTime;

int steps, flag;         // initialise variables for pedometer

float paceAve;           // initialise variables for pace monitor
int stepsOld;
