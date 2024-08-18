#define BLYNK_TEMPLATE_ID "TMPL3hdwB_xZw"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation"
#define BLYNK_AUTH_TOKEN "u7dwOxKYgNZzGrvAYbLdZF6NAg8L1Z-i"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Blynk Auth Token
char auth[] = "u7dwOxKYgNZzGrvAYbLdZF6NAg8L1Z-i";

// WiFi credentials
char ssid[] = "vivo 1983";
char pass[] = "12345678";

// Soil moisture sensor pin
const int soilMoisturePin = 34;

// Relay pin
const int led = 2;

// Threshold value for soil moisture (0-1000)
const int threshold = 500;

BlynkTimer timer;
bool manualControl = false;

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Set relay pin as output
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  // Set up a timer to check soil moisture every second
  timer.setInterval(1000L, checkSoilMoisture);
}

void checkSoilMoisture() {
  if (!manualControl) { // Only check soil moisture if not in manual control mode
    int soilMoistureValue = analogRead(soilMoisturePin);
    Serial.print("Soil Moisture Value: ");
    Serial.println(soilMoistureValue);

    // Send soil moisture value to virtual pin V5
    Blynk.virtualWrite(V5, soilMoistureValue);

    if (soilMoistureValue < threshold) {
      // If soil is dry, turn on the pump
      digitalWrite(led, HIGH);
      // Blynk.notify("Soil is dry! Turning on the pump.");
    } else {
      // If soil is wet, turn off the pump
      digitalWrite(led, LOW);
    }
  }
}

BLYNK_WRITE(V6) {
  int pinValue = param.asInt(); // Get the state of the button
  manualControl = pinValue == 1; // If button is pressed, set manual control to true

  if (manualControl) {
    digitalWrite(led, HIGH); // Turn on the LED manually
  } else {
    digitalWrite(led, LOW); // Turn off the LED manually
  }
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Run timer
  timer.run();
}
