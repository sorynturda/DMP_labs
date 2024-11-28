/*
 * UTCN LAB 8 - ESP32 TCP client
 * originally adapted from https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi/examples/WiFiClient
 */

#include <WiFi.h>

const char* ssid = "DMP Server";     // Change this to your WiFi SSID
const char* password = "123456789";  // Change this to your WiFi password

const char* host = "192.168.4.1";  // Default address of the server
const int port = 80;               // Default port. You can put any value, as long as
                                   // the client and server are the same
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
  WiFiClient client;  // TCP client

  // Try to connect to the server at address "host" and port "port"
  if (!client.connect(host, port)) {
    Serial.println("Cannot connect");
    delay(2000);
    return;
  }

  client.println("Hello server");  // Send message to server

  // wait for response
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  String line = "";
  while (client.available()) {
    // read server response, char by char
    char c = client.read();
    line = line + c;

    if (c == '\n')
      Serial.print(line);  // print the response to Serial
  }

  delay(2000);  // wait 2 seconds and start again
}
