/*
 * ov5640_regs_settings.h
 *
 *  Created on: 8 Mar 2023
 *      Author: sol
 */

#ifndef INC_OV5640_REG_SETTINGS_H_
#define INC_OV5640_REG_SETTINGS_H_

#include "ov5640_registers.h"


const uint16_t OV5640_default_reg_settings[][2] =
{

//=============================================WAVEShare regs==========================================================

		// // 24MHz input clock, 24MHz PCLK
		// {SYSTEM_CTROL0, 0x42}, // software power down, bit[6]
		// {OV5640_SCCB_SYSTEM_CTRL1, 0x03}, // system clock from PLL, bit[1]
		// {OV5640_PAD_OUTPUT_ENABLE01, 0xff}, // FREX, Vsync, HREF, PCLK, D[9:6] output enable
		// {OV5640_PAD_OUTPUT_ENABLE02, 0xff}, // D[5:0], GPIO[1:0] output enable
		// {OV5640_SC_PLL_CONTRL0, 0x1a}, // MIPI 10-bit
		// {OV5640_SC_PLL_CONTRL3, 0x13}, // PLL root divider, bit[4], PLL pre-divider, bit[3:0]
		// {OV5640_SYSTEM_ROOT_DIVIDER, 0x01}, // PCLK root divider, bit[5:4], SCLK2x root divider, bit[3:2]
		// // SCLK r}oot} divider, bit[1:0]
		// {0x3630, 0x36},
		// {0x3631, 0x0e},
		// {0x3632, 0xe2},
		// {0x3633, 0x12},
		// {0x3621, 0xe0},
		// {0x3704, 0xa0},
		// {0x3703, 0x5a},
		// {0x3715, 0x78},
		// {0x3717, 0x01},
		// {0x370b, 0x60},
		// {0x3705, 0x1a},
		// {0x3905, 0x02},
		// {0x3906, 0x10},
		// {0x3901, 0x0a},
		// {0x3731, 0x12},
		// {0x3600, 0x08}, // VCM control
		// {0x3601, 0x33}, // VCM control
		// {0x302d, 0x60}, // system control
		// {0x3620, 0x52},
		// {0x371b, 0x20},
		// {0x471c, 0x50},
		// {OV5640_AEC_CTRL13, 0x43}, // pre-gain = 1.047x
		// {OV5640_AEC_GAIN_CEILING_HIGH, 0x00}, // gain ceiling
		// {OV5640_AEC_GAIN_CEILING_LOW, 0xf8}, // gain ceiling = 15.5x
		// {0x3635, 0x13},
		// {0x3636, 0x03},
		// {0x3634, 0x40},
		// {0x3622, 0x01},
		// // 50/60Hz d}etection 50/60Hz
		// {OV5640_5060HZ_CTRL01, 0x34}, // Band auto, bit[7]
		// {OV5640_5060HZ_CTRL04, 0x28}, // threshold low sum
		// {OV5640_5060HZ_CTRL05, 0x98}, // threshold high sum
		// {OV5640_LIGHTMETER1_TH_HIGH, 0x00}, // light meter 1 threshold[15:8]
		// {OV5640_LIGHTMETER1_TH_LOW, 0x08}, // light meter 1 threshold[7:0]
		// {OV5640_LIGHTMETER2_TH_HIGH, 0x00}, // light meter 2 threshold[15:8]
		// {OV5640_LIGHTMETER2_TH_LOW, 0x1c}, // light meter 2 threshold[7:0]
		// {OV5640_SAMPLE_NUMBER_HIGH, 0x9c}, // sample number[15:8]
		// {OV5640_SAMPLE_NUMBER_LOW, 0x40}, // sample number[7:0]
		// {OV5640_TIMING_HOFFSET_HIGH, 0x00}, // Timing Hoffset[11:8]
		// {OV5640_TIMING_HOFFSET_LOW, 0x10}, // Timing Hoffset[7:0]
		// {Y_OFFSET_H, 0x00}, // Timing Voffset[10:8]
		// {0x3708, 0x64},
		// {OV5640_BLC_CTRL01, 0x02}, // BLC start from line 2
		// {OV5640_BLC_CTRL05, 0x1a}, // BLC always update
		// {OV5640_SYSREM_RESET00, 0x00}, // enable blocks
		// {OV5640_CLOCK_ENABLE00, 0xff}, // enable clocks
		// {OV5640_MIPI_CONTROL00, 0x58}, // MIPI power down, DVP enable
		// {0x302e, 0x00},
		// {OV5640_FORMAT_CTRL00, 0x30}, // YUV 422, YUYV
		// {OV5640_FORMAT_MUX_CTRL, 0x00}, // YUV 422
		// {COMPRESSION_CTRL0E, 0x00},
		// {OV5640_ISP_CONTROL00, 0xa7}, // Lenc on, raw gamma on, BPC on, WPC on, CIP on
		// // AEC targe}t
		// {OV5640_AEC_CTRL0F, 0x30}, // stable range in high
		// {OV5640_AEC_CTRL10, 0x28}, // stable range in low
		// {OV5640_AEC_CTRL1B, 0x30}, // stable range out high
		// {OV5640_AEC_CTRL1E, 0x26}, // stable range out low
		// {OV5640_AEC_CTRL11, 0x60}, // fast zone high
		// {OV5640_AEC_CTRL1F, 0x14}, // fast zone low
		// // Lens corr}ection for ?
		// {OV5640_GMTRX00, 0x23},
		// {OV5640_GMTRX01, 0x14},
		// {OV5640_GMTRX02, 0x0f},
		// {OV5640_GMTRX03, 0x0f},
		// {OV5640_GMTRX04, 0x12},
		// {OV5640_GMTRX05, 0x26},
		// {OV5640_GMTRX10, 0x0c},
		// {OV5640_GMTRX11, 0x08},
		// {OV5640_GMTRX12, 0x05},
		// {OV5640_GMTRX13, 0x05},
		// {OV5640_GMTRX14, 0x08},

		// {OV5640_GMTRX15, 0x0d},
		// {OV5640_GMTRX20, 0x08},
		// {OV5640_GMTRX21, 0x03},
		// {0x580e, 0x00},
		// {0x580f, 0x00},
		// {0x5810, 0x03},
		// {0x5811, 0x09},
		// {0x5812, 0x07},
		// {0x5813, 0x03},
		// {0x5814, 0x00},
		// {0x5815, 0x01},
		// {0x5816, 0x03},
		// {0x5817, 0x08},
		// {0x5818, 0x0d},
		// {0x5819, 0x08},
		// {0x581a, 0x05},
		// {0x581b, 0x06},
		// {0x581c, 0x08},
		// {0x581d, 0x0e},
		// {0x581e, 0x29},
		// {0x581f, 0x17},
		// {0x5820, 0x11},
		// {0x5821, 0x11},
		// {0x5822, 0x15},
		// {0x5823, 0x28},
		// {0x5824, 0x46},
		// {0x5825, 0x26},
		// {0x5826, 0x08},
		// {0x5827, 0x26},
		// {0x5828, 0x64},
		// {0x5829, 0x26},
		// {0x582a, 0x24},
		// {0x582b, 0x22},
		// {0x582c, 0x24},
		// {0x582d, 0x24},
		// {0x582e, 0x06},
		// {0x582f, 0x22},
		// {0x5830, 0x40},
		// {0x5831, 0x42},
		// {0x5832, 0x24},
		// {0x5833, 0x26},
		// {0x5834, 0x24},
		// {0x5835, 0x22},
		// {0x5836, 0x22},
		// {0x5837, 0x26},
		// {0x5838, 0x44},
		// {0x5839, 0x24},
		// {0x583a, 0x26},
		// {0x583b, 0x28},
		// {0x583c, 0x42},
		// {OV5640_LENC_BR_OFFSET, 0xce}, // lenc BR offset

		// {0x5180, 0xff}, // AWB B block
		// {0x5181, 0xf2}, // AWB control
		// {0x5182, 0x00}, // [7:4] max local counter, [3:0] max fast counter
		// {0x5183, 0x14}, // AWB advanced
		// {0x5184, 0x25},
		// {0x5185, 0x24},
		// {0x5186, 0x09},
		// {0x5187, 0x09},
		// {0x5188, 0x09},
		// {0x5189, 0x75},
		// {0x518a, 0x54},
		// {0x518b, 0xe0},
		// {0x518c, 0xb2},
		// {0x518d, 0x42},
		// {0x518e, 0x3d},
		// {0x518f, 0x56},
		// {0x5190, 0x46},
		// {0x5191, 0xf8}, // AWB top limit
		// {0x5192, 0x04}, // AWB bottom limit
		// {0x5193, 0x70}, // red limit
		// {0x5194, 0xf0}, // green limit
		// {0x5195, 0xf0}, // blue limit
		// {0x5196, 0x03}, // AWB control
		// {0x5197, 0x01}, // local limit
		// {0x5198, 0x04},
		// {0x5199, 0x12},
		// {0x519a, 0x04},
		// {0x519b, 0x00},
		// {0x519c, 0x06},
		// {0x519d, 0x82},
		// {0x519e, 0x38}, // AWB control

		// {0x5480, 0x01}, // Gamma bias plus on, bit[0]
		// {0x5481, 0x08},
		// {0x5482, 0x14},
		// {0x5483, 0x28},
		// {0x5484, 0x51},
		// {0x5485, 0x65},
		// {0x5486, 0x71},
		// {0x5487, 0x7d},
		// {0x5488, 0x87},
		// {0x5489, 0x91},
		// {0x548a, 0x9a},
		// {0x548b, 0xaa},
		// {0x548c, 0xb8},
		// {0x548d, 0xcd},
		// {0x548e, 0xdd},
		// {0x548f, 0xea},
		// {0x5490, 0x1d},
		// // color mat}rix
		// {0x5381, 0x1e}, // CMX1 for Y
		// {0x5382, 0x5b}, // CMX2 for Y
		// {0x5383, 0x08}, // CMX3 for Y
		// {0x5384, 0x0a}, // CMX4 for U
		// {0x5385, 0x7e}, // CMX5 for U
		// {0x5386, 0x88}, // CMX6 for U
		// {0x5387, 0x7c}, // CMX7 for V
		// {0x5388, 0x6c}, // CMX8 for V
		// {0x5389, 0x10}, // CMX9 for V
		// {0x538a, 0x01}, // sign[9]
		// {0x538b, 0x98}, // sign[8:1]
		// // UV adjust} UV
		// {0x5580, 0x06}, // saturation on, bit[1]
		// {0x5583, 0x40},
		// {0x5584, 0x10},
		// {0x5589, 0x10},
		// {0x558a, 0x00},
		// {0x558b, 0xf8},
		// {0x501d, 0x40}, // enable manual offset of contrast

		// {0x5300, 0x08}, // CIP sharpen MT threshold 1
		// {0x5301, 0x30}, // CIP sharpen MT threshold 2
		// {0x5302, 0x10}, // CIP sharpen MT offset 1
		// {0x5303, 0x00}, // CIP sharpen MT offset 2
		// {0x5304, 0x08}, // CIP DNS threshold 1
		// {0x5305, 0x30}, // CIP DNS threshold 2
		// {0x5306, 0x08}, // CIP DNS offset 1
		// {0x5307, 0x16}, // CIP DNS offset 2
		// {0x5309, 0x08}, // CIP sharpen TH threshold 1
		// {0x530a, 0x30}, // CIP sharpen TH threshold 2
		// {0x530b, 0x04}, // CIP sharpen TH offset 1
		// {0x530c, 0x06}, // CIP sharpen TH offset 2
		// {0x5025, 0x00},
		// {SYSTEM_CTROL0, 0x02}, // wake up from standby, bit[6]
		// {0x4740, 0X21}, //VSYNC active HIGH	// 24MHz input clock, 24MHz PCLK

//=============================================STM32 REGs==========================================================
{OV5640_SCCB_SYSTEM_CTRL1, 0x11},
	    {OV5640_SYSTEM_CTROL0, 0x82},
	    {OV5640_SCCB_SYSTEM_CTRL1, 0x03},
	    {OV5640_PAD_OUTPUT_ENABLE01, 0xFF},
	    {OV5640_PAD_OUTPUT_ENABLE02, 0xf3},
	    {OV5640_SC_PLL_CONTRL0, 0x18},
	    {OV5640_SYSTEM_CTROL0, 0x02},

		//XX FPS
	    {OV5640_SC_PLL_CONTRL1, 0x41},
	    {OV5640_SC_PLL_CONTRL2, 0x30},
	    {OV5640_SC_PLL_CONTRL3, 0x13},

	    {OV5640_SYSTEM_ROOT_DIVIDER, 0x01},


	    {0x3630, 0x36},
	    {0x3631, 0x0e},
	    {0x3632, 0xe2},
	    {0x3633, 0x12},
	    {0x3621, 0xe0},
	    {0x3704, 0xa0},
	    {0x3703, 0x5a},
	    {0x3715, 0x78},
	    {0x3717, 0x01},
	    {0x370b, 0x60},
	    {0x3705, 0x1a},
	    {0x3905, 0x02},
	    {0x3906, 0x10},
	    {0x3901, 0x0a},
	    {0x3731, 0x12},
	    {0x3600, 0x08},
	    {0x3601, 0x33},
	    {0x302d, 0x60},
	    {0x3620, 0x52},
	    {0x371b, 0x20},
	    {0x471c, 0x50},
	    {OV5640_AEC_CTRL13, 0x43},
	    {OV5640_AEC_GAIN_CEILING_HIGH, 0x00},
	    {OV5640_AEC_GAIN_CEILING_LOW, 0xf8},
	    {0x3635, 0x13},
	    {0x3636, 0x03},
	    {0x3634, 0x40},
	    {0x3622, 0x01},
	    {OV5640_5060HZ_CTRL01, 0x34},
	    {OV5640_5060HZ_CTRL04, 0x28},
	    {OV5640_5060HZ_CTRL05, 0x98},
	    {OV5640_LIGHTMETER1_TH_HIGH, 0x00},
	    {OV5640_LIGHTMETER1_TH_LOW, 0x00},
	    {OV5640_LIGHTMETER2_TH_HIGH, 0x01},
	    {OV5640_LIGHTMETER2_TH_LOW, 0x2c},
	    {OV5640_SAMPLE_NUMBER_HIGH, 0x9c},
	    {OV5640_SAMPLE_NUMBER_LOW, 0x40},
	    {OV5640_TIMING_TC_REG20, 0x06},
	    {OV5640_TIMING_TC_REG21, 0x00},
	    {OV5640_TIMING_X_INC, 0x31},
	    {OV5640_TIMING_Y_INC, 0x31},
	    {OV5640_TIMING_HS_HIGH, 0x00},
	    {OV5640_TIMING_HS_LOW, 0x00},
	    {OV5640_TIMING_VS_HIGH, 0x00},
	    {OV5640_TIMING_VS_LOW, 0x04},
	    {OV5640_TIMING_HW_HIGH, 0x0a},
	    {OV5640_TIMING_HW_LOW, 0x3f},
	    {OV5640_TIMING_VH_HIGH, 0x07},
	    {OV5640_TIMING_VH_LOW, 0x9b},
	    {OV5640_TIMING_DVPHO_HIGH, 0x03},
	    {OV5640_TIMING_DVPHO_LOW, 0x20},
	    {OV5640_TIMING_DVPVO_HIGH, 0x02},
	    {OV5640_TIMING_DVPVO_LOW, 0x58},
	    {OV5640_TIMING_HTS_HIGH, 0x06},
	    {OV5640_TIMING_HTS_LOW, 0x40},
	    {OV5640_TIMING_VTS_HIGH, 0x03},
	    {OV5640_TIMING_VTS_LOW, 0xe8},
	    {OV5640_TIMING_HOFFSET_HIGH, 0x00},
	    {OV5640_TIMING_HOFFSET_LOW, 0x10},
	    {OV5640_TIMING_VOFFSET_HIGH, 0x00},
	    {OV5640_TIMING_VOFFSET_LOW, 0x06},
	    {0x3618, 0x00},
	    {0x3612, 0x29},
	    {0x3708, 0x64},
	    {0x3709, 0x52},
	    {0x370c, 0x03},
	    {OV5640_AEC_CTRL02, 0x03},
	    {OV5640_AEC_CTRL03, 0xd8},
	    {OV5640_AEC_B50_STEP_HIGH, 0x01},
	    {OV5640_AEC_B50_STEP_LOW, 0x27},
	    {OV5640_AEC_B60_STEP_HIGH, 0x00},
	    {OV5640_AEC_B60_STEP_LOW, 0xf6},
	    {OV5640_AEC_CTRL0E, 0x03},
	    {OV5640_AEC_CTRL0D, 0x04},
	    {OV5640_AEC_MAX_EXPO_HIGH, 0x03},
	    {OV5640_AEC_MAX_EXPO_LOW, 0xd8},
	    {OV5640_BLC_CTRL01, 0x02},
	    {OV5640_BLC_CTRL04, 0x02},
	    {OV5640_SYSREM_RESET00, 0x00},
	    {OV5640_SYSREM_RESET02, 0x1c},
	    {OV5640_CLOCK_ENABLE00, 0xff},
	    {OV5640_CLOCK_ENABLE02, 0xc3},
	    {OV5640_MIPI_CONTROL00, 0x58},
	    {0x302e, 0x00},
	    {OV5640_POLARITY_CTRL, 0x22},
	    {OV5640_FORMAT_CTRL00, 0x6F},
	    {OV5640_FORMAT_MUX_CTRL, 0x01},
	    {OV5640_JPG_MODE_SELECT, 0x03},
	    {OV5640_JPEG_CTRL07, 0x04},
	    {0x440e, 0x00},
	    {0x460b, 0x35},
	    {0x460c, 0x23},
	    {OV5640_PCLK_PERIOD, 0x22},
	    {0x3824, 0x02},
	    {OV5640_ISP_CONTROL00, 0xa7},
	    {OV5640_ISP_CONTROL01, 0xa3},
	    {OV5640_AWB_CTRL00, 0xff},
	    {OV5640_AWB_CTRL01, 0xf2},
	    {OV5640_AWB_CTRL02, 0x00},
	    {OV5640_AWB_CTRL03, 0x14},
	    {OV5640_AWB_CTRL04, 0x25},
	    {OV5640_AWB_CTRL05, 0x24},
	    {OV5640_AWB_CTRL06, 0x09},
	    {OV5640_AWB_CTRL07, 0x09},
	    {OV5640_AWB_CTRL08, 0x09},
	    {OV5640_AWB_CTRL09, 0x75},
	    {OV5640_AWB_CTRL10, 0x54},
	    {OV5640_AWB_CTRL11, 0xe0},
	    {OV5640_AWB_CTRL12, 0xb2},
	    {OV5640_AWB_CTRL13, 0x42},
	    {OV5640_AWB_CTRL14, 0x3d},
	    {OV5640_AWB_CTRL15, 0x56},
	    {OV5640_AWB_CTRL16, 0x46},
	    {OV5640_AWB_CTRL17, 0xf8},
	    {OV5640_AWB_CTRL18, 0x04},
	    {OV5640_AWB_CTRL19, 0x70},
	    {OV5640_AWB_CTRL20, 0xf0},
	    {OV5640_AWB_CTRL21, 0xf0},
	    {OV5640_AWB_CTRL22, 0x03},
	    {OV5640_AWB_CTRL23, 0x01},
	    {OV5640_AWB_CTRL24, 0x04},
	    {OV5640_AWB_CTRL25, 0x12},
	    {OV5640_AWB_CTRL26, 0x04},
	    {OV5640_AWB_CTRL27, 0x00},
	    {OV5640_AWB_CTRL28, 0x06},
	    {OV5640_AWB_CTRL29, 0x82},
	    {OV5640_AWB_CTRL30, 0x38},
	    {OV5640_CMX1, 0x1e},
	    {OV5640_CMX2, 0x5b},
	    {OV5640_CMX3, 0x08},
	    {OV5640_CMX4, 0x0a},
	    {OV5640_CMX5, 0x7e},
	    {OV5640_CMX6, 0x88},
	    {OV5640_CMX7, 0x7c},
	    {OV5640_CMX8, 0x6c},
	    {OV5640_CMX9, 0x10},
	    {OV5640_CMXSIGN_HIGH, 0x01},
	    {OV5640_CMXSIGN_LOW, 0x98},
	    {OV5640_CIP_SHARPENMT_TH1, 0x08},
	    {OV5640_CIP_SHARPENMT_TH2, 0x30},
	    {OV5640_CIP_SHARPENMT_OFFSET1, 0x10},
	    {OV5640_CIP_SHARPENMT_OFFSET2, 0x00},
	    {OV5640_CIP_DNS_TH1, 0x08},
	    {OV5640_CIP_DNS_TH2, 0x30},
	    {OV5640_CIP_DNS_OFFSET1, 0x08},
	    {OV5640_CIP_DNS_OFFSET2, 0x16},
	    {OV5640_CIP_CTRL, 0x08},
	    {OV5640_CIP_SHARPENTH_TH1, 0x30},
	    {OV5640_CIP_SHARPENTH_TH2, 0x04},
	    {OV5640_CIP_SHARPENTH_OFFSET1, 0x06},
	    {OV5640_GAMMA_CTRL00, 0x01},
	    {OV5640_GAMMA_YST00, 0x08},
	    {OV5640_GAMMA_YST01, 0x14},
	    {OV5640_GAMMA_YST02, 0x28},
	    {OV5640_GAMMA_YST03, 0x51},
	    {OV5640_GAMMA_YST04, 0x65},
	    {OV5640_GAMMA_YST05, 0x71},
	    {OV5640_GAMMA_YST06, 0x7d},
	    {OV5640_GAMMA_YST07, 0x87},
	    {OV5640_GAMMA_YST08, 0x91},
	    {OV5640_GAMMA_YST09, 0x9a},
	    {OV5640_GAMMA_YST0A, 0xaa},
	    {OV5640_GAMMA_YST0B, 0xb8},
	    {OV5640_GAMMA_YST0C, 0xcd},
	    {OV5640_GAMMA_YST0D, 0xdd},
	    {OV5640_GAMMA_YST0E, 0xea},
	    {OV5640_GAMMA_YST0F, 0x1d},
	    {OV5640_SDE_CTRL0, 0x02},
	    {OV5640_SDE_CTRL3, 0x40},
	    {OV5640_SDE_CTRL4, 0x10},
	    {OV5640_SDE_CTRL9, 0x10},
	    {OV5640_SDE_CTRL10, 0x00},
	    {OV5640_SDE_CTRL11, 0xf8},
	    {OV5640_GMTRX00, 0x23},
	    {OV5640_GMTRX01, 0x14},
	    {OV5640_GMTRX02, 0x0f},
	    {OV5640_GMTRX03, 0x0f},
	    {OV5640_GMTRX04, 0x12},
	    {OV5640_GMTRX05, 0x26},
	    {OV5640_GMTRX10, 0x0c},
	    {OV5640_GMTRX11, 0x08},
	    {OV5640_GMTRX12, 0x05},
	    {OV5640_GMTRX13, 0x05},
	    {OV5640_GMTRX14, 0x08},
	    {OV5640_GMTRX15, 0x0d},
	    {OV5640_GMTRX20, 0x08},
	    {OV5640_GMTRX21, 0x03},
	    {OV5640_GMTRX22, 0x00},
	    {OV5640_GMTRX23, 0x00},
	    {OV5640_GMTRX24, 0x03},
	    {OV5640_GMTRX25, 0x09},
	    {OV5640_GMTRX30, 0x07},
	    {OV5640_GMTRX31, 0x03},
	    {OV5640_GMTRX32, 0x00},
	    {OV5640_GMTRX33, 0x01},
	    {OV5640_GMTRX34, 0x03},
	    {OV5640_GMTRX35, 0x08},
	    {OV5640_GMTRX40, 0x0d},
	    {OV5640_GMTRX41, 0x08},
	    {OV5640_GMTRX42, 0x05},
	    {OV5640_GMTRX43, 0x06},
	    {OV5640_GMTRX44, 0x08},
	    {OV5640_GMTRX45, 0x0e},
	    {OV5640_GMTRX50, 0x29},
	    {OV5640_GMTRX51, 0x17},
	    {OV5640_GMTRX52, 0x11},
	    {OV5640_GMTRX53, 0x11},
	    {OV5640_GMTRX54, 0x15},
	    {OV5640_GMTRX55, 0x28},
	    {OV5640_BRMATRX00, 0x46},
	    {OV5640_BRMATRX01, 0x26},
	    {OV5640_BRMATRX02, 0x08},
	    {OV5640_BRMATRX03, 0x26},
	    {OV5640_BRMATRX04, 0x64},
	    {OV5640_BRMATRX05, 0x26},
	    {OV5640_BRMATRX06, 0x24},
	    {OV5640_BRMATRX07, 0x22},
	    {OV5640_BRMATRX08, 0x24},
	    {OV5640_BRMATRX09, 0x24},
	    {OV5640_BRMATRX20, 0x06},
	    {OV5640_BRMATRX21, 0x22},
	    {OV5640_BRMATRX22, 0x40},
	    {OV5640_BRMATRX23, 0x42},
	    {OV5640_BRMATRX24, 0x24},
	    {OV5640_BRMATRX30, 0x26},
	    {OV5640_BRMATRX31, 0x24},
	    {OV5640_BRMATRX32, 0x22},
	    {OV5640_BRMATRX33, 0x22},
	    {OV5640_BRMATRX34, 0x26},
	    {OV5640_BRMATRX40, 0x44},
	    {OV5640_BRMATRX41, 0x24},
	    {OV5640_BRMATRX42, 0x26},
	    {OV5640_BRMATRX43, 0x28},
	    {OV5640_BRMATRX44, 0x42},
	    {OV5640_LENC_BR_OFFSET, 0xce},
	    {0x5025, 0x00},
	    {OV5640_AEC_CTRL0F, 0x30},
	    {OV5640_AEC_CTRL10, 0x28},
	    {OV5640_AEC_CTRL1B, 0x30},
	    {OV5640_AEC_CTRL1E, 0x26},
	    {OV5640_AEC_CTRL11, 0x60},
	    {OV5640_AEC_CTRL1F, 0x14},
	    {OV5640_SYSTEM_CTROL0, 0x02},
	    // {OV5640_SCCB_SYSTEM_CTRL1, 0x11},
	    // {OV5640_SYSTEM_CTROL0, 0x82},
	    // {OV5640_SCCB_SYSTEM_CTRL1, 0x03},
	    // {OV5640_PAD_OUTPUT_ENABLE01, 0xFF},
	    // {OV5640_PAD_OUTPUT_ENABLE02, 0xf3},
	    // {OV5640_SC_PLL_CONTRL0, 0x18},
	    // {OV5640_SYSTEM_CTROL0, 0x02},

		// //XX FPS
	    // {OV5640_SC_PLL_CONTRL1, 0x41},
	    // {OV5640_SC_PLL_CONTRL2, 0x30},
	    // {OV5640_SC_PLL_CONTRL3, 0x13},

	    // {OV5640_SYSTEM_ROOT_DIVIDER, 0x01},

	    // {0x3630, 0x36},
	    // {0x3631, 0x0e},
	    // {0x3632, 0xe2},
	    // {0x3633, 0x12},
	    // {0x3621, 0xe0},
	    // {0x3704, 0xa0},
	    // {0x3703, 0x5a},
	    // {0x3715, 0x78},
	    // {0x3717, 0x01},
	    // {0x370b, 0x60},
	    // {0x3705, 0x1a},
	    // {0x3905, 0x02},
	    // {0x3906, 0x10},
	    // {0x3901, 0x0a},
	    // {0x3731, 0x12},
	    // {0x3600, 0x08},
	    // {0x3601, 0x33},
	    // {0x302d, 0x60},
	    // {0x3620, 0x52},
		// {0x371b, 0x20},
	    // {0x471c, 0x50},
	    // {OV5640_AEC_CTRL13, 0x43},
	    // {OV5640_AEC_GAIN_CEILING_HIGH, 0x00},
	    // {OV5640_AEC_GAIN_CEILING_LOW, 0xf8},
	    // {0x3635, 0x13},
	    // {0x3636, 0x03},
	    // {0x3634, 0x40},
	    // {0x3622, 0x01},
	    // {OV5640_5060HZ_CTRL01, 0x34},
	    // {OV5640_5060HZ_CTRL04, 0x28},
	    // {OV5640_5060HZ_CTRL05, 0x98},
	    // {OV5640_LIGHTMETER1_TH_HIGH, 0x00},
	    // {OV5640_LIGHTMETER1_TH_LOW, 0x00},
	    // {OV5640_LIGHTMETER2_TH_HIGH, 0x01},
	    // {OV5640_LIGHTMETER2_TH_LOW, 0x2c},
	    // {OV5640_SAMPLE_NUMBER_HIGH, 0x9c},
	    // {OV5640_SAMPLE_NUMBER_LOW, 0x40},
	    // {OV5640_TIMING_TC_REG20, 0x06},
	    // {OV5640_TIMING_TC_REG21, 0x00},
	    // {OV5640_TIMING_X_INC, 0x31},
	    // {OV5640_TIMING_Y_INC, 0x31},
	    // {OV5640_TIMING_HS_HIGH, 0x00},
	    // {OV5640_TIMING_HS_LOW, 0x00},
	    // {OV5640_TIMING_VS_HIGH, 0x00},
	    // {OV5640_TIMING_VS_LOW, 0x04},
	    // {OV5640_TIMING_HW_HIGH, 0x0a},
	    // {OV5640_TIMING_HW_LOW, 0x3f},
	    // {OV5640_TIMING_VH_HIGH, 0x07},
	    // {OV5640_TIMING_VH_LOW, 0x9b},
	    // {OV5640_TIMING_DVPHO_HIGH, 0x03},
	    // {OV5640_TIMING_DVPHO_LOW, 0x20},
	    // {OV5640_TIMING_DVPVO_HIGH, 0x02},
	    // {OV5640_TIMING_DVPVO_LOW, 0x58},
	    // {OV5640_TIMING_HTS_HIGH, 0x06},
	    // {OV5640_TIMING_HTS_LOW, 0x40},
	    // {OV5640_TIMING_VTS_HIGH, 0x03},
	    // {OV5640_TIMING_VTS_LOW, 0xe8},
	    // {OV5640_TIMING_HOFFSET_HIGH, 0x00},
	    // {OV5640_TIMING_HOFFSET_LOW, 0x10},
	    // {OV5640_TIMING_VOFFSET_HIGH, 0x00},
	    // {OV5640_TIMING_VOFFSET_LOW, 0x06},
	    // {0x3618, 0x00},
	    // {0x3612, 0x29},
	    // {0x3708, 0x64},
	    // {0x3709, 0x52},
	    // {0x370c, 0x03},
	    // {OV5640_AEC_CTRL02, 0x03},
	    // {OV5640_AEC_CTRL03, 0xd8},
	    // {OV5640_AEC_B50_STEP_HIGH, 0x01},
	    // {OV5640_AEC_B50_STEP_LOW, 0x27},
	    // {OV5640_AEC_B60_STEP_HIGH, 0x00},
	    // {OV5640_AEC_B60_STEP_LOW, 0xf6},
	    // {OV5640_AEC_CTRL0E, 0x03},
	    // {OV5640_AEC_CTRL0D, 0x04},
	    // {OV5640_AEC_MAX_EXPO_HIGH, 0x03},
	    // {OV5640_AEC_MAX_EXPO_LOW, 0xd8},
	    // {OV5640_BLC_CTRL01, 0x02},
	    // {OV5640_BLC_CTRL04, 0x02},
	    // {OV5640_SYSREM_RESET00, 0x00},
	    // {OV5640_SYSREM_RESET02, 0x1c},
	    // {OV5640_CLOCK_ENABLE00, 0xff},
	    // {OV5640_CLOCK_ENABLE02, 0xc3},
	    // {OV5640_MIPI_CONTROL00, 0x58},
	    // {0x302e, 0x00},
	    // {OV5640_POLARITY_CTRL, 0x22},
	    // {OV5640_FORMAT_CTRL00, 0x6F},
	    // {OV5640_FORMAT_MUX_CTRL, 0x01},
	    // {OV5640_JPG_MODE_SELECT, 0x03},
	    // {OV5640_JPEG_CTRL07, 0x04},
	    // {0x440e, 0x00},
	    // {0x460b, 0x35},
	    // {0x460c, 0x23},
	    // {OV5640_PCLK_PERIOD, 0x22},
	    // {0x3824, 0x02},
	    // {OV5640_ISP_CONTROL00, 0xa7},
	    // {OV5640_ISP_CONTROL01, 0xa3},
	    // {OV5640_AWB_CTRL00, 0xff},
	    // {OV5640_AWB_CTRL01, 0xf2},
	    // {OV5640_AWB_CTRL02, 0x00},
	    // {OV5640_AWB_CTRL03, 0x14},
	    // {OV5640_AWB_CTRL04, 0x25},
	    // {OV5640_AWB_CTRL05, 0x24},
	    // {OV5640_AWB_CTRL06, 0x09},
	    // {OV5640_AWB_CTRL07, 0x09},
	    // {OV5640_AWB_CTRL08, 0x09},
	    // {OV5640_AWB_CTRL09, 0x75},
	    // {OV5640_AWB_CTRL10, 0x54},
	    // {OV5640_AWB_CTRL11, 0xe0},
	    // {OV5640_AWB_CTRL12, 0xb2},
	    // {OV5640_AWB_CTRL13, 0x42},
	    // {OV5640_AWB_CTRL14, 0x3d},
	    // {OV5640_AWB_CTRL15, 0x56},
	    // {OV5640_AWB_CTRL16, 0x46},
	    // {OV5640_AWB_CTRL17, 0xf8},
	    // {OV5640_AWB_CTRL18, 0x04},
	    // {OV5640_AWB_CTRL19, 0x70},
	    // {OV5640_AWB_CTRL20, 0xf0},
	    // {OV5640_AWB_CTRL21, 0xf0},
	    // {OV5640_AWB_CTRL22, 0x03},
	    // {OV5640_AWB_CTRL23, 0x01},
	    // {OV5640_AWB_CTRL24, 0x04},
	    // {OV5640_AWB_CTRL25, 0x12},
	    // {OV5640_AWB_CTRL26, 0x04},
	    // {OV5640_AWB_CTRL27, 0x00},
	    // {OV5640_AWB_CTRL28, 0x06},
	    // {OV5640_AWB_CTRL29, 0x82},
	    // {OV5640_AWB_CTRL30, 0x38},
	    // {OV5640_CMX1, 0x1e},
	    // {OV5640_CMX2, 0x5b},
	    // {OV5640_CMX3, 0x08},
	    // {OV5640_CMX4, 0x0a},
	    // {OV5640_CMX5, 0x7e},
	    // {OV5640_CMX6, 0x88},
	    // {OV5640_CMX7, 0x7c},
	    // {OV5640_CMX8, 0x6c},
	    // {OV5640_CMX9, 0x10},
	    // {OV5640_CMXSIGN_HIGH, 0x01},
	    // {OV5640_CMXSIGN_LOW, 0x98},
	    // {OV5640_CIP_SHARPENMT_TH1, 0x08},
	    // {OV5640_CIP_SHARPENMT_TH2, 0x30},
	    // {OV5640_CIP_SHARPENMT_OFFSET1, 0x10},
	    // {OV5640_CIP_SHARPENMT_OFFSET2, 0x00},
	    // {OV5640_CIP_DNS_TH1, 0x08},
	    // {OV5640_CIP_DNS_TH2, 0x30},
	    // {OV5640_CIP_DNS_OFFSET1, 0x08},
	    // {OV5640_CIP_DNS_OFFSET2, 0x16},
	    // {OV5640_CIP_CTRL, 0x08},
	    // {OV5640_CIP_SHARPENTH_TH1, 0x30},
	    // {OV5640_CIP_SHARPENTH_TH2, 0x04},
	    // {OV5640_CIP_SHARPENTH_OFFSET1, 0x06},
	    // {OV5640_GAMMA_CTRL00, 0x01},
	    // {OV5640_GAMMA_YST00, 0x08},
	    // {OV5640_GAMMA_YST01, 0x14},
	    // {OV5640_GAMMA_YST02, 0x28},
	    // {OV5640_GAMMA_YST03, 0x51},
	    // {OV5640_GAMMA_YST04, 0x65},
	    // {OV5640_GAMMA_YST05, 0x71},
	    // {OV5640_GAMMA_YST06, 0x7d},
	    // {OV5640_GAMMA_YST07, 0x87},
	    // {OV5640_GAMMA_YST08, 0x91},
	    // {OV5640_GAMMA_YST09, 0x9a},
	    // {OV5640_GAMMA_YST0A, 0xaa},
	    // {OV5640_GAMMA_YST0B, 0xb8},
	    // {OV5640_GAMMA_YST0C, 0xcd},
	    // {OV5640_GAMMA_YST0D, 0xdd},
	    // {OV5640_GAMMA_YST0E, 0xea},
	    // {OV5640_GAMMA_YST0F, 0x1d},
	    // {OV5640_SDE_CTRL0, 0x02},
	    // {OV5640_SDE_CTRL3, 0x40},
	    // {OV5640_SDE_CTRL4, 0x10},
	    // {OV5640_SDE_CTRL9, 0x10},
	    // {OV5640_SDE_CTRL10, 0x00},
	    // {OV5640_SDE_CTRL11, 0xf8},
	    // {OV5640_GMTRX00, 0x23},
	    // {OV5640_GMTRX01, 0x14},
	    // {OV5640_GMTRX02, 0x0f},
	    // {OV5640_GMTRX03, 0x0f},
	    // {OV5640_GMTRX04, 0x12},
	    // {OV5640_GMTRX05, 0x26},
	    // {OV5640_GMTRX10, 0x0c},
	    // {OV5640_GMTRX11, 0x08},
	    // {OV5640_GMTRX12, 0x05},
	    // {OV5640_GMTRX13, 0x05},
	    // {OV5640_GMTRX14, 0x08},
	    // {OV5640_GMTRX15, 0x0d},
	    // {OV5640_GMTRX20, 0x08},
	    // {OV5640_GMTRX21, 0x03},
	    // {OV5640_GMTRX22, 0x00},
	    // {OV5640_GMTRX23, 0x00},
	    // {OV5640_GMTRX24, 0x03},
	    // {OV5640_GMTRX25, 0x09},
	    // {OV5640_GMTRX30, 0x07},
	    // {OV5640_GMTRX31, 0x03},
	    // {OV5640_GMTRX32, 0x00},
	    // {OV5640_GMTRX33, 0x01},
	    // {OV5640_GMTRX34, 0x03},
	    // {OV5640_GMTRX35, 0x08},
	    // {OV5640_GMTRX40, 0x0d},
	    // {OV5640_GMTRX41, 0x08},
	    // {OV5640_GMTRX42, 0x05},
	    // {OV5640_GMTRX43, 0x06},
	    // {OV5640_GMTRX44, 0x08},
	    // {OV5640_GMTRX45, 0x0e},
	    // {OV5640_GMTRX50, 0x29},
	    // {OV5640_GMTRX51, 0x17},
	    // {OV5640_GMTRX52, 0x11},
	    // {OV5640_GMTRX53, 0x11},
	    // {OV5640_GMTRX54, 0x15},
	    // {OV5640_GMTRX55, 0x28},
	    // {OV5640_BRMATRX00, 0x46},
	    // {OV5640_BRMATRX01, 0x26},
	    // {OV5640_BRMATRX02, 0x08},
	    // {OV5640_BRMATRX03, 0x26},
	    // {OV5640_BRMATRX04, 0x64},
	    // {OV5640_BRMATRX05, 0x26},
	    // {OV5640_BRMATRX06, 0x24},
	    // {OV5640_BRMATRX07, 0x22},
	    // {OV5640_BRMATRX08, 0x24},
	    // {OV5640_BRMATRX09, 0x24},
	    // {OV5640_BRMATRX20, 0x06},
	    // {OV5640_BRMATRX21, 0x22},
	    // {OV5640_BRMATRX22, 0x40},
	    // {OV5640_BRMATRX23, 0x42},
	    // {OV5640_BRMATRX24, 0x24},
	    // {OV5640_BRMATRX30, 0x26},
	    // {OV5640_BRMATRX31, 0x24},
	    // {OV5640_BRMATRX32, 0x22},
	    // {OV5640_BRMATRX33, 0x22},
	    // {OV5640_BRMATRX34, 0x26},
	    // {OV5640_BRMATRX40, 0x44},
	    // {OV5640_BRMATRX41, 0x24},
	    // {OV5640_BRMATRX42, 0x26},
	    // {OV5640_BRMATRX43, 0x28},
	    // {OV5640_BRMATRX44, 0x42},
	    // {OV5640_LENC_BR_OFFSET, 0xce},
	    // {0x5025, 0x00},
	    // {OV5640_AEC_CTRL0F, 0x30},
	    // {OV5640_AEC_CTRL10, 0x28},
	    // {OV5640_AEC_CTRL1B, 0x30},
	    // {OV5640_AEC_CTRL1E, 0x26},
	    // {OV5640_AEC_CTRL11, 0x60},
	    // {OV5640_AEC_CTRL1F, 0x14},
	    // {OV5640_SYSTEM_CTROL0, 0x02},
		// {0x371b, 0x20},
	    // {0x471c, 0x50},
	    // {OV5640_AEC_CTRL13, 0x43},
	    // {OV5640_AEC_GAIN_CEILING_HIGH, 0x00},
	    // {OV5640_AEC_GAIN_CEILING_LOW, 0xf8},
	    // {0x3635, 0x13},
	    // {0x3636, 0x03},
	    // {0x3634, 0x40},
	    // {0x3622, 0x01},
	    // {OV5640_5060HZ_CTRL01, 0x34},
	    // {OV5640_5060HZ_CTRL04, 0x28},
	    // {OV5640_5060HZ_CTRL05, 0x98},
	    // {OV5640_LIGHTMETER1_TH_HIGH, 0x00},
	    // {OV5640_LIGHTMETER1_TH_LOW, 0x00},
	    // {OV5640_LIGHTMETER2_TH_HIGH, 0x01},
	    // {OV5640_LIGHTMETER2_TH_LOW, 0x2c},
	    // {OV5640_SAMPLE_NUMBER_HIGH, 0x9c},
	    // {OV5640_SAMPLE_NUMBER_LOW, 0x40},
	    // {OV5640_TIMING_TC_REG20, 0x06},
	    // {OV5640_TIMING_TC_REG21, 0x00},
	    // {OV5640_TIMING_X_INC, 0x31},
	    // {OV5640_TIMING_Y_INC, 0x31},
	    // {OV5640_TIMING_HS_HIGH, 0x00},
	    // {OV5640_TIMING_HS_LOW, 0x00},
	    // {OV5640_TIMING_VS_HIGH, 0x00},
	    // {OV5640_TIMING_VS_LOW, 0x04},
	    // {OV5640_TIMING_HW_HIGH, 0x0a},
	    // {OV5640_TIMING_HW_LOW, 0x3f},
	    // {OV5640_TIMING_VH_HIGH, 0x07},
	    // {OV5640_TIMING_VH_LOW, 0x9b},
	    // {OV5640_TIMING_DVPHO_HIGH, 0x03},
	    // {OV5640_TIMING_DVPHO_LOW, 0x20},
	    // {OV5640_TIMING_DVPVO_HIGH, 0x02},
	    // {OV5640_TIMING_DVPVO_LOW, 0x58},
	    // {OV5640_TIMING_HTS_HIGH, 0x06},
	    // {OV5640_TIMING_HTS_LOW, 0x40},
	    // {OV5640_TIMING_VTS_HIGH, 0x03},
	    // {OV5640_TIMING_VTS_LOW, 0xe8},
	    // {OV5640_TIMING_HOFFSET_HIGH, 0x00},
	    // {OV5640_TIMING_HOFFSET_LOW, 0x10},
	    // {OV5640_TIMING_VOFFSET_HIGH, 0x00},
	    // {OV5640_TIMING_VOFFSET_LOW, 0x06},
	    // {0x3618, 0x00},
	    // {0x3612, 0x29},
	    // {0x3708, 0x64},
	    // {0x3709, 0x52},
	    // {0x370c, 0x03},
	    // {OV5640_AEC_CTRL02, 0x03},
	    // {OV5640_AEC_CTRL03, 0xd8},
	    // {OV5640_AEC_B50_STEP_HIGH, 0x01},
	    // {OV5640_AEC_B50_STEP_LOW, 0x27},
	    // {OV5640_AEC_B60_STEP_HIGH, 0x00},
	    // {OV5640_AEC_B60_STEP_LOW, 0xf6},
	    // {OV5640_AEC_CTRL0E, 0x03},
	    // {OV5640_AEC_CTRL0D, 0x04},
	    // {OV5640_AEC_MAX_EXPO_HIGH, 0x03},
	    // {OV5640_AEC_MAX_EXPO_LOW, 0xd8},
	    // {OV5640_BLC_CTRL01, 0x02},
	    // {OV5640_BLC_CTRL04, 0x02},
	    // {OV5640_SYSREM_RESET00, 0x00},
	    // {OV5640_SYSREM_RESET02, 0x1c},
	    // {OV5640_CLOCK_ENABLE00, 0xff},
	    // {OV5640_CLOCK_ENABLE02, 0xc3},
	    // {OV5640_MIPI_CONTROL00, 0x58},
	    // {0x302e, 0x00},
	    // {OV5640_POLARITY_CTRL, 0x22},
	    // {OV5640_FORMAT_CTRL00, 0x6F},
	    // {OV5640_FORMAT_MUX_CTRL, 0x01},
	    // {OV5640_JPG_MODE_SELECT, 0x03},
	    // {OV5640_JPEG_CTRL07, 0x04},
	    // {0x440e, 0x00},
	    // {0x460b, 0x35},
	    // {0x460c, 0x23},
	    // {OV5640_PCLK_PERIOD, 0x22},
	    // {0x3824, 0x02},
	    // {OV5640_ISP_CONTROL00, 0xa7},
	    // {OV5640_ISP_CONTROL01, 0xa3},
	    // {OV5640_AWB_CTRL00, 0xff},
	    // {OV5640_AWB_CTRL01, 0xf2},
	    // {OV5640_AWB_CTRL02, 0x00},
	    // {OV5640_AWB_CTRL03, 0x14},
	    // {OV5640_AWB_CTRL04, 0x25},
	    // {OV5640_AWB_CTRL05, 0x24},
	    // {OV5640_AWB_CTRL06, 0x09},
	    // {OV5640_AWB_CTRL07, 0x09},
	    // {OV5640_AWB_CTRL08, 0x09},
	    // {OV5640_AWB_CTRL09, 0x75},
	    // {OV5640_AWB_CTRL10, 0x54},
	    // {OV5640_AWB_CTRL11, 0xe0},
	    // {OV5640_AWB_CTRL12, 0xb2},
	    // {OV5640_AWB_CTRL13, 0x42},
	    // {OV5640_AWB_CTRL14, 0x3d},
	    // {OV5640_AWB_CTRL15, 0x56},
	    // {OV5640_AWB_CTRL16, 0x46},
	    // {OV5640_AWB_CTRL17, 0xf8},
	    // {OV5640_AWB_CTRL18, 0x04},
	    // {OV5640_AWB_CTRL19, 0x70},
	    // {OV5640_AWB_CTRL20, 0xf0},
	    // {OV5640_AWB_CTRL21, 0xf0},
	    // {OV5640_AWB_CTRL22, 0x03},
	    // {OV5640_AWB_CTRL23, 0x01},
	    // {OV5640_AWB_CTRL24, 0x04},
	    // {OV5640_AWB_CTRL25, 0x12},
	    // {OV5640_AWB_CTRL26, 0x04},
	    // {OV5640_AWB_CTRL27, 0x00},
	    // {OV5640_AWB_CTRL28, 0x06},
	    // {OV5640_AWB_CTRL29, 0x82},
	    // {OV5640_AWB_CTRL30, 0x38},
	    // {OV5640_CMX1, 0x1e},
	    // {OV5640_CMX2, 0x5b},
	    // {OV5640_CMX3, 0x08},
	    // {OV5640_CMX4, 0x0a},
	    // {OV5640_CMX5, 0x7e},
	    // {OV5640_CMX6, 0x88},
	    // {OV5640_CMX7, 0x7c},
	    // {OV5640_CMX8, 0x6c},
	    // {OV5640_CMX9, 0x10},
	    // {OV5640_CMXSIGN_HIGH, 0x01},
	    // {OV5640_CMXSIGN_LOW, 0x98},
	    // {OV5640_CIP_SHARPENMT_TH1, 0x08},
	    // {OV5640_CIP_SHARPENMT_TH2, 0x30},
	    // {OV5640_CIP_SHARPENMT_OFFSET1, 0x10},
	    // {OV5640_CIP_SHARPENMT_OFFSET2, 0x00},
	    // {OV5640_CIP_DNS_TH1, 0x08},
	    // {OV5640_CIP_DNS_TH2, 0x30},
	    // {OV5640_CIP_DNS_OFFSET1, 0x08},
	    // {OV5640_CIP_DNS_OFFSET2, 0x16},
	    // {OV5640_CIP_CTRL, 0x08},
	    // {OV5640_CIP_SHARPENTH_TH1, 0x30},
	    // {OV5640_CIP_SHARPENTH_TH2, 0x04},
	    // {OV5640_CIP_SHARPENTH_OFFSET1, 0x06},
	    // {OV5640_GAMMA_CTRL00, 0x01},
	    // {OV5640_GAMMA_YST00, 0x08},
	    // {OV5640_GAMMA_YST01, 0x14},
	    // {OV5640_GAMMA_YST02, 0x28},
	    // {OV5640_GAMMA_YST03, 0x51},
	    // {OV5640_GAMMA_YST04, 0x65},
	    // {OV5640_GAMMA_YST05, 0x71},
	    // {OV5640_GAMMA_YST06, 0x7d},
	    // {OV5640_GAMMA_YST07, 0x87},
	    // {OV5640_GAMMA_YST08, 0x91},
	    // {OV5640_GAMMA_YST09, 0x9a},
	    // {OV5640_GAMMA_YST0A, 0xaa},
	    // {OV5640_GAMMA_YST0B, 0xb8},
	    // {OV5640_GAMMA_YST0C, 0xcd},
	    // {OV5640_GAMMA_YST0D, 0xdd},
	    // {OV5640_GAMMA_YST0E, 0xea},
	    // {OV5640_GAMMA_YST0F, 0x1d},
	    // {OV5640_SDE_CTRL0, 0x02},
	    // {OV5640_SDE_CTRL3, 0x40},
	    // {OV5640_SDE_CTRL4, 0x10},
	    // {OV5640_SDE_CTRL9, 0x10},
	    // {OV5640_SDE_CTRL10, 0x00},
	    // {OV5640_SDE_CTRL11, 0xf8},
	    // {OV5640_GMTRX00, 0x23},
	    // {OV5640_GMTRX01, 0x14},
	    // {OV5640_GMTRX02, 0x0f},
	    // {OV5640_GMTRX03, 0x0f},
	    // {OV5640_GMTRX04, 0x12},
	    // {OV5640_GMTRX05, 0x26},
	    // {OV5640_GMTRX10, 0x0c},
	    // {OV5640_GMTRX11, 0x08},
	    // {OV5640_GMTRX12, 0x05},
	    // {OV5640_GMTRX13, 0x05},
	    // {OV5640_GMTRX14, 0x08},
	    // {OV5640_GMTRX15, 0x0d},
	    // {OV5640_GMTRX20, 0x08},
	    // {OV5640_GMTRX21, 0x03},
	    // {OV5640_GMTRX22, 0x00},
	    // {OV5640_GMTRX23, 0x00},
	    // {OV5640_GMTRX24, 0x03},
	    // {OV5640_GMTRX25, 0x09},
	    // {OV5640_GMTRX30, 0x07},
	    // {OV5640_GMTRX31, 0x03},
	    // {OV5640_GMTRX32, 0x00},
	    // {OV5640_GMTRX33, 0x01},
	    // {OV5640_GMTRX34, 0x03},
	    // {OV5640_GMTRX35, 0x08},
	    // {OV5640_GMTRX40, 0x0d},
	    // {OV5640_GMTRX41, 0x08},
	    // {OV5640_GMTRX42, 0x05},
	    // {OV5640_GMTRX43, 0x06},
	    // {OV5640_GMTRX44, 0x08},
	    // {OV5640_GMTRX45, 0x0e},
	    // {OV5640_GMTRX50, 0x29},
	    // {OV5640_GMTRX51, 0x17},
	    // {OV5640_GMTRX52, 0x11},
	    // {OV5640_GMTRX53, 0x11},
	    // {OV5640_GMTRX54, 0x15},
	    // {OV5640_GMTRX55, 0x28},
	    // {OV5640_BRMATRX00, 0x46},
	    // {OV5640_BRMATRX01, 0x26},
	    // {OV5640_BRMATRX02, 0x08},
	    // {OV5640_BRMATRX03, 0x26},
	    // {OV5640_BRMATRX04, 0x64},
	    // {OV5640_BRMATRX05, 0x26},
	    // {OV5640_BRMATRX06, 0x24},
	    // {OV5640_BRMATRX07, 0x22},
	    // {OV5640_BRMATRX08, 0x24},
	    // {OV5640_BRMATRX09, 0x24},
	    // {OV5640_BRMATRX20, 0x06},
	    // {OV5640_BRMATRX21, 0x22},
	    // {OV5640_BRMATRX22, 0x40},
	    // {OV5640_BRMATRX23, 0x42},
	    // {OV5640_BRMATRX24, 0x24},
	    // {OV5640_BRMATRX30, 0x26},
	    // {OV5640_BRMATRX31, 0x24},
	    // {OV5640_BRMATRX32, 0x22},
	    // {OV5640_BRMATRX33, 0x22},
	    // {OV5640_BRMATRX34, 0x26},
	    // {OV5640_BRMATRX40, 0x44},
	    // {OV5640_BRMATRX41, 0x24},
	    // {OV5640_BRMATRX42, 0x26},
	    // {OV5640_BRMATRX43, 0x28},
	    // {OV5640_BRMATRX44, 0x42},
	    // {OV5640_LENC_BR_OFFSET, 0xce},
	    // {0x5025, 0x00},
	    // {OV5640_AEC_CTRL0F, 0x30},
	    // {OV5640_AEC_CTRL10, 0x28},
	    // {OV5640_AEC_CTRL1B, 0x30},
	    // {OV5640_AEC_CTRL1E, 0x26},
	    // {OV5640_AEC_CTRL11, 0x60},
	    // {OV5640_AEC_CTRL1F, 0x14},
	    // {OV5640_SYSTEM_CTROL0, 0x02},
	   

};


