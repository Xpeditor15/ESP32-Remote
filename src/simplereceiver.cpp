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

void generateTone();
void handleOverflow();
bool detectLongPress(uint16_t aLongPressDurationMillis);

void loop() {
    if (IrReceiver.decode()) {
        Serial.println();
        IrReceiver.printIRResultMinimal(&Serial);

        if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_WAS_OVERFLOW) {
            
        }
    }
}