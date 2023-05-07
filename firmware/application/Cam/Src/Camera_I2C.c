#include "./camera_I2C.h"

static I2C_HandleTypeDef hI2cExtHandler = {0};
//static I2C_HandleTypeDef hI2cAudioHandler = {0};

static HAL_StatusTypeDef I2Cx_ReadMultiple(I2C_HandleTypeDef *i2c_handler,
                                           uint8_t Addr, uint16_t Reg,
                                           uint16_t MemAddSize, uint8_t *Buffer,
                                           uint16_t Length);
static HAL_StatusTypeDef I2Cx_WriteMultiple(I2C_HandleTypeDef *i2c_handler,
                                            uint8_t Addr, uint16_t Reg,
                                            uint16_t MemAddSize,
                                            uint8_t *Buffer, uint16_t Length);
;
static void I2Cx_Error(I2C_HandleTypeDef *i2c_handler, uint8_t Addr);
static void I2Cx_MspInit(I2C_HandleTypeDef *i2c_handler);
static void I2Cx_Init(I2C_HandleTypeDef *i2c_handler);

void CAMERA_IO_Init(void) { I2Cx_Init(&hI2cExtHandler); }

//=======================Read/Write for ov2640 & ov9655
//==============================================
void CAMERA_IO_Write(uint8_t Addr, uint8_t Reg, uint8_t Value) {
  I2Cx_WriteMultiple(&hI2cExtHandler, Addr, (uint16_t)Reg, I2C_MEMADD_SIZE_8BIT,
                     (uint8_t *)&Value, 1);
}

uint8_t CAMERA_IO_Read(uint8_t Addr, uint8_t Reg) {
  uint8_t read_value = 0;

  I2Cx_ReadMultiple(&hI2cExtHandler, Addr, Reg, I2C_MEMADD_SIZE_8BIT,
                    (uint8_t *)&read_value, 1);

  return read_value;
}

//============================Read/Write for
//0v5640=======================================================

void CAMERA_IO_Write_OV5640(uint16_t Addr, uint16_t Reg, uint8_t value) {
  I2Cx_WriteMultiple(&hI2cExtHandler, Addr, (uint16_t)Reg,
                     I2C_MEMADD_SIZE_16BIT, (uint8_t *)&value, 1);
}

void CAMERA_IO_Write_OV5640_16(uint16_t Addrup, uint16_t Reg, uint16_t value) {
  // NB: This is implicitly masking the 8 least-significant bits
  uint8_t val_be[2];
  val_be[0] = value >> 8;
  val_be[1] = value;

  I2Cx_WriteMultiple(&hI2cExtHandler, Addrup, (uint16_t)Reg,
                     I2C_MEMADD_SIZE_16BIT, val_be, 2);
}

uint8_t CAMERA_IO_Read_OV5640(uint16_t Addr, uint16_t Reg) {
uint8_t read_value = 0;
HAL_StatusTypeDef status = HAL_OK;
  // status = HAL_I2C_IsDeviceReady(&hI2cExtHandler, 0x5640, 5, HAL_MAX_DELAY);

  // if (status == HAL_BUSY) { //returning HAL_BUSY
  //   /* I2C error occurred */
  //   I2Cx_Error(&hI2cExtHandler, Addr);
  // }

  // }

  I2Cx_ReadMultiple(&hI2cExtHandler, Addr, Reg, I2C_MEMADD_SIZE_16BIT,
                    (uint8_t *)&read_value, 1);
  return read_value;
}

uint16_t CAMERA_IO_Read_OV5640_16(uint16_t Addr, uint16_t Reg) {
  uint8_t val_be[2];

  I2Cx_ReadMultiple(&hI2cExtHandler, Addr, Reg, I2C_MEMADD_SIZE_16BIT, val_be,
                    2);

  return (val_be[0] << 8) + val_be[1];
}


// delay (ms)
void CAMERA_Delay(uint32_t Delay) { HAL_Delay(Delay); }

//==============================I2C Init==================================================================//

