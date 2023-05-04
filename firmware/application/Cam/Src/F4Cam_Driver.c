#include "F4Cam_Driver.h"


#include "camera_I2C.h"
// #include "events.h"
// #include "stm32f7xx_hal.h"
// #include "stm32f7xx_hal_dcmi.h"
// #include "stm32f7xx_hal_gpio.h"

#define OV5640

char cam_fb[CAM_FB_SIZE];  // __attribute__ ((section (".sdram"), aligned (4)));

uint8_t frames_per_second = 0;

bool capture_data = false;

DCMI_HandleTypeDef hDcmiHandler;

void DCMI_DMA_TRANSFER_HALF_COMPLETE(DMA_HandleTypeDef *hdma);
void DCMI_DMA_TRANSFER_COMPLETE(DMA_HandleTypeDef *hdma);
static void DCMI_DMAError(DMA_HandleTypeDef *hdma);

#ifdef OV5640
Camera_StatusTypeDef CAM_Init(uint8_t format, uint16_t x_res, uint16_t y_res, uint8_t FPS, uint8_t jpeg_comp_ratio) {
  DCMI_HandleTypeDef *phdcmi;

  /* Get the DCMI handle structure */
  phdcmi = &hDcmiHandler;

  /*** Configures the DCMI to interface with the camera module ***/
  /* DCMI configuration */
  phdcmi->Init.CaptureRate = DCMI_CR_ALL_FRAME;
  phdcmi->Init.HSPolarity = DCMI_HSPOLARITY_HIGH;
  phdcmi->Init.SynchroMode = DCMI_SYNCHRO_HARDWARE;
  phdcmi->Init.VSPolarity = DCMI_VSPOLARITY_HIGH;
  phdcmi->Init.ExtendedDataMode = DCMI_EXTEND_DATA_8B;
  phdcmi->Init.PCKPolarity = DCMI_PCKPOLARITY_RISING;
  if (format == FMT_JPEG) {
    phdcmi->Init.JPEGMode = DCMI_JPEG_ENABLE;
  }
  phdcmi->Instance = DCMI;

  BSP_CAMERA_PwrDown();
  BSP_CAMERA_PwrUp();
  HAL_Delay(1000);
  
  const uint16_t id = ov5640_ReadID();
  if (id != OV5640_ID) {
    printf("Read ID incorrect\n");
    return CAMERA_NOT_SUPPORTED;
  }
  printf("Read ID correct\n");

  // Set image format
  switch (format) {
    case FMT_JPEG: {
      ov5640_Init_JPEG(x_res, y_res, PACKET_SIZE, PACKET_COUNT,
                       jpeg_comp_ratio);
      if (FPS != 9) {
        OV5640_SetPCLK(FPS);
      }
      OV5640_Set_Comp_Ratio(jpeg_comp_ratio);
      break;
    }
    case FMT_RGB565: {
      ov5640_Init_RGB565(x_res, y_res);
      break;
    }
    default: {
      break;
    }
  }

  /* DCMI Initialization */
  BSP_CAMERA_MspInit(&hDcmiHandler, NULL);
  HAL_DCMI_Init(phdcmi);
  HAL_DCMI_DisableCROP(phdcmi);

  return CAMERA_OK;
}
#endif

uint8_t BSP_CAMERA_DeInit(void) {
  hDcmiHandler.Instance = DCMI;

  HAL_DCMI_DeInit(&hDcmiHandler);
  BSP_CAMERA_MspDeInit(&hDcmiHandler, NULL);
  return CAMERA_OK;
}

void BSP_CAMERA_ContinuousStart() {
  // Wait for first VSYNC
  while (!(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7))) {
  }

  capture_data = true;
  HAL_DCMI_Start_DMA2(&hDcmiHandler, DCMI_MODE_CONTINUOUS, (uintptr_t)cam_fb,
                      CAM_FB_SIZE);
}

void BSP_CAMERA_Suspend(void) {
  HAL_DCMI_Suspend(&hDcmiHandler);
}

void BSP_CAMERA_Resume(void) {
  HAL_DCMI_Resume(&hDcmiHandler);
}

