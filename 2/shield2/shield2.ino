int latchPin = 4;
int clockPin = 7;
int dataPin = 8;  // Pinii SSD
int n = 9999;
int button = 0;
int bstate = 0;
int anotherbutton = 0;
int astate = 0;
int buzzer = 3;
int buzzerstate = 0;

unsigned char afisor = 0;
const unsigned char ssdlut[] = { 0b00111111, 0b00000110, 0b01011011,
                                 0b01001111, 0b01100110, 0b01101101, 0b01111101,
                                 0b00000111, 0b01111111, 0b01101111,
                                 0b01110111, 0b01111100, 0b00111001, 0b01011110, 0b01111001 };  // A b C d E

const unsigned char anodelut[] = { 0b00000001, 0b00000010,
                                   0b00000100, 0b00001000 };
const unsigned char digits[] = { 10, 11, 12, 13 };  // Numărul afişat va
//fi 1234. Modificaţi aici pt alt număr
void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  // Cei trei pini pentru registrii
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  // pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  // de deplasare, configuraţi ca ieșire
}
void loop() {

  button = digitalRead(A1);
  anotherbutton = digitalRead(A2);
  if (button == LOW && bstate == 0) {
    // delay(100);
    bstate = 1;
    n = (n + 1) % 10000;
  } else if (button == HIGH && bstate == 1)
    bstate = 0;

  if (anotherbutton == LOW && astate == 0) {
    astate = 1;
    if (n != 0)
      n = (n - 1) % 10000;
    else
      n = 9999;
  } else if (anotherbutton == HIGH && astate == 1)
    astate = 0;

  if (n == 69 && buzzerstate == 0) {
    buzzerstate = 1;
    Serial.println("BUTON1");
  } else if (n != 69 && buzzerstate == 1)
    buzzerstate = 0;
  for (int i = 0; i <= 3; i++) {
    unsigned char cifra[] = { (n / 1000) % 10, (n / 100) % 10, (n / 10) % 10, n % 10 };
    unsigned char digit = cifra[i];      // cifra curentă
    unsigned char cathodes = ~ssdlut[digit];  // catozii
    //cifrei curente, vom nega valoarea din LUT
    digitalWrite(latchPin, LOW);  // vom activa semnalul
    //latch pentru a permite scrierea
    shiftOut(dataPin, clockPin, MSBFIRST, cathodes);  //
    //serializăm octetul anozilor
    shiftOut(dataPin, clockPin, MSBFIRST, anodelut[i]);
    // serializăm octetul anozilor
    digitalWrite(latchPin, HIGH);  // dezactivăm semnalul
    //latch
  }
  delay(2);
}