//==============================================
// File:    M5Stick_ESPNOW.h
//
// Author:  J. Hathway
//
// Description:
//     - Functions for sending/receiving ESPNOW
//       messages on M5StickCPlus
//===============================================

#include <esp_now.h>
#include <WiFi.h>

esp_now_peer_info_t _peerInfo;

//==============================================
// PAIR DEVICES
void sendTo(uint8_t *_address)
{
    // register peer
    memcpy(_peerInfo.peer_addr, _address, 6);
    if (esp_now_add_peer(&_peerInfo) != ESP_OK)
    {
        M5.Lcd.println("Failed to add peer");
        return;
    }
}

//==============================================
// INITIALISE ESPNOW SEND
void espInitSend()
{
    // set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // init ESPNOW
    if (esp_now_init() != ESP_OK)
    {
        M5.Lcd.println("Error initializing ESP-NOW");
        return;
    }

    // function called when message is sent
    esp_now_register_send_cb(
        [](const uint8_t *mac_addr, esp_now_send_status_t status)
        {
            if (status != ESP_NOW_SEND_SUCCESS)
                M5.Lcd.println("Failed to deliver");
        });

    // register peer
    _peerInfo.channel = 0;
    _peerInfo.encrypt = false;
}

//==============================================
// INITIALISE ESPNOW RECEIVE
void espInitRcv()
{
    // Set device as a Wi-Fi Station
    WiFi.mode(WIFI_STA);

    // init ESPNOW
    if (esp_now_init() != ESP_OK)
    {
        M5.Lcd.println("Error initializing ESP-NOW");
        return;
    }
}

//==============================================
// ESP NOW SEND
template <typename T>
void espSend(T _message)
{
    // send message via ESPNOW
    esp_err_t result = esp_now_send(0, (uint8_t *)&_message, sizeof(_message));

    if (result != ESP_OK)
        M5.Lcd.println("Error sending the data");
}

//==============================================
// ESPNOW RECEIVE
void *_ptr = nullptr;

template <typename T>
void espReceive(T &_message)
{
    _ptr = &_message;

    // function called when receive is registered
    esp_now_register_recv_cb(
        [](const uint8_t *_mac, const uint8_t *_incomingData, int _len)
        {
            memcpy(_ptr, _incomingData, sizeof(*(T *)_ptr));
        });
}