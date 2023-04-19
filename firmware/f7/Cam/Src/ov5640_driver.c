
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

void ov5640_Init_JPEG(uint16_t x_res, uint16_t y_res, uint16_t FifoWidth, uint16_t packetNumber, uint8_t compRatio)
{

  uint8_t tmp = 0;

//1. set default register values
  ov5640_Init(); 
  OV5640_Config_FIFO(FifoWidth, packetNumber);



  //

//2. set pixel format
  ov5640_Set_JPEG();

//3. Set REsoltuion before size (pixel format)
  //OV5640_Set_Size(4, 0, x_res, y_res);

//4. configure timings for the output size
 uint8_t sys_mul = 160;
 //set_pll(false, sys_mul, 4, 2, false, 2, true, 4);


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


  //OV5640_SetPCLK(OV5640_PCLK_23FPS);
  // OV5640_Set_Comp_Ratio(compRatio);
  // uint16_t FIFOW = CAMERA_IO_Read_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_X_SIZE_H);
  // printf("\nFIFOW: %i\n", FIFOW);

  

    //CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3035, 0X41); // slow down OV5640 clocks //Turned off --> TURN BACK ON?
  //CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, 0x3036, 0x79);


  


}

void set_pll(bool bypass, uint8_t multiplier, uint8_t sys_div, uint8_t pre_div, bool root_2x, uint8_t pclk_root_div, bool pclk_manual, uint8_t pclk_div)
{
   //int ret = 0;

   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL5, bypass?0x80:0x00);
   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL0, 0x1A);
   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL1, 0x01 | ((sys_div & 0x0f) << 4));
   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, multiplier & 0xff);
   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, (pre_div & 0xf) | (root_2x?0x10:0x00));
   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SYSTEM_ROOT_DIVIDER, (pclk_root_div & 0x3) << 4 | 0x06);
   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, PCLK_RATIO, pclk_div & 0x1f);
   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, VFIFO_CTRL0C, pclk_manual?0x22:0x20);
   CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SCCB_SYSTEM_CTRL1, 0x13);
}




void OV5640_SetPCLK(uint32_t ClockValue)
{


  switch(ClockValue)
  {
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
// tmp = 0x60;
//     CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL2, tmp);

//     tmp = 0x10;
//     CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SC_PLL_CONTRL3, tmp);
//     break;



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

void OV5640_Set_Size(uint16_t offx,uint16_t offy,uint16_t width,uint16_t height)
{

  //@REVIST --check register initilisatio
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SRM_GROUP_ACCESS, 0x03);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, X_OUTPUT_SIZE_H, width >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, X_OUTPUT_SIZE_L, width &0xff);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OUTPUT_SIZE_H, height >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OUTPUT_SIZE_L, height &0xff);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_TIMING_HOFFSET_HIGH, offx >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_TIMING_HOFFSET_LOW, offx &0xff);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OFFSET_H, offy >> 8);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, Y_OFFSET_L, offy &0xff);

		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SRM_GROUP_ACCESS, 0x13);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_SRM_GROUP_ACCESS, 0xa3);

		//CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, FORMAT_CTRL00, 0x6F);
		CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, CLOCK_POL_CONTROL, 0x22);

      
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

void OV5640_Config_FIFO(uint16_t fifo_width, uint16_t packet_count)
 {

	CAMERA_IO_Write_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_X_SIZE_H, fifo_width);

   //set FIFO height 
  CAMERA_IO_Write_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_Y_SIZE_H, packet_count);
  
  //set to fifo size to fixed number of bits
  uint8_t temp =  CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, OV5640_VFIFO_CTRL00);
  temp |= (1 << 5);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_VFIFO_CTRL00, temp);


 
  uint16_t read_height = CAMERA_IO_Read_OV5640_16(OV5640_I2C_ADDRESS, VFIFO_Y_SIZE_H);

  printf("\n\nREAD_Height = :%i\n\n", read_height);

  //printf f

  printf("\nVFIFO control = :%i\n", temp);

  printf("\nVFIFO control set bit = :%i\n", temp & (1 << 5));

  //enable huffman table out
  uint8_t JPEG_CTRL_3 =  CAMERA_IO_Read_OV5640(OV5640_I2C_ADDRESS, OV5640_JPEG_CTRL03);
  JPEG_CTRL_3 |= (1 << 4);
  CAMERA_IO_Write_OV5640(OV5640_I2C_ADDRESS, OV5640_JPEG_CTRL03, JPEG_CTRL_3);

  printf("\nJPEG_CTRL_3  = :%i\n", JPEG_CTRL_3);



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

