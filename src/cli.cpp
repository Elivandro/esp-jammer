#include <Arduino.h>
#include "cli.h"

void printWelcomeMessage()
{
    Serial.println("\nRF Jammer Controller Ready for 2 nRF24L01 Modules");
    Serial.println("System is in standby mode");
    printModeHelp();
    Serial.println("Send 'start' to initialize jammers");
    Serial.println("Send 'stop' to deactivate jammers");
}

void printModeHelp()
{
    Serial.println("\nAvailable commands:");
    Serial.println("start  - Initialize and activate jammers");
    Serial.println("stop   - Deactivate jammers");
    Serial.println("help/? - Show this help");
    Serial.println("\nAvailable modes (send single character):");
    Serial.println("r - Random Bluetooth hopping (odd/even)");
    Serial.println("w - WiFi channels");
    Serial.println("b - BLE advertising channels");
    Serial.println("u - USB wireless channels");
    Serial.println("v - Video streaming channels");
    Serial.println("c - RC toys/drones channels");
    Serial.println("f - Full spectrum (all channels)");
}

void printModeName(char m)
{
    switch (m)
    {
    case 'r':
        Serial.println("Random Bluetooth hopping (odd/even)");
        break;
    case 'w':
        Serial.println("WiFi channels");
        break;
    case 'b':
        Serial.println("BLE advertising channels");
        break;
    case 'u':
        Serial.println("USB wireless channels");
        break;
    case 'v':
        Serial.println("Video streaming channels");
        break;
    case 'c':
        Serial.println("RC toys/drones channels");
        break;
    case 'f':
        Serial.println("Full spectrum (all channels)");
        break;
    default:
        Serial.println("Unknown mode");
        break;
    }
}

bool isValidMode(char m)
{
    return (m == 'r' || m == 'w' || m == 'b' || m == 'u' || m == 'v' || m == 'c' || m == 'f');
}