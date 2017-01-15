#include "tones.h"

const int led1 = 13; // the pin that the LED is attached to
const int led2 = 12; //
const int led3 = 11; //
const int led4 = 10; //
const int led5 = 9; //
int incomingByte;      // a variable to read incoming serial data into

// notes in the melody:

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup(){
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
}

void song() {
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();
    Serial.print(incomingByte);
    Serial.print("\n");
    
      switch(incomingByte){
        case 49:
          digitalWrite(led1, HIGH);
          break;
     
        case 50:
         digitalWrite(led1, LOW);
         break;
        
        case 51:
          digitalWrite(led2, HIGH);
          break;
     
        case 52:
         digitalWrite(led2, LOW);
         break;

        case 53:
          digitalWrite(led3, HIGH);
          break;
     
        case 54:
         digitalWrite(led3, LOW);
         break;

        case 55:
          digitalWrite(led4, HIGH);
          break;
     
        case 56:
         digitalWrite(led4, LOW);
         break;

        case 57:
          song();
          break;
       default:
        Serial.print("RETRTY");
        Serial.print(incomingByte);
    }
  }
}

