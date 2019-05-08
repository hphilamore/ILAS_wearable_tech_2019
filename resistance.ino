 /*
 * Hardware setup: Digital switch
 * 
 * |----Pin D2 (Internal pull-up resister)
 * |
 * |----Conductive pad A
 * |
 * // (switch closed when conductive pads A and B touch)
 * |
 * |----Conductive pad B
 * |
 * |---- GND
 */

 
 
 /*
 * Hardware setup: Stretch sensor
 * 
 * |----Vs (e.g. 5V)
 * |
 * | R1 (rubber cord)
 * |
 * |----Pin A0
 * |
 * | R2 (Rs = fixed)
 * |
 * |---- GND
 */

 float res_stretch(){
  // Calculates V2 (voltage measured across R2)
  R2 = Rs;
  V2_raw  = analogRead( stretch_pin );   // measured value, range 0 to 1023 
  R1 =  (1023 - V2_raw) * R2 / V2_raw;   // R1 (Ohms) calculated from equation of voltage divider 
  return R1;
}


/*
 * Hardware setup: Pressure sensor
 * 
 * |----Vs (e.g. 5V)
 * |
 * | R1 (pressure sensitive fabric)
 * |
 * |----Pin A1
 * |
 * | R2 (Rp = fixed)
 * |
 * |---- GND
 */
 
 float res_pressure(){
  // Calculates V2 (voltage measured across R2)
  R2 = Rp;
  V2_raw  = analogRead( pressure_pin );   // measured value, range 0 to 1023  
  R1 =  (1023 - V2_raw) * R2 / V2_raw;    // R1 (Ohms) calculated from equation of voltage divider 
  return R1;
}

//float res_resistivity(float R){
//  // Calculates resistivity of material that forms R1 (Ohms/cm)
//  int r = R / dist;
//  return r;           
//  
//}


//int res_digital_switch(){
//  // Outputs high or low voltage on probe
//  int V2_switch  = digitalRead(probe_pin);      // voltage on voltage divider pin read as binary value (range 0 to 1023)   
//  return V2_switch;
//}


void res_setup(){
  pinMode(dig_switch_pin, INPUT_PULLUP);
  pinMode(stretch_pin, INPUT);
  pinMode(pressure_pin, INPUT);
  //pinMode(LED_pin, OUTPUT);
}