//output formats

const uint16_t format_jpeg[][2] = {
		// {OV5640_FORMAT_CTRL00, 0x30}, // YUV 422, YUYV --> DIFF!
		// {OV5640_FORMAT_MUX_CTRL, 0x00}, // YUV 422 --> DIFF!

		// // Input clo}ck = 24Mhz
		// {0x3035, 0x21}, // PLL (PLL) --> DIFF!
		// {0x3036, 0x69}, // PLL (PLL)


		// {OV5640_LIGHTMETER1_TH_LOW, 0x07}, // lightmeter 1 threshold[7:0]
		// {0x3820, 0x46}, // flip
		// {0x3821, 0x20}, // mirror --> DIFF!
		// {0x3814, 0x11}, // timing X inc --> DIFF!
		// {0x3815, 0x11}, // timing Y inc --> DIFF!
		// {X_ADDR_ST_H, 0x00}, // HS
		// {0x3801, 0x00}, // HS
		// {0x3802, 0x00}, // VS
		// {0x3803, 0x00}, // VS
		// {0x3804, 0x0a}, // HW (HE)
		// {0x3805, 0x3f}, // HW (HE)
		// {0x3806, 0x07}, // VH (VE) --> DIFF!
		// {0x3807, 0x9f}, // VH (VE) --> DIFF!

		// {0x3808, 0x02}, // DVPHO --> DIFF!
		// {0x3809, 0x80}, // DVPHO --> DIFF!
		// {0x380a, 0x01}, // DVPVO --> DIFF!
		// {0x380b, 0xe0}, // DVPVO --> DIFF!

		// {0x380c, 0x0b}, // HTS 		// --> DIFF!
		// {0x380d, 0x1c}, // HTS--> DIFF!
		// {0x380e, 0x07}, // VTS 		//--> DIFF!
		// {0x380f, 0xb0}, // VTS--> DIFF!
		// {0x3813, 0x04}, // timing V offset   04
		// {0x3618, 0x04},// --> DIFF!
		// {0x3612, 0x2b},//--> DIFF!
		// {0x3709, 0x12},// --> DIFF!
		// {0x370c, 0x00},//--> DIFF!

	    // {0x3a02, 0x02}, // 60Hz max exposure
		// {0x3a03, 0xe0}, // 60Hz max exposure
		// {0x3a14, 0x02}, // 50Hz max exposure
		// {0x3a15, 0xe0}, // 50Hz max exposure

		// {OV5640_BLC_CTRL04, 0x06}, // BLC line number --> --> DIFF!
		// {OV5640_SYSREM_RESET02, 0x00}, // enable JFIFO, SFIFO, JPG  --> DIFF!
		// {OV5640_CLOCK_ENABLE02, 0xff}, // enable clock of JPEG2x, JPEG --> DIFF!
		// {JPG_MODE_SELECT, 0x03}, // JPEG mode 3
		// {COMPRESSION_CTRL07, 0x01}, // Quantization sacle --> DIFF!
		// {0x460b, 0x35}, //--> DIFF!
		// {0x460c, 0x22}, //--> DIFF!
		// {OV5640_PCLK_PERIOD, 0x16}, // MIPI global timing
		// {PCLK_RATIO, 0x02}, // PCLK manual divider --> DIFF!
		// {OV5640_ISP_CONTROL01, 0xA3}, // SDE on, Scaling on, CMX on, AWB on --> DIFF!
		// {AEC_PK_MANUAL, 0x00},// --> DIFF!

				{0x4300, 0x30}, // YUV 422, YUYV --> DIFF!
		{0x501f, 0x00}, // YUV 422 --> DIFF!

		// Input clo}ck = 24Mhz
		{0x3035, 0x21}, // PLL (PLL) --> DIFF!
		{0x3036, 0x69}, // PLL (PLL)


		{0x3c07, 0x07}, // lightmeter 1 threshold[7:0]
		{0x3820, 0x46}, // flip
		{0x3821, 0x20}, // mirror --> DIFF!
		{0x3814, 0x11}, // timing X inc --> DIFF!
		{0x3815, 0x11}, // timing Y inc --> DIFF!
		{0x3800, 0x00}, // HS
		{0x3801, 0x00}, // HS
		{0x3802, 0x00}, // VS
		{0x3803, 0x00}, // VS
		{0x3804, 0x0a}, // HW (HE)
		{0x3805, 0x3f}, // HW (HE)
		{0x3806, 0x07}, // VH (VE) --> DIFF!
		{0x3807, 0x9f}, // VH (VE) --> DIFF!

		{0x3808, 0x02}, // DVPHO --> DIFF!
		{0x3809, 0x80}, // DVPHO --> DIFF!
		{0x380a, 0x01}, // DVPVO --> DIFF!
		{0x380b, 0xe0}, // DVPVO --> DIFF!

		{0x380c, 0x0b}, // HTS 		// --> DIFF!
		{0x380d, 0x1c}, // HTS--> DIFF!
		{0x380e, 0x07}, // VTS 		//--> DIFF!
		{0x380f, 0xb0}, // VTS--> DIFF!
		{0x3813, 0x04}, // timing V offset   04
		{0x3618, 0x04},// --> DIFF!
		{0x3612, 0x2b},//--> DIFF!
		{0x3709, 0x12},// --> DIFF!
		{0x370c, 0x00},//--> DIFF!

	    {0x3a02, 0x02}, // 60Hz max exposure
		{0x3a03, 0xe0}, // 60Hz max exposure
		{0x3a14, 0x02}, // 50Hz max exposure
		{0x3a15, 0xe0}, // 50Hz max exposure

		{0x4004, 0x06}, // BLC line number --> --> DIFF!
		{0x3002, 0x00}, // enable JFIFO, SFIFO, JPG  --> DIFF!
		{0x3006, 0xff}, // enable clock of JPEG2x, JPEG --> DIFF!
		{0x4713, 0x03}, // JPEG mode 3
		{0x4407, 0x01}, // Quantization sacle --> DIFF!
		{0x460b, 0x35}, //--> DIFF!
		{0x460c, 0x22}, //--> DIFF!
		{0x4837, 0x16}, // MIPI global timing
		{0x3824, 0x02}, // PCLK manual divider --> DIFF!
		{0x5001, 0xA3}, // SDE on, Scaling on, CMX on, AWB on --> DIFF!
		{0x3503, 0x00},// --> DIFF!

//set resolution
//	    {OV5640_TIMING_DVPHO_HIGH, 0x01},
//	    {OV5640_TIMING_DVPHO_LOW, 0xE0},
//	    {OV5640_TIMING_DVPVO_HIGH, 0x01},
//	    {OV5640_TIMING_DVPVO_LOW, 0x10},

// Set pixel fomat to JPEG
	    {OV5640_FORMAT_CTRL00, 0x30},
	    {OV5640_FORMAT_MUX_CTRL, 0x00},


//Write timings
		//{OV5640_TIMING_TC_REG21,}

};


