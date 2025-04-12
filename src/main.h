/*
Header file used for including dependencies for the project and function declarations
*/

#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#include <IRremote.hpp>

//definitions for IR receiver and transmitter data pins
#define RECEIV_PIN 15 //
#define TRANS_PIN 40

//definitions for LCD screen pins
#define TFT_CS 10
#define TFT_DC 8
#define TFT_RST 9
#define TFT_LED 21

#define Button 42 //button used to send IR signals

#endif