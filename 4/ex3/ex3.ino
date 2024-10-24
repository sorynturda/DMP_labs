#include <TimerOne.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
volatile int myVar;
void setup(void) {
  Timer1.initialize(1 * 1e6);  //se inițializează intervalul
  //de timp la care temporizatorul va
  // declanşa evenimente (în microsecunde, 1000000
  //microsecunde = 1 secundă)
  Timer1.attachInterrupt(ShowMessage);  // funcţia
  //ShowMessage se va apela la intevalul
  // stabilit
}
void ShowMessage(void) {
  lcd.setCursor(0, 0);
  lcd.print(myVar);
  myVar++;
}
void loop(void) {
}