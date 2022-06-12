#include "bmp280.hpp"
#include <stdint.h>
#include <cmath>

uint32_t BMP280::compensatePressure(int32_t uncomp_pres)
{
	int64_t var1, var2, p;

	var1 = ((int64_t) (t_fine)) - 128000;
	var2 = var1 * var1 * (int64_t) compensationParameters.dig_p6;
	var2 = var2 + ((var1 * (int64_t) compensationParameters.dig_p5) * 131072);
	var2 = var2 + (((int64_t) compensationParameters.dig_p4) * 34359738368);
	var1 = ((var1 * var1 * (int64_t) compensationParameters.dig_p3) / 256)
			+ ((var1 * (int64_t) compensationParameters.dig_p2) * 4096);
	var1 = ((INT64_C(0x800000000000) + var1)
			* ((int64_t) compensationParameters.dig_p1)) / 8589934592;
	if (var1 == 0)
	{
		return 0;
	}
	p = 1048576 - uncomp_pres;
	p = (((((p * 2147483648U)) - var2) * 3125) / var1);
	var1 = (((int64_t) compensationParameters.dig_p9) * (p / 8192) * (p / 8192))
			/ 33554432;
	var2 = (((int64_t) compensationParameters.dig_p8) * p) / 524288;
	p = ((p + var1 + var2) / 256)
			+ (((int64_t) compensationParameters.dig_p7) * 16);
	return (uint32_t) p;
}

float BMP280::getPressure(){
    return pressure;
}

uint8_t BMP280::initialize()
{
    auto id = getID();
	if (id != BMP280_CHIP_ID)
	{
		return 1;
	}

	reset();
	HAL_Delay(500);

	// Ustawienia samplingu ciśnienia
	uint8_t ctrl = readRegister(BMP280_REG_CTRL_MEAS);
	ctrl = (ctrl & 0b11100011) | (0b101 << 2);
	ctrl = (ctrl & 0b00011111) | (0b010 << 5);
	ctrl = (ctrl & 0b11111100) | 0b11;
	writeRegister(BMP280_REG_CTRL, ctrl);

    uint8_t conf = readRegister(BMP280_REG_CONFIG);
	conf = (conf & 0b11100011) | (0b100 << 2);
	conf = (conf & 0b00011111) | (0b000 << 5);
	writeRegister(BMP280_REG_CONFIG, conf);

	readCompensationParameters();

	return 0;
}

void BMP280::reset()
{
	writeRegister(BMP280_REG_RESET, BMP280_RESET_VALUE);
}

uint8_t BMP280::getID()
{
	return readRegister(BMP280_REG_ID);
}

void BMP280::readCompensationParameters()
{
	uint8_t buf[24];
	readMBRegister(BMP280_REG_CALIB, buf, 24);
	compensationParameters.dig_p1 = ((buf[7] << 8) | buf[6]);
	compensationParameters.dig_p2 = ((buf[9] << 8) | buf[8]);
	compensationParameters.dig_p3 = ((buf[11] << 8) | buf[10]);
	compensationParameters.dig_p4 = ((buf[13] << 8) | buf[12]);
	compensationParameters.dig_p5 = ((buf[15] << 8) | buf[14]);
	compensationParameters.dig_p6 = ((buf[17] << 8) | buf[16]);
	compensationParameters.dig_p7 = ((buf[19] << 8) | buf[18]);
	compensationParameters.dig_p8 = ((buf[21] << 8) | buf[20]);
	compensationParameters.dig_p9 = ((buf[23] << 8) | buf[22]);
}

void BMP280::measure()
{
	uint8_t data[6];
	readMBRegister(BMP280_REG_DATA, data, 6);

	int32_t adc_P = data[0] << 12 | data[1] << 4 | data[2] >> 4;
	pressure = (float) compensatePressure(adc_P) / 25600.0;

}

uint8_t BMP280::readRegister(uint8_t address)
{
	cs->writePin(false);
	spiReadWrite(address);
	uint8_t value = spiReadWrite(0);
	cs->writePin(true);
	return value;
}

void BMP280::writeRegister(uint8_t address, uint8_t value)
{
	cs->writePin(false);
	spiReadWrite(address & BMP280_SPI_MASK_WRITE);
	spiReadWrite(value);
	cs->writePin(true);
}

void BMP280::readMBRegister(uint8_t address, uint8_t *values, uint8_t length)
{
	cs->writePin(false);
	spiReadWrite(address);
	while (length--)
	{
		*values++ = spiReadWrite(0);
	}
	cs->writePin(true);
}

uint8_t BMP280::spiReadWrite(uint8_t tx_message)
{
	uint8_t rx_message = 255;
	HAL_SPI_TransmitReceive(spiHandle, &tx_message, &rx_message, 1,
			HAL_MAX_DELAY);
	return rx_message;
}
