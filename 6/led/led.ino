int val = 0;


void setup() {
  pinMode(11, OUTPUT);
  Serial.begin(9600);
}


void loop() {

  val = analogRead(0);
  val = map(val, 0, 1023, 0, 255);
  analogWrite(11, 255 - val);
  Serial.println(val);
  delay(200);
}
