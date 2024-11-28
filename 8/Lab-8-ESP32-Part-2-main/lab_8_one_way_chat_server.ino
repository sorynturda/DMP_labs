/*
 * UTCN LAB 8 - ESP32 One-way TCP Chat Server that receives messages
 * originally adapted from https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi/examples/WiFiClient
 */

#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>

// MESSAGE STRINGS
const String SETUP_INIT = "SETUP: Initializing ESP32 dev board";
const String SETUP_ERROR = "!!ERROR!! SETUP: Unable to start SoftAP mode";
const String INFO_NEW_CLIENT = "New client connected";
const String INFO_DISCONNECT_CLIENT = "Client disconnected";

// BASIC WIFI CONFIGURATION CONSTANTS
// The SSID (Service Set IDentifier), in other words, the network's name
// Make sure to CHANGE THIS to something unique before uploading the code to
// the development board
const char *SSID = "DMP Server";
// Password for the network
// By default the ESP32 uses WPA / WPA2-Personal security, therefore the
// the password MUST be between 8 and 63 ASCII characters
const char *PASS = "123456789";
// The default port (both TCP & UDP) of a WWW HTTP server number according to
// RFC1340 is 80
const int port = 80;

// Initialize the server on the ESP32 board
WiFiServer server(port);

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

  if (!WiFi.softAP(SSID, PASS)) {
    Serial.println(SETUP_ERROR);
    // Lock system in infinite loop in order to prevent further execution
    while (1)
      ;
  }

  // Get AP's IP address for info message
  const IPAddress accessPointIP = WiFi.softAPIP();
  const String serverInfoMessage = "Server started " + accessPointIP.toString()
                                   + " on port " + port;

  // Start the server
  server.begin();
  Serial.println(serverInfoMessage);
}

void loop() {
  WiFiClient client = server.available();

  if (client) {  // Check if a device has connected to the AP
    Serial.println(INFO_NEW_CLIENT);
    String currentLine = "";
    while (client.connected()) {  // Loop until a client is connected to the TCP server
      if (client.available()) {   // If there's data in the buffer
        const char c = client.read();
        currentLine += c;
        if (c == '\n') {
          // No need for println, because it already has a new line at the end
          Serial.print("Received message from client: " + currentLine);
          client.stop();  // disconnect the client
          Serial.println(INFO_DISCONNECT_CLIENT);
          Serial.println();
        }
      }
    }
  }
}
