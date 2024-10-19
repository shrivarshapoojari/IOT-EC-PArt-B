// #define BLYNK_TEMPLATE_ID "TMPL3hdwB_xZw"
// #define BLYNK_TEMPLATE_NAME "Smart Irrigation"
// #define BLYNK_AUTH_TOKEN "u7dwOxKYgNZzGrvAYbLdZF6NAg8L1Z-i"

// #define BLYNK_PRINT Serial

// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <BlynkSimpleEsp32.h>

// // Blynk Auth Token
// char auth[] = "u7dwOxKYgNZzGrvAYbLdZF6NAg8L1Z-i";

// // WiFi credentials
// char ssid[] = "vivo 1983";
// char pass[] = "12345678";

// // Soil moisture sensor pin
// const int soilMoisturePin = 34;

// // Relay pin
// const int led = 2;

// // Threshold value for soil moisture (0-1000)
// const int threshold = 4090;

// BlynkTimer timer;
// bool manualControl = false;

// void setup() {
//   // Start serial communication
//   Serial.begin(115200);

//   // Initialize Blynk
//   Blynk.begin(auth, ssid, pass);

//   // Set relay pin as output
//   pinMode(led, OUTPUT);
//   digitalWrite(led, HIGH);

//   // Set up a timer to check soil moisture every second
//   timer.setInterval(1000L, checkSoilMoisture);
// }

// void checkSoilMoisture() {
//   if (!manualControl) { // Only check soil moisture if not in manual control mode
//     int soilMoistureValue = analogRead(soilMoisturePin);
//     Serial.print("Soil Moisture Value: ");
//     Serial.println(soilMoistureValue);

//     // Send soil moisture value to virtual pin V5
//     Blynk.virtualWrite(V5, soilMoistureValue);

//     if (soilMoistureValue >threshold) {
//       // If soil is dry, turn on the pump
//       digitalWrite(led, HIGH);
//       // Blynk.notify("Soil is dry! Turning on the pump.");
//     } else {
//       // If soil is wet, turn off the pump
//       digitalWrite(led, LOW);
//     }
//   }
// }

// BLYNK_WRITE(V6) {
//   int pinValue = param.asInt(); // Get the state of the button
//   manualControl = pinValue == 1; // If button is pressed, set manual control to true

//   if (manualControl) {
//     digitalWrite(led, HIGH); // Turn on the LED manually
//   } else {
//     digitalWrite(led, LOW); // Turn off the LED manually
//   }
// }

// void loop() {
//   // Run Blynk
//   Blynk.run();

//   // Run timer
//   timer.run();
// }

















// #define BLYNK_TEMPLATE_ID "TMPL3hdwB_xZw"
// #define BLYNK_TEMPLATE_NAME "Smart Irrigation"
// #define BLYNK_AUTH_TOKEN "u7dwOxKYgNZzGrvAYbLdZF6NAg8L1Z-i"

// #define BLYNK_PRINT Serial

// #include <WiFi.h>
// #include <WiFiClient.h>
// #include <BlynkSimpleEsp32.h>

// // Blynk Auth Token
// char auth[] = BLYNK_AUTH_TOKEN;

// // WiFi credentials
// char ssid[] = "vivo 1983";
// char pass[] = "12345678";

// // Soil moisture sensor pin
// const int soilMoisturePin = 34;

// // Relay pin (pump control)
// const int led = 2;

// // Threshold value for soil moisture (0-4095)
// const int threshold = 4090;

// BlynkTimer timer;
// bool manualControl = false;  // Flag for manual/auto mode
// int manualState = LOW;        // Store relay state in manual mode

// void setup() {
//   // Start serial communication
//   Serial.begin(115200);

//   // Initialize Blynk
//   Blynk.begin(auth, ssid, pass);

//   // Set relay pin as output and initialize it to OFF
//   pinMode(led, OUTPUT);
//   digitalWrite(led, LOW);  // Pump off initially

//   // Set up a timer to check soil moisture every second
//   timer.setInterval(1000L, checkSoilMoisture);
// }

// void checkSoilMoisture() {
//   if (!manualControl) {  // Run auto logic only if manual control is off
//     int soilMoistureValue = analogRead(soilMoisturePin);  // Read soil moisture
//     Serial.print("Soil Moisture Value: ");
//     Serial.println(soilMoistureValue);