const  uint16_t format_rgb565[][2] = {

//	 1280x800, 15fps
//	 input clock 24Mhz, PCLK 42Mhz
		{OV5640_FORMAT_CTRL00, 0X6F},
		{OV5640_FORMAT_MUX_CTRL, 0x01},
		// 1280x800,} 15fps
		// input clo}ck 24Mhz, PCLK 42Mhz

		{0x3035, 0x41}, // PLL
		{0x3036, 0x69}, // PLL

		{OV5640_LIGHTMETER1_TH_LOW, 0x07}, // lightmeter 1 threshold[7:0]
		{0x3820, 0x46}, // flip
		{0x3821, 0x00}, // mirror
		{0x3814, 0x31}, // timing X inc
		{0x3815, 0x31}, // timing Y inc
		{X_ADDR_ST_H, 0x00}, // HS
		{0x3801, 0x00}, // HS
		{0x3802, 0x00}, // VS
		{0x3803, 0x00}, // VS
		{0x3804, 0x0a}, // HW (HE)
		{0x3805, 0x3f}, // HW (HE)
		{0x3806, 0x06}, // VH (VE)
		{0x3807, 0xa9}, // VH (VE)
		{0x3808, 0x05}, // DVPHO
		{0x3809, 0x00}, // DVPHO
		{0x380a, 0x02}, // DVPVO
		{0x380b, 0xd0}, // DVPVO
		{0x380c, 0x05}, // HTS
		{0x380d, 0xF8}, // HTS
		{0x380e, 0x03}, // VTS
		{0x380f, 0x84}, // VTS
		{0x3813, 0x04}, // timing V offset
		{0x3618, 0x00},
		{0x3612, 0x29},
		{0x3709, 0x52},
		{0x370c, 0x03},
		{0x3a02, 0x02}, // 60Hz max exposure
		{0x3a03, 0xe0}, // 60Hz max exposure

		{0x3a14, 0x02}, // 50Hz max exposure
		{0x3a15, 0xe0}, // 50Hz max exposure
		{0x4004, 0x02}, // BLC line number
		{0x3002, 0x1c}, // reset JFIFO, SFIFO, JPG
		{0x3006, 0xc3}, // disable clock of JPEG2x, JPEG
		//{0x4713, 0x03}, // JPEG mode 3
		{0x4713, 0x02}, // JPEG mode 2
		{0x4407, 0x04}, // Quantization scale
		{0x460b, 0x37},
		{0x460c, 0x20}, //VFIFO CTRL0C - default value
		{0x4837, 0x16}, // MIPI global timing
		{0x3824, 0x04}, // PCLK manual divider
		{OV5640_ISP_CONTROL01, 0xA3}, // SDE on, scale on, UV average off, color matrix on, AWB on
		{AEC_PK_MANUAL, 0x00}, // A


		//==================
		//set resolution
//		{OV5640_TIMING_DVPHO_HIGH, 0x01},
//		{OV5640_TIMING_DVPHO_LOW, 0xE0},
//		{OV5640_TIMING_DVPVO_HIGH, 0x01},
//		{OV5640_TIMING_DVPVO_LOW, 0x10},

		// Set pixel fomat to RGB565
//	    {OV5640_FORMAT_CTRL00, 0x6F},
//	    {OV5640_FORMAT_MUX_CTRL, 0x01}

};

