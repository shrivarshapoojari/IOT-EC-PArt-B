//  #define BLYNK_TEMPLATE_ID "TMPL3w8vRIx42"
// #define BLYNK_TEMPLATE_NAME "IOT Lab"
// #define BLYNK_AUTH_TOKEN "cqi5rsj8ritHuZDz6f-48Vh8dCdHrAYM"

// #include <WiFi.h>
// #include <BlynkSimpleEsp32.h>

// char auth[] = BLYNK_AUTH_TOKEN;
// char ssid[] = "vivo 1983";     // Your WiFi SSID
// char pass[] = "12345678"; // Your WiFi Password

// #define LDR_PIN 34    // LDR connected to GPIO 34 (analog pin)
// #define LED_PIN 26    // LED connected to GPIO 26 (digital pin)

// BlynkTimer timer;
// bool isManualControl = false;  // Flag to determine manual/auto control
// int manualLedState = LOW;      // Store the LED state in manual mode

// void setup() {
//   Serial.begin(115200);

//   // Initialize LDR and LED pin
//   pinMode(LDR_PIN, INPUT);
//   pinMode(LED_PIN, OUTPUT);

//   // Connect to WiFi and Blynk
//   Blynk.begin(auth, ssid, pass);

//   // Setup a timer to continuously check the LDR value
//   timer.setInterval(1000L, checkLightSensor);
// }

// void checkLightSensor() {
//   if (!isManualControl) {  // Only run the automatic logic if manual control is off
//     int ldrValue = analogRead(LDR_PIN); // Read the LDR value
//     Serial.println(ldrValue);

//     if (ldrValue >500) {  // Adjust this threshold according to your environment
//       digitalWrite(LED_PIN, HIGH); // Turn ON the LED if it's dark
//     } else {
//       digitalWrite(LED_PIN, LOW);  // Turn OFF the LED if it's bright
//     }

//     // Optionally, sync with Blynk App to display the LDR value
//     Blynk.virtualWrite(V0, ldrValue); // Push the LDR value to the app
//   } else {
//     digitalWrite(LED_PIN, manualLedState);  // Maintain the state set by manual control
//   }
// }

// BLYNK_WRITE(V2) {  // Virtual pin V1 is for selecting manual or automatic mode
//   int mode = param.asInt();  // Get the switch state from Blynk
//   isManualControl = (mode == 1);  // If V1 is 1, enable manual control; otherwise, auto mode

//   if (!isManualControl) {
//     // If switching to auto mode, turn off the LED in case it's still on
//     digitalWrite(LED_PIN, LOW);
//   }
// }

// BLYNK_WRITE(V3) {  // Virtual pin V2 controls the LED manually
//   if (isManualControl) {  // Only allow manual control when manual mode is on
//     manualLedState = param.asInt(); // Get the value of the button
//     digitalWrite(LED_PIN, manualLedState); // Control the LED via Blynk button
//   }
// }

// void loop() {
//   Blynk.run();
//   timer.run(); // Run the timer for LDR checking
// }


#define BLYNK_TEMPLATE_ID "TMPL3w8vRIx42"
#define BLYNK_TEMPLATE_NAME "IOT Lab"
#define BLYNK_AUTH_TOKEN "cqi5rsj8ritHuZDz6f-48Vh8dCdHrAYM"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vivo 1983";   // Your WiFi SSID
char pass[] = "12345678";     // Your WiFi Password

#define LDR_PIN 34    // LDR connected to GPIO 34 (analog pin)
#define LED_PIN 26    // LED connected to GPIO 26 (digital pin)

BlynkTimer timer;
bool isManualControl = false;  // Flag to determine manual/auto control
int manualLedState = LOW;       // Store the LED state in manual mode

void setup() {
  Serial.begin(115200);
  
  // Initialize LDR and LED pins
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Connect to WiFi and Blynk
  Blynk.begin(auth, ssid, pass);
  
  // Setup a timer to continuously check the LDR value
  timer.setInterval(1000L, checkLightSensor);
}

void checkLightSensor() {
  if (!isManualControl) {  // Only run automatic logic if manual control is off
    int ldrValue = analogRead(LDR_PIN);  // Read the LDR value
    Serial.println(ldrValue);

    if (ldrValue > 500) {  // Adjust the threshold according to your environment
      digitalWrite(LED_PIN, HIGH);  // Turn ON the LED if it's dark
    } else {
      digitalWrite(LED_PIN, LOW);   // Turn OFF the LED if it's bright
    }

    // Sync with Blynk App to display the LDR value
    Blynk.virtualWrite(V0, ldrValue);  // Push the LDR value to the app
  } else {
    // Maintain the state set by manual control
    digitalWrite(LED_PIN, manualLedState);
  }
}

BLYNK_WRITE(V3) {  // Virtual pin V2 is for selecting manual or automatic mode
  int mode = param.asInt();  // Get the switch state from Blynk
  isManualControl = (mode == 1);  // Enable manual control if V2 is 1

  if (!isManualControl) {
    // If switching to auto mode, ensure the LED follows auto logic
    checkLightSensor();
  }
}

BLYNK_WRITE(V2) {  // Virtual pin V3 controls the LED manually
  if (isManualControl) {  // Allow manual control only when in manual mode
    manualLedState = param.asInt();  // Get the button state from Blynk
    digitalWrite(LED_PIN, manualLedState);  // Update LED state accordingly
  }
}

void loop() {
  Blynk.run();
  timer.run();  // Run the timer for LDR checking
}

