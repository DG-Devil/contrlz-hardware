#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "SSSIHL-Student"; // your Wi-Fi SSID
// const char* password = "your_password"; // your Wi-Fi password (if needed)
// MQTT broker details
const char* mqtt_server = "10.130.234.80"; // your MQTT broker IP address
const int mqtt_port = 1883; // your MQTT broker port (default is 1883)

WiFiClient espClient;
PubSubClient client(espClient);
String macAddress;

// Relay pin
const int relayPin = 0; // GPIO0 for ESP-01

// Function prototypes
void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Start with relay OFF

  setup_wifi();

  // Retrieve and format MAC address
  macAddress = WiFi.macAddress();
  macAddress.replace(":", "");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  client.setKeepAlive(60);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Always listening for messages
}

void setup_wifi() {
  WiFi.disconnect();
  WiFi.begin(ssid);
  // WiFi.begin(ssid, password); // Uncomment if password is needed

  Serial.print("Connecting to Wi-Fi... ");
  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 20) { // Retry for 10 seconds
    delay(500);
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Connected!");
  } else {
    Serial.println("Failed! Restarting...");
    ESP.restart();
  }

  Serial.print("Connecting to MQTT... ");
  client.setServer(mqtt_server, mqtt_port);
  if (client.connect(("ESP8266Client-" + macAddress).c_str())) {
    Serial.println("MQTT Connected!");
    String topic = "contrlz/devices/" + macAddress;
    client.subscribe(topic.c_str());
    Serial.print("Subscribed to: ");
    Serial.println(topic);
  } else {
    Serial.println("MQTT Connection Failed! Restarting...");
    ESP.restart();
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Received message on ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(message);

  if (message == "ON") {
    digitalWrite(relayPin, HIGH); // Turn relay ON
    Serial.println("Relay ON");
  } else if (message == "OFF") {
    digitalWrite(relayPin, LOW);  // Turn relay OFF
    Serial.println("Relay OFF");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Reconnecting to MQTT... ");
    if (client.connect(("ESP8266Client-" + macAddress).c_str())) {
      Serial.println("Connected!");
      String topic = "contrlz/devices/" + macAddress;
      client.subscribe(topic.c_str());
      Serial.print("Subscribed to: ");
      Serial.println(topic);
    } else {
      Serial.println("Failed! Retrying...");
      delay(5000);
    }
  }
}
