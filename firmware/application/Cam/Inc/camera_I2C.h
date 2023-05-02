
#ifndef __CAMERA_I2C_H
#define __CAMERA_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2C.h"


#define FMT_JPEG 0x00
#define FMT_RGB565 0x01

#define CAMERA_I2C_ADDRESS ((uint16_t)0x60)
#define CAMERA_I2C_ADDRESS_OV5640 ((uint16_t)0x78)


/* I2C clock speed configuration (in Hz)
   WARNING:
   Make sure that this define is not already declared in other files (ie.
   stm32746g_discovery.h file). It can be used in parallel by other modules. */
#ifndef I2C_SPEED
#define I2C_SPEED ((uint32_t)100000)
#endif /* I2C_SPEED */

/* User can use this section to tailor I2Cx/I2Cx instance used and associated
   resources */
/* Definition for AUDIO and LCD I2Cx resources */
#define DISCOVERY_AUDIO_I2Cx I2C3
#define DISCOVERY_AUDIO_I2Cx_CLK_ENABLE() __HAL_RCC_I2C3_CLK_ENABLE()
#define DISCOVERY_AUDIO_DMAx_CLK_ENABLE() __HAL_RCC_DMA1_CLK_ENABLE()
#define DISCOVERY_AUDIO_I2Cx_SCL_SDA_GPIO_CLK_ENABLE() \
  __HAL_RCC_GPIOH_CLK_ENABLE()

#define DISCOVERY_AUDIO_I2Cx_FORCE_RESET() __HAL_RCC_I2C3_FORCE_RESET()
#define DISCOVERY_AUDIO_I2Cx_RELEASE_RESET() __HAL_RCC_I2C3_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define DISCOVERY_AUDIO_I2Cx_SCL_PIN GPIO_PIN_7
#define DISCOVERY_AUDIO_I2Cx_SCL_SDA_GPIO_PORT GPIOH
#define DISCOVERY_AUDIO_I2Cx_SCL_SDA_AF GPIO_AF4_I2C3
#define DISCOVERY_AUDIO_I2Cx_SDA_PIN GPIO_PIN_8

/* I2C interrupt requests */
#define DISCOVERY_AUDIO_I2Cx_EV_IRQn I2C3_EV_IRQn
#define DISCOVERY_AUDIO_I2Cx_ER_IRQn I2C3_ER_IRQn

/* Definition for external, camera and Arduino connector I2Cx resources */
#define DISCOVERY_EXT_I2Cx I2C1
#define DISCOVERY_EXT_I2Cx_CLK_ENABLE() __HAL_RCC_I2C1_CLK_ENABLE()
#define DISCOVERY_EXT_DMAx_CLK_ENABLE() __HAL_RCC_DMA1_CLK_ENABLE()
#define DISCOVERY_EXT_I2Cx_SCL_SDA_GPIO_CLK_ENABLE() \
  __HAL_RCC_GPIOB_CLK_ENABLE()

#define DISCOVERY_EXT_I2Cx_FORCE_RESET() __HAL_RCC_I2C1_FORCE_RESET()
#define DISCOVERY_EXT_I2Cx_RELEASE_RESET() __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx Pins */
#define DISCOVERY_EXT_I2Cx_SCL_PIN GPIO_PIN_8 // 6 for f446
#define DISCOVERY_EXT_I2Cx_SCL_SDA_GPIO_PORT GPIOB
#define DISCOVERY_EXT_I2Cx_SCL_SDA_AF GPIO_AF4_I2C1
#define DISCOVERY_EXT_I2Cx_SDA_PIN GPIO_PIN_9 // 9 for SDA

/* I2C interrupt requests */
#define DISCOVERY_EXT_I2Cx_EV_IRQn I2C1_EV_IRQn
#define DISCOVERY_EXT_I2Cx_ER_IRQn I2C1_ER_IRQn

/* I2C TIMING Register define when I2C clock source is SYSCLK */
/* I2C TIMING is calculated from APB1 source clock = 50 MHz */
/* Due to the big MOFSET capacity for adapting the camera level the rising time
 * is very large (>1us) */
/* 0x40912732 takes in account the big rising and aims a clock of 100khz */
#ifndef DISCOVERY_I2Cx_TIMING
#define DISCOVERY_I2Cx_TIMING ((uint32_t)0x40912732)
#endif /* DISCOVERY_I2Cx_TIMING */



void CAMERA_IO_Init(void);
void CAMERA_Delay(uint32_t Delay);
// ov2640, ov9655
void CAMERA_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value);
uint8_t CAMERA_IO_Read(uint8_t Addr, uint8_t Reg);

// ov5640 change the input interface of CAMERA_IO_Write and CAMERA_IO_Read to
// handle 16 bit registers

void CAMERA_IO_Write_OV5640(uint16_t DeviceAddr, uint16_t Reg, uint8_t Value);
uint8_t CAMERA_IO_Read_OV5640(uint16_t DeviceAddr, uint16_t Reg);
void CAMERA_IO_Write_OV5640_16(uint16_t Addrup, uint16_t Reg, uint16_t value);
uint16_t CAMERA_IO_Read_OV5640_16(uint16_t Addr, uint16_t Reg);


#define OV5640_PCLK_7M 0x00  /* Pixel Clock set to 7Mhz    */
#define OV5640_PCLK_8M 0x01  /* Pixel Clock set to 8Mhz    */
#define OV5640_PCLK_9M 0x02  /* Pixel Clock set to 9Mhz    */
#define OV5640_PCLK_12M 0x08 /* Pixel Clock set to 12Mhz   */
#define OV5640_PCLK_24M 0x0F
#define OV5640_PCLK_23FPS 0x17
#define OV5640_PCLK_30FPS 0x1E



#ifdef __cplusplus
}
#endif

#endif /* __CAMERA_H */
