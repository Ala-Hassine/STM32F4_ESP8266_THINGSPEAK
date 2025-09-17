# STM32F4_ESP8266_THINGSPEAK
IoT Project : Send ADC Data From STM32 + ESP8266 To ThingSpeak Using Sensor.

# Setup Hardware

## USB To TTL Serial Adapter

| USB To TTL | MCU Pin |
|------------|---------|
| 5V         | 5V      |
| GND        | GND     |
| TX         | PA3     |
| RX         | PA2     |

**Interface:** UART2

---

## ESP8266 WiFi Module

| ESP8266   | MCU Pin |
|-----------|---------|
| GND       | GND     |
| 5V        | 5V      |
| CH-PD/EN  | 5V      |
| GPIO0     | 5V      |
| GPIO2     | 5V      |
| TX        | PC7     |
| RX        | PC6     |

**Interface:** UART6

---

## Potentiometer

| POT | MCU Pin |
|-----|---------|
| 5V  | 5V      |
| GND | GND     |
| OUT | PA4     |

**Interface:** ADC

---
