#pragma once
#include "pin.hpp"

#define BMP280_CHIP_ID 0x58

#define BMP280_SPI_MASK_WRITE 0b01111111

#define BMP280_REG_ID         0xD0
#define BMP280_REG_RESET      0xE0
#define BMP280_REG_STATUS	  0xF3
#define BMP280_REG_CTRL_MEAS  0xF4
#define BMP280_REG_CONFIG     0xF5
#define BMP280_REG_PRESS      0xF7
#define BMP280_REG_TEMP       0xFA
#define BMP280_REG_CTRL       0xF4
#define BMP280_REG_CALIB      0x88
#define BMP280_REG_DATA       0xF7
#define BMP280_RESET_VALUE    0xB6

class BMP280
{
public:
    

	/**
	 * @brief Konstruktor do czujnika 
	 * 
	 * @param[in,out] handle HAL'owski Handler od SPI do którego podłączony jest nasz czujnik
	 * @param[in] GPIO_Port Port chip select'u
	 * @param[in] GPIO_Pin Pin portu chip select'u
	 */
	BMP280(SPI_HandleTypeDef *handle, GPIO_TypeDef* GPIO_Port, uint16_t GPIO_Pin):cs(new Pin(GPIO_Port,GPIO_Pin)), spiHandle(handle){cs->setModeOutput();};

	/**
	 * @brief Getter ciśnienia z po pomiarze
	 * 
	 * @return float ciśnienie
	 */
    float getPressure();

	/**
	 * @brief Inicjalizator czujnika wraz z odpowiednimi rejestrami
	 * 
	 * @return uint8_t 1 Klucz id jest niepoprawny
	 * @return uint8_t 0 Wszystko zostało zainicjalizowane poprawnie
	 */
	uint8_t initialize();

	/**
	 * @brief Wykonaj pomiar
	 * 
	 */
	void measure();

	/**
	 * @brief Getter id urządzenia
	 * 
	 * @return uint8_t id od urządzenia BMP280 powinno wynosić 0x58
	 */
	uint8_t getID();

private:
    float temperature = 0;
    float pressure = 0;
    Pin* cs;
	SPI_HandleTypeDef *spiHandle;
	float p_reference = 0;
	int32_t t_fine = 0;

	/**
	 * @brief parametry kompensacyjne odczytane z urządzenia
	 * 
	 */
	struct CompensationParameters
	{
		uint16_t dig_p1;
		int16_t dig_p2;
		int16_t dig_p3;
		int16_t dig_p4;
		int16_t dig_p5;
		int16_t dig_p6;
		int16_t dig_p7;
		int16_t dig_p8;
		int16_t dig_p9;
	} compensationParameters;

	/**
	 * @brief Resetowanie wartości rejestru
	 */
	void reset();

	/**
	 * @brief Odczytaj z urządzenia kompensacje
	 */
	void readCompensationParameters();

	/**
	 * @brief kompensuje wartości odczytane z przetwornika adc ciśnienia.
	 * 
	 * @param[in] adc_P wartość odczytana z przetwornika czujnika ciśnienia
	 * @return uint32_t wartość skompensowana o parametry fabryczne czujnika.
	 */
	uint32_t compensatePressure(int32_t adc_P);

	/**
	 * @brief Odczytaj dane z określonego rejestru
	 * 
	 * @param[in] address Adres rejestru
	 * @return uint8_t Wartość z rejestru
	 */
	uint8_t readRegister(uint8_t address);

	/**
	 * @brief Wpisz dane do rejestru.
	 * 
	 * @param[in] address Adres rejestru.
	 * @param[in] value Nowa wartość rejestru.
	 */
	void writeRegister(uint8_t address, uint8_t value);

	/**
	 * @brief Odczytaj wiele bajtóœ z rejestru/
	 * 
	 * @param[in] address Adres rejestru początkowego.
	 * @param[out] values Wartości odczytane z rejestrów.
	 * @param[in] length ilość bajtów. 
	 */
	void readMBRegister(uint8_t address, uint8_t *values, uint8_t length);

	/**
	 * @brief Wrapper SPI transmitRecive HAL'a
	 * 
	 * @param[in] tx_message Wiadoomość do przesłania.
	 * @return uint8_t Bajt zwrócony przez czujnik 
	 */
	uint8_t spiReadWrite(uint8_t tx_message);
};