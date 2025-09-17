#ifndef ESP8266_H
#define ESP8266_H

#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdio.h>

#define ESP_UART 			huart6
#define RX_BUFFER_SIZE 		512
extern UART_HandleTypeDef 	ESP_UART;

typedef enum
{
    ESP_OK = 0,
    ESP_ERROR,
    ESP_TIMEOUT
} ESP_Status;

typedef enum
{
    ESP_DISCONNECTED = 0,
    ESP_CONNECTED
} ESP_ConnectionState;

ESP_Status ESP8266_INIT(void);
ESP_Status ESP8266_CONNECTWIFI(const char *ssid, const char *password);
ESP_Status ESP8266_SENDDATATOCLOUD(const char *apiKey, float value);

#endif
