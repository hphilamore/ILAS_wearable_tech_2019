#include <Wire.h>
#include "resistance.h"
#include "capacitance.h"
#include "accelerometer.h"
#include "LED.h"
#include "vib_motor.h"
#include "servo.h"
#include "EMG.h"
#include "software_filters.h" 

unsigned long time_ms;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  res_setup();
  //servo_setup();
  //acc_setup();
  //LED_setup();
  //vib_motor_setup();
  pinMode(13, OUTPUT);
  
}

void loop() {

  // Time
  //time_ms = millis();
  //Serial.print( time_ms );
  //Serial.print("\t");

  // Digital Switch
  /*
  bool d_switch = digitalRead( dig_switch_pin );
  Serial.print( d_switch );
  digitalWrite(13, d_switch); 
  
//Serial.print("\t");
*/
  // Stretch sensor
float stretch = res_stretch();
  Serial.print( stretch );
  //Serial.print("\t");

  // Pressure sensor
//  float pressure = res_pressure();
//  //Serial.print( pressure );
//  //Serial.print("\t");

//  // Capacitive sensor
//  cap_sense0 = C0.capacitiveSensor(5);
//  cap_sense1 = C1.capacitiveSensor(5);
  //  Serial.print( cap_sense0 );
  //  Serial.print("\t");
  //  Serial.print( cap_sense1 );
  //  Serial.print("\t");

  // Filtered Capacitive sensor
  // Moving Average
//  cap_sense0_f = MA_filter_cap( C0 );
//  cap_sense1_f = MA_filter_cap( C1 );
//  // Exponential
//  cap_sense0_f = weightC0 * cap_sense0 + (1 - weightC0) * cap_sense0_f;
//  cap_sense1_f = weightC1 * cap_sense1 + (1 - weightC1) * cap_sense1_f;
  // Low Pass 
  //cap_sense0_f = LP_filter_cap0.filterIn( cap_sense0 );
  //cap_sense1_f = LP_filter_cap1.filterIn( cap_sense1 );
  //  Serial.print( cap_sense0_f );
  //  Serial.print("\t");
  //  Serial.print( cap_sense1_f );
  //  Serial.print("\t");

  // EMG 
//  EMG = analogRead(EMG_pin);
//  Serial.print( EMG );
//  Serial.print( "\t" );
//
//  // Filtered EMG
//  // Moving Average
//  EMG_f = MA_filter_EMG();
//  // Exponential
//  EMG_f = weightEMG * EMG + (1 - weightEMG) * EMG_f;
//  // Low Pass
//  EMG_f = LP_filter_EMG.filterIn( EMG );
//  Serial.print( EMG_f );
//  Serial.print( "\t" );
//
//  // Servo
//  servo_mapto_EMG(EMG_f);
////  int servo_pos = map(ExpEMG, 
////                  EMG_min, 
////                  EMG_max, 
////                  min_servo_write, 
////                  max_servo_write);
////  servo.write(servo_pos);         // write scaled value to servo

  


//  if( resistance_sensor ){
//    float R1 = res_resistance();
//    float r1 = res_resistivity(R1);
//    V2_raw = analogRead(probe_pin);
//    int val = map(V2_raw, 
//                  Vin_min, 
//                  Vin_max, 
//                  Vout_min, 
//                  Vout_max);
//                  
//    analogWrite(LED_pin, val);
//  
//    float S = res_digital_switch();
//    Serial.print(S);
//    Serial.print("\t");
//    delay(100); 
//  }


//  if( capacitance_sensor ){
//    cap_print();
//  }
//
//  if( accelerometer ){
//    acc_sense();
//    acc_step_counter();
//    acc_pace();
//  }
//
//  if( LED ){
//    //    theaterChase(strip.Color(127, 127, 127), 50);
////    theaterChaseRainbow(50);
////    rainbow(50);
//   // rainbowFade2White(3,3,1);
////    whiteOverRainbow(20,75,5);
////    LED_myCol(3);
////    LED_fade_in();
////    LED_fade_out();
////    colorWipe(strip.Color(0, 255, 0), 50);
////    colorWipe(strip.Color(0, 255, 0), 50); // Green
////    colorWipe(strip.Color(0, 0, 255), 50); // Blue
////    colorWipe(strip.Color(255, 255, 255, 255), 50); // White
//  }
//
//  if( capacitance_sensor && LED ){
//
//    // Filter output of capacitive sensor
//    //filter_cap_average();
//    //filter_cap_running_average();
//    exponential_filter();
//
//    /*
//    // Colour level
//    int mapC1 = map(ExpC1, 0, 200, 0, strip.numPixels());
//    if(mapC1<0){mapC1=0;}
//    colorLevel(strip.Color(0, 255, 0), mapC1);
//    */
//
//    /*
//    // Scale to input
//    int mapC0 = map(ExpC0, 0, 200, 0, 255);
//    int mapC1 = map(ExpC1, 0, 200, 0, 255);
//    for (int m=0; m<NUM_LEDS; m++){ 
//    LED_scaleToInput(m, 255, mapC0, mapC1);}
//    */
//
//    // Colour wipe 
//    long mapC0 = map(ExpC0, 0, 100, 1000, 0.01);
//    if(mapC0<0){mapC0=0;}
//    colorWipe(strip.Color(0, 255, 100), mapC0);
//
//  }
//
//  if( vib_motor ){
//      //digitalWrite(vib_motor_pin, HIGH);
////      analogWrite(vib_motor_pin, 255);
////      delay(2000);
////      analogWrite(vib_motor_pin, 100);  
////      delay(2000);   
//  }
//
//
//  if( buzzer ){
//    
//    //tone(buzzer_pin, 1000);//, 5000);
//    
//    //tone(buzzer_pin, 200);//, 5000);
//    /*
//    delay(2000);
//    tone(buzzer_pin, 2000);//, 5000);
//    delay(2000);
//    noTone(buzzer_pin);
//    delay(2000);
//    */
//
//    
//    buzz_play_song();
//    
//  }
//
//  if( servo ){
//    
//    if( EMG ){
//      V2_raw = analogRead(EMG_pin);
//      Serial.print( V2_raw );
//      Serial.print( "\t" );
//      ExpEMG = weight * V2_raw + (1-weight)*ExpEMG;
//
//    }
//
//    else{
//      V2_raw = analogRead(probe_pin);   // read input value
//    }
//
//    int servo_pos = map(ExpEMG, 
//                  Vin_min, 
//                  Vin_max, 
//                  min_servo_write, 
//                  max_servo_write);
//    
//    myservo.write(servo_pos);         // write scaled value to servo
//  }
//
//
//
//  if( EMG ){
//    V2_raw = analogRead(EMG_pin);
//    //Serial.print( V2_raw );
//    //Serial.print( "\t" );
//    ExpEMG = weight * V2_raw + (1-weight)*ExpEMG;
//    Serial.print( ExpEMG );
//    Serial.print( "\t" );
//  }
//
//
//
//
//
//

  
  delay(100);
  Serial.println();
  
}


