#include <LiquidCrystal.h>
// Includem biblioteca wire pentru I2C
#include <Wire.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
int x = 0;
void setup() {
  // Dechidem magistrala I2C ca master
  Wire.begin();
  lcd.begin(16, 2);
  lcd.print("Master");
}
void loop() {
  Wire.beginTransmission(9);  // transmitem spre device #9
  Wire.write(x);
  // trimitem x
  Wire.endTransmission();
  // oprim transmisia
  lcd.setCursor(0, 1);
  //master
  lcd.print(x);
  // afișare caracter transmis pe lcd
  x++;               // incrementăm x
  if (x > 5) x = 0;  // resetăm x odată ce ajunge la 6
  delay(500);
}