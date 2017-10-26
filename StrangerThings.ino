#include <bitswap.h>
#include <chipsets.h>
#include <color.h>
#include <colorpalettes.h>
#include <colorutils.h>
#include <controller.h>
#include <cpp_compat.h>
#include <dmx.h>
#include <FastLED.h>
#include <fastled_config.h>
#include <fastled_delay.h>
#include <fastled_progmem.h>
#include <fastpin.h>
#include <fastspi.h>
#include <fastspi_bitbang.h>
#include <fastspi_dma.h>
#include <fastspi_nop.h>
#include <fastspi_ref.h>
#include <fastspi_types.h>
#include <hsv2rgb.h>
#include <led_sysdefs.h>
#include <lib8tion.h>
#include <noise.h>
#include <pixelset.h>
#include <pixeltypes.h>
#include <platforms.h>
#include <power_mgt.h>

#define NUM_LEDS 60
CRGB leds[NUM_LEDS];

// variable to hold LED integers that correspond to leds[int] and alphabet
int letters[26];

// arduino setup function
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  setupLetters(); // setup our letters first
  clearLeds(); // clear the leds just in case
}

// arduino main loop function
void loop() {
  message("I WILL KILL YOU", 1000);
  delay(1000);
  message("I WANT BRAINS DAMMIT", 1000);
  delay(1000);

  // if we are going to have user inputted messages, the code should go here to read from the serial
  // and run the message function
}

void setupLetters(){
  // baseLED, if letter A does not start on the first pixel
  int baseLED = 0;

  // letter A
  letters[0] = baseLED + 0;

  // letter B
  letters[1] = baseLED + 1;

  // letter C
  letters[2] = baseLED + 2;

  // letter D
  letters[3] = baseLED + 3;

  // letter E
  letters[4] = baseLED + 4;

  // letter F
  letters[5] = baseLED + 5;

  // letter G
  letters[6] = baseLED + 6;

  // letter H
  letters[7] = baseLED + 7;

  // letter I
  letters[8] = baseLED + 16;

  // letter J
  letters[9] = baseLED + 15;

  // letter K
  letters[10] = baseLED + 14;

  // letter L
  letters[11] = baseLED + 13;

  // letter M
  letters[12] = baseLED + 12;

  // letter N
  letters[13] = baseLED + 11;

  // letter O
  letters[14] = baseLED + 10;

  // letter P
  letters[15] = baseLED + 9;

  // letter Q
  letters[16] = baseLED + 8;

  // letter R
  letters[17] = baseLED + 17;

  // letter S
  letters[18] = baseLED + 18;

  // letter T
  letters[19] = baseLED + 19;

  // letter U
  letters[20] = baseLED + 20;

  // letter V
  letters[21] = baseLED + 21;

  // letter W
  letters[22] = baseLED + 22;

  // letter X
  letters[23] = baseLED + 23;

  // letter Y
  letters[24] = baseLED + 24;

  // letter Z
  letters[25] = baseLED + 25;

}

// function to clear ALL of the LEDS
void clearLeds() {
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
    FastLED.show();
  }
}

// hopefully this method is non-blocking 
void fadeOutLeds(){

  int animationTime = 500;

  int startLED = 256;
  int endLED = 0;

  unsigned long start = millis();
  unsigned long delta = millis() - start;

  while(delta < animationTime) {
    float pos = float(delta) / float(animationTime);
    int ledAmount = lerp(pos, 0.0, 1.0, startLED, endLED);
    for(int i = 0; i < NUM_LEDS; i++){
      leds[i].fadeToBlackBy(ledAmount);
    }
    delta = millis() - start;
  }


}

// linear interpolation function
float lerp(float x, float x0, float x1, float y0, float y1) {
  // clamp
  x = x > x1 ? x1 : x;
  x = x < x0 ? x0 : x;

  // calculate linear interpolation
  return y0 + (y1 - y0) * ((x-x0) / (x1-x0));
}

// function to fade a led in or out using linear interpolation
void animateLED(String dir, int ledInteger, int animationTime) {
  int startLED = 0;
  int endLED = 256;

  if (dir.equals("in")) {
    startLED = 0;
    endLED = 256;
  }

  if (dir.equals("out")) {
    startLED = 256;
    endLED = 0;
  }

  unsigned long start = millis();
  unsigned long delta = millis() - start;

  while(delta < animationTime) {
    float pos = float(delta) / float(animationTime);
    int ledAmount = (int)lerp(pos, 0.0, 1.0, startLED, endLED);
    leds[ledInteger].fadeToBlackBy(ledAmount);
    FastLED.show();
    delta = millis() - start;
  }
}

// function that turns on the LED corresponding to each letter of the message sent
void message(String words, int delayLength) {

  String ucWords = words;
  ucWords.toUpperCase(); // make them all uppercase for consistency

  int letterInt = -1;

  for(int i = 0; i < ucWords.length(); i++){
    String letter = (String)ucWords.charAt(i);
    if (letter == "A") {
       letterInt = 0;
    }
    
    if (letter == "B") {
       letterInt = 1;
    }
    
    if (letter == "C") {
       letterInt = 2;
    }
    
    if (letter == "D") {
       letterInt = 3;
    }
    
    if (letter == "E") {
       letterInt = 4;
    }
    
    if (letter == "F") {
       letterInt = 5;
    }
    
    if (letter == "G") {
       letterInt = 6;
    }
    
    if (letter == "H") {
       letterInt = 7;
    }
    
    if (letter == "I") {
       letterInt = 8;
    }
    
    if (letter == "J") {
       letterInt = 9;
    }
    
    if (letter == "K") {
       letterInt = 10;
    }
    
    if (letter == "L") {
       letterInt = 11;
    }
    
    if (letter == "M") {
       letterInt = 12;
    }
    
    if (letter == "N") {
       letterInt = 13;
    }
    
    if (letter == "O") {
       letterInt = 14;
    }
    
    if (letter == "P") {
       letterInt = 15;
    }
    
    if (letter == "Q") {
       letterInt = 16;
    }
    
    if (letter == "R") {
       letterInt = 17;
    }
    
    if (letter == "S") {
       letterInt = 18;
    }
    
    if (letter == "T") {
       letterInt = 19;
    }
    
    if (letter == "U") {
       letterInt = 20;
    }
    
    if (letter == "V") {
       letterInt = 21;
    }
    
    if (letter == "W") {
       letterInt = 22;
    }
    
    if (letter == "X") {
       letterInt = 23;
    }
    
    if (letter == "Y") {
       letterInt = 24;
    }
    
    if (letter == "Z") {
       letterInt = 25;
    }



    // before we show the LED we should clear the leds
    clearLeds();

    // test if the letterInt is valid before we try and send it to FastLED
    if(letterInt >= 0 && letterInt <= NUM_LEDS - 1){
      //leds[letterInt] = CRGB::White;
      //FastLED.show();
      animateLED("in", letters[letterInt], 600);  // this should fade in the letter over 600ms
      delay(delayLength); // we will delay each char of a word by delayLength
      Serial.print("SHOWING LETTER -");
      Serial.println(letter);
      Serial.println("");
      
    }

    if(letterInt < 0){
      delay(delayLength * 2); // we will delay spaces, commas, and other non-alphas with double the delayLength
    }

  }

}