//void filter_cap_average(void){
//  int n_C = sizeof(cap_sensors)/sizeof(cap_sensors[0]);
//  long capRead[n_C];              // an array of same length as the number of sensors
//  cap_sense(capRead);             // update array with sensor values
//  
//  float C0ave = 0;
//  float C1ave = 0;
//  int MeasurementsToAverage = 16;
//  for(int i = 0; i < MeasurementsToAverage; ++i)
//  {
//    cap_sense(capRead);
//    C0ave += capRead[0];
//    C1ave += capRead[1];
//    delay(1);
//  }
//  C0ave /= MeasurementsToAverage;
//  C1ave /= MeasurementsToAverage;
//
//  Serial.print(capRead[0]);
//  Serial.print("\t");
//
//  Serial.print(C0ave);
//  Serial.print("\t");
//
//
//  
//  //Serial.print(C1ave);
//  //Serial.print("\t");
//
//  
//
////  for (int i = 0; i < n_C; i++){
////    Serial.print(capRead[i]);
////    Serial.print("\t");}
//}

//void AvergeFilterCapacitor(int capacitor){
//  int n_C = sizeof(cap_sensors)/sizeof(cap_sensors[0]);
//  long capRead[n_C];              // an array of same length as the number of sensors
//  cap_sense(capRead);             // update array with sensor values
//  
//  float C0ave = 0;
//  float C1ave = 0;
//  int MeasurementsToAverage = 16;
//  for(int i = 0; i < MeasurementsToAverage; ++i)
//  {
//    cap_sense(capRead);
//    C0ave += capRead[0];
//    C1ave += capRead[1];
//    delay(1);
//  }
//  C0ave /= MeasurementsToAverage;
//  C1ave /= MeasurementsToAverage;
//
//  Serial.print(capRead[0]);
//  Serial.print("\t");
//
//  Serial.print(C0ave);
//  Serial.print("\t");
//
//
//  
//  //Serial.print(C1ave);
//  //Serial.print("\t");
//
//  
//
////  for (int i = 0; i < n_C; i++){
////    Serial.print(capRead[i]);
////    Serial.print("\t");}
//}