static void I2Cx_Init(I2C_HandleTypeDef *i2c_handler) {
  if (HAL_I2C_GetState(i2c_handler) == HAL_I2C_STATE_RESET) {
    
      /* External, camera I2C configuration*/
    i2c_handler->Instance = I2C1; //
    i2c_handler->Init.ClockSpeed = 100000; // Could be 10000 --> Have a play around DIFF
    i2c_handler->Init.DutyCycle = I2C_DUTYCYCLE_2; // Diff
    i2c_handler->Init.OwnAddress1 = 0;
    i2c_handler->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    i2c_handler->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    i2c_handler->Init.OwnAddress2 = 0;
    i2c_handler->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    i2c_handler->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;


    I2Cx_MspInit(i2c_handler);

   if (HAL_I2C_Init(i2c_handler) != HAL_OK)
  {
    I2Cx_Error(i2c_handler, 0);
  }
    


    /* Init the I2C */
    //I2Cx_MspInit(i2c_handler);
    //HAL_I2C_Init(i2c_handler);


  }
}


/**
  * @brief  Read an amount of data in blocking mode from a specific memory address
  * @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
  *                the configuration information for the specified I2C.
  * @param  DevAddress Target device address: The device 7 bits address value
  *         in datasheet must be shifted to the left before calling the interface
  * @param  MemAddress Internal memory address
  * @param  MemAddSize Size of internal memory address
  * @param  pData Pointer to data buffer
  * @param  Size Amount of data to be sent
  * @param  Timeout Timeout duration
  * @retval HAL status
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(I2C_HandleTypeDef *i2c_handler,
                                           uint8_t Addr, uint16_t Reg,
                                           uint16_t MemAddress, uint8_t *Buffer,
                                           uint16_t Length) {
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Read(i2c_handler, Addr, (uint16_t)Reg, MemAddress,
                            Buffer, Length, 10);

  /* Check the communication status */
  if (status == HAL_BUSY) { //returning HAL_BUSY
    /* I2C error occurred */
    I2Cx_Error(i2c_handler, Addr);
  }
  return status;
}




static HAL_StatusTypeDef I2Cx_WriteMultiple(I2C_HandleTypeDef *i2c_handler,
                                            uint8_t Addr, uint16_t Reg,
                                            uint16_t MemAddress,
                                            uint8_t *Buffer, uint16_t Length) {
  HAL_StatusTypeDef status = HAL_OK;

  status = HAL_I2C_Mem_Write(i2c_handler, Addr, (uint16_t)Reg, MemAddress,
                             Buffer, Length, 1000);

  /* Check the communication status */
  if (status != HAL_OK) {
    /* Re-Initiaize the I2C Bus */
    I2Cx_Error(i2c_handler, Addr);
  }
  return status;
}


static void I2Cx_MspInit(I2C_HandleTypeDef *i2c_handler) {
  GPIO_InitTypeDef gpio_init_structure;

    /* External, camera and Arduino connector I2C MSP init */

    /*** Configure the GPIOs ***/
    /* Enable GPIO clock */
    __HAL_RCC_GPIOB_CLK_ENABLE(); //enabel GPIO B clock for I2C

    /* Configure I2C Tx as alternate function */
    gpio_init_structure.Pin = GPIO_PIN_6 || GPIO_PIN_9;
    gpio_init_structure.Mode = GPIO_MODE_AF_PP;
    gpio_init_structure.Pull = GPIO_NOPULL;
    gpio_init_structure.Speed = GPIO_SPEED_FAST;
    gpio_init_structure.Alternate = GPIO_AF4_I2C1; //correct
    HAL_GPIO_Init(GPIOB, &gpio_init_structure);

    /* Configure I2C Rx as alternate function */
    // gpio_init_structure.Pin = GPIO_PIN_9; // MAY NEED MORE
    // gpio_init_structure.Mode = GPIO_MODE_AF_OD;
    // gpio_init_structure.Pull = GPIO_NOPULL;
    // gpio_init_structure.Speed = GPIO_SPEED_FAST;
    // gpio_init_structure.Alternate = GPIO_AF4_I2C1; //correct
    // HAL_GPIO_Init(GPIOB, &gpio_init_structure);

    /*** Configure the I2C peripheral ***/
    /* Enable I2C clock */
    __HAL_RCC_I2C1_CLK_ENABLE();

    /* Force the I2C peripheral clock reset */
    __HAL_RCC_I2C1_FORCE_RESET();

    /* Release the I2C peripheral clock reset */
    __HAL_RCC_I2C1_RELEASE_RESET();

    /* Enable and set I2Cx Interrupt to a lower priority */
    // HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0x0F, 0);
    // HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);

    // /* Enable and set I2Cx Interrupt to a lower priority */
    // HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0x0F, 0);
    // HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);

}

