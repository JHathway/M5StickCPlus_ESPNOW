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
#include "M5Stick_ESPNOW.h"

// variable to store received messages
// ***MUST be same data type as data being sent
int message = 0;
int newMessage = 0;

void setup()
{
  // initialise M5Stick
  M5.begin();

  // initialise ESPNOW receive
  espInitRcv();

  // copies received messages to input paramter
  // ***MUST specify data type
  espReceive<int>(message);

  M5.Lcd.setTextSize(5);
}

void loop()
{
  if (message != newMessage)
  {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);

    M5.Lcd.print(message);
    newMessage = message;    
  }
}