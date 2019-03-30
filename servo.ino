/*Hardware setup:
 
 Servo -------- Arduino
 VDD --------------------- 5V
 GND --------------------- GND
 PWM in ------------------ 3 
 */
 
 void servo_setup() {
  myservo.attach(servo_pin);  // attaches the servo on pin 9 to the servo object
}


void servo_sweep() {
  for (int pos = 0; pos <= 180; pos += 1) { // go from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // go to position in variable 'pos'
    delay(15);                       // waits to reach the position
  }
  for (int pos = 180; pos >= 0; pos -= 1) { // go from 180 degrees to 0 degrees
    myservo.write(pos);                     // go to position in variable 'pos'
    delay(15);                              // waits to reach the position
  }
}
