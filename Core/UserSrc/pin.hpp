#pragma once
#include "../../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

class Pin{
    public:
        /**
         * @brief Tryby w których pin może się znaleźć
         */
        enum PinMode{
          Input,
          Output,
          Uninitialized  
        };
        /**
         * @brief Konstruktor pin'u
         * 
         * @param GPIOx Szereg portu GPIO
         * @param GPIO_Pin Port GPIO
         */
        Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin): GPIO_Port(GPIOx), GPIO_Pin(GPIO_Pin) {};

        /**
         * @brief Ustawia tryb pinu w zależności od wybranego trybu.
         * 
         * @param mode Tryb pinu w którym pin powinien się znaleźć
         */
        void setMode(PinMode mode);

        /**
        * @brief Ustawia pin jako output
        * 
        */
        void setModeOutput();
        /**
         * @brief Ustawia pin jako input
         * 
         */
        void setModeInput();
        /**
         * @brief Odczyt pinu
         * 
         * @return true Stan wysoki na pinie
         * @return false Stan niski na pinie
         */
        bool readPin();

        /**
         * @brief Wpisuje stan na określony pin
         * 
         * @param state stan pinu jaki ma zostać ustawiony
         */
        void writePin(bool state);
        
        /**
         * @brief Getter trybu pinu
         * 
         * @return PinMode Tryb w którym pin się obecnie znajduje
         */
        PinMode getMode();
    private:
        PinMode currentMode;
        GPIO_TypeDef *GPIO_Port;
        uint16_t GPIO_Pin;
};