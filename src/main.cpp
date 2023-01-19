//==============================================
// File:    M5StickCPlus_SendESPNOW
//
// Author:  J. Hathway
//
// Description:
//     - Send incoming ESP NOW messages
//     - Repeat every 10 seconds
//===============================================

#include <M5StickCPlus.h>
#include "M5Stick_ESPNOW.h"

float outgoingMessage = 5.0;

void setup()
{
  // Init Serial Monitor
  M5.begin();

  uint8_t broadcastAddress[] = {0x4C, 0x75, 0x25, 0x9F, 0x64, 0xF0};
  espInit(broadcastAddress);
}

void loop()
{
  espSend<float>(outgoingMessage);
  delay(10000);
}
