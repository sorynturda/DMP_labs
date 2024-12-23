/*
 * UTCN LAB 8 - ESP32 One-way TCP Chat client that sends messages
 * originally adapted from https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi/examples/WiFiClient
 */

#include <WiFi.h>

const char* ssid = "duba filaj cluj";     // Change this to your WiFi SSID
const char* password = "123456789";  // Change this to your WiFi password

const char* host = "192.168.4.1";  // Default address of the server
const int port = 80;               // Default port. You can put any value, as long as
                                   // the client and server are the same

const char STRING_TERMINATOR = '\n';
String textToSend = "";

void setup() {
  Serial.begin(9600);
  // ESP32 boards have a delay with UART for some reason from a reset after
  // uploading new code to the development board
#if 1  // board was newly programmed
  delay(1000);
#else
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB
  }
#endif

  // We start by connecting to a WiFi network
  Serial.println("******************************************************");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read input from serial terminal
  readInputFromTerminal();

  if (textToSend.length() > 0) {

    WiFiClient client;  // TCP client

    // Try to connect to the server at address "host" and port "port"
    if (!client.connect(host, port)) {
      Serial.println("Cannot connect");
      delay(2000);
      return;
    }

    Serial.print("Sending text to server: ");
    Serial.println(textToSend);
    client.print(textToSend + "\n");
    textToSend = "";
  }
}

void readInputFromTerminal() {
  while (Serial.available() > 0) {
    textToSend = Serial.readStringUntil(STRING_TERMINATOR);
  }
}
