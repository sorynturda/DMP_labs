//includem librăria de LCD
#include <LiquidCrystal.h>
String inputString = "";  // creăm un string care să ne țină datele
//care vin pe serial
// condiție pentru verificare dacă stringul este complet (s-a
//apăsat enter)
boolean stringComplete = false;
//inițializăm obiectul de tip lcd (vezi exemplul 1 pentru
//explicații asupra pinilor)
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
void setup() {
  // inițializare interfață serială
  Serial.begin(9600);  // format frame serial implicit
  // inițializare și setare lcd
  lcd.begin(16, 2);
  // rezervăm 200 de octeti pentru șirul de preluare a datelor
  //de intrare
  inputString.reserve(200);
}
void loop() {
  // afișăm stringul când primim new line
  if (stringComplete) {
    // setăm cursorul la coloana și rândul 0
    lcd.setCursor(0, 0);
    if (inputString == "clear")
      lcd.clear();
    else
      lcd.print(inputString);
    Serial.println(inputString);
    // golim șirul
    inputString = "";
    // resetăm contorul care verifică dacă stringul este sau
    //nu complet
    stringComplete = false;
  }
}
/*
SerialEvent este apelată de fiecare dată când date noi ajung pe
portul RX
Această funcție rulează de fiecare dată când rulează și loop. Deci
dacă am pune un delay în loop ne-ar întârzia și afișarea
rezltatului.
*/
void serialEvent() {
  while (Serial.available()) {
    // luăm byte-ul nou venit:
    // îl citim cu serial.read
    char inChar = (char)Serial.read();
    // verificăm dacă nu e cumva new line și dacă nu este, îl
    //adăugăm în inputString
    // nu adăugăm new line în input string întrucât ne va
    //afișa un caracter în plus pe lcd
    if (inChar != '\n')
      inputString += inChar;
    // dacă caracterul care vine este new line, setăm flagul
    // în așa fel încât loop-ul principal poate face ceva în
    //legătură cu asta
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}