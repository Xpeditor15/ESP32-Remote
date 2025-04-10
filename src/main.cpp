#include <Arduino.h>
#include <string.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define DECODE_STRICT_CHECKS
#define EXCLUDE_UNIVERSAL_PROTOCOLS
#define USE_SHARP_PROTOCOL
#include <IRremote.hpp>

#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9
#define TFT_LED 21
#define Receiver_Pin 15
#define Transmitter_Pin 40
#define Button 42

const uint16_t Color_Black = 0x0000;
const uint16_t Color_Blue = 0x001F;
const uint16_t Color_Red = 0xF800;
const uint16_t Color_Green = 0x07E0;
const uint16_t Color_Cyan = 0x07FF;
const uint16_t Color_Magenta = 0xF81F;
const uint16_t Color_Yellow = 0xFFE0;
const uint16_t Color_White = 0xFFFF;

int delay_between_repeat = 50;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

struct storedIRDataStruct {
  IRData receivedIRData;

  uint8_t rawCode[RAW_BUFFER_LENGTH];
  uint8_t rawCodeLength;
} sStoredIRData;

bool buttonWasActive;

void compare_protocol(decode_type_t protocol, char *string);
void storeCode();
void sendCode(storedIRDataStruct *aIRDataToSend);

void setup() {
  Serial.begin(115200);

  pinMode(RGB_BUILTIN, OUTPUT);
  pinMode(TFT_LED, OUTPUT);
  pinMode(Button, INPUT_PULLUP);

  digitalWrite(TFT_LED, HIGH);

  tft.initR(INITR_144GREENTAB);

  tft.setFont();
  tft.fillScreen(Color_Blue);
  tft.setTextColor(Color_White);
  tft.setTextSize(1);
  tft.enableDisplay(true);

  IrReceiver.begin(Receiver_Pin, false);
  Serial.println("Ready to receive IR signals");
  IrSender.begin(Transmitter_Pin);
  disableLEDFeedback();
  Serial.println("Ready to send IR signals");
}

/*void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();
  }
}*/

void loop() {
  bool buttonIsActive = (digitalRead(Button) == LOW);

  if (buttonIsActive) {
    if (buttonWasActive) {
      Serial.println(F("Stop receiving"));
      IrReceiver.stop();
    }

    Serial.print(F("Button pressed, now sending"));
    if (buttonWasActive == buttonIsActive) {
      Serial.print(F("Repeat"));
      sStoredIRData.receivedIRData.flags = IRDATA_FLAGS_IS_REPEAT;
    } else {
      sStoredIRData.receivedIRData.flags = IRDATA_FLAGS_EMPTY;
    }
    Serial.flush();
    sendCode(&sStoredIRData);
    delay(delay_between_repeat);
  } else if (buttonWasActive) {
    Serial.println(F("Button released -> start receiving"));
    IrReceiver.start();
  } else if (IrReceiver.decode()) {
    storeCode();
    IrReceiver.resume();
  }

  buttonWasActive = buttonIsActive;
  delay(100);
}

void storeCode() {
  if (IrReceiver.decodedIRData.rawDataPtr->rawlen < 4) {
    Serial.print(F("Ignore data with rawlen="));
    Serial.println(IrReceiver.decodedIRData.rawDataPtr->rawlen);
    return;
  }
  if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT) {
    Serial.println(F("Ignore repeat"));
    return;
  }
  if (IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_AUTO_REPEAT) {
    Serial.println(F("Ignore autorepeat"));
    return;
  }

  sStoredIRData.receivedIRData = IrReceiver.decodedIRData;

  if (sStoredIRData.receivedIRData.protocol == UNKNOWN) {
    Serial.print(F("Received unknwon code and store "));
    Serial.print(IrReceiver.decodedIRData.rawDataPtr->rawlen - 1);
    Serial.println(F(" timing entries as raw "));
    IrReceiver.printIRResultRawFormatted(&Serial, true);
    sStoredIRData.rawCodeLength = IrReceiver.decodedIRData.rawDataPtr->rawlen - 1;

    IrReceiver.compensateAndStoreIRResultInArray(sStoredIRData.rawCode);
  } else {
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    sStoredIRData.receivedIRData.flags = 0;
    Serial.println();
  }
}

void sendCode(storedIRDataStruct *aIRDataToSend) {
  if (aIRDataToSend->receivedIRData.protocol == UNKNOWN) {
    IrSender.sendRaw(aIRDataToSend->rawCode, aIRDataToSend->rawCodeLength, 38);

    Serial.print(F("raw "));
    Serial.print(aIRDataToSend->rawCodeLength);
    Serial.println(F(" marks or spaces"));
  } else {
    IrSender.write(&aIRDataToSend->receivedIRData);
    printIRResultShort(&Serial, &aIRDataToSend->receivedIRData, false);
  }
}


void compare_protocol(decode_type_t protocol, char *string) {
  switch (protocol) {
    case NEC: 
      strcpy(string, "NEC");
      break;
    case NEC2:
      strcpy(string, "NEC2");
      break;
    case SHARP:
      strcpy(string, "SHARP");
      break;
    case APPLE:
      strcpy(string, "APPLE");
      break;
    case DENON:
      strcpy(string, "DENON");
      break;
    case JVC:
      strcpy(string, "JVC");
      break;
    case LG:
      strcpy(string, "LG");
      break;
    case LG2:
      strcpy(string, "LG2");
      break;
    case ONKYO:
      strcpy(string, "ONKYO");
      break;
    case PANASONIC:
      strcpy(string, "PANASONIC");
      break;
    case KASEIKYO:
      strcpy(string, "KASEIKYO");
      break;
    case KASEIKYO_DENON:
      strcpy(string, "KASEIKYO_DENON");
      break;
    case KASEIKYO_SHARP:
      strcpy(string, "KASEIKYO_SHARP");
      break;
    case KASEIKYO_JVC:
      strcpy(string, "KASEIKYO_JVC");
      break;
    case KASEIKYO_MITSUBISHI:
      strcpy(string, "KASEIKYO_MITSUBISHI");
      break;
    case RC5:
      strcpy(string, "RC5");
      break;
    case RC6:
      strcpy(string, "RC6");
      break;
    case SAMSUNG:
      strcpy(string, "SAMSUNG");
      break;
    case SAMSUNGLG:
      strcpy(string, "SAMSUNGLG");
      break;
    case SAMSUNG48:
      strcpy(string, "SAMSUNG48");
      break;
    case SONY:
      strcpy(string, "SONY");
      break;
    case PULSE_DISTANCE:
      strcpy(string, "PULSE DISTANCE");
      break;
    case PULSE_WIDTH:
      strcpy(string, "PULSE WIDTH");
      break;
    case BANG_OLUFSEN:
      strcpy(string, "BANG OLUFSEN");
      break;
    case BOSEWAVE:
      strcpy(string, "BOSEWAVE");
      break;
    case LEGO_PF:
      strcpy(string, "LEGO PF");
      break;
    case MAGIQUEST:
      strcpy(string, "MAGIQUEST");
      break;
    case WHYNTER:
      strcpy(string, "WHYNTER");
      break;
    case FAST:
      strcpy(string, "FAST");
      break;
    default:
      strcpy(string, "UNKNOWN");
  }
}