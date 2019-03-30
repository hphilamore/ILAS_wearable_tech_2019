void LED_setup(){
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void LED_green(int n){
   // pixel n colour is GRB (255, 0, 0)
   strip.setPixelColor(n, 255, 0, 0);
   strip.show();
}


void LED_red(int n){
  // pixel n colour is GRB (0, 255, 0)
  strip.setPixelColor(n, 0, 255, 0);
  strip.show();
}


void LED_blue(int n){
  // pixel n colour is GRB (0, 0, 255)
  strip.setPixelColor(n, 0, 0, 255);
  strip.show();
}


void LED_white(int n){
  // pixel n colour is GRB (255, 255, 255)
  strip.setPixelColor(n, 255, 255, 255);
  strip.show();
}


void LED_off(int n){
  // pixel n colour is GRB (0, 0, 0)
   strip.setPixelColor(n, 0, 0, 0);
   strip.show();
}


void LED_myCol(int n){
    uint32_t my_col = strip.Color(0, 255, 255); //magenta
    //uint32_t my_col = strip.Color(64, 0, 100);   //light green
    strip.setPixelColor(n, my_col);
    strip.show();
}

  
void LED_scaleToInput(int pixel, int c1, int c2, int c3){
  // pixel n colour is GRB (i, j, k)
  strip.setPixelColor(pixel, c1, c2, c3);
  strip.show();
}


void LED_fade_in(){
  for (int i=0; i<256; i++)
  {  
    for (int j=0; j<NUM_LEDS; j++){
      strip.setPixelColor(j, i , i , i);
    }
    strip.show();
    delay(50);
  }
}


void LED_fade_out(){
for (int i=255; i>0; i--)
  {  
    for (int j=0; j<NUM_LEDS; j++){
      strip.setPixelColor(j, i , i , i);
    }
    strip.show();
    delay(50);
  }
}


void colorLevel(uint32_t c, int pixels) {
  // Fill the pixels one after the other with a color
  // e.g. colorLevel(strip.Color(0, 255, 0), 50);
  //int mapC1 = map(ExpC1, 0, 100, 0, strip.numPixels()-1);
  for(uint16_t i=0; i<pixels; i++) {
    strip.setPixelColor(i, c);}
  strip.show();
  delay(50);

  // reset all pixels to black
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));}
}


void colorWipe(uint32_t c, long wait) {
  // Fill the pixels one after the other with a color
  // e.g. colorWipe(strip.Color(0, 255, 0), 50);
  if(millis() - LED_timer > wait){
    strip.setPixelColor(LED_pixel, c);
    LED_timer = millis();
    if(LED_pixel < NUM_LEDS){
      LED_pixel += 1;
    }
    else{
      LED_pixel = 0;
      for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, (0, 255, 0));}
    }
    strip.show();
  }
  
}


void LED_cycle_cols_uniform(){
  unsigned int colours[3];
  
  // Start with red.
  colours[0] = 255;
  colours[1] = 0;
  colours[2] = 0;  
  
  
  for (int C1 = 0; C1 < 3; C1 += 1) 
    {
        // If (C1 == 2), C2 = 0. Otherwise C2 = C1 + 1  
        int C2 = (C1 == 2) ? 0 : C1 + 1;
  
        // Cross fade two colours
        for(int i = 0; i < 255; i ++) 
        {
          colours[C1] -= 1;
          colours[C2] += 1;  
          for (int j=0; j<NUM_LEDS; j++){    
            strip.setPixelColor(j, colours[0] , colours[1] , colours[2]);
          }
          strip.show();
          delay(10);
        }
    }
}


//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  //e.g. theaterChase(strip.Color(127, 127, 127), 50); // White
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}



//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  // e.g. theaterChaseRainbow(50);
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}


void rainbowFade2White(uint8_t wait, int rainbowLoops, int whiteLoops) {
  // e.g. rainbowFade2White(3,3,1);
  float fadeMax = 100.0;
  int fadeVal = 0;
  uint32_t wheelVal;
  int redVal, greenVal, blueVal;

  for(int k = 0 ; k < rainbowLoops ; k ++){
    
    for(int j=0; j<256; j++) { // 5 cycles of all colors on wheel

      for(int i=0; i< strip.numPixels(); i++) {

        wheelVal = Wheel(((i * 256 / strip.numPixels()) + j) & 255);

        redVal = red(wheelVal) * float(fadeVal/fadeMax);
        greenVal = green(wheelVal) * float(fadeVal/fadeMax);
        blueVal = blue(wheelVal) * float(fadeVal/fadeMax);

        strip.setPixelColor( i, strip.Color( redVal, greenVal, blueVal ) );

      }

      //First loop, fade in!
      if(k == 0 && fadeVal < fadeMax-1) {
          fadeVal++;
      }

      //Last loop, fade out!
      else if(k == rainbowLoops - 1 && j > 255 - fadeMax ){
          fadeVal--;
      }

        strip.show();
        delay(wait);
    }
  
  }



  delay(500);


  for(int k = 0 ; k < whiteLoops ; k ++){

    for(int j = 0; j < 256 ; j++){

        for(uint16_t i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0,0,0) );
          }
          strip.show();
        }

        delay(2000);
    for(int j = 255; j >= 0 ; j--){

        for(uint16_t i=0; i < strip.numPixels(); i++) {
            strip.setPixelColor(i, strip.Color(0,0,0) );
          }
          strip.show();
        }
  }

  delay(500);


}

void whiteOverRainbow(uint8_t wait, uint8_t whiteSpeed, uint8_t whiteLength ) {
  
  if(whiteLength >= strip.numPixels()) whiteLength = strip.numPixels() - 1;

  int head = whiteLength - 1;
  int tail = 0;

  int loops = 3;
  int loopNum = 0;

  static unsigned long lastTime = 0;


  while(true){
    for(int j=0; j<256; j++) {
      for(uint16_t i=0; i<strip.numPixels(); i++) {
        if((i >= tail && i <= head) || (tail > head && i >= tail) || (tail > head && i <= head) ){
          strip.setPixelColor(i, strip.Color(0,0,0, 255 ) );
        }
        else{
          strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
        
      }

      if(millis() - lastTime > whiteSpeed) {
        head++;
        tail++;
        if(head == strip.numPixels()){
          loopNum++;
        }
        lastTime = millis();
      }

      if(loopNum == loops) return;
    
      head%=strip.numPixels();
      tail%=strip.numPixels();
        strip.show();
        delay(wait);
    }
  }
  
}
void fullWhite() {
  
    for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, strip.Color(0,0,0, 255 ) );
    }
      strip.show();
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256 * 5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3,0);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3,0);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0,0);
}

uint8_t red(uint32_t c) {
  return (c >> 8);
}
uint8_t green(uint32_t c) {
  return (c >> 16);
}
uint8_t blue(uint32_t c) {
  return (c);
}
