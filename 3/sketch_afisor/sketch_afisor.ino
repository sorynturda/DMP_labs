#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int time = 0;
int seconds = 0;
int minutes = 0;
int pos = 10;
int pos2 = 10;
// Masca pentru primul caracter, fiecare linie de biţi
//reprezintă o linie a caracterului
byte happy[8] = {
  B00000,
  B11011,
  B11011,
  B00000,
  B00000,
  B10001,
  B01110,
};
// Masca pentru al doilea caracter
byte sad[8] = {
  B00000,
  B11011,
  B11011,
  B00000,
  B00000,
  B01110,
  B10001,
};
byte paint[8] = {
  B01110,
  B01110,
  B11111,
  B00100,
  B00100,
  B00100,
  B01010,
  B10001,
};
void setup() {
  lcd.begin(16, 2);
  // cele două caractere sunt stocate în CGROM, zona
  //utilizator, poziţiile 0 şi 1
  lcd.createChar(0, happy);
  lcd.createChar(1, sad);
  lcd.createChar(2, paint);
  // Afişare prima linie, un text standard urmat de primul
  //caracter utilizator
  lcd.setCursor(0, 0);
  lcd.print("Happy ");
  lcd.write(byte(0));  // Observaţi diferenta dintre print şi
  //write
  /* când referiți caracterul „0” trebuie să faceți un cast
la byte. Altfel compilatorul va semnala o eroare. Excepție
este cazul în care referiți o variabilă:
byte zero = 0;
lcd.write(zero);
*/
  // Afișare pe a doua linie
  lcd.setCursor(0, 1);
  lcd.print("Sad ");
  lcd.write(1);  // când referiți caractere diferite de „0”
  lcd.setCursor(10, 0);
  //nu mai este necesar cast-ul;
}
// Funcţia loop rămâne nefolosită, puteți să o folosiți pentru
//a extinde funcționalitatea
void loop() {
  lcd.setCursor(pos, 1);
  time = millis() / 10;
  seconds = time % 60;
  minutes = time / 60 % 60;
  lcd.print(minutes);
  lcd.setCursor(11, 1);
  lcd.print(":");
  lcd.setCursor(12, 1);
  lcd.print(seconds);
  if (minutes < 10) {
    lcd.setCursor(9, 1);
    lcd.print("0");
  } else
    pos = 9;
  if (time % 100 == 0) {
    lcd.setCursor(pos2, 0);
    lcd.print(" ");

    lcd.setCursor(pos2 + 1, 0);
    lcd.write(2);
    if (pos2 == 15) {
      pos2 = 9;
    } else {
      // lcd.print(" ");
      pos2++;
    }
  }
}