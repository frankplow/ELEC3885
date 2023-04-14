
#include <ov5640_driver.h>
#include "ov5640_registers.h"
#include "ov5640_reg_settings.h"

#define OV5640_POLARITY_PCLK_LOW  0x00U /* Signal Active Low          */
#define OV5640_POLARITY_PCLK_HIGH 0x01U /* Signal Active High         */
#define OV5640_POLARITY_HREF_LOW  0x00U /* Signal Active Low          */
#define OV5640_POLARITY_HREF_HIGH 0x01U /* Signal Active High         */
#define OV5640_POLARITY_VSYNC_LOW 0x01U /* Signal Active Low          */
#define OV5640_POLARITY_VSYNC_HIGH  0x00U /* Signal Active High         */

//static uint32_t ov5640_ConvertValue(uint32_t feature, uint32_t value);
uint32_t  jpeg_buf_size = 0;

const uint16_t jpeg_size_tbl[][2]=
{
  {160, 120},	//QQVGA
	{176, 144},	//QCIF
	{320, 240},	//QVGA
	{400, 240},	//WQVGA
	{352, 288},	//CIF
	{640, 480},	//VGA
  {800, 600},	//SVGA
};

const uint32_t jpeg_buf_max_size[]=
{
    20*1024,	//QQVGA
	30*1024,	//QCIF
	100*1024,	//QVGA
	100*1024,	//WQVGA
	100*1024,	//CIF
	200*1024,	//VGA
    400*1024,	//SVGA
};

void ov5640_Init(void) {
	uint32_t index = 0;
	  for(index=0; index< (sizeof(OV5640_default_reg_settings)/4) ; index++)
	  {
	    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_default_reg_settings[index][0], OV5640_default_reg_settings[index][1]);
	  }
}

void ov5640_Set_JPEG(void) {
	uint32_t index = 0;
	for(index=0; index<(sizeof(format_jpeg)/4); index++)
	{
	   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, format_jpeg[index][0], format_jpeg[index][1]);
	}
}

void ov5640_Set_RGB565(void) {
	uint32_t index = 0;
	for(index=0; index<(sizeof(format_rgb565)/4); index++)
	{
	   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, format_rgb565[index][0], format_rgb565[index][1]);
	}
}

void ov5640_Init_JPEG(uint16_t x_res, uint16_t y_res)
{
  //uint32_t index = 0;
  uint8_t tmp = 0;
  //uint8_t redreg = 0;
  //send initial config

  ov5640_Init();
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3035, 0X41); // slow down OV5640 clocks
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3036, 0x79);

  OV5640_Set_Size(4, 0, x_res, y_res);
  ov5640_Set_JPEG();
  //OV5640_SetPCLK(OV5640_PCLK_24M);


  //set timings

  tmp = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS,OV5640_TIMING_TC_REG21);
  tmp |= (1 << 5);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_TIMING_TC_REG21, tmp);

  tmp = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS,OV5640_SYSREM_RESET02);
  tmp &= ~((1 << 4) | (1 << 3) | (1 << 2));
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SYSREM_RESET02, tmp);


  tmp = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS,OV5640_CLOCK_ENABLE02);
  tmp |= ((1 << 5) | (1 << 3));
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_CLOCK_ENABLE02, tmp);
  //set polaratis

  tmp = (uint8_t)(OV5640_POLARITY_PCLK_HIGH << 5U) | (OV5640_POLARITY_HREF_HIGH << 1U) | OV5640_POLARITY_VSYNC_HIGH;
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_POLARITY_CTRL, tmp);


}

int32_t OV5640_SetPCLK(uint32_t ClockValue)
{

  uint8_t tmp;

  switch(ClockValue)
  {
  case OV5640_PCLK_7M:
    tmp = 0x38;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);

    tmp = 0x16;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);

    break;
  case OV5640_PCLK_8M:
    tmp = 0x40;
    //ret = ov5640_write_reg(&pObj->Ctx, OV5640_SC_PLL_CONTRL2, &tmp, 1);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);
    tmp = 0x16;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);
    break;
  case OV5640_PCLK_9M:
  tmp = 0x00; //unsure
	CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);
    tmp = 0x18;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);
    break;
  case OV5640_PCLK_12M:
  tmp = 0x00; //unsure
	CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);
    tmp = 0x16;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);
    break;
  case OV5640_PCLK_24M:
  default:
    tmp = 0x60;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);

    tmp = 0x13;
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);
    break;

    //return ret;

  }
}


void ov5640_Init_RGB565(uint16_t x_res, uint16_t y_res)
{
  ov5640_Init();
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3035, 0X21);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3036, 0x98);


  OV5640_Set_Size(4, 0, x_res, y_res);
  ov5640_Set_RGB565();
  OV5640_SetPCLK(OV5640_PCLK_24M);

//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL1, 0X41);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, 0x69);
//  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, 0x98);


}

uint16_t ov5640_ReadID(void)
{
  uint16_t read_val = 0;

  /* Initialize I2C */
  CAMERA_IO_Init();

  /* Prepare the camera to be configured */
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, SYSTEM_CTROL0, 0x80);
  CAMERA_Delay(500);

  read_val = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, 0x300A);
  read_val = read_val << 8;
  read_val |= CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, 0x300B);
  /* Get the camera ID */
  return read_val;
}

