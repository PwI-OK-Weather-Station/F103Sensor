#include "dht22.hpp"
#include "stm32f1xx_hal_gpio.h"
#include "util.hpp"
#include <stdint.h>



uint8_t DHT22::readByte(){
    uint8_t i,j;
	for (j=0;j<8;j++)
	{
		while (!(pin.readPin()));
		delay_us(40);
		if (!(pin.readPin()))
		{
			i&= ~(1<<(7-j));
		}
		else i|= (1<<(7-j));
		while ((pin.readPin()));
	}
	return i;
}

void DHT22::init(){

    
    pin.setModeOutput();
    pin.writePin(false);

	delay_us (1200);

    pin.writePin(true);
    delay_us (20);
	pin.setMode(Pin::PinMode::Input);
}

bool DHT22::checkResponse(){
    uint8_t Response = 0;
	delay_us (40);
	if (!(pin.readPin()))
	{
		delay_us (80);
		if ((pin.readPin())) Response = 1;
		else Response = -1;
	}
	while ((pin.readPin()));

	return Response;
}

void DHT22::read(){
    init();
    checkResponse();
    

    uint8_t Rh_byte1, Rh_byte2, Temp_byte1, Temp_byte2;
    uint16_t SUM;
    Rh_byte1 = readByte();
	Rh_byte2 = readByte();
	Temp_byte1 = readByte();
	Temp_byte2 = readByte();
	SUM = readByte();
	if(SUM == (Rh_byte1+Rh_byte2+Temp_byte1+Temp_byte2)){

        temperature = ((Temp_byte1<<8)|Temp_byte2)/10.0f;
        humidity = ((Rh_byte1<<8)|Rh_byte2)/10.0f;
    }
}

float DHT22::getHumid(){
    return humidity;
}

float DHT22::getTemp(){
    return temperature;
}