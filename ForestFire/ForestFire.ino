#define BLYNK_TEMPLATE_ID "TMPL3I7C7S4Kx"
#define BLYNK_TEMPLATE_NAME "ForestFire"
#define BLYNK_AUTH_TOKEN "cfISm3U9LuVq4q16Sz4PTi1BqMSC66aM"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vivo 1983";
char pass[] = "12345678";

BlynkTimer timer;

const int smokeA0 = 34; // Pin for smoke sensor
int sensorThres = 100;
int data;

void sendSensor() {
  Blynk.virtualWrite(V0, data);
  
  if (data > 1200) {
    Blynk.logEvent("fire_detected", "Fire Detected");
    Serial.println(data);
  } else {
    Serial.println("No Danger");
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(smokeA0, INPUT);
  timer.setInterval(2500L, sendSensor);
}

void loop() {
  data = analogRead(smokeA0);
  delay(1000);
  Serial.println(data);
  
  Blynk.run();
  timer.run();
}
