/**
 ******************************************************************************
 * @file    stm32746g_discovery_camera.h
 * @author  MCD Application Team
 * @brief   This file contains the common defines and functions prototypes for
 *          the stm32746g_discovery_camera.c driver.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2016 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __F4CAM_DRIVER_H
#define __F4CAM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "camera_I2C.h"
#include "events.h"
#include "ov5640_driver.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_dcmi.h"
#include "stm32f4xx_hal_gpio.h"


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define PACKET_SIZE (1024)
#define PACKET_COUNT (16)
#define FRAME_SIZE (PACKET_COUNT * PACKET_SIZE)
#define CAM_FB_SIZE (2 * FRAME_SIZE)

extern char cam_fb[CAM_FB_SIZE];

typedef enum {
  CAMERA_OK = 0x00,
  CAMERA_ERROR = 0x01,
  CAMERA_TIMEOUT = 0x02,
  CAMERA_NOT_DETECTED = 0x03,
  CAMERA_NOT_SUPPORTED = 0x04
} Camera_StatusTypeDef;

#define BSP_CAMERA_IRQHandler DCMI_IRQHandler
#define BSP_CAMERA_DMA_IRQHandler DMA2_Stream1_IRQHandler

Camera_StatusTypeDef CAM_Init(uint8_t format, uint16_t x_res, uint16_t y_res, uint8_t FPS,
                 uint8_t jpeg_comp_ratio, OV5640_Mirror mirror);
uint8_t BSP_CAMERA_DeInit(void);
void BSP_CAMERA_ContinuousStart();
void BSP_CAMERA_SnapshotStart(uint8_t *buff);
void BSP_CAMERA_Suspend(void);
void BSP_CAMERA_Resume(void);
uint8_t BSP_CAMERA_Stop(void);
void BSP_CAMERA_PwrUp(void);
void BSP_CAMERA_PwrDown(void);
void BSP_CAMERA_LineEventCallback(void);
void BSP_CAMERA_VsyncEventCallback(void);
void BSP_CAMERA_FrameEventCallback(void);
void BSP_CAMERA_ErrorCallback(void);

void FPSCalculate(void);
void JPEG_search_mini(void);
void JPEG_search_Full_Frame(void);

void BSP_CAMERA_MspInit(DCMI_HandleTypeDef *hdcmi, void *Params);
void BSP_CAMERA_MspDeInit(DCMI_HandleTypeDef *hdcmi, void *Params);

HAL_StatusTypeDef HAL_DCMI_Start_DMA2(DCMI_HandleTypeDef *hdcmi,
                                      uint32_t DCMI_Mode, uint32_t pData,
                                      uint32_t Length);

void dcmi_dma_Half_TC_callback(DMA_HandleTypeDef *hdma);
void dcmi_dma_Full_TC_callback(DMA_HandleTypeDef *_hdma);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __STM32746G_DISCOVERY_CAMERA_H */
