//includem headerul responsabil pentru operații cu întreruperi
#include "avr/interrupt.h"
//include biblioteca de manipulat LCD
#include <LiquidCrystal.h>
  //inițializează lcd-ul la valorile stabilite ale pinilor
  LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
volatile int buttonVariable;  //variabila publica ce poate fi
//modificata de o intrerupere
void setup(void) {
  buttonVariable = 0;  //initializăm variabila shared între
  //ISR și programul principal
  //setează numărul de rânduri și coloane ale LCD-ului
  lcd.begin(16, 2);
  lcd.print("Incepe experimentul");
  delay(1000);  //facem o scurtă pauză pentru a vizualiza
                //mesajul de pe ecran
                //setăm pinul 21 ca și pin de intrare; pinul pe care se
  //află întreruperea INT0
  pinMode(21, INPUT);
  //setăm pinul 20 ca și pin de intrare; pinul pe care se
  //afla întreruperea INT1
  pinMode(20, INPUT);
  pinMode(13, OUTPUT);     //setăm pinul 13 ca și iesire
  digitalWrite(13, HIGH);  //aprindem led-ul ataşat la pinul
  //13
  delay(1000);
  EIMSK |= (1 << INT0);   //activăm punctual întreruperea INT0
  EIMSK |= (1 << INT1);   //activăm punctual întreruperea INT1
  EICRA |= (1 << ISC01);  //activăm întreruperea 0 pentru
  //front descrescător.
  EICRA |= (1 << ISC11);  //ca și mai sus, pentru
  //întreruperea 1
  sei();                  //activăm întreruperile la nivel global
  digitalWrite(13, LOW);  // stingem led-ul ataşat la pinul
  //13
  lcd.clear();  //ștergem ecranul LCD
}
void loop() {
  //dacă a fost executată o ISR trebuie să ștergem ecranul
  //și să afișăm iar mesajul
  // principal
  if (buttonVariable == 1) {
    lcd.clear();         //se șterge ecranul LCD
    buttonVariable = 0;  // variabila este re-inițializată
  }
  delay(1000);
  lcd.setCursor(0, 0);    //setăm cursorul
  lcd.print("Liniste…");  //afișăm un mesaj
}
//Rutina pentru tratarea întreruperii atașată la INT0
ISR(INT0_vect) {
  digitalWrite(13, !digitalRead(13));  //schimbă starea pin
  //13
  lcd.setCursor(0, 0);      //poziționăm cursorul stânga sus
  lcd.print("Intrerupem");  //afişăm mesaj
  lcd.setCursor(0, 1);
  lcd.print("ptr stirea zilei");
  buttonVariable = 1;
}
//Rutina pentru tratarea întreruperii atașată la INT0
ISR(INT1_vect) {
  digitalWrite(13, !digitalRead(13));
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Stirea Doi");
  buttonVariable = 1;
}