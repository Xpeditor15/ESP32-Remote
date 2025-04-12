#include "main.h"

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
    Serial.begin(115200); 

    pinMode(RGB_BUILTIN, OUTPUT);
    pinMode(TFT_LED, OUTPUT);
    pinMode(Button, INPUT_PULLUP); //sets the RGB light and LCD backlight as output, button as input pullup
    
    digitalWrite(TFT_LED, HIGH); //sets the LCD backlight as high so the screen lights up
    
    tft.initR(INITR_144GREENTAB);

    tft.setFont();
    tft.fillScreen()

    IrReceiver.begin(RECEIV_PIN, false); //initializes the IR receiver
    Serial.println("IR receiver initialized");
    IrSender.begin(TRANS_PIN); //initializes the IR transmitter
    Serial.println("IR transmitter initialized"); 
    disableLEDFeedback();
}

void loop() {
    if (IrReceiver.decode()) {
        char protocol[20];
        Serial.println("Successfully decoded IR signals");
    }

    delay(1000);
}