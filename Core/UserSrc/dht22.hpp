#pragma once
#include "pin.hpp"
#include "stm32f103xb.h"


class DHT22{
    public:
    /**
     * @brief Konstruktor obiektu DHT22.
     * 
     * @param[in] GPIO_Port Port do którego DHT22 jest przypięty.
     * @param[in] GPIO_Pin Pin na porcie do którego czujnik jest przypięty.
     */
    DHT22(GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin): pin(new Pin(GPIO_Port,GPIO_Pin)){};

    /**
     * @brief Odczytaj wartości z DHT22.
     * 
     */
    void read();

    /**
     * @brief Getter temperatury.
     * 
     * @return float temperatura odczytana z czujnika.
     */
    float getTemp();
    
    /**
     * @brief Getter wilgotności powietrza.
     * 
     * @return float wilgotność powietrza.
     */
    float getHumid();

    private:

    /**
     * @brief Inicjalizuj czujnik
     * 
     */
    void init();

    /**
     * @brief Sprawdź czy czujnik zaczął nadawać
     * 
     * @return true czujnik nadaje
     * @return false czujnik nie nadaje
     */
    bool checkResponse();

    /**
     * @brief Odczytaj bajt danych z czujnika
     * 
     * @return uint8_t Bajt danych odczytany
     */
    uint8_t readByte();

    
    float temperature = 0;
    float humidity = 0;
    Pin* pin;
};