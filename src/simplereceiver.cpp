/*
This example receives the IR signal and tries to decode it and display the protocol used
*/

#include "simplereceiver.h"

void setup() {
    Serial.begin(115200);

    IrReceiver.begin(RECEIV_PIN, false); //disables LED feedback
    Serial.print("IR receiver initialized on ");
    printActiveIRProtocols(&Serial);
}

void loop() {
    if (IrReceiver.decode()) {
        Serial.println();
    }
}