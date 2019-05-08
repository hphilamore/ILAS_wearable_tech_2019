/*Hardware setup:
 
 MPU9250 Breakout -------- Arduino
 VDD --------------------- 5V
 GND --------------------- GND
 PWM in ------------------ 3 
 */

#include <Servo.h>

#define servo_pin 3

Servo servo;  // create servo object to control a servo
 
int min_servo_write = 0;      // range = 0 --> 180
int max_servo_write = 180;    // range = 0 --> 180
