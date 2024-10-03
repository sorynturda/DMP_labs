// Citirea stării butoanelor conectate la pinii 4, 5, 6, 7
// afișarea prin interfața serială
// se transmite un număr care are ultimele 4 cifre starea
//butoanelor apăsate
// variabile pentru starea butoanelor
int b1;
int b2;
int b3;
int b4;
// variabila pentru compunerea numărului de transmis
int stat = 0;
void setup() {
  // configurare pini pentru butoane, intrare
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  // activare comunicatie serială
  Serial.begin(9600);
}
void loop() {
  // citire stare butoane
  b1 = digitalRead(4);
  b2 = digitalRead(5);
  b3 = digitalRead(6);
  b4 = digitalRead(7);
  // compunere rezultat
  stat = 10000 + b4 * 1000 + b3 * 100 + b2 * 10 + b1;
  // transmisie
  Serial.println(stat);
  // așteptare 0.5 sec
  delay(500);
}