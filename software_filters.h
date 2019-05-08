//https://martinvb.com/wp/minimalist-low-pass-filter-library/
//https://github.com/MartinBloedorn/libFilter/blob/master/filters.cpp
#include <filters.h>

// AVERAGE FILTER
float ave_filter_cap(CapacitiveSensor &C){
  // Returns the average of N readings. 
  int N = 16;
  float average;
  for(int i = 0; i < N; ++i){
    average += C.capacitiveSensor(5); // update sensor value 
  }  
  average /= N;
  return average;
}


float ave_filter_EMG(){
  // Returns the average of N readings. 
  int N = 16;
  float average;
  for(int i = 0; i < N; ++i){
    average += analogRead(EMG_pin); // update sensor value 
  }  
  average /= N;
  return average;
}



// RUNNING AVERAGE FILTER
const int BufferLength = 16;
float RunningAveBuffer[BufferLength];
int NextRunningAve;

void running_ave_filter_cap(CapacitiveSensor &C){
    // Returns the running average of RunningAveN readings. 
    
    RunningAveBuffer[NextRunningAve++] = C.capacitiveSensor(5);  // Increment buffer by one element, update sensor value
    if (NextRunningAve >= BufferLength){NextRunningAve = 0;}     // If end of buffer reached, reset position to zero

    float RunningAve; 
    for(int i=0; i< BufferLength; ++i)
    {
      RunningAve += RunningAveBuffer[i];
    }
    RunningAve /= BufferLength;
    
    delay(100);
    
    return RunningAve;
}


// LOW PASS FILTER
// frequencies > cutoff frequency are removed. 
const float cutoff_freq   = 5.0;      //Cutoff frequency in Hz
const float sampling_time = 0.005;    //Sampling time in seconds.
IIR::ORDER  order  = IIR::ORDER::OD3; // Order (OD1 to OD4)

Filter LP_filter_cap0(cutoff_freq, sampling_time, order);
Filter LP_filter_cap1(cutoff_freq, sampling_time, order);
Filter LP_filter_EMG(cutoff_freq, sampling_time, order);



// EXPONENTIAL FILTER
// weight between 0 and 1
float weightC0 = 0.1;
float weightC1 = 0.1;
float weightEMG = 0.1;