//resolutions

const uint16_t OV5640_WVGA[][2]=
{
  {X_OUTPUT_SIZE_H, 0x03},
  {X_OUTPUT_SIZE_L, 0x20},
  {Y_OUTPUT_SIZE_H, 0x01},
  {Y_OUTPUT_SIZE_L, 0xE0},
  {FORMAT_CTRL00, 0x6F},
  {CLOCK_POL_CONTROL, 0x22},
  //{FORMAT_CTRL, 0x01},
};

/* Initialization sequence for VGA resolution (640x480)*/
const uint16_t OV5640_VGA[][2]=
{
  {X_OUTPUT_SIZE_H, 0x02},
  {X_OUTPUT_SIZE_L, 0x80},
  {Y_OUTPUT_SIZE_H, 0x01},
  {Y_OUTPUT_SIZE_L, 0xE0},
  {FORMAT_CTRL00, 0x6F},
  {CLOCK_POL_CONTROL, 0x22},
  //{FORMAT_CTRL, 0x01}, //RGB
};

/* Initialization sequence for 480x272 resolution */
const uint16_t OV5640_480x272[][2]=
{
  {X_OUTPUT_SIZE_H, 0x01},
  {X_OUTPUT_SIZE_L, 0xE0},
  {Y_OUTPUT_SIZE_H, 0x01},
  {Y_OUTPUT_SIZE_L, 0x10},
  {FORMAT_CTRL00, 0x6F},
  {CLOCK_POL_CONTROL, 0x22},
  //{FORMAT_CTRL, 0x01},
};

