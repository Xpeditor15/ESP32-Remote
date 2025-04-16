/*
This example receives the IR signal and tries to decode it and display the protocol used
*/

#include "main.h"

IRrecv irrecv(RECEIV_PIN);

decode_results results;

void setup() {
    Serial.begin(115200);
    irrecv.enableIRIn();
    while (!Serial)
        delay(50);
    Serial.println();
    Serial.print(F("IR sensor is now initialized on"));
    Serial.println(RECEIV_PIN);
}

void loop() {
    if (irrecv.decode(&results)) {
        serialPrintUint64(results.value, HEX);
        Serial.println("");
        irrecv.resume();
    }
    delay(100);
}