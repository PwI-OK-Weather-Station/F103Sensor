#include "pin.hpp"
#include "stm32f1xx_hal_gpio.h"

void Pin::setMode(PinMode mode){
    switch (mode){
        case PinMode::Input: {
            setModeInput();
            break;
        }
        case PinMode::Output: {
            setModeOutput();
            break;
        }
        case PinMode::Uninitialized: {
            break;
        }
    }

}
void Pin::setModeInput(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIO_Port, &GPIO_InitStruct);
}

void Pin::setModeOutput(){
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIO_Port, &GPIO_InitStruct);

}

volatile GPIO_PinState Pin::readPin(){
    return HAL_GPIO_ReadPin(GPIO_Port, GPIO_Pin);
}

void Pin::writePin(bool state){
    HAL_GPIO_WritePin(GPIO_Port, GPIO_Pin, (state?GPIO_PIN_SET:GPIO_PIN_RESET));
}

bool Pin::buttonCounter(GPIO_PinState nextState){
    if(readPin() == nextState){
        counter++;
        if(counter > 10){
            counter=0;
            return true;
        }
    }
    else{
        counter = 0;
    }
    return false;
}

Pin::PinState Pin::getPinState(){
    switch(currentState){
        case Pin::PinState::StillUnpressed:{
            if(buttonCounter(GPIO_PIN_RESET)){
                currentState = PinState::Pressed;
            }
            break;
        }
        case Pin::PinState::Pressed:{
            currentState = PinState::StillPressed;
            break;
        }
        case Pin::PinState::StillPressed:{
            if(buttonCounter(GPIO_PIN_SET)){
                currentState = PinState::Unpressed;
            }
            break;
        }
        case Pin::PinState::Unpressed:{
            currentState = PinState::StillUnpressed;
            break;
        }
    }
    return currentState;
}

void Pin::setState(Pin::PinState newState){
    currentState = newState;
}