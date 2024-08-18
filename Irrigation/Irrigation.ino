#define BLYNK_TEMPLATE_ID "TMPL3hdwB_xZw"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation"
#define BLYNK_AUTH_TOKEN "u7dwOxKYgNZzGrvAYbLdZF6NAg8L1Z-i"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h> 

#define SOIL_MOISTURE_PIN 34   // Analog pin for soil moisture sensor
#define THRESHOLD_MOISTURE 100 // Threshold for soil moisture
#define PUMP_PIN 5  // Digital pin for controlling the pump
#define PUMP_SWITCH V6  // Virtual pin for controlling the pump manually

char auth[] = BLYNK_AUTH_TOKEN;  
char ssid[] = "vivo 1983";   
char pass[] = "12345678";

BlynkTimer timer;
bool isPumpOn = false;  // Track pump status

void sendSensorData()
{
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);
  int soilMoisturePercentage = map(soilMoisture, 3500, 4095, 100, 0);
  Blynk.virtualWrite(V5, soilMoisturePercentage);

  if (isPumpOn || soilMoisturePercentage < THRESHOLD_MOISTURE)
  {
    digitalWrite(PUMP_PIN, HIGH);
    if (!isPumpOn) {
      Blynk.logEvent("low_moisture", "Soil moisture is below the threshold!");
    }
  }
  else
  {
    if (!isPumpOn) {
      digitalWrite(PUMP_PIN, LOW);
    }
  }
}

BLYNK_WRITE(PUMP_SWITCH)
{
  isPumpOn = param.asInt();
  Serial.println(isPumpOn ? "Pump manually turned ON" : "Pump manually turned OFF");
}

void setup()
{
  Serial.begin(9600);
  pinMode(PUMP_PIN, OUTPUT); 

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(3000L, sendSensorData);
  Blynk.syncVirtual(PUMP_SWITCH);
}

void loop()
{
  Blynk.run();
  timer.run();
}
