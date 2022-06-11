#pragma once
#include "pin.hpp"
#include "stm32f103xb.h"


class DHT22{
    public:
    /**
     * @brief Konstruktor obiektu DHT22
     * 
     */
    DHT22(GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin): pin(Pin(GPIO_Port,GPIO_Pin)){};
    void read();
    float getTemp();
    float getHumid();

    private:
    void init();
    bool checkResponse();
    uint8_t readByte();
    float temperature = 0;
    float humidity = 0;
    Pin pin;
};