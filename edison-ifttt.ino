#include <Wire.h>
#include <WiFi.h>
#include "rgb_lcd.h"

// WiFi Parameters
char SSID[] = "<PUT YOUR WIFI SSID HERE>";
char PASSWORD[] = "<PUT YOUR WIFI PASSWORD HERE>";

// IFTTT Webservice
char server[] = "maker.ifttt.com";
int port = 80;
char makeChannelKey[] = "<PUT-YOUR-KEY-HERE>";

rgb_lcd lcd;
WiFiClient client;

int status = WL_IDLE_STATUS;

void setup() {
  // Initializing LCD
  lcd.begin(16, 2);

  // My amazing splash screen
  debugPrint("Edison + IFTTT.");
  delay(500);

  // Let's connect to Wifi
  connectToWifi(SSID, PASSWORD);
}

void loop() {
  // Chekcing if the board is connected to WiFi
  if(WiFi.status() != WL_CONNECTED){
    debugPrint("Please check the", "Wifi connection");
    return;
  }

  // Let's fire the IFTTT event event each 1 second.
  fireIftttEvent("EVENT-NAME", "TEST-VALUE1", "TEST-VALUE2", "TEST-VALUE3"); // Customize your event and values here. You could send some information from sensors, for example.
  debugPrint("Message sent!");
  delay(1000);
  return;
}

void fireIftttEvent(char* eventName) { // Simple requests without parameters
  char iftttPage[128];
  sprintf(iftttPage, "/trigger/%s/with/key/%s", eventName, makeChannelKey);
  makeGetRequest(server, port, iftttPage);
}

void fireIftttEvent(char* eventName, char* value1, char* value2, char* value3) { // Events with parameters
  char iftttPage[128];
  sprintf(iftttPage, "/trigger/%s/with/key/%s", eventName, makeChannelKey);

  // Creating the JSON to passa values to IFTTT Maker Channel
  char jsonValues[512]; // If you need to pass bigger strings, please adjust the size of this variable.
  sprintf(jsonValues, "{ \"value1\" : \"%s\", \"value2\" : \"%s\", \"value3\" : \"%s\" }", value1, value2, value3);

  makePostRequest(server, port, iftttPage, jsonValues);
}

void makePostRequest(char* server, int port, char* page, char* data) {
  char strBuffer[512];

  if (client.connect(server, port)) {
    debugPrint("Server connected");

    sprintf(strBuffer, "POST %s HTTP/1.1", page);
    client.println(strBuffer);

    sprintf(strBuffer, "Host: %s", server);
    client.println(strBuffer);

    client.println(F("Connection: close\r\nContent-Type: application/json"));

    sprintf(strBuffer, "Content-Length: %u\r\n", strlen(data));
    client.println(strBuffer);

    client.print(data);
  }

  // Ignoring the answer for a while. If you want to check if the message was received you need to parse the HTTP answer.

  client.stop();
}

void makeGetRequest(char* server, int port, char* page) {
  char strBuffer[128];

  if (client.connect(server, port)) {
    debugPrint("Server connected");

    sprintf(strBuffer, "GET %s HTTP/1.1", page);
    client.println(strBuffer);

    sprintf(strBuffer, "Host: %s", server);
    client.println(strBuffer);

    client.println("Connection: close\r\n");
  }

  // Ignoring the answer for a while. If you want to check if the message was received you need to parse the HTTP answer.

  client.stop();
}

void connectToWifi(char* ssid, char* password) {
  while (status != WL_CONNECTED) {
    status = WiFi.begin(ssid, password);
    debugPrint("Connecting to", ssid);
    delay(3000);
  }

  debugPrint("Connected!");
  delay(500);
}

void debugPrint(char* message) { // Was written using the Grove kit, feel free to replace for your favorite debug method.
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

void debugPrint(char* line0, char* line1) {
  debugPrint(line0);
  lcd.setCursor(0, 1);
  lcd.print(line1);
}
