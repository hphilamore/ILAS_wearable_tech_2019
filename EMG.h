/* 
 Hardware setup:
 
 Myoware Muscle sensor (AT-04-001) --------- Arduino
 + -------------------------- 3.3V or 5V
 - -------------------------- GND
 SIG ------------------------ A7
 
 */
 
 # define EMG_pin A7

 int EMG;

 int EMG_min = 500;
 int EMG_max = 1000;
 
