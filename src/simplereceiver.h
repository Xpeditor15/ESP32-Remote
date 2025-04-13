/*
Header file used for simplereceiver.cpp
*/

#ifndef SIMPLERECEIVER_H
#define SIMPLERECEIVER_H

#include <Arduino.h>

#if !defined(RAW_BUFFER_LENGTH) //To detect IR signals from air condition remotes, 750 is needed. Default is 200
    #if !((defined(RAMEND) && RAMEND <= 0x4FF) || (defined(RAMSIZE) && RAMSIZE < 0x4FF))
    #define RAW_BUFFER_LENGTH 750
    #endif
#endif

#include <IRremote.hpp>

//definitions for IR receiver
#define RECEIV_PIN 15

#endif