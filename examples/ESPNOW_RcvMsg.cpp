
#include <M5StickCPlus.h>
#include <esp_now.h>
#include <WiFi.h>

float incomingMessage;


// Callback when data is received
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{

  memcpy(&incomingMessage, incomingData, sizeof(incomingMessage));

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("Bytes received: ");
  M5.Lcd.println(len);

  M5.Lcd.println(incomingMessage);
}

void setup()
{
  // Init Serial Monitor
  M5.begin();

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK)
  {
    M5.Lcd.println("Error initializing ESP-NOW");
    return;
  }

}

void loop()
{}