#include <WiFi.h>
#include <ThingSpeak.h>

// Pin definitions
const int trigPin = 5;
const int echoPin = 18;
const int buzzerPin = 4;  // Define buzzer pin

// Wi-Fi credentials
const char* ssid = "vivo 1983";       // Replace with your network SSID
const char* password = "12345678";   // Replace with your network password

// ThingSpeak settings
unsigned long myChannelNumber = 2628777;  // Replace with your ThingSpeak channel number
const char* myWriteAPIKey = "WZ6UGSI5FA8WCOW9";  // Replace with your ThingSpeak write API key

WiFiClient client;

// Define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buzzerPin, OUTPUT); // Sets the buzzerPin as an Output

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED / 2;
  
  // Prints the distance in the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  // Send data to ThingSpeak
  ThingSpeak.setField(1, distanceCm);  // Update field 1 with the distance value
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    // Serial.println("Error sending data to ThingSpeak");
  }
  
  // Activate buzzer if distance is less than 30 cm
  if (distanceCm < 30) {
    digitalWrite(buzzerPin, HIGH);  // Turn on buzzer
  } else {
    digitalWrite(buzzerPin, LOW);   // Turn off buzzer
  }
  
  delay(1000);  // Wait for a second before the next reading
}