static void I2Cx_Error(I2C_HandleTypeDef *i2c_handler, uint8_t Addr) {
  /* De-initialize the I2C communication bus */
  HAL_I2C_DeInit(i2c_handler);

  /* Re-Initialize the I2C communication bus */
  I2Cx_Init(i2c_handler);
}

// uint8_t CAMERA_IO_Read_OV5640(uint16_t Addr, uint16_t Reg) {
//   uint8_t read_value = 0;
//   I2Cx_ReadMultiple(&hI2cExtHandler, Addr, Reg, I2C_MEMADD_SIZE_16BIT,
//                     (uint8_t *)&read_value, 1);
//   return read_value;
// }


// uint8_t OV2640_ReadReg(uint16_t Addr)
// {
//   uint32_t timeout = DCMI_TIMEOUT_MAX;
//   uint8_t Data = 0;

//   /* Generate the Start Condition */
//   I2C_GenerateSTART(I2C1, ENABLE);

//   /* Test on I2C1 EV5 and clear it */
//   timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
//   while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
//   {
//     /* If the timeout delay is exceeded, exit with error code */
//     if ((timeout--) == 0) return 0xFF;
//   } 
  
//   /* Send DCMI selected device slave Address for write */
//   I2C_Send7bitAddress(I2C1, OV2640_DEVICE_READ_ADDRESS, I2C_Direction_Transmitter);
 
//   /* Test on I2C1 EV6 and clear it */
//   timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
//   while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
//   {
//     /* If the timeout delay is exceeded, exit with error code */
//     if ((timeout--) == 0) return 0xFF;
//   } 

//   /* Send I2C1 location address LSB */
//   I2C_SendData(I2C1, (uint8_t)(Addr));

//   /* Test on I2C1 EV8 and clear it */
//   timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
//   while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED))
//   {
//     /* If the timeout delay is exceeded, exit with error code */
//     if ((timeout--) == 0) return 0xFF;
//   } 
  
//   /* Clear AF flag if arised */
//   I2C1->SR1 |= (uint16_t)0x0400;

//   /* Generate the Start Condition */
//   I2C_GenerateSTART(I2C1, ENABLE);
  
//   /* Test on I2C1 EV6 and clear it */
//   timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
//   while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT))
//   {
//     /* If the timeout delay is exceeded, exit with error code */
//     if ((timeout--) == 0) return 0xFF;
//   } 
  
//   /* Send DCMI selected device slave Address for write */
//   I2C_Send7bitAddress(I2C1, OV2640_DEVICE_READ_ADDRESS, I2C_Direction_Receiver);
   
//   /* Test on I2C1 EV6 and clear it */
//   timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
//   while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
//   {
//     /* If the timeout delay is exceeded, exit with error code */
//     if ((timeout--) == 0) return 0xFF;
//   }  
 
//   /* Prepare an NACK for the next data received */
//   I2C_AcknowledgeConfig(I2C1, DISABLE);

//   /* Test on I2C1 EV7 and clear it */
//   timeout = DCMI_TIMEOUT_MAX; /* Initialize timeout value */
//   while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))
//   {
//     /* If the timeout delay is exceeded, exit with error code */
//     if ((timeout--) == 0) return 0xFF;
//   }   
    
//   /* Prepare Stop after receiving data */
//   I2C_GenerateSTOP(I2C1, ENABLE);

//   /* Receive the Data */
//   Data = I2C_ReceiveData(I2C1);

//   /* return the read data */
//   return Data;
// }