//void filter_cap_running_average(){
//  int n_C = sizeof(cap_sensors)/sizeof(cap_sensors[0]);
//  long capRead[n_C];              // an array of same length as the number of sensors
//    cap_sense(capRead);             // update array with sensor values
//    float RawC0 = capRead[0];
//  
//    RunningAverageBuffer[NextRunningAverage++] = RawC0;
//    if (NextRunningAverage >= RunningAverageCount)
//    {
//      NextRunningAverage = 0; 
//    }
//    float RunningAveC0 = 0;
//    for(int i=0; i< RunningAverageCount; ++i)
//    {
//      RunningAveC0 += RunningAverageBuffer[i];
//    }
//    RunningAveC0 /= RunningAverageCount;
//  
//    delay(100);
//
//    Serial.print(RunningAveC0);
//    Serial.print("\t");
//    //Serial.print(capRead[0]);
//    //Serial.print("\t");
//}
//
//
//
//
//void exponential_filter(void){
//  int n_C = sizeof(cap_sensors)/sizeof(cap_sensors[0]);
//  long capRead[n_C];              // an array of same length as the number of sensors
//  cap_sense(capRead);             // update array with sensor values
//
//  // exponential filter
//  //ExpC0 += (capRead[0] - ExpC0) * weight;
//  //ExpC1 += (capRead[1] - ExpC1) * weight;
//  ExpC0 = weight * capRead[0] + (1-weight)*ExpC0;
//  ExpC1 = weight * capRead[1] + (1-weight)*ExpC1;
//
//
//  //int mapC0 = map(ExpC0, 0, 5000, 0, 255);
//  //int mapC1 = map(ExpC1, 0, 5000, 0, 255);
//  
//  //for (int m=0; m<NUM_LEDS; m++){ 
//  //LED_scaleToInput(m, 255, mapC0, mapC1);}
//
//    Serial.print(ExpC0);
//    Serial.print("\t");
//    Serial.print(ExpC1);
//    Serial.print("\t");
//}
//
//
//
//
//
//
//void filter_cap_average_array(){
//    int n_C = sizeof(cap_sensors)/sizeof(cap_sensors[0]);
//  long capRead[n_C];              // an array of same length as the number of sensors
//  cap_sense(capRead);             // update array with sensor values
//  float AverageC[n_C];
//  memset (AverageC, 0, sizeof(AverageC));
//  int MeasurementsToAverage = 16;
//  
//  for(int i = 0; i < MeasurementsToAverage; ++i){
//    cap_sense(capRead);             // update array with sensor values 
//    for (int i = 0; i < n_C; i++){    
//      AverageC[i] += capRead[i];}
//  }  
//
//  for (int i = 0; i < n_C; i++){    
//      AverageC[i] /= MeasurementsToAverage;}
//  
//  for (int i = 0; i < n_C; i++){
//    Serial.print(AverageC[i]);
//    Serial.print("\t");}
//
//  for (int i = 0; i < n_C; i++){
//    Serial.print(capRead[i]);
//    Serial.print("\t");}
//}
//
//
//
// 
