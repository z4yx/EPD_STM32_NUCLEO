
#ifndef _DISPLAY_EPD_W21_AUX_H_
#define _DISPLAY_EPD_W21_AUX_H_
#include "stm32l0xx_hal.h"
#include "stm32l0xx_ll_spi.h"


// #define EPD_W21_MOSI_0	HAL_GPIO_WritePin(GPIOA, MOSI_Pin, GPIO_PIN_RESET)
// #define EPD_W21_MOSI_1	HAL_GPIO_WritePin(GPIOA, MOSI_Pin, GPIO_PIN_SET)

// #define EPD_W21_CLK_0	HAL_GPIO_WritePin(GPIOA, SCK_Pin, GPIO_PIN_RESET)
// #define EPD_W21_CLK_1	HAL_GPIO_WritePin(GPIOA, SCK_Pin, GPIO_PIN_SET)

#define EPD_W21_CS_0	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET)
#define EPD_W21_CS_1	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET)

#define EPD_W21_DC_0	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET)
#define EPD_W21_DC_1	HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET)

#define EPD_W21_RST_0	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET)
#define EPD_W21_RST_1	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET)

// #define EPD_W21_BS_0	HAL_GPIO_WritePin(GPIOB, GPIO_Pin_11, GPIO_PIN_RESET)

#define EPD_W21_BUSY_LEVEL 0
#define isEPD_W21_BUSY HAL_GPIO_ReadPin(BUSY_GPIO_Port, BUSY_Pin) 

static inline void SPI_Write(unsigned char value)
{
    while(!LL_SPI_IsActiveFlag_TXE (SPI1));
    LL_SPI_TransmitData8(SPI1, value);
    while(!LL_SPI_IsActiveFlag_RXNE (SPI1));
    LL_SPI_ReceiveData8(SPI1);
}
static inline void driver_delay_xms(unsigned long xms)
{
    HAL_Delay(xms);
}

#endif
/***********************************************************
						end file
***********************************************************/


