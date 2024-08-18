#include <WiFi.h>
#include "FirebaseESP32.h"



#define WIFI_SSID "realme GT Master Edition"
#define WIFI_PASSWORD "g7dmxhpk"
#define FIREBASE_HOST "smart-parking-5ba45-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Mqbnv5XMqN00zAN8AYPD467F7AYyqQ2nueR680dh"
String FIREBASE_BUCKET = "parking"; 

// Define the GPIO pins for the IR sensors
#define IR_SENSOR1_PIN 5
#define IR_SENSOR2_PIN 6

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  // Set GPIO pins as input for the IR sensors
  pinMode(IR_SENSOR1_PIN, INPUT);
  pinMode(IR_SENSOR2_PIN, INPUT);
}

void loop() {
  // Read the IR sensor values
  bool spot1Occupied = digitalRead(IR_SENSOR1_PIN);
  bool spot2Occupied = digitalRead(IR_SENSOR2_PIN);

  Firebase.setInt(firebaseData, String(FIREBASE_BUCKET) + "/spot1", spot1Occupied);
  Firebase.setInt(firebaseData, String(FIREBASE_BUCKET) + "/spot2", spot2Occupied);

  delay(1000); // Delay between checks
}
