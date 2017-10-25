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

int letters[26];

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LEDS);
  setupLetters();
  clearLeds();
}

void loop() {
  message("I WILL KILL YOU", 1000);
  delay(1000);
  message("I WANT BRIANS DAMMIT", 1000);
  delay(1000);
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

void clearLeds() {
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(5);
  }
}

void message(String words, int delayLength) {
  String ucWords = words.toUpperCase();
  
  int letterInt = -1;
  
  for(int i = 0; i < ucWords.length; i++){
    String letter = ucWords[i];
    switch(letter){
      case "A":
        letterInt = 0;
      break;
      
      case "B":
        letterInt = 1;
      break;
      
      case "C":
        letterInt = 2;
      break;
      
      case "D":
        letterInt = 3;
      break;
      
      case "E":
        letterInt = 4;
      break;
      
      case "F":
        letterInt = 5;
      break;
      
      case "G":
        letterInt = 6;
      break;
      
      case "H":
        letterInt = 7;
      break;
      
      case "I":
        letterInt = 8;
      break;
      
      case "J":
        letterInt = 9;
      break;
      
      case "K":
        letterInt = 10;
      break;
      
      case "L":
        letterInt = 11;
      break;
      
      case "M":
        letterInt = 12;
      break;
      
      case "N":
        letterInt = 13;
      break;
      
      case "O":
        letterInt = 14;
      break;
      
      case "P":
        letterInt = 15;
      break;
      
      case "Q":
        letterInt = 16;
      break;
      
      case "R":
        letterInt = 17;
      break;
      
      case "S":
        letterInt = 18;
      break;
      
      case "T":
        letterInt = 19;
      break;
      
      case "U":
        letterInt = 20;
      break;
      
      case "V":
        letterInt = 21;
      break;
      
      case "W":
        letterInt = 22;
      break;
      
      case "X":
        letterInt = 23;
      break;
      
      case "Y":
        letterInt = 24;
      break;
      
      case "Z":
        letterInt = 25;
      break;

      // for spaces or other
      default:
        letterInt = -2;
      break;
    }

    clearLeds();
    
    if(letterInt >= 0 && letterInt <= NUM_LEDS - 1){
      leds[letterInt] = CRGB::White; 
      FastLED.show();
      delay(delayLength);
    }

    if(letterInt < 0){
      delay(delayLength * 2);
    }
    
  }
  
}


