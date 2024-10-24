#include <avr/io.h>
#include <avr/interrupt.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
volatile int myVar;
void setup() {
  // initialize Timer1
  cli();
  // facem disable la întreruperile globale
  TCCR1A = 0;
  // setăm TCCR1A și B la 0
  TCCR1B = 0;
  lcd.begin(16, 2);
  lcd.print("Timere cu CTC");
  // setăm registrul cu valoarea căruia vom compara TCNT
  OCR1A = 15624;
  // activăm modul CTC:
  TCCR1B |= (1 << WGM3);
  // divizăm ceasul plăcii cu 1024:
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  // facem enable la întreruperea la comparare prin setarea
  //bitului
  // corespunzător din mască
  TIMSK1 |= (1 << OCIE1A);
  // validăm sistemul global de întreruperi
  sei();
}
void loop() {
  lcd.setCursor(0, 1);
  lcd.print(myVar);
  lcd.setCursor(5, 1);
  lcd.print(TCNT1);
}
ISR(TIMER1_COMPA_vect) {
  myVar = myVar + 1;
}