#include <esp_now.h>
#include <WiFi.h>

uint8_t _broadcastAddress[] = {0x4C, 0x75, 0x25, 0x9F, 0x64, 0xF0};
esp_now_peer_info_t _peerInfo;

// INITIALISE ESPNOW SEND
void espInit(uint8_t *_address)
{
    //_broadcastAddress = _address;

    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        M5.Lcd.println("Error initializing ESP-NOW");
        return;
    }

    // Register peer
    memcpy(_peerInfo.peer_addr, _broadcastAddress, 6);
    _peerInfo.channel = 0;
    _peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&_peerInfo) != ESP_OK)
    {
        M5.Lcd.println("Failed to add peer");
        return;
    }
    else
    {
        M5.Lcd.println("Peer added:");
    }

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(
        [](const uint8_t *mac_addr, esp_now_send_status_t status)
        {
            M5.Lcd.print("\r\nLast Packet Send Status:\t");

            M5.Lcd.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
        });
}

// INITIALISE ESPNOW RECEIVE
void espInit()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        M5.Lcd.println("Error initializing ESP-NOW");
        return;
    }
}

void *_ptr = nullptr;

template <typename T>
void espReceive(T &_message)
{
    _ptr = &_message;

    esp_now_register_recv_cb(
        [](const uint8_t *_mac, const uint8_t *_incomingData, int _len)
        {
            memcpy(_ptr, _incomingData, sizeof(*(T *)_ptr));
        });
}

template <typename T>
void espSend(T _message)
{
    M5.Lcd.println("Sending:" + String(_message));

    // Send message via ESP-NOW
    esp_err_t result = esp_now_send(_broadcastAddress, (uint8_t *)&_message, sizeof(_message));

    if (result == ESP_OK)
    {
        M5.Lcd.println("Sent with success");
    }
    else
    {
        M5.Lcd.println("Error sending the data");
    }
}
