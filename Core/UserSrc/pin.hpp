#pragma once
#include "../../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

/**
 * @brief Wrapper pinu do klasy
 * 
 */
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
         * @brief Stan przycisku
         * 
         */
        enum PinState{
          StillUnpressed,
          Pressed,
          StillPressed,
          Unpressed
        };


        /**
         * @brief Konstruktor pin'u
         * 
         * @param[in] GPIOx Szereg portu GPIO
         * @param[in] GPIO_Pin Port GPIO
         */
        Pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin): GPIO_Port(GPIOx), GPIO_Pin(GPIO_Pin) {};

        /**
         * @brief Ustawia tryb pinu w zależności od wybranego trybu.
         * 
         * @param[in] mode Tryb pinu w którym pin powinien się znaleźć
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
        volatile GPIO_PinState readPin();

        /**
         * @brief Wpisuje stan na określony pin
         * 
         * @param[in] state stan pinu jaki ma zostać ustawiony
         */
        void writePin(bool state);
        
        /**
         * @brief Getter trybu pinu
         * 
         * @return PinMode Tryb w którym pin się obecnie znajduje
         */
        PinMode getMode();

        /**
         * @brief Getter stanu pinu
         * 
         * @return stan pinu wg Pin::PinState
         */
        PinState getPinState();

        /**
         * @brief Setter stanu pinu.
         * 
         * @param[in] newState Nowy stan pinu.
         */
        void setState(Pin::PinState newState);

    private:
        /**
         * @brief metoda odliczająca następny stan pinu.
         * 
         * @param[in] nextState Sygnał wymagany na zmianę stanu od przycisku 
         * @return true Zmiana stanu powinna nastąpić teraz
         * @return false Zmiana stanu nie powinna nastąpić
         */
        bool buttonCounter(GPIO_PinState nextState);

        PinMode currentMode;
        PinState currentState = PinState::StillUnpressed;
        GPIO_TypeDef * volatile GPIO_Port;
        uint16_t volatile GPIO_Pin;
        uint8_t counter = 0;
};