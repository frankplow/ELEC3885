
#include <ov5640_driver.h>

#include "ov5640_reg_settings.h"
#include "ov5640_registers.h"

#define OV5640_POLARITY_PCLK_LOW 0x00U   /* Signal Active Low          */
#define OV5640_POLARITY_PCLK_HIGH 0x01U  /* Signal Active High         */
#define OV5640_POLARITY_HREF_LOW 0x00U   /* Signal Active Low          */
#define OV5640_POLARITY_HREF_HIGH 0x01U  /* Signal Active High         */
#define OV5640_POLARITY_VSYNC_LOW 0x01U  /* Signal Active Low          */
#define OV5640_POLARITY_VSYNC_HIGH 0x00U /* Signal Active High         */

uint32_t jpeg_buf_size = 0;

const uint16_t jpeg_size_tbl[][2] = {
    {160, 120},  // QQVGA
    {176, 144},  // QCIF
    {320, 240},  // QVGA
    {400, 240},  // WQVGA
    {352, 288},  // CIF
    {640, 480},  // VGA
    {800, 600},  // SVGA
};

const uint32_t jpeg_buf_max_size[] = {
    20 * 1024,   // QQVGA
    30 * 1024,   // QCIF
    100 * 1024,  // QVGA
    100 * 1024,  // WQVGA
    100 * 1024,  // CIF
    200 * 1024,  // VGA
    400 * 1024,  // SVGA
};

void ov5640_Init(void) {
  uint32_t index = 0;
  for (index = 0; index < (sizeof(OV5640_default_reg_settings) / 4); index++) {
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS,
                           OV5640_default_reg_settings[index][0],
                           OV5640_default_reg_settings[index][1]);
  }
}

void ov5640_Set_JPEG(void) {
  uint32_t index = 0;
  for (index = 0; index < (sizeof(format_jpeg) / 4); index++) {
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, format_jpeg[index][0],
                           format_jpeg[index][1]);
  }
}

void ov5640_Set_RGB565(void) {
  uint32_t index = 0;
  for (index = 0; index < (sizeof(format_rgb565) / 4); index++) {
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, format_rgb565[index][0],
                           format_rgb565[index][1]);
  }
}

void ov5640_Init_JPEG(uint16_t x_res, uint16_t y_res, uint16_t FifoWidth,
                      uint16_t packetNumber, uint8_t compRatio) {
  uint8_t tmp = 0;
  ov5640_Init();
  HAL_Delay(50);
  ov5640_Set_JPEG();

  OV5640_Set_Size(4, 0, x_res, y_res);

  OV5640_Config_FIFO(FifoWidth, packetNumber);


  // //set timings

  tmp = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, OV5640_TIMING_TC_REG21);
  tmp |= (1 << 5);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_TIMING_TC_REG21, tmp);

  tmp = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, OV5640_SYSREM_RESET02);
  tmp &= ~((1 << 4) | (1 << 3) | (1 << 2));
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SYSREM_RESET02, tmp);

  tmp = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, OV5640_CLOCK_ENABLE02);
  tmp |= ((1 << 5) | (1 << 3));
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_CLOCK_ENABLE02, tmp);

  // set polaratis

  tmp = (uint8_t)(OV5640_POLARITY_PCLK_HIGH << 5U) |
        (OV5640_POLARITY_HREF_HIGH << 1U) | OV5640_POLARITY_VSYNC_HIGH;
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_POLARITY_CTRL, tmp);
      
calc_sysclk(  // Xclk 
    24000000,
    false,      // bypass 0x3039 bit 7                          OV5640_SC_PLL_CONTRL5
    0xC0,       // 1. multiplier 0x3036 (changable)     (96)    OV5640_SC_PLL_CONTRL2
    4,          // 2. Sysdivider 0x3035 bits 4:7                OV5640_SC_PLL_CONTRL1
    3,          // 3. pre div  0x3037 bits 3:0 (changable)      OV5640_SC_PLL_CONTRL3
    true,       // 4.PLL root div - 0x3037 bit 4 (changable)    OV5640_SC_PLL_CONTRL3
    1,          // 5. pclk_root_div 0x3108 (bits 4-5)           OV5640_SYSTEM_ROOT_DIVIDER
    true,       // PCLK manual enable 0x406c bits 1             0x460c
    1           //6. PCLK divider 0x3035 bits 3:0               OV5640_SC_PLL_CONTRL1
    );          
}

uint32_t calc_sysclk(uint32_t xclk, bool pll_bypass, uint16_t pll_multiplier,
                     uint16_t pll_sys_div, uint16_t pre_div, bool root_2x,
                     uint16_t pclk_root_div, bool pclk_manual,
                     uint16_t pclk_div) {
  float pll_pre_div2x_map[] = {1, 1, 2, 3, 4, 1.5, 6, 2.5, 8};
  uint8_t* pll_pclk_root_div_map[] = {1, 2, 4, 8};

  if (!pll_sys_div) {
    pll_sys_div = 1;
  }

  float pll_pre_div = pll_pre_div2x_map[pre_div];
  uint32_t root_2x_div = root_2x ? 2 : 1;
  uint32_t pll_pclk_root_div = pll_pclk_root_div_map[pclk_root_div];

  uint32_t REFIN = xclk / pll_pre_div;

  uint32_t VCO = REFIN * pll_multiplier / root_2x_div;

  uint32_t PLL_CLK =
      pll_bypass
          ? (xclk)
          : (VCO / pll_sys_div * 2 / 4);  // 5 here is 10bit mode / 2, for 8bit
                                          // it should be 4 (reg 0x3034)

  uint32_t PCLK =
      PLL_CLK / pll_pclk_root_div / ((pclk_manual && pclk_div) ? pclk_div : 2);

  uint32_t SYSCLK = PLL_CLK / 4;

  printf(
      "Calculated XVCLK: %d Hz\nREFIN: %u Hz\nVCO: %u Hz\nPLL_CLK: %u Hz\n"
      "SYSCLK: %u Hz\nPCLK: %u Hz\n",
      xclk, REFIN, VCO, PLL_CLK, SYSCLK, PCLK);
  return SYSCLK;
}