const uint16_t OV5640_QVGA[][2] =
{
  {X_OUTPUT_SIZE_H, 0x01},
  {X_OUTPUT_SIZE_L, 0x40},
  {Y_OUTPUT_SIZE_H, 0x00},
  {Y_OUTPUT_SIZE_L, 0xF0},
  {FORMAT_CTRL00, 0x6F},
  {CLOCK_POL_CONTROL, 0x22},
  //{FORMAT_CTRL, 0x01},
};

/* Initialization sequence for QQVGA resolution (160x120) */
const uint16_t OV5640_QQVGA[][2]=
{
  {X_OUTPUT_SIZE_H, 0x00},
  {X_OUTPUT_SIZE_L, 0xA0},
  {Y_OUTPUT_SIZE_H, 0x00},
  {Y_OUTPUT_SIZE_L, 0x78},
  {FORMAT_CTRL00, 0x6F},
  {CLOCK_POL_CONTROL, 0x22},
  //{FORMAT_CTRL, 0x01}, //rgb, YUB
};


/* OV5640 Light Mode setting */
const uint16_t OV5640_LightModeAuto[][2]=
{
  {0x3406, 0x00},
  {0x3400, 0x04},
  {0x3401, 0x00},
  {0x3402, 0x04},
  {0x3403, 0x00},
  {0x3404, 0x04},
  {0x3405, 0x00},
};

