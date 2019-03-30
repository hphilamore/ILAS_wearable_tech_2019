
 /*
 * 
 * Hardware setup: 
 * Capacitive sensors --------- Arduino
 * 
 *  Pin D7 [Send]
 *      |
 * ----------
 * |        |            
 * 1Mohm    1Mohm       
 * |        |        
 * |        |        
 * sensor   sensor   
 * |        |        
 * |        |           
 * PinD11    PinD10  [Receive]
 * 
 * 
 * 
 */

#include <CapacitiveSensor.h>

CapacitiveSensor C0 = CapacitiveSensor(7,11);
CapacitiveSensor C1 = CapacitiveSensor(7,10);

long cap_sense0;
long cap_sense1;
