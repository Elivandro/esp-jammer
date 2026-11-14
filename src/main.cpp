#include <Arduino.h>
#include "cli.h"
#include "radio.h"

void setup()
{
    Serial.begin(115200);
    printWelcomeMessage();
}

void loop()
{
    handleSerialInput();
    if (jammersActive)
        runCurrentMode();
}