const uint16_t OV5640_LightModeCloudy[][2]=
{
  {0x3406, 0x01},
  {0x3400, 0x06},
  {0x3401, 0x48},
  {0x3402, 0x04},
  {0x3403, 0x00},
  {0x3404, 0x04},
  {0x3405, 0xd3},
};

const uint16_t OV5640_LightModeOffice[][2]=
{
  {0x3406, 0x01},
  {0x3400, 0x05},
  {0x3401, 0x48},
  {0x3402, 0x04},
  {0x3403, 0x00},
  {0x3404, 0x07},
  {0x3405, 0xcf},
};

const uint16_t OV5640_LightModeHome[][2]=
{
  {0x3406, 0x01},
  {0x3400, 0x04},
  {0x3401, 0x10},
  {0x3402, 0x04},
  {0x3403, 0x00},
  {0x3404, 0x08},
  {0x3405, 0xB6},
};

const uint16_t OV5640_LightModeSunny[][2]=
{
  {0x3406, 0x01},
  {0x3400, 0x06},
  {0x3401, 0x1c},
  {0x3402, 0x04},
  {0x3403, 0x00},
  {0x3404, 0x04},
  {0x3405, 0xf3},
};

const uint16_t OV5640_NightMode[][2]=
{
  {OV5640_SC_PLL_CONTRL4, 0x00},
  {OV5640_SC_PLL_CONTRL5, 0x00},
  {OV5640_AEC_CTRL00, 0x7C},
  {OV5640_AEC_B50_STEP_HIGH, 0x01},
  {OV5640_AEC_B50_STEP_LOW, 0x27},
  {OV5640_AEC_B60_STEP_HIGH,0x00},
  {OV5640_AEC_B60_STEP_LOW, 0xF6},
  {OV5640_AEC_CTRL0D, 0x04},
  {OV5640_AEC_CTRL0E, 0x04},
  {OV5640_AEC_CTRL02, 0x0B},
  {OV5640_AEC_CTRL03, 0x88},
  {OV5640_AEC_MAX_EXPO_HIGH, 0x0B},
  {OV5640_AEC_MAX_EXPO_LOW, 0x88},
};



























#endif /* INC_OV5640_REG_SETTINGS_H_ */
