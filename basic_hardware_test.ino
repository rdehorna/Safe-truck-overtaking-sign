#include <Adafruit_NeoPixel.h>
#include "pitches.h"
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0; 

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 4

#define NUM_LEDS 12

#define BRIGHTNESS 50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, 4);
Adafruit_NeoPixel back = Adafruit_NeoPixel(NUM_LEDS, 2);

int gamma[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };


void setup() {
  Serial.begin(115200);
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code
  strip.setBrightness(BRIGHTNESS);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  back.setBrightness(BRIGHTNESS);
  back.begin();
  back.show(); // Initialize all pixels to 'off'
  //tone
//  for (int thisNote = 0; thisNote < 8; thisNote++) {
//
//    // to calculate the note duration, take one second
//    // divided by the note type.
//    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//    int noteDuration = 1000 / noteDurations[thisNote];
//    tone(3, melody[thisNote], noteDuration);
//
//    // to distinguish the notes, set a minimum time between them.
//    // the note's duration + 30% seems to work well:
//    int pauseBetweenNotes = noteDuration * 1.30;
//    delay(pauseBetweenNotes);
//    // stop the tone playing:
//    noTone(3);
//  }

  myservo.attach(9);
  
//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
  //whiteOverRainbow(20,75,5);

    // line sensor
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A6, INPUT);

  //distance sensor
    pinMode(A7, INPUT);
    //right
//     pinMode(8, OUTPUT);
//     pinMode(10, OUTPUT);
//     digitalWrite(8, HIGH);
//     digitalWrite(10, LOW);
//
//    //left
//     pinMode(11, OUTPUT);
//     pinMode(12, OUTPUT);
//     digitalWrite(11, HIGH);
//     digitalWrite(12, LOW);

doDimLight(true);
}

void loop() {
  int zero =  analogRead(0);
  int uno =  analogRead(1);
  int due =   analogRead(2);
  int tre =  analogRead(3);
  int quatro =  analogRead(6);
  int distance  =  analogRead(6);
  doDimLight(distance); // map(distance, 0, 1023, 0, 1)
  fillCircle( map(distance, 0, 1023, 1, 12));
  delay(200);
  

  Serial.println("zero");
  Serial.println(zero);
  Serial.println("uno");
    Serial.println(uno);

  Serial.println("due");
    Serial.println(due);

  Serial.println("tre");
    Serial.println(tre);
  
  Serial.println("quatro");
  Serial.println(quatro);
  Serial.println();
  

}
//  setBackTo(false);
//   myservo.write(70);
//   delay(2000);
// setBackTo(true);
//   myservo.write(100);
//  delay(2000);

//int val = analogRead(6);
//  pos = map(val, 0, 170, 0, 255);
//  myservo.write(val);
//  delay(100);
void fillCircle(int amount){
  strip.clear();
  for(uint16_t i=0; i<amount; i++) {
    strip.setPixelColor(i, 63, 136, 143);//63, 136, 143
  }
  strip.show();
}
// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, 63, 136, 143);//63, 136, 143
    strip.show();
    delay(wait);
  }
}

void doDimLight(int shouldDo) {
  if(shouldDo > 400){
    for(uint16_t i=0; i<back.numPixels(); i++) {
      back.setPixelColor(i, 255, 0, 0);
    }
     myservo.write(100);
  } else {
    back.clear();
    myservo.write(70);
  }
  back.show();
}

