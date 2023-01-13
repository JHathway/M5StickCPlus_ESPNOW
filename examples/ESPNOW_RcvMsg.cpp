//==============================================
// File:    M5StickCPlus_RcvESPNOW
//
// Author:  J. Hathway
//
// Description:
//     - Receive incoming ESP NOW messages
//     - Print to LCD every 10 seconds
//===============================================

#include <M5StickCPlus.h>
#include "ESPNOW_Receive.h"

// variable to store received messages
float message = 0;

void setup()
{
  // initialise M5Stick
  M5.begin();

  // copies received messages to input paramter
  espReceive<float>(message);
}

void loop()
{
  // print every 10 seconds
  M5.Lcd.print(message);
  delay(10000);
}