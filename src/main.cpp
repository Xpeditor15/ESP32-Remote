/*
This example receives the IR signal and tries to decode it and display the protocol used
*/

#include "main.h"

void setup() {
    Serial.begin(115200);

    IrReceiver.begin(RECEIV_PIN, false); //disables LED feedback
    Serial.print("IR receiver initialized on ");
    printActiveIRProtocols(&Serial);
}   

void loop() {
    if (IrReceiver.decode()) {
        Serial.println();
        IrReceiver.printIRResultMinimal(&Serial);

        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            Serial.println(F("Received unknown protocol"));
            IrReceiver.printIRResultRawFormatted(&Serial, true);
            IrReceiver.resume();
        } else {
            IrReceiver.resume();
            IrReceiver.printIRResultShort(&Serial);
            IrReceiver.printIRSendUsage(&Serial);
        }
        Serial.println();

        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
            Serial.println(F("Repeat received. Here you can repeat the same action as before"));
        }
    }
}