void set_pll(bool pll_bypass, uint16_t  pll_multiplier,
            uint16_t pll_sys_div, uint16_t pre_div, bool root_2x,
            uint16_t pclk_root_div, bool pclk_manual,
            uint16_t pclk_div){
    //int ret = 0;
    if(pll_multiplier > 252 || pll_multiplier < 4 || pll_sys_div > 15 || pre_div > 8 || pclk_div > 31 || pclk_root_div > 3){
        printf("Invalid arguments");
    }
    if(pll_multiplier > 127){
        pll_multiplier &= 0xFE;//only even integers above 127
    }
    printf("Set PLL: bypass: %u, multiplier: %u, sys_div: %u, pre_div: %u, root_2x: %u, pclk_root_div: %u, pclk_manual: %u, pclk_div: %u", pll_bypass, pll_multiplier, pll_sys_div, pre_div, root_2x, pclk_root_div, pclk_manual, pclk_div);

    calc_sysclk(24000000, pll_bypass, pll_multiplier, pll_sys_div, pre_div, root_2x, pclk_root_div, pclk_manual, pclk_div);

    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL5, pll_bypass?0x80:0x00);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL0, 0x18);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL1, 0x01 | ((pll_sys_div & 0x0f) << 4));
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, pll_multiplier & 0xff);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, (pre_div & 0xf) | (root_2x?0x10:0x00));

    //It is suggested that sysclock should be < 2* PCLK however seems fine --> Needs work to isolate
    //CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SYSTEM_ROOT_DIVIDER, (pclk_root_div & 0x3) << 4 | 0x06);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SYSTEM_ROOT_DIVIDER, pclk_root_div); 
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, PCLK_RATIO, pclk_div & 0x1f);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_VFIFO_CTRL0C, pclk_manual?0x22:0x20);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SCCB_SYSTEM_CTRL1, 0x13);

}


void OV5640_SetPCLK(uint32_t ClockValue) { 
  switch (ClockValue) {
    case OV5640_PCLK_7M:

      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0x38);
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x16);
      break;
    case OV5640_PCLK_8M:
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0x40);
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x16);
      break;
    case OV5640_PCLK_9M:
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0x00);
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x18);
      break;
    case OV5640_PCLK_12M:
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0x00);
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x16);
      break;
    case OV5640_PCLK_24M:
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0x60);
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x13);
      break;

    case OV5640_PCLK_23FPS:
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0x60);
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x12);
      break;

    case 20:
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0x80);
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x13);
      break;

    case 24:
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0x80);
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x05);
      break;

    case 25:
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0xA0);
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x13);
      break;

    case 30:
    default:
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0xC0);
      CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x13);
      break;
  }
}

void ov5640_Init_RGB565(uint16_t x_res, uint16_t y_res) {
  ov5640_Init();
  OV5640_Set_Size(4, 0, x_res, y_res);
  ov5640_Set_RGB565();
}

uint16_t ov5640_ReadID(void) {
  uint16_t read_val = 0;

  /* Initialize I2C */
  CAMERA_IO_Init();
  CAMERA_Delay(30);
  read_val = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, 0x300A);
  read_val = read_val << 8;
  read_val |= CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, 0x300B);

  /* Prepare the camera to be configured */
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3103,
                         0x11);  // system clock from pad, bit[1]
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, SYSTEM_CTROL0, 0x80);
  CAMERA_Delay(10);

  // HAL_Delay(10);
  /* Get the camera ID */
  return read_val;
}

void OV5640_Set_Size(uint16_t offx, uint16_t offy, uint16_t width,
                     uint16_t height) {
  //@REVIST --check register initilisatio
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SRM_GROUP_ACCESS, 0X03);

  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, X_OUTPUT_SIZE_H, width >> 8);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, X_OUTPUT_SIZE_L, width & 0xff);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OUTPUT_SIZE_H, height >> 8);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OUTPUT_SIZE_L, height & 0xff);

  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_TIMING_HOFFSET_HIGH,
                         offx >> 8);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_TIMING_HOFFSET_LOW,
                         offx & 0xff);

  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OFFSET_H, offy >> 8);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OFFSET_L, offy & 0xff);

  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SRM_GROUP_ACCESS, 0x13);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SRM_GROUP_ACCESS, 0xa3);
}

void OV5640_Config_FIFO(uint16_t fifo_width, uint16_t packet_count) {
  // Set output height fixed
  uint8_t temp = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, OV5640_VFIFO_CTRL00);
  temp |= (1 << 5);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_VFIFO_CTRL00, temp);

  // Set FIFO width (bytes per packet)
  CAMERA_IO_Write_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_X_SIZE_H, fifo_width);

  // Set FIFO height (packets per frame if output height is fixed)
  CAMERA_IO_Write_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_Y_SIZE_H, packet_count);
}

void OV5640_Set_Comp_Ratio(uint16_t comp_ratio) {
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, COMPRESSION_CTRL07,
                         comp_ratio & 0x3f);
}


