/*
This example receives the IR signal and tries to decode it and display the protocol used
*/

#include "main.h"

IRDaikinESP ac(TRANS_PIN);

void setup() {
    ac.begin();
    Serial.begin(115200);
}

void loop() {
    Serial.println("Sending");

    ac.on();
    ac.send();

    Serial.println("Sent");

    delay(15000);
}