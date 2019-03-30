 /* 
 
 /*
 * Hardware setup:
 * Vibrating motor -------- Arduino
 * 
 * |----Vs (e.g. 3.3V)
 * |
 * | 
 * | DC vibrating motor
 * |
 * |
 * |----collector 
 * |              
 * |---- base ------- Pin 5      
 * |              
 * |----emitter   
 * |
 * | 
 * |
 * |----GND
 */



void vib_motor_setup(){
   pinMode(vib_motor_pin, OUTPUT);
}