uint8_t BSP_CAMERA_Stop(void) {
  uint8_t status = CAMERA_ERROR;

  if (HAL_DCMI_Stop(&hDcmiHandler) == HAL_OK) {
    status = CAMERA_OK;
  }

  BSP_CAMERA_PwrDown();

  return status;
}

void BSP_CAMERA_PwrUp(void) {
  GPIO_InitTypeDef gpio_init_structure;

  /* Enable GPIO clock */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*** Configure the GPIO ***/
  /* Configure DCMI GPIO as alternate function */
  gpio_init_structure.Pin = GPIO_PIN_7;
  gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);

  /* De-assert the camera POWER_DOWN pin (active high) */ 
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_RESET);

  HAL_Delay(5); /* POWER_DOWN de-asserted during 3ms */
}

void BSP_CAMERA_PwrDown(void) {
  GPIO_InitTypeDef gpio_init_structure;

  /* Enable GPIO clock */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*** Configure the GPIO ***/
  /* Configure DCMI GPIO as alternate function */
  gpio_init_structure.Pin = GPIO_PIN_7;
  gpio_init_structure.Mode = GPIO_MODE_OUTPUT_PP;
  gpio_init_structure.Pull = GPIO_NOPULL;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);

  /* Assert the camera POWER_DOWN pin (active high) */
  //HAL_GPIO_WritePin(GPIOD, GPIO_PIN_15, GPIO_PIN_SET);

  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_7, GPIO_PIN_SET);

  //HAL_GPIO_TogglePin(STAT_GPIO_Port, STAT_Pin);

}

__weak void BSP_CAMERA_MspInit(DCMI_HandleTypeDef *hdcmi, void *Params) {
  static DMA_HandleTypeDef hdma_handler;
  GPIO_InitTypeDef gpio_init_structure;

  /*** Enable peripherals and GPIO clocks ***/
  /* Enable DCMI clock */
  __HAL_RCC_DCMI_CLK_ENABLE();

  /* Enable DMA2 clock */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /* Enable GPIO clocks   A B C D E for DCMI GPIO */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();

  /*** Configure the GPIO ***/
  /* Configure DCMI GPIO as alternate function */

  //PINS A4 HYSNC A6 PIXCLK
  //A4 - HYSNC, A6 - PCLK
  gpio_init_structure.Pin = GPIO_PIN_4 | GPIO_PIN_6;
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOA, &gpio_init_structure); //

  //PINS G9 --> VSYNC
  //VSYNC : PB7
  gpio_init_structure.Pin = GPIO_PIN_7;
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOB, &gpio_init_structure); //

  //C6, C7  --> DATA0, DATA 1
  gpio_init_structure.Pin = GPIO_PIN_6 | GPIO_PIN_7;
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOC, &gpio_init_structure);

  //D3 --> DATA 5
  gpio_init_structure.Pin = GPIO_PIN_3;
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOD, &gpio_init_structure);


  //E0,1,4,5,6 --> DATA 2:7
  gpio_init_structure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
  gpio_init_structure.Mode = GPIO_MODE_AF_PP;
  gpio_init_structure.Pull = GPIO_PULLUP;
  gpio_init_structure.Speed = GPIO_SPEED_HIGH;
  gpio_init_structure.Alternate = GPIO_AF13_DCMI;
  HAL_GPIO_Init(GPIOE, &gpio_init_structure);

  /*** Configure the DMA ***/
  /* Set the parameters to be configured */
  hdma_handler.Init.Channel = DMA_CHANNEL_1;
  hdma_handler.Init.Direction = DMA_PERIPH_TO_MEMORY;
  hdma_handler.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_handler.Init.MemInc = DMA_MINC_ENABLE;
  hdma_handler.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_handler.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
  hdma_handler.Init.Mode = DMA_CIRCULAR;  // DMA_NORMAL
  // hdma_handler.Init.Mode                = DMA_NORMAL;
  // hdma_handler.Init.Mode                = DMA_NORMAL;
  hdma_handler.Init.Priority = DMA_PRIORITY_HIGH;
  hdma_handler.Init.FIFOMode = DMA_FIFOMODE_ENABLE;  // was disable
  hdma_handler.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
  hdma_handler.Init.MemBurst = DMA_MBURST_SINGLE;
  hdma_handler.Init.PeriphBurst = DMA_PBURST_INC4;  // wasDMA_PBURST_SINGLE 

  hdma_handler.Instance = DMA2_Stream1;

  /* Associate the initialized DMA handle to the DCMI handle */
  __HAL_LINKDMA(hdcmi, DMA_Handle, hdma_handler);

  /*** Configure the NVIC for DCMI and DMA ***/
  /* NVIC configuration for DCMI transfer complete interrupt */
  HAL_NVIC_SetPriority(DCMI_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(DCMI_IRQn);

  /* NVIC configuration for DMA2D transfer complete interrupt */
  HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, 0x0F, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

  /* Configure the DMA stream */
  HAL_DMA_Init(hdcmi->DMA_Handle);
}

