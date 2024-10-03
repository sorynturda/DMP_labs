// Citirea stării butoanelor conectate la pinii 4,5,6,7
// afișarea pe LED-uri conectate la PORTA
// variabile pentru starea butoanelor
int b1;
int b2;
int b3;
int b4;
// variabila pentru compunerea numărului de transmis
unsigned char stat = 0;
void setup() {
  // configurare pini pentru butoane, intrare
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Hello from arduino");

  // activare PORTA , ca ieșire,
  DDRA = 0b11111111;
}
void loop() {
  // citire stare butoane
  b1 = digitalRead(4);
  b2 = digitalRead(5);
  b3 = digitalRead(6);
  b4 = digitalRead(7);
  // compunere rezultat
  // fiecare LED e controlat de 1 buton, unele butoane sunt
  //duplicate
  // stat = (b4 << 5) | (b3 << 4) | (b4 << 3) | (b3 << 2) | (b2 << 1) | b1;
  // afișare pe LED-uri, legate la port a
  PORTA = stat;
  // așteptare 50 ms
  if (b4 == 1) {
    Serial.println("buton 4");
    stat = 0;
  }
  if (b1 == 1) {
    stat = 0b111111;
    Serial.println(millis() / 1000);
  }
  if (b2 == 1) {
    stat = stat >> 1;
  }
  if(b3 == 1)
    stat = stat << 1 | 1;
  delay(50);
}