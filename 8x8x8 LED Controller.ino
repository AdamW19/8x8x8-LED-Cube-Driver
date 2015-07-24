/*
 *  8x8x8 LED Cube Driver using a Arduino Mega 2560 and a TPIC6B505 shift register.
 *  Code written by Adam W., 2015. Code was written as a project for Bluestamp Engineering (2015).
 *
 *  This program uses both digital and analog pins to control the LCD cube.
 *
 *  Hardware Required:
 *  - Arduino Mega 2560
 *  - TPIC6B595 shift register - Sadly the Arduino Mega 2560 does have enough pins for the LED cube, so I'm using a shift register to add aditional pins to the Arduino.
 *  - 8x8x8 LED Cube - You need the LED cube to light up an LED cube :D
 *
 *  I've borrowed and modified a lot of code from Jens C Brynildsen's TPIC6B595 shift register example and chr's Instructable. Thanks!
 */

//Defines the output pins of for the positive leads.
const int outputPins[] = {0, 1, 2, 3, 4, 5, 6, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, A8, A9, A10, A11, A12, A13, A14, A15};

// Defines the ground pins for the negitive leads.
const int groundPins[] = {A0, A1, A2, A3, A4, A5, A6, A7};

// Defines the pins used in the shift register for the animations.
const int shiftPins[] = {7, 8, 9, 10};

// The below pins will be used to connect to the shift register.
const int clearPin = 7;
const int latchPin = 8;
const int clockPin = 9;
const int dataPin = 10;

// Counters and info used for the shift register.
int shiftCounter = 0;
int shiftNumLedsInUse = 8;

void setup() {
  shiftSetup(clearPin, latchPin, dataPin, clockPin); // Method used to set up the shift register.
   //Used to define the pins.
    for(int i = 0; i < 58; i++) {
    pinMode(outputPins[i], OUTPUT);
  }
  for(int i = 0; i < 8; i++) {
    pinMode(groundPins[i], OUTPUT);
  }
}

void loop() {

  for(int i = 0; i < 8; i++) { //Sets ground pins to high to turn off the ground pins; no potential difference in voltage, therefore no connection
    digitalWrite(groundPins[i], HIGH);
  }
  for(int i = 0; i < 58; i++) { //Sets output pins high.
    digitalWrite(outputPins[i], HIGH);
    for(int i = 0; i < 4; i++) {
       // the bits you want to send
  byte bitsToSend0 = 0;
  // write number as bits
  bitWrite(bitsToSend0, shiftPins[i], HIGH);

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(shiftPins[1], LOW);

  // shift the bits out
  shiftOut(shiftPins[3], shiftPins[2], MSBFIRST, bitsToSend0);

  // turn on the output so the LEDs can light up:
  digitalWrite(shiftPins[1], HIGH);
    }
  }
  for(int i = 0; i < 8; i++) { //By setting the ground pins low, there is a potential difference in voltage, so there will be a connection
    digitalWrite(groundPins[i], LOW);
    delay(501);
    digitalWrite(groundPins[i],HIGH);
  }

}

// Method below is used to set up the shift register program.
void shiftSetup(int clearPin, int latchPin, int dataPin, int clockPin) {
  //set pins to output because they are addressed in the main loop
  pinMode(clearPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  delay(100);
  // Always start by sentting clearPin high
  digitalWrite(clearPin, HIGH);
}

// Method below sends bits to the shift register.
void shiftRegisterWrite(int whichPin, int whichState) {
  // the bits you want to send
  byte bitsToSend0 = 0;
  // write number as bits
  bitWrite(bitsToSend0, whichPin, whichState);

  // turn off the output so the pins don't light up
  // while you're shifting bits:
  digitalWrite(latchPin, LOW);

  // shift the bits out
  shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend0);

  // turn on the output so the LEDs can light up:
  digitalWrite(latchPin, HIGH);
}
