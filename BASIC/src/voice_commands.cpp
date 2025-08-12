#include "voice_commands.h"
#include "actuators.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Single global Bluetooth instance
BluetoothSerial SerialBT;

// Simple helper to normalize input
static String toLowerTrimmed(String s) {
  s.trim();
  s.toLowerCase();
  return s;
}

void initVoiceCommands() {
  SerialBT.begin("ESP32-Voice");
  Serial.println("=== Bluetooth Commands ===");
  Serial.println("open door");
  Serial.println("close door");
  Serial.println("ac on");
  Serial.println("ac off");
  Serial.println("==========================");
}

void handleVoiceCommands() {
  if (!SerialBT.available()) return;

  String cmd = SerialBT.readStringUntil('\n');
  cmd = toLowerTrimmed(cmd);

  if (cmd == "open door") {
    setServoPosition(180);
    Serial.println("BT: Door Opened");
  } else if (cmd == "close door") {
    setServoPosition(0);
    Serial.println("BT: Door Closed");
  } else if (cmd == "ac on") {
    turnOnFan();
    Serial.println("BT: AC ON");
  } else if (cmd == "ac off") {
    turnOffFan();
    Serial.println("BT: AC OFF");
  } else if (cmd.length() > 0) {
    Serial.print("BT: Unknown command -> ");
    Serial.println(cmd);
  }
}

void TaskBluetooth(void* pvParameters) {
  (void) pvParameters;
  for(;;) {
    handleVoiceCommands();
    vTaskDelay(pdMS_TO_TICKS(30));
  }
}


