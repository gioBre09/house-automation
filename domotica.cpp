#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// WiFi credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Sinric Pro credentials
#define APP_KEY "YOUR_APP_KEY"
#define APP_SECRET "YOUR_APP_SECRET"
#define LIGHT_ID "YOUR_LIGHT_DEVICE_ID"
#define FAN_ID "YOUR_FAN_DEVICE_ID"

// Relay pins
#define RELAY_PIN_LIGHT 5
#define RELAY_PIN_FAN 4

void setupWiFi() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
}

bool onLightPowerState(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN_LIGHT, state ? HIGH : LOW);
  Serial.printf("Light turned %s\n", state ? "ON" : "OFF");
  return true;
}

bool onFanPowerState(const String &deviceId, bool &state) {
  digitalWrite(RELAY_PIN_FAN, state ? HIGH : LOW);
  Serial.printf("Fan turned %s\n", state ? "ON" : "OFF");
  return true;
}

void setupSinricPro() {
  SinricProSwitch &myLight = SinricPro[LIGHT_ID];
  myLight.onPowerState(onLightPowerState);

  SinricProSwitch &myFan = SinricPro[FAN_ID];
  myFan.onPowerState(onFanPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  setupWiFi();
  pinMode(RELAY_PIN_LIGHT, OUTPUT);
  pinMode(RELAY_PIN_FAN, OUTPUT);
  
  setupSinricPro();
}

void loop() {
  SinricPro.handle();
}



