float resolutionADC = .0049;  // rezoluția implicită (pentru
//referința 5V) = 0.049 [V] / unitate
float resolutionSensor = .01;  // rezoluție senzor = 0.01V/°C
void setup() {
  Serial.begin(9600);
}
void loop() {
  Serial.print("Temp [C]: ");
  float temp = readTempInCelsius(10, 0);  // citeste temperatura
  //de 10 ori, face media
  Serial.println(temp);  // afisare
  delay(200);
}
float readTempInCelsius(int count, int pin) {
  // citește temperatura de count ori de pe pinul analogic pin
  float sumTemp = 0;
  for (int i = 0; i < count; i++) {
    int reading = analogRead(pin);
    float voltage = reading * resolutionADC;
    float tempCelsius = (voltage - 0.5) / resolutionSensor;
    // scade deplasament, convertește în grade C
    sumTemp = sumTemp + tempCelsius;  // suma temperaturilor
  }
  return sumTemp / (float)count;  // media returnată
}