//includem fișierul cu definițiile pentru tonuri
#include "pitches.h"
// melodia ca lista de note
int melody[] = {
  NOTE_A3,
  NOTE_C4,
  NOTE_E4,
  NOTE_C4,
  NOTE_A3,
  NOTE_G3,
  0,
  NOTE_B3,
};

int buttonPin1 = A8, buttonPin2 = A9, buttonPin3 = A10;
int bs1 = 0, bs2 = 0, bs3 = 0;
int bflag1 = 0, bflag2 = 0, bflag3 = 0;
//introducem durata pentru fiecare notă din melodie
int noteDurations[] = {4, 4, 4, 4, 4, 4, 4, 4 };
void setup() {
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  // pentru fiecare notă din vectorul melody
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    //calculăm durata de afișare a notei
    int noteDuration = 1000 / noteDurations[thisNote];
    //apelăm funcția de tone pentru difuzorul atașat la
    //pinul 8 și durata specificată
    tone(8, melody[thisNote], noteDuration);
    noTone(8);
  }
  Serial.begin(9600);
}
void loop() {
  bs1 = digitalRead(buttonPin1);
  bs2 = digitalRead(buttonPin2);
  bs3 = digitalRead(buttonPin3);
  int noteDuration = (1000 / noteDurations[0]) / 2;
    int pauseBetweenNotes = noteDuration * 1.30;

  if (bs1 == LOW && bflag1 == 0) {
    tone(8, melody[0], noteDuration);
    delay(pauseBetweenNotes);

    noTone(8);
    Serial.println(1);
    bflag1 = 1;
  } else if (bs1 == HIGH && bflag1 == 1) {
    bflag1 = 0;
  }
  if (bs2 == LOW && bflag2 == 0) {
    tone(8, melody[1], noteDuration);
    delay(pauseBetweenNotes);

    noTone(8);
    Serial.println(2);
    bflag2 = 1;
  } else if (bs2 == HIGH && bflag2 == 1) {
    bflag2 = 0;
  }
  if (bs3 == LOW && bflag3 == 0) {
    tone(8, melody[2], noteDuration);
    delay(pauseBetweenNotes);

    Serial.println(3);
    noTone(8);
    bflag3 = 1;
  } else if (bs3 == HIGH && bflag3 == 1) {
    bflag3 = 0;
  }
}
