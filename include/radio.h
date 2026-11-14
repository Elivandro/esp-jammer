#ifndef RADIO_H
#define RADIO_H

#include "RF24.h"

extern bool jammersActive; 

void handleSerialInput();
void initializeJammers();
void deactivateJammers();
void runCurrentMode();
void updateChannels(byte newCh[4]);
void configureRadio(RF24 &radio, byte channel);

#endif