/**
 * @brief  DeInitializes the DCMI MSP.
 * @param  hdcmi: HDMI handle
 * @param  Params
 * @retval None
 */
__weak void BSP_CAMERA_MspDeInit(DCMI_HandleTypeDef *hdcmi, void *Params) {
  /* Disable NVIC  for DCMI transfer complete interrupt */
  HAL_NVIC_DisableIRQ(DCMI_IRQn);

  /* Disable NVIC for DMA2 transfer complete interrupt */
  HAL_NVIC_DisableIRQ(DMA2_Stream1_IRQn);

  /* Configure the DMA stream */
  HAL_DMA_DeInit(hdcmi->DMA_Handle);

  /* Disable DCMI clock */
  __HAL_RCC_DCMI_CLK_DISABLE();

  /* GPIO pins clock and DMA clock can be shut down in the application
     by surcharging this __weak function */
}

/**
 * @brief  Line event callback
 * @param  hdcmi: pointer to the DCMI handle
 * @retval None
 */
void HAL_DCMI_LineEventCallback(DCMI_HandleTypeDef *hdcmi) {
  if (!capture_data) {
    return;
  }

  BSP_CAMERA_LineEventCallback();
}

/**
 * @brief  Line Event callback.
 * @retval None
 */
__weak void BSP_CAMERA_LineEventCallback(void) {
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_LineEventCallback could be implemented in the user file
   */
}

/**
 * @brief  VSYNC event callback
 * @param  hdcmi: pointer to the DCMI handle
 * @retval None
 */
void HAL_DCMI_VsyncEventCallback(DCMI_HandleTypeDef *hdcmi) {
  if (!capture_data) {
    return;
  }

  BSP_CAMERA_VsyncEventCallback();
  frames_per_second++;

  DCMIFrameCompleteEventData *frame_complete_payload =
      malloc(sizeof(DCMIFrameCompleteEventData));
  frame_complete_payload->size = FRAME_SIZE;

  Event frame_event = {DCMIFrameComplete, frame_complete_payload};

  push_event_queue(frame_event);
}

/**
 * @brief  VSYNC Event callback.
 * @retval None
 */
__weak void BSP_CAMERA_VsyncEventCallback(void) {
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_VsyncEventCallback could be implemented in the user
     file
   */
}

/**
 * @brief  Frame event callback
 * @param  hdcmi: pointer to the DCMI handle
 * @retval None
 */
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi) {
  BSP_CAMERA_FrameEventCallback();
}

/**
 * @brief  Frame Event callback.
 * @retval None
 */
__weak void BSP_CAMERA_FrameEventCallback(void) {
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_FrameEventCallback could be implemented in the user
     file
   */
}

/**
 * @brief  Error callback
 * @param  hdcmi: pointer to the DCMI handle
 * @retval None
 */
void HAL_DCMI_ErrorCallback(DCMI_HandleTypeDef *hdcmi) {
  BSP_CAMERA_ErrorCallback();
}

/**
 * @brief  Error callback.
 * @retval None
 */
__weak void BSP_CAMERA_ErrorCallback(void) {
  /* NOTE : This function Should not be modified, when the callback is needed,
            the HAL_DCMI_ErrorCallback could be implemented in the user file
   */
}

/**
 * @}
 */

void FPSCalculate(void) {
  printf("\nFPS:%i\n", frames_per_second);
  frames_per_second = 0;
}

void DCMI_DMA_TRANSFER_COMPLETE(DMA_HandleTypeDef *hdma) {
  uint32_t tmp = 0;

  DCMI_HandleTypeDef *hdcmi =
      (DCMI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (hdcmi->XferCount != 0) {
    /* Update memory 0 address location */
    tmp = ((hdcmi->DMA_Handle->Instance->CR) & DMA_SxCR_CT);
    if (((hdcmi->XferCount % 2) == 0) && (tmp != 0)) {
      tmp = hdcmi->DMA_Handle->Instance->M0AR;
      HAL_DMAEx_ChangeMemory(hdcmi->DMA_Handle, (tmp + (8 * hdcmi->XferSize)),
                             MEMORY0);
      hdcmi->XferCount--;
    }
    /* Update memory 1 address location */
    else if ((hdcmi->DMA_Handle->Instance->CR & DMA_SxCR_CT) == 0) {
      tmp = hdcmi->DMA_Handle->Instance->M1AR;
      HAL_DMAEx_ChangeMemory(hdcmi->DMA_Handle, (tmp + (8 * hdcmi->XferSize)),
                             MEMORY1);
      hdcmi->XferCount--;
    }
  }
  /* Update memory 0 address location */
  else if ((hdcmi->DMA_Handle->Instance->CR & DMA_SxCR_CT) != 0) {
    hdcmi->DMA_Handle->Instance->M0AR = hdcmi->pBuffPtr;
  }
  /* Update memory 1 address location */
  else if ((hdcmi->DMA_Handle->Instance->CR & DMA_SxCR_CT) == 0) {
    tmp = hdcmi->pBuffPtr;
    hdcmi->DMA_Handle->Instance->M1AR = (tmp + (4 * hdcmi->XferSize));
    hdcmi->XferCount = hdcmi->XferTransferNumber;
  }

  /* Check if the frame is transferred */
  if (hdcmi->XferCount == hdcmi->XferTransferNumber) {
    __HAL_DCMI_ENABLE_IT(hdcmi, DCMI_IT_FRAME);

    DCMIDataReadyEventData *full_data_ready_payload =
        malloc(sizeof(DCMIDataReadyEventData));
    full_data_ready_payload->data = cam_fb + (CAM_FB_SIZE / 2);
    full_data_ready_payload->size = (CAM_FB_SIZE / 2);

    Event data_ready_full_event = {DCMIDataReady, full_data_ready_payload};

    push_event_queue(data_ready_full_event);
    printf("Transfer complete\n");
  } else if (hdcmi->XferTransferNumber != 0 &&
             hdcmi->XferCount == hdcmi->XferTransferNumber / 2) {
    DCMIDataReadyEventData *full_data_ready_payload =
        malloc(sizeof(DCMIDataReadyEventData));
    full_data_ready_payload->data = cam_fb;
    full_data_ready_payload->size = (CAM_FB_SIZE / 2);
    printf("/nELSE IF/n");

    Event data_ready_full_event = {DCMIDataReady, full_data_ready_payload};

    push_event_queue(data_ready_full_event);
  }

  /* When snapshot mode, set dcmi state to ready */
  if ((hdcmi->Instance->CR & DCMI_CR_CM) == DCMI_MODE_SNAPSHOT) {
    hdcmi->State = HAL_DCMI_STATE_READY;
  }
}

void DCMI_DMA_TRANSFER_HALF_COMPLETE(DMA_HandleTypeDef *hdma) {
  DCMIDataReadyEventData *half_data_ready_payload =
      malloc(sizeof(DCMIDataReadyEventData));
  half_data_ready_payload->data = cam_fb;
  half_data_ready_payload->size = (CAM_FB_SIZE / 2);

  Event data_ready_half_event = {DCMIDataReady, half_data_ready_payload};

  push_event_queue(data_ready_half_event);
  printf("Transfer Half complete\n");

}

HAL_StatusTypeDef HAL_DCMI_Start_DMA2(DCMI_HandleTypeDef *hdcmi,
                                      uint32_t DCMI_Mode, uint32_t pData,
                                      uint32_t Length) {
  // Convert Length to DMA data units
  switch (hdcmi->DMA_Handle->Init.PeriphDataAlignment) {
    case DMA_PDATAALIGN_BYTE:
      break;
    case DMA_PDATAALIGN_HALFWORD:
      Length /= 2;
      break;
    case DMA_PDATAALIGN_WORD:
      Length /= 4;
      break;
    default:
      // @TODO: Error here?
      break;
  }

  /* Initialize the second memory address */
  uint32_t SecondMemAddress = 0;

  /* Check function parameters */
  assert_param(IS_DCMI_CAPTURE_MODE(DCMI_Mode));

  /* Process Locked */
  __HAL_LOCK(hdcmi);

  /* Lock the DCMI peripheral state */
  hdcmi->State = HAL_DCMI_STATE_BUSY;

  /* Enable DCMI by setting DCMIEN bit */
  __HAL_DCMI_ENABLE(hdcmi);

  /* Configure the DCMI Mode */
  hdcmi->Instance->CR &= ~(DCMI_CR_CM);
  hdcmi->Instance->CR |= (uint32_t)(DCMI_Mode);

  /* Set the DMA memory0 conversion complete callback */
  hdcmi->DMA_Handle->XferCpltCallback = DCMI_DMA_TRANSFER_COMPLETE;

  /* Set the DMA error callback */
  hdcmi->DMA_Handle->XferErrorCallback = DCMI_DMAError;

  /* Set the dma abort callback */
  hdcmi->DMA_Handle->XferAbortCallback = NULL;

  /* Reset transfer counters value */
  hdcmi->XferCount = 0;
  hdcmi->XferTransferNumber = 0;
  hdcmi->XferSize = 0;
  hdcmi->pBuffPtr = 0;

  if (Length <= 0xFFFFU) {
    printf("\nSTARTED DMA STREAM SMALL\n");
    /* Enable the DMA Stream */
    hdcmi->DMA_Handle->XferHalfCpltCallback = DCMI_DMA_TRANSFER_HALF_COMPLETE;
    if (HAL_DMA_Start_IT(hdcmi->DMA_Handle, (uint32_t)&hdcmi->Instance->DR,
                         (uint32_t)pData, Length) != HAL_OK) {
      return HAL_ERROR;
    }
  } else /* DCMI_DOUBLE_BUFFER Mode */
  {
    /* Set the DMA memory1 conversion complete callback */
    hdcmi->DMA_Handle->XferM1CpltCallback = DCMI_DMA_TRANSFER_COMPLETE;

    /* Initialize transfer parameters */
    hdcmi->XferCount = 1;
    hdcmi->XferSize = Length;
    hdcmi->pBuffPtr = pData;

    /* Get the number of buffer */
    while (hdcmi->XferSize > 0xFFFFU) {
      hdcmi->XferSize = (hdcmi->XferSize / 2U);
      hdcmi->XferCount = hdcmi->XferCount * 2U;
    }

    /* Update DCMI counter  and transfer number*/
    hdcmi->XferCount = (hdcmi->XferCount - 2U);
    hdcmi->XferTransferNumber = hdcmi->XferCount;

    /* Update second memory address */
    SecondMemAddress = (uint32_t)(pData + (4 * hdcmi->XferSize));

    /* Start DMA multi buffer transfer */
    if (HAL_DMAEx_MultiBufferStart_IT(
            hdcmi->DMA_Handle, (uint32_t)&hdcmi->Instance->DR, (uint32_t)pData,
            SecondMemAddress, hdcmi->XferSize) != HAL_OK) {
      return HAL_ERROR;
    }
  }

  /* Enable Capture */
  hdcmi->Instance->CR |= DCMI_CR_CAPTURE;

  /* Release Lock */
  __HAL_UNLOCK(hdcmi);

  /* Return function status */
  return HAL_OK;
}
static void DCMI_DMAError(DMA_HandleTypeDef *hdma) {
  DCMI_HandleTypeDef *hdcmi =
      (DCMI_HandleTypeDef *)((DMA_HandleTypeDef *)hdma)->Parent;

  if (hdcmi->DMA_Handle->ErrorCode != HAL_DMA_ERROR_FE) {
    /* Initialize the DCMI state*/
    hdcmi->State = HAL_DCMI_STATE_READY;

    /* Set DCMI Error Code */
    hdcmi->ErrorCode |= HAL_DCMI_ERROR_DMA;
  }
}

