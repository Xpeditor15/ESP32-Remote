#include "main.h"

void setup() {
    Serial.begin(115200);

    pinMode(RGB_BUILTIN, OUTPUT);

    IrReceiver.begin(RECEIV_PIN, false);
    Serial.println("IR receiver initialized");
    disableLEDFeedback(); 
}

void loop() {
    Serial.println("Hello world");

    if (IrReceiver.decode()) {
        char protocol[20];
        Serial.println("Successfully decoded IR signals");
    }

    delay(1000);
}