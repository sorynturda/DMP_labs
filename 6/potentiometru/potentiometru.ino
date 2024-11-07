#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
void setup() {
  analogReference(DEFAULT);  //setarea tensiunii de referință la
  //tensiunea default
  lcd.begin(16, 2);  //inițializarea LCD ului
  lcd.setCursor(0, 0);
  lcd.print("Cititi senzor");
  pinMode(A1, INPUT);  // setarea pinului analogic A1 ca și pin
  //de intrare
}
void loop() {
  int val = analogRead(A1);  //citirea valorii analogice
  lcd.setCursor(0, 1);
  lcd.print(val);
}