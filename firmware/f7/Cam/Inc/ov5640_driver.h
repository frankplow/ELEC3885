/**
 ******************************************************************************
 * @file    ov5640.h
 * @author  MCD Application Team
 * @brief   This file contains all the functions prototypes for the ov5640.c
 *          driver.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __OV5640_H
#define __OV5640_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "camera_I2C.h"
#include "stdbool.h"
#include "stdio.h"
// #include "./camera_I2C.h"
/** @addtogroup BSP
 * @{
 */

/** @addtogroup Components
 * @{
 */

/** @addtogroup ov5640
 * @{
 */

/** @defgroup OV5640_Exported_Types
 * @{
 */

/**
 * @}
 */

/** @defgroup OV5640_Exported_Constants
 * @{
 */
/**
 * @brief  OV5640 ID
 */
#define OV5640_ID 0x5640

#define QQVGA_160_120 0
#define QCIF_176_144 1
#define QVGA_320_240 2
#define WQVGA_400_240 3
#define CIF_352_288 4
#define VGA_640_480 5
#define SVGA_800_600 6

#define OV5640_I2C_ADDRESS 0x78

void ov5640_Init(void);
void ov5640_Set_RGB565(void);
void ov5640_Set_JPEG(void);
void ov5640_Init_JPEG(uint16_t x_res, uint16_t y_res, uint16_t FifoWidth,
                      uint16_t packetNumber, uint8_t compRatio);
void ov5640_Init_RGB565(uint16_t x_res, uint16_t y_res);
void OV5640_Set_Size(uint16_t offx, uint16_t offy, uint16_t width,
                     uint16_t height);

uint32_t calc_sysclk(uint32_t xclk, bool pll_bypass, uint16_t pll_multiplier,
                     uint16_t pll_sys_div, uint16_t pre_div, bool root_2x,
                     uint16_t pclk_root_div, bool pclk_manual,
                     uint16_t pclk_div);
void OV5640_Set_Comp_Ratio(uint16_t comp_ratio);
void OV5640_SetPCLK(uint32_t ClockValue);
uint16_t ov5640_ReadID();
void CAMERA_IO_Init(void);
void CAMERA_Delay(uint32_t delay);

#ifdef __cplusplus
}
#endif

#endif /* __OV5640_H */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
