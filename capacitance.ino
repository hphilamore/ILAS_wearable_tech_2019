
//void cap_sense(long * capRead){
//  
//  // Loads the array given as input with the sensed value on each input.
//  int n_capsense = sizeof(cap_sensors)/sizeof(cap_sensors[0]);  
//  for (int i = 0; i < n_capsense; i++) {  
//    capRead[i] =  cap_sensors[i].capacitiveSensor(5);
//  }  
//}


//void cap_print(){
//  int n_C = sizeof(cap_sensors)/sizeof(cap_sensors[0]);
//    long capRead[n_C];              // an array of same length as the number of sensors
//    cap_sense(capRead);             // update array with sensor values   
//    for (int i = 0; i < n_C; i++){
//      Serial.print(capRead[i]);
//      Serial.print("\t");
//    }
//    Serial.println("");
//}
