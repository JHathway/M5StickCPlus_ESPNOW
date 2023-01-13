#include <esp_now.h>
#include <WiFi.h>

void *_ptr = nullptr;

void espInit()
{
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        M5.Lcd.println("Error initializing ESP-NOW");
        return;
    }
}

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
