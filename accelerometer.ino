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
 
 void acc_sense(){
  // If intPin goes high, all data registers have new data
  // On interrupt, check if data ready interrupt
  if (myIMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
  {  
    myIMU.readAccelData(myIMU.accelCount);  // Read the x/y/z adc values
    myIMU.getAres();

    // Now we'll calculate the accleration value into actual g's
    // This depends on scale being set
    myIMU.ax = (float)myIMU.accelCount[0]*myIMU.aRes; // - accelBias[0];
    myIMU.ay = (float)myIMU.accelCount[1]*myIMU.aRes; // - accelBias[1];
    myIMU.az = (float)myIMU.accelCount[2]*myIMU.aRes; // - accelBias[2];

    myIMU.readGyroData(myIMU.gyroCount);  // Read the x/y/z adc values
    myIMU.getGres();

    // Calculate the gyro value into actual degrees per second
    // This depends on scale being set
    myIMU.gx = (float)myIMU.gyroCount[0]*myIMU.gRes;
    myIMU.gy = (float)myIMU.gyroCount[1]*myIMU.gRes;
    myIMU.gz = (float)myIMU.gyroCount[2]*myIMU.gRes;

    myIMU.readMagData(myIMU.magCount);  // Read the x/y/z adc values
    myIMU.getMres();
    // User environmental x-axis correction in milliGauss, should be
    // automatically calculated
    myIMU.magbias[0] = +470.;
    // User environmental x-axis correction in milliGauss TODO axis??
    myIMU.magbias[1] = +120.;
    // User environmental x-axis correction in milliGauss
    myIMU.magbias[2] = +125.;

    // Calculate the magnetometer values in milliGauss
    // Include factory calibration per data sheet and user environmental corrections
    // Get actual magnetometer value, this depends on scale being set
    myIMU.mx = (float)myIMU.magCount[0]*myIMU.mRes*myIMU.magCalibration[0] -
               myIMU.magbias[0];
    myIMU.my = (float)myIMU.magCount[1]*myIMU.mRes*myIMU.magCalibration[1] -
               myIMU.magbias[1];
    myIMU.mz = (float)myIMU.magCount[2]*myIMU.mRes*myIMU.magCalibration[2] -
               myIMU.magbias[2];
  } // if (readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)

  // Must be called before updating quaternions!
  myIMU.updateTime();

  // Sensors x (y)-axis of the accelerometer is aligned with the y (x)-axis of
  // the magnetometer; the magnetometer z-axis (+ down) is opposite to z-axis
  // (+ up) of accelerometer and gyro! We have to make some allowance for this
  // orientationmismatch in feeding the output to the quaternion filter. For the
  // MPU-9250, we have chosen a magnetic rotation that keeps the sensor forward
  // along the x-axis just like in the LSM9DS0 sensor. This rotation can be
  // modified to allow any convenient orientation convention. This is ok by
  // aircraft orientation standards! Pass gyro rate as rad/s
//  MadgwickQuaternionUpdate(ax, ay, az, gx*PI/180.0f, gy*PI/180.0f, gz*PI/180.0f,  my,  mx, mz);
  MahonyQuaternionUpdate(myIMU.ax, myIMU.ay, myIMU.az, myIMU.gx*DEG_TO_RAD,
                         myIMU.gy*DEG_TO_RAD, myIMU.gz*DEG_TO_RAD, myIMU.my,
                         myIMU.mx, myIMU.mz, myIMU.deltat);


    myIMU.delt_t = millis() - myIMU.count;
    if (myIMU.delt_t > 200)
    {

//        // Print acceleration values in milligs!
//        Serial.print("X-acceleration: "); Serial.print(1000*myIMU.ax);
//        Serial.print(" mg ");
//        Serial.print("Y-acceleration: "); Serial.print(1000*myIMU.ay);
//        Serial.print(" mg ");
//        Serial.print("Z-acceleration: "); Serial.print(1000*myIMU.az);
//        Serial.println(" mg ");
//        Serial.println("  ");
//        
//
//        // Print gyro values in degree/sec
//        Serial.print("X-gyro rate: "); Serial.print(myIMU.gx, 3);
//        Serial.print(" degrees/sec ");
//        Serial.print("Y-gyro rate: "); Serial.print(myIMU.gy, 3);
//        Serial.print(" degrees/sec ");
//        Serial.print("Z-gyro rate: "); Serial.print(myIMU.gz, 3);
//        Serial.println(" degrees/sec");
//        Serial.println("  ");

        // Acceleration values in Gs!
        acceleration[x] = myIMU.ax;
        acceleration[y] = myIMU.ay;
        acceleration[z] = myIMU.az;
        
        // Gyro values in degree/sec
        gyro[x] = myIMU.gx;
        gyro[y] = myIMU.gy;
        gyro[z] = myIMU.gz;

        myIMU.tempCount = myIMU.readTempData();  // Read the adc values
        // Temperature in degrees Centigrade
        temperature_C = myIMU.temperature = ((float) myIMU.tempCount) / 333.87 + 21.0;
        // Temperature in degrees Centigrade
        //temperature_C = (myIMU.temperature, 1);
        //Serial.print("Temperature is ");  Serial.print(myIMU.temperature, 1);
        //Serial.println(" degrees C");
        //Serial.println("  ");




      myIMU.count = millis();

    } // if (myIMU.delt_t > 500)
}


float acc_magnitude_3D(){
  /*
  Returns the magnitude of the 3D acceleration vector 
  */
 
  float M = sqrt(sq(acceleration[x]) + 
            sq(acceleration[y]) + 
            sq(acceleration[z])
           );

  return M;
}



void acc_step_counter(){
  /*
  Sums the number of steps taken. 
  Flashes an LED when a step is logged.
  */

  float M = acc_magnitude_3D();

  // if the magnitude is greater than the threshold and the flag is down...
  if (M>step_threshold && flag==0){
      
      steps=steps+1;      // ...count a setp
 
      flag=1;             // ...raise the flag


      
      /*
      // Flash an LED every time step counted
      if( LED ){
        for (int m=0; m<NUM_LEDS; m++){ 
          LED_scaleToInput(m, 255, 0, 0);}
        strip.show();
        delay(100);
        for (int m=0; m<NUM_LEDS; m++){ 
          LED_scaleToInput(m, 0, 0, 0);}
        strip.show();
      }
      */
      
 }
    


  // if the flag is up, the step has already been counted 
  else if (M>step_threshold && flag==1)
    {
      // do nothing
    }


  // if the magnitude is less than the threshold and the flag is up, put the flag down
  else if (M<step_threshold  && flag==1)
  {   
    flag=0;         
  }
}




void acc_pace(){
  /*
  Calculates the average pace (steps / time second)
  Lights an LED if the pace drops below a threshold value
  */

  float paceAve;

  // if time since last measurement exceeds period, calculate pace
  if ((millis() - startTime) > pace_period){     
     endTime = millis();
     paceAve = 1000 * (steps - stepsOld) / float(endTime - startTime);
     stepsOld = steps;
     startTime = millis(); 

     // if the pace falls below a threshold, turn LED on
     if (paceAve < pace_threshold){     
        for (int m=0; m<NUM_LEDS; m++){ 
          LED_white(m);}
        strip.show();
     }
  
     // otherwise turn it off
     else{                
        for (int m=0; m<NUM_LEDS; m++){ 
          LED_off(m);}
        strip.show();
     }
     
   } 
}


void acc_print(){  
  for (int i = 0; i < 3; i++){
    Serial.print(acceleration[i]);
    Serial.print("\t");
  }
}

void gyr_print(){  
  for (int i = 0; i < 3; i++){
    Serial.print(gyro[i]);
    Serial.print("\t");
  }
}

void acc_setup(){
  // Read the WHO_AM_I register, this is a good test of communication
    byte c = myIMU.readByte(MPU9250_ADDRESS, WHO_AM_I_MPU9250);
    //Serial.print("MPU9250 "); Serial.print("I AM "); Serial.print(c, HEX);
    //Serial.print(" I should be "); Serial.println(0x73, HEX);

    // Calibrate gyro and accelerometers, load biases in bias registers
    myIMU.calibrateMPU9250(myIMU.gyroBias, myIMU.accelBias);

    myIMU.initMPU9250();
    //Serial.println("MPU9250 initialized for active data mode....");

    // Read the WHO_AM_I register of the magnetometer, this is a good test of communication
    byte d = myIMU.readByte(AK8963_ADDRESS, WHO_AM_I_AK8963);
    //Serial.print("AK8963 "); Serial.print("I AM "); Serial.print(d, HEX);
    //Serial.print(" I should be "); Serial.println(0x48, HEX);

    // Get magnetometer calibration from AK8963 ROM
    myIMU.initAK8963(myIMU.magCalibration);
}