//     // Send the soil moisture value to Blynk (V5)
//     Blynk.virtualWrite(V5, soilMoistureValue);

//     if (soilMoistureValue > threshold) {
//       // If soil is dry, turn on the pump
//       digitalWrite(led, HIGH);
//     } else {
//       // If soil is wet, turn off the pump
//       digitalWrite(led, LOW);
//     }
//   } else {
//     // Maintain the manual state of the relay
//     digitalWrite(led, manualState);
//   }
// }

// BLYNK_WRITE(V6) {  // Virtual pin V6 for mode selection (manual/auto)
//   int mode = param.asInt();  // Get button state from Blynk
//   manualControl = (mode == 1);  // Enable manual mode if button is ON

//   if (!manualControl) {
//     // If switching to auto mode, ensure auto logic is applied immediately
//     checkSoilMoisture();
//   }
// }

// BLYNK_WRITE(V7) {  // Virtual pin V7 for manual control of the relay
//   if (manualControl) {  // Allow control only in manual mode
//     manualState = param.asInt();  // Get relay state from Blynk
//     digitalWrite(led, manualState);  // Update the relay state
//   }
// }

// void loop() {
//   // Run Blynk
//   Blynk.run();

//   // Run the timer
//   timer.run();
// }













#define BLYNK_TEMPLATE_ID "TMPL3hdwB_xZw"
#define BLYNK_TEMPLATE_NAME "Smart Irrigation"
#define BLYNK_AUTH_TOKEN "u7dwOxKYgNZzGrvAYbLdZF6NAg8L1Z-i"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Blynk Auth Token
char auth[] = BLYNK_AUTH_TOKEN;

// WiFi credentials
char ssid[] = "vivo 1983";
char pass[] = "12345678";

// Soil moisture sensor pin
const int soilMoisturePin = 34;

// Relay pin (pump control)
const int led = 2;

// Threshold value for soil moisture (0-4095)
const int threshold = 4090;

BlynkTimer timer;
bool manualControl = false;  // Flag for manual/auto mode
int manualState = LOW;        // Store relay state in manual mode

void setup() {
  // Start serial communication
  Serial.begin(115200);

  // Initialize Blynk
  Blynk.begin(auth, ssid, pass);

  // Set relay pin as output and initialize it to OFF
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);  // Pump off initially

  // Set up a timer to check soil moisture every second
  timer.setInterval(1000L, checkSoilMoisture);
}

void checkSoilMoisture() {
  if (!manualControl) {  // Run auto logic only if manual control is off
    int soilMoistureValue = analogRead(soilMoisturePin);  // Read soil moisture
    Serial.print("Soil Moisture Value: ");
    Serial.println(soilMoistureValue);

    // Send the soil moisture value to Blynk (V5)
    Blynk.virtualWrite(V5, soilMoistureValue);

    if (soilMoistureValue > threshold) {
      // If soil is dry, turn on the pump
      digitalWrite(led, HIGH);
      Serial.println("Auto Mode: Pump ON");
    } else {
      // If soil is wet, turn off the pump
      digitalWrite(led, LOW);
      Serial.println("Auto Mode: Pump OFF");
    }
  }
}

BLYNK_WRITE(V7) {  // Virtual pin V6 for mode selection (manual/auto)
  int mode = param.asInt();  // Get button state from Blynk
  manualControl = (mode == 1);  // Enable manual mode if button is ON

  if (manualControl) {
    Serial.println("Manual Mode: Enabled");
  } else {
    Serial.println("Auto Mode: Enabled");
    checkSoilMoisture();  // Apply auto logic immediately when switching
  }
}

BLYNK_WRITE(V6) {  // Virtual pin V7 for manual control of the relay
  if (manualControl) {  // Allow control only in manual mode
    manualState = param.asInt();  // Get relay state from Blynk
    digitalWrite(led, manualState);  // Update the relay state
    Serial.printf("Manual Mode: Pump %s\n", manualState ? "ON" : "OFF");
  }
}

void loop() {
  // Run Blynk
  Blynk.run();

  // Run the timer
  timer.run();
}
