#include "ESP8266.h"
#include "stdlib.h"

static char rx_buffer[512];
static ESP_Status SendCommand(const char *cmd, const char *ack, uint32_t timeout);

ESP_Status ESP8266_INIT(void)
{
    printf("Initializing ESP8266\n");
    HAL_Delay(1000);
    if (SendCommand("AT\r\n", "OK", 2000) != ESP_OK)
    {
        printf("ESP8266 Not Responding\n");
        return ESP_ERROR;
    }
    SendCommand("ATE0\r\n", "OK", 2000); // Disable Echo
    printf("ESP8266 Initialized Successfully\n");
    return ESP_OK;
}

ESP_Status ESP8266_CONNECTWIFI(const char *ssid, const char *password)
{
    char cmd[128];
    snprintf(cmd, sizeof(cmd), "AT+CWMODE=1\r\n");
    if (SendCommand(cmd, "OK", 2000) != ESP_OK)
    {
        printf("Station Mode Failed\n");
        return ESP_ERROR;
    }
    printf("Connecting To : %s\n", ssid);
    snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"\r\n", ssid, password);
    if (SendCommand(cmd, "WIFI CONNECTED", 10000) != ESP_OK)
    {
        printf("WiFi Connection Failed\n");
        return ESP_ERROR;
    }
    printf("WiFi Connected\n");
    return ESP_OK;
}

ESP_Status ESP8266_SENDDATATOCLOUD(const char *apiKey, float value1)
{
    char cmd[128];
    // Start TCP connection
    snprintf(cmd, sizeof(cmd), "AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80\r\n");
    if (SendCommand(cmd, "CONNECT", 5000) != ESP_OK)
    {
        printf("TCP Connection Failed\n");
        return ESP_ERROR;
    }
    // Build and send HTTP request
    char httpReq[128];
    snprintf(httpReq, sizeof(httpReq), "GET /update?api_key=%s&field1=%.2f\r\n", apiKey, value1);
    snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%d\r\n", (int)strlen(httpReq));
    if (SendCommand(cmd, ">", 2000) != ESP_OK)
    {
        printf("Send Preparation Failed\n");
        return ESP_ERROR;
    }
    if (SendCommand(httpReq, "SEND OK", 5000) != ESP_OK)
    {
        printf("HTTP Send Failed\n");
        return ESP_ERROR;
    }
    printf("Data Sent To Cloud With Successfully\n");
    return ESP_OK;
}

static ESP_Status SendCommand(const char *cmd, const char *ack, uint32_t timeout)
{
    uint8_t  ch;
    uint16_t index 	= 0;
    uint32_t start 	= HAL_GetTick();
    memset(rx_buffer, 0, sizeof(rx_buffer));
    // Send command
    if (strlen(cmd) > 0)
    {
        HAL_UART_Transmit(&ESP_UART, (uint8_t*)cmd, strlen(cmd), HAL_MAX_DELAY);
    }
    // Receive response
    while ((HAL_GetTick() - start) < timeout && index < sizeof(rx_buffer) - 1)
    {
        if (HAL_UART_Receive(&ESP_UART, &ch, 1, 10) == HAL_OK)
        {
            rx_buffer[index++] = ch;
            rx_buffer[index] = '\0';
            if (strstr(rx_buffer, ack))
            {
                return ESP_OK; // ACK found
            }

            if (strstr(rx_buffer, "busy"))
            {
                HAL_Delay(1500);
                return SendCommand(cmd, ack, timeout); // Retry
            }
        }
    }
    return ESP_TIMEOUT; // Timeout
}
