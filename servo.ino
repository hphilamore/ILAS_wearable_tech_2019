/*Hardware setup:
 
 Servo -------- Arduino
 VDD --------------------- 5V
 GND --------------------- GND
 PWM in ------------------ 3 
 */
 
void servo_setup() {
  servo.attach(servo_pin);  // attaches the servo on pin 9 to the servo object
}



void servo_mapto_EMG(float EMG_val){
    // selects servo position based on EMG data
    int servo_pos = map(EMG_val, 
                        EMG_min, 
                        EMG_max, 
                        min_servo_write, 
                        max_servo_write);
    servo.write(servo_pos); // write scaled value to servo
}



void servo_sweep() {
  for (int pos = 0; pos <= 180; pos += 1) { // go from 0 degrees to 180 degrees
    // in steps of 1 degree
    servo.write(pos);              // go to position in variable 'pos'
    delay(15);                       // waits to reach the position
  }
  for (int pos = 180; pos >= 0; pos -= 1) { // go from 180 degrees to 0 degrees
    servo.write(pos);                     // go to position in variable 'pos'
    delay(15);                              // waits to reach the position
  }
}
