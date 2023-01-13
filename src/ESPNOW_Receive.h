#include <esp_now.h>
#include <WiFi.h>

float *ptr = nullptr;

void espReceive(float &_message)
{
    ptr = &_message;
    
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != ESP_OK)
    {
        M5.Lcd.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(
        [](const uint8_t *_mac, const uint8_t *_incomingData, int _len)
        {
            memcpy(ptr, _incomingData, sizeof(*ptr));
        });
}