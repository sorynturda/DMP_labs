#include <LiquidCrystal.h>
// Includem biblioteca necesară pentru I2C
#include <Wire.h>
int x = 0;

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
void setup() {
  // Pornim busul I2C ca și slave la adresa 9
  Wire.begin(9);
  // Atașăm o funcție care să se declanșeze atunci când primim
  //ceva
  Wire.onReceive(receiveEvent);
  lcd.begin(16, 2);
  lcd.print("Slave");
}
void receiveEvent(int bytes) {
  x = Wire.read();
  // citim un caracter din I2C
}
void loop() {
  lcd.setCursor(0, 1);  // afișare caracter recepționat
  lcd.print(x);
}