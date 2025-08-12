#ifndef VOICE_COMMANDS_H
#define VOICE_COMMANDS_H

#include <Arduino.h>
#include "BluetoothSerial.h"

// Global Bluetooth instance (defined in voice_commands.cpp)
extern BluetoothSerial SerialBT;

// Initialize Bluetooth and print available commands
void initVoiceCommands();

// Poll and handle incoming Bluetooth commands (non-blocking)
void handleVoiceCommands();

// FreeRTOS task wrapper that periodically calls handleVoiceCommands()
void TaskBluetooth(void* pvParameters);

#endif // VOICE_COMMANDS_H


