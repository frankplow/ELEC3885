
#ifndef _F746CAM_DRIVER_H
#define _F746CAM_DRIVER_H

#ifdef __cplusplus
 extern "C" {
#endif 

#include "ov5640_driver.h"
//#include "stm32746g_discovery.h"
#include "camera_I2C.h"
#include "ov5640_driver.h"
#include "ov5640_registers.h"

#define X_RES 320
#define Y_RES 40
#define CAM_FB_SIZE X_RES * Y_RES * 2

extern uint8_t cam_fb[CAM_FB_SIZE];

typedef enum 
{
  CAMERA_OK            = 0x00,
  CAMERA_ERROR         = 0x01,
  CAMERA_TIMEOUT       = 0x02,
  CAMERA_NOT_DETECTED  = 0x03,
  CAMERA_NOT_SUPPORTED = 0x04

} Camera_StatusTypeDef;

 
#define BSP_CAMERA_IRQHandler      DCMI_IRQHandler
#define BSP_CAMERA_DMA_IRQHandler  DMA2_Stream1_IRQHandler  
 
uint8_t BSP_CAMERA_Init(uint32_t Format, uint16_t x_res, uint16_t y_res);
uint8_t BSP_CAMERA_DeInit(void);
uint8_t BSP_CAMERA_Init_OV2640(uint32_t Resolution);
//void    BSP_CAMERA_ContinuousStart(uint8_t *buff)
void    BSP_CAMERA_ContinuousStart();
void    BSP_CAMERA_SnapshotStart(uint8_t *buff);
void    BSP_CAMERA_Suspend(void);
void    BSP_CAMERA_Resume(void);
uint8_t BSP_CAMERA_Stop(void); 
void    BSP_CAMERA_PwrUp(void);
void    BSP_CAMERA_PwrDown(void);
void    BSP_CAMERA_LineEventCallback(void);
void    BSP_CAMERA_VsyncEventCallback(void);
void    BSP_CAMERA_FrameEventCallback(void);
void    BSP_CAMERA_ErrorCallback(void);

void    BSP_CAMERA_ContrastBrightnessConfig(uint32_t contrast_level, uint32_t brightness_level);
void    BSP_CAMERA_BlackWhiteConfig(uint32_t Mode);
void    BSP_CAMERA_ColorEffectConfig(uint32_t Effect);
   
void BSP_CAMERA_MspInit(DCMI_HandleTypeDef *hdcmi, void *Params);
void BSP_CAMERA_MspDeInit(DCMI_HandleTypeDef *hdcmi, void *Params);



#ifdef __cplusplus
}
#endif

#endif /* __STM32746G_DISCOVERY_CAMERA_H */

