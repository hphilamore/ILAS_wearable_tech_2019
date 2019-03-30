 /* 
 
 Hardware setup:
 Neopixel strip --------- Arduino
 LED strip input --------- 6
 VDD --------------------- 3.3V
 GND --------------------- GND

 */
 
 #include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define NUM_LEDS 20
#define BRIGHTNESS 100 

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

long LED_timer = millis();
int LED_pixel = 0;
