#include <M5StickCPlus.h>
#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH THE MAC Address of your receiver
uint8_t broadcastAddress[] = {0x4C, 0x75, 0x25, 0x9F, 0x64, 0xF0};

float outgoingMessage = 5.;

// Variable to store if sending data was successful
String success;

esp_now_peer_info_t peerInfo;

// Callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
{

  M5.Lcd.print("\r\nLast Packet Send Status:\t");

  M5.Lcd.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");

  if (status == 0)
  {
    success = "Delivery Success";
  }
  else
  {
    success = "Delivery Fail";
  }
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

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    M5.Lcd.println("Failed to add peer");
    return;
  }

}

void loop()
{

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&outgoingMessage, sizeof(outgoingMessage));

  if (result == ESP_OK)
  {
    M5.Lcd.println("Sent with success");
  }
  else
  {
    M5.Lcd.println("Error sending the data");
  }

  delay(10000);
}
