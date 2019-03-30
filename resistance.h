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
 

#define dig_switch_pin 2   // digital switch pin
#define stretch_pin A0     // voltage divider pin 
#define pressure_pin A1    // voltage divider pin 
#define Vs 3.5             // supply voltage 
#define Rs 2000000         // fixed resister 
#define Rp 2000000         // fixed resister 

bool dig_raw;

float V1;
float V2;
int V2_raw;          

float R1;
float R2;