uint8_t OV5640_Set_Size(uint16_t offx,uint16_t offy,uint16_t width,uint16_t height)
{
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3212, 0x03);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, X_OUTPUT_SIZE_H, width >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, X_OUTPUT_SIZE_L, width &0xff);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OUTPUT_SIZE_H, height >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OUTPUT_SIZE_L, height &0xff);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3810, offx >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3811, offx &0xff);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3812, offy >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3813, offy &0xff);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3212, 0x13);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3212, 0xa3);

		//CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, FORMAT_CTRL00, 0x6F);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, CLOCK_POL_CONTROL, 0x22);

        if(width==jpeg_size_tbl[QQVGA_160_120][0] && height==jpeg_size_tbl[QQVGA_160_120][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[QQVGA_160_120];
        }
        else if(width==jpeg_size_tbl[QCIF_176_144][0] && height==jpeg_size_tbl[QCIF_176_144][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[QCIF_176_144];
        }
        else if(width==jpeg_size_tbl[QVGA_320_240][0] && height==jpeg_size_tbl[QVGA_320_240][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[QVGA_320_240];
        }
        else if(width==jpeg_size_tbl[WQVGA_400_240][0] && height==jpeg_size_tbl[WQVGA_400_240][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[WQVGA_400_240];
        }
        else if(width==jpeg_size_tbl[CIF_352_288][0] && height==jpeg_size_tbl[CIF_352_288][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[CIF_352_288];
        }
        else if(width==jpeg_size_tbl[VGA_640_480][0] && height==jpeg_size_tbl[VGA_640_480][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[VGA_640_480];
        }
        else if(width==jpeg_size_tbl[SVGA_800_600][0] && height==jpeg_size_tbl[SVGA_800_600][1])
        {
                jpeg_buf_size = jpeg_buf_max_size[SVGA_800_600];
        }

        return 0;
}

//0-63, lower number means higher quality
//void OV5640_JPEG_Config(uint16_t quality, uint16_t width, uint16_t height) {
//	 //set JPEG quality
//	 uint8_t fifo_control = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, OV5640_VFIFO_CTRL00);
//	 printf("\nrfifo control: %x\n", fifo_control);
//	 //CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_VFIFO_CTRL00, fifo_control | 0x08);
//
//	 //CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, COMPRESSION_CTRL07, quality & 0x3f);
//	 //set JPEG PACKET size, variable width
//
//
////	 uint16_t left_byte = width >> 8;
////	 uint16_t right_byte = width << 8;
////	 uint16_t bit_swapped;
//
//	 //&0x00FF;
//
//	 //swapped = (num>>8) | (num<<8);
//
//
//
//	  // = (width >> 8) + width &0x00FF;
//
//
//	 printf("\n Left byte = %x\n", left_byte);
//	 printf("\n  right_byte = %x\n", right_byte);
//
//	 //bit_swapped = right_byte | left_byte;
//
//	 printf("\n bits swapped = %x\n", bit_swapped);
//
//
//	 //width (variable)
//	 //CAMERA_IO_Write_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_X_SIZE_H, bit_swapped);
//
//	 //Height (constant)
//     //CAMERA_IO_Write_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_Y_SIZE_H, height);
//
//	 uint16_t read_width = CAMERA_IO_Read_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_X_SIZE_H);
//     printf("\nread fifo width: %i\n", read_width);
//
//	 uint16_t read_height = CAMERA_IO_Read_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_Y_SIZE_H);
//	 printf("\nread height width: %i\n", read_height);
//
//
//
//
//}

void OV5640_Set_FIFO_Width(uint16_t fifo_width)
 {
	 uint16_t left_byte, right_byte, bit_swapped;

	 left_byte	= fifo_width >> 8;
	 right_byte = fifo_width << 8;
	 bit_swapped = right_byte | left_byte;

	 CAMERA_IO_Write_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_X_SIZE_H, bit_swapped);
}

void OV5640_Set_Comp_Ratio(uint16_t comp_ratio) {
	 CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, COMPRESSION_CTRL07, comp_ratio & 0x3f);
   //printf("test\n");
}


void OV5640_Set_NightMode(void)
{
	uint32_t index = 0;
	for(index=0; index<(sizeof(OV5640_NightMode)/4); index++)
	{
	   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_NightMode[index][0], OV5640_NightMode[index][1]);
	}
}

void OV5640_MirrorFlipConfig1(uint8_t Config)
{
  uint8_t tmp3820 = 0, tmp3821;

  tmp3820 = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20);
  tmp3820 &= 0xF9;
  tmp3821 = CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21);
  tmp3821 &= 0xF9;

  switch (Config)
  {
  case OV5640_MIRROR:
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20, tmp3820 | 0x00);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21, tmp3821 | 0x06);
    break;

  case OV5640_FLIP:
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20, tmp3820 | 0x06);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21, tmp3821 | 0x00);
    break;
  case OV5640_MIRROR_FLIP:
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20, tmp3820 | 0x06);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21, tmp3821 | 0x06);
    break;

  case OV5640_MIRROR_FLIP_NORMAL:
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20, tmp3820 | 0x00);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21, tmp3821 | 0x06);
    break;

  default:
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG20, tmp3820 | 0x00);
    CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, TIMING_TC_REG21, tmp3821 | 0x00);
    break;
  }
}

