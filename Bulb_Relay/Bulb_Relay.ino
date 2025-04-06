const int relayPin = 7; // Pin connected to the relay's S (Signal) pin

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(relayPin, LOW); // Ensure the relay is off at startup
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input == '1') {
      digitalWrite(relayPin, HIGH); // Turn relay ON
      Serial.println("Bulb ON");
      //delay(100);
    } else if (input == '0') {
      digitalWrite(relayPin, LOW); // Turn relay OFF
      Serial.println("Bulb OFF");
      //delay(100);
    }
  }
}
