#include <FastLED.h>

#define NUM_LEDS 100
#define AVAIL 32

CRGB leds[NUM_LEDS];

// variable to hold LED integers that correspond to leds[int] and alphabet
// overlap / incorrect values because the StrangerThingsBoard isn't a full or correct alphabet
int letters[30];

// an array for the availLeds considering we are going to use every third led
int availLeds[AVAIL];

// function to set up the leds that are available
void setupAvailLeds(){
  int baseLED = 0;
  int spacing = 2;

  for(int i = 0; i < AVAIL; i ++) {
    availLeds[i] = baseLED + i + spacing;
  }
}

// arduino setup function
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, 6>(leds, NUM_LEDS);
  setupAvailLeds();
  setupLetters(); // setup our letters first
  clearLeds(); // clear the leds just in case
}

// arduino main loop function
void loop() {

  fadeInLeds();
  delay(2000);
  fadeOutLeds();
  delay(2000);
  message("ESC@P# V!$", 500);
  fadeOutLeds();
  delay(2000);


  // if we are going to have user inputted messages, the code should go here to read from the serial
  // and run the message function
}

// not sure if we want to use this function
void turnOnAllLights(){
  FastLED.clear();
  for(int led = 0; led < NUM_LEDS; led++) {
    int availInt = availLedToLed(led);
    leds[availInt] = CRGB::White;
  }
  FastLED.show();
}

void setupLetters(){
  // baseLED, if letter A does not start on the first pixel
  int baseLED = 0;

  // spacing since wire distance between leds is so small
  int spacing = 0; // zero because i believe we handled it with our availLeds

  // letter A
  letters[0] = baseLED + spacing + 0;

  // letter B
  letters[1] = baseLED + spacing + 1;

  // letter C
  letters[2] = baseLED + spacing + 12;

  // letter D
  letters[3] = baseLED + spacing + 3;

  // letter E
  letters[4] = baseLED + spacing + 14;

  // letter F
  letters[5] = baseLED + spacing + 5;

  // letter G
  letters[6] = baseLED + spacing + 6;

  // letter H
  letters[7] = baseLED + spacing + 7;

  // letter I
  letters[8] = baseLED + spacing + 16;

  // letter J
  letters[9] = baseLED + spacing + 15;

  // letter K
  letters[10] = baseLED + spacing + 14;

  // letter L
  letters[11] = baseLED + spacing + 18;

  // letter M
  letters[12] = baseLED + spacing + 12;

  // letter N
  letters[13] = baseLED + spacing + 11;

  // letter O
  letters[14] = baseLED + spacing + 2;

  // letter P
  letters[15] = baseLED + spacing + 10;

  // letter Q
  letters[16] = baseLED + spacing + 8;

  // letter R
  letters[17] = baseLED + spacing + 17;

  // letter S
  letters[18] = baseLED + spacing + 13;

  // letter T
  letters[19] = baseLED + spacing + 19;

  // letter U
  letters[20] = baseLED + spacing + 20;

  // letter V
  letters[21] = baseLED + spacing + 20;

  // letter W
  letters[22] = baseLED + spacing + 22;

  // letter X
  letters[23] = baseLED + spacing + 23;

  // letter Y
  letters[24] = baseLED + spacing + 24;

  // letter Z
  letters[25] = baseLED + spacing + 25;

  // letter A2 [@]
  letters[26] = baseLED + spacing + 11;

  // letters E2 [#]
  letters[27] = baseLED + spacing + 9;

  // letters I2 [!]
  letters[28] = baseLED + spacing + 21;

  // letters P2 [$]
  letters[29] = baseLED + spacing + 22;


}

int availLedToLed(int availInt) {
  // just in case
  if(true) {
    return availLeds[availInt];
  }

  return availInt;
}

// function to clear ALL of the LEDS
void clearLeds() {
  for(int i = 0; i < NUM_LEDS; i++){
    int availInt = availLedToLed(i);
    leds[availInt] = CRGB::Black;
  }
  FastLED.show();
}

// hopefully this method is non-blocking
void fadeOutLeds(){

  Serial.println("fading out leds...");

  int animationTime = 500;

  int startLED = 256;
  int endLED = 0;

  unsigned long start = millis();
  unsigned long delta = millis() - start;

  while(delta < animationTime) {
    float pos = float(delta) / float(animationTime);
    int ledAmount = lerp(pos, 0.0, 1.0, startLED, endLED);
    for(int i = 0; i < NUM_LEDS; i++){
      int availInt = availLedToLed(i);
      leds[availInt] = CRGB::White;
      leds[availInt].fadeToBlackBy(ledAmount);
    }
    FastLED.show();
    delta = millis() - start;
  }
}

// hopefully this method is non-blocking
void fadeInLeds(){

  Serial.println("fading in leds...");

  int animationTime = 500;

  int startLED = 0;
  int endLED = 256;

  unsigned long start = millis();
  unsigned long delta = millis() - start;

  while(delta < animationTime) {
    float pos = float(delta) / float(animationTime);
    int ledAmount = lerp(pos, 0.0, 1.0, startLED, endLED);
    for(int i = 0; i < NUM_LEDS; i++){
      int availInt = availLedToLed(i);
      leds[availInt] = CRGB::White;
      leds[availInt].fadeLightBy(ledAmount);
    }
    FastLED.show();
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
    int availInt = availLedToLed(ledInteger);
    leds[availInt] = CRGB::White;
    leds[availInt].fadeToBlackBy(ledAmount);
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
    letterInt = -1;

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

    if (letter == "@") {
      letterInt = 26;
    }

    if (letter == "#") {
      letterInt = 27;
    }

    if (letter == "!") {
      letterInt = 28;
    }

    if (letter == "$") {
      letterInt = 29;
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
