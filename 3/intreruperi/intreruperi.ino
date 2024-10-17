#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
volatile int buttonVariable;
int sec = 0;
int min = 0;
char s[15];
int flag = 1;

void setup() {
  buttonVariable = 0;
  lcd.begin(16, 2);
  lcd.print("A inceput");
  lcd.setCursor(0, 1);
  lcd.print("din nou");
  delay(1000);
  // cei doi pini de întrerupere, 21 și 20, declarați ca
  //intrare și rezistențe Pull-Up active
  pinMode(21, INPUT);
  pinMode(21, INPUT);
  digitalWrite(20, HIGH);
  digitalWrite(21, HIGH);
  // atașăm pinilor 21 și 21, corespunzători INT1 și INT0,
  //funcţii ISR
  attachInterrupt(digitalPinToInterrupt(20), functieUnu,
                  RISING);
  attachInterrupt(digitalPinToInterrupt(21), functieDoi,
                  RISING);
  Serial.begin(9600);
}

void loop() {
  //aici sunt taskuri care se execută în mod normal cînd se
  //rulează programul
  if (min < 10)
    sprintf(s, "0%d:%d", min, sec);
  else
    sprintf(s, "%d:%d", min, sec);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print(s);
  delay(1000);
  Serial.println(flag);
  if (flag == 0) {
    sec++;
    if (sec == 60) {
      sec = 0;
      min++;
    }
  }
}
//prima procedură ISR
void functieDoi() {
  if(flag == 0)
    flag = 1;
  else
    flag = 0;
  lcd.setCursor(6, 0);
  lcd.print("test");
}
//a doua procedură ISR
void functieUnu() {
  sec = 0;
  min = 0;
}