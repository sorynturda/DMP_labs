#include <avr/io.h>
#include <avr/interrupt.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
volatile int myVar;
void setup() {
  myVar = 0;
  //inițializarea primului numărător
  cli();  //facem disable la întreruperile globale pentru a
  //face
  //modificările corespunzătoare timerelor
  TCCR1A = 0;  // SETĂM TCCR1A și B la 0
  TCCR1B = 0;  // timer este setat în Normal mode (WGMx3:0 =
  //0)
  lcd.begin(16, 2);
  lcd.print("Timere");
  //facem enable la întrerupere de overflow pentru timerul 1
  TIMSK1 = (1 << TOIE1);  //timer overflow întrerupt enable
  //for timer 1
  //setăm temporizatorul să ruleze o frecvență divizată cu
  //1024
  //DE MENȚIONAT CĂ FRECVENȚA PROCESORULUI e de 16 MHZ și
  //timer 1
  //este un temporizator de 16 biți
  //cu un prescaller de 1024 avem incrementare o data la
  //t = 1024 / (16 * 10^6) secunde
  //temporizatorul va da overflow la fiecare (t * 2^16) =
  //4.194 secunde
  TCCR1B |= (1 << CS10);
  TCCR1B |= (1 << CS12);
  //activăm întreruperile globale
  sei();
}
void loop() {
  lcd.setCursor(0, 1);
  lcd.print(myVar);
  lcd.setCursor(5, 1);
  lcd.print(TCNT1);
}
ISR(TIMER1_OVF_vect) {
  myVar = myVar + 1;
}