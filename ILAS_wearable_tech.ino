#include "Wire.h"
#include "resistance.h"
#include "capacitance.h"
#include "accelerometer.h"
#include "LED.h"
#include "vib_motor.h"
//#include "buzzer.h"
#include "servo.h"
#include "EMG.h"
//#include "Filters.h" 

unsigned long time_ms;

#include "filters.h"
 
//const float cutoff_freq   = 20.0;  //Cutoff frequency in Hz
//const float sampling_time = 0.005; //Sampling time in seconds.
//IIR::ORDER  order  = IIR::ORDER::OD3; // Order (OD1 to OD4)
// 
// Low-pass filter
//Filter f(cutoff_freq, sampling_time, order);

//Filter LPfilter(cutoff_freq, sampling_time, order);

//#define resistance_sensor false
//#define capacitance_sensor false
//#define accelerometer false
//#define LED false
//#define vib_motor false
//#define buzzer false
//#define servo true
//#define EMG true

//// Variables used to map input scale to output scale 
//int Vin_min = 60;     // the minimum read value
//int Vin_max = 120;   // the maximum read value 
//int Vout_min = 0;     // the minimum write value 
//int Vout_max = 255;   // the maximum write value 
//
//// running average filter variables
//const int RunningAverageCount = 16;
//float RunningAverageBuffer[RunningAverageCount];
//int NextRunningAverage;
//
//// exponential filter variables
//float ExpEMG = 0;
//float ExpC0 = 0;
//float ExpC1 = 1;
//float weight = 0.1;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  res_setup();
  //acc_setup();
  //LED_setup();
  //vib_motor_setup();
  //servo_setup();
}

void loop() {

  // Time
  time_ms = millis();
  //Serial.print( time_ms );
  //Serial.print("\t");

  // Digital Switch
  bool d_switch = res_dig_switch();
  //Serial.print( d_switch );
  //Serial.print("\t");

  // Stretch sensor
  float stretch = res_stretch();
  //Serial.print( stretch );
  //Serial.print("\t");

  // Pressure sensor
  float pressure = res_pressure();
  //Serial.print( pressure );
  //Serial.print("\t");

  // Capacitive sensor
  cap_sense0 = C0.capacitiveSensor(5);
  cap_sense1 = C1.capacitiveSensor(5);
  //Serial.print( cap_sense0 );
  //Serial.print("\t");
  //Serial.print( cap_sense1 );
  //Serial.print("\t");

  // Filtered Capacitive sensor

  // EMG 
  EMG = analogRead(EMG_pin);
  Serial.print( EMG );
  Serial.print( "\t" );
  //ExpEMG = weight * V2_raw + (1-weight)*ExpEMG;

  // Filtered EMG


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

//float LP_filter(){
//  // Applies the filter given as input to the raw data input and returns the filtered value.
//  
//  //LP_filter = Filter(cutoff_freq, sampling_time, order);
//  float filtered_val = LPfilter.filterIn(raw_val);
//  return filtered_val;
//}
