# STM32F4_ESP8266_THINGSPEAK
IoT Project : Send ADC Data From STM32 + ESP8266 To ThingSpeak Using Sensor.

## Hardware Setup
1. USB To TTL  	==>		MCU 	
=============
5V	==>	5V	
GND	==>	GND	
TX	==>	PA3	
RX	==>	PA2	
=============
2. ESP822 		==>		MCU 	
=============
GND			==>	GND	
5V			==>	5V	
CH-PD/EN	==>	5V	
GPIO0		==>	5V	
GPIO2		==>	5V	
TX			==>	PC7	
RX			==>	PC6	
=============
3. POT			==>		MCU 	
=============
5V	==>	5V	
GND	==>	GND	
OUT	==>	PA4	
=============
