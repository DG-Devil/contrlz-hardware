#include <IRremote.h> // library for the IR functions

const int IR_PIN = 2;  // IR receiver pin
const int RELAY_PIN = 13;  // Relay control pin
const unsigned long TOGGLE_CODE = 0xCA;  // the hex code of the buttuon pressed on the remote, for which we want the bulb to on/off

bool bulbState = false; // Keeps track of ON/OFF state

void setup() {
    Serial.begin(9600);
    IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK); // IR module is started, and it is awaiting for signals
    pinMode(RELAY_PIN, OUTPUT); // setting the relaypin to output
    digitalWrite(RELAY_PIN, LOW); // Initially OFF
}

void loop() {
    if (IrReceiver.decode()) {
        if (IrReceiver.decodedIRData.command != 0) {  // Ignore invalid signals
            Serial.println(IrReceiver.decodedIRData.command, HEX); // printing the recived signal in hex for verification
            
            if (IrReceiver.decodedIRData.command == TOGGLE_CODE) { // if the pressed button is the desired button
                bulbState = !bulbState;  // Toggle state of the bulb i.e, if off: on and if on: off
                digitalWrite(RELAY_PIN, bulbState ? HIGH : LOW); // togling the relay module
                Serial.println(bulbState ? "Bulb ON" : "Bulb OFF"); // printing if the bulb is off or on
            }
        }
        IrReceiver.resume(); // Prepare to receive next signal
    }
}