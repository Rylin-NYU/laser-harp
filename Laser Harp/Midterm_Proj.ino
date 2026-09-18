/*Project Title: Laser Harp
 *Authors: Ryan Lin and Anastasia Slyusar
 *Date: 3/11/2026
 */
#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"
#include <FastLED.h>

#define NUM_LEDS 20 // How many leds on your strip?
#define DATA_PIN 3
CRGB leds[NUM_LEDS];
SoftwareSerial mySerial(8, 9); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int val;
int file = 1;
int folder = 1;
int state = 0;

int LDRValue1, LDRValue2, LDRValue3, LDRValue4, LDRValue5, LDRValue6;

bool isPlaying = false;
int currentFile = -1;   // tracks what file is currently playing
//arcade button
const int button = 2;

bool lastButton = HIGH;  // previous button state

void setup() {
  //Led startup
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(60); 
  pinMode(9, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  mySerial.begin(9600);
  delay(1000);
  
  //DFPlayer Mini startup
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println("Unable to begin:");
    Serial.println("1. Please recheck the connection!");
    Serial.println("2. Please insert the SD card!");
    while (true);
    
  }

  myDFPlayer.volume(60);
}

void loop() {
  //button code to switch instrument 
  bool buttonState = digitalRead(button);

  if (buttonState == LOW && lastButton == HIGH) {
    state = (state + 1) % 3;   // cycles 0 → 1 → 2 → 0

  if (state == 0) {
    folder = 1;
    Serial.println("Piano");
    }
  else if (state == 1) {
    folder = 2;
    Serial.println("Violin");
    }
  else if (state == 2) {
    folder = 3;
    Serial.println("Guitar");
    }

  currentFile = -1;
  }  
  lastButton = buttonState;
  
  digitalWrite(9, HIGH);

  // Read all LDRs
  LDRValue1 = analogRead(A0);
  LDRValue2 = analogRead(A1);
  LDRValue3 = analogRead(A2);
  LDRValue4 = analogRead(A3);
  LDRValue5 = analogRead(A4);
  LDRValue6 = analogRead(A5);
//  Serial.print(LDRValue1); Serial.print(" ");
//  Serial.print(LDRValue2); Serial.print(" ");
//  Serial.print(LDRValue3); Serial.print(" ");
//  Serial.print(LDRValue4); Serial.print(" ");
//  Serial.print(LDRValue5); Serial.print(" ");
//  Serial.println(LDRValue6);
  delay(100);
  int newFile = -1;

  //in the absence of light (laser) the corresponding Leds 
  //as well as the music note will play
  if (LDRValue1 <= 920) {
    newFile = 1;
    
    leds[19] = CRGB(random(255),random(255), random(255));
    leds[18] = CRGB(random(255),random(255), random(255));
    leds[17] = CRGB(random(255),random(255), random(255));

  } else {
    leds[19] = CRGB::Black;
    leds[18] = CRGB::Black;
    leds[17] = CRGB::Black;
  }
  if (LDRValue2 <= 920) {
    newFile = 2;
    leds[16] = CRGB(random(255),random(255), random(255));
    leds[15] = CRGB(random(255),random(255), random(255));
    leds[14] = CRGB(random(255),random(255), random(255));
  } else{
    leds[16] = CRGB::Black;
    leds[15] = CRGB::Black;
    leds[14] = CRGB::Black;
  }
  if (LDRValue3 <= 920) {
    newFile = 3;
    leds[13] = CRGB(random(255),random(255), random(255));
    leds[12] = CRGB(random(255),random(255), random(255));
    leds[11] = CRGB(random(255),random(255), random(255));
  } else{
    leds[13] = CRGB::Black;
    leds[12] = CRGB::Black;
    leds[11] = CRGB::Black;
  }
  if (LDRValue4 <= 920) {
    newFile = 4;
    leds[10] = CRGB(random(255),random(255), random(255));
    leds[9] = CRGB(random(255),random(255), random(255));
    leds[8] = CRGB(random(255),random(255), random(255));
  } else {
    leds[10] = CRGB::Black;
    leds[9] = CRGB::Black;
    leds[8] = CRGB::Black;
  }
  if (LDRValue5 <= 920) {
    newFile = 5;
    leds[7] = CRGB(random(255),random(255), random(255));
    leds[6] = CRGB(random(255),random(255), random(255));
    leds[5] = CRGB(random(255),random(255), random(255));
  } else{
    leds[7] = CRGB::Black;
    leds[6] = CRGB::Black;
    leds[5] = CRGB::Black;
  }
  if (LDRValue6 <= 920) {
    newFile = 6;
    leds[4] = CRGB(random(255),random(255), random(255));
    leds[3] = CRGB(random(255),random(255), random(255));
    leds[2] = CRGB(random(255),random(255), random(255));
  } else {
    leds[4] = CRGB::Black;
    leds[3] = CRGB::Black;
    leds[2] = CRGB::Black;
  }

  
  // Only change sound if file changed
  if (newFile != currentFile) {

    if (newFile == -1) {
      myDFPlayer.stop();
      isPlaying = false;
    }
    else {
      myDFPlayer.playFolder(folder, newFile);
      isPlaying = true;
    }

    currentFile = newFile;
  }

  FastLED.show();

 
}
