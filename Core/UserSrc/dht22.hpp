#pragma once

#include "util.hpp"

#define DHT22_Pin GPIO_PIN_1
#define DHT22_GPIO_Port GPIOA

typedef struct
{
	float Temperature;
	float Humidity;
} DHT22_DataTypedef;

class DHT22{
    private:
    uint16_t pin = DHT22_Pin;
    GPIO_TypeDef* port = DHT22_GPIO_Port;
    int temp;
};