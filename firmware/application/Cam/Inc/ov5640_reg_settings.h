/*
 * ov5640_regs_settings.h
 *
 *  Created on: 8 Mar 2023
 *      Author: sol
 */

#ifndef INC_OV5640_REG_SETTINGS_H_
#define INC_OV5640_REG_SETTINGS_H_

#include "ov5640_registers.h"

const uint16_t OV5640_default_reg_settings[][2] = {
    {OV5640_SCCB_SYSTEM_CTRL1, 0x11},
    {OV5640_SYSTEM_CTROL0, 0x82},
    {OV5640_SCCB_SYSTEM_CTRL1, 0x03},
    {OV5640_PAD_OUTPUT_ENABLE01, 0xFF},
    {OV5640_PAD_OUTPUT_ENABLE02, 0xf3},
    {OV5640_SC_PLL_CONTRL0, 0x18},
    {OV5640_SYSTEM_CTROL0, 0x02},
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
    //=======================================
    {OV5640_JPG_MODE_SELECT, 0x02},  // set to 2 --> set to 3
    {OV5640_JPEG_CTRL07, 0x01},      // 0c
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

};

const uint16_t format_jpeg[][2] = {
    // 0x4300, 0x30, // YUV 422, YUYV
    // 0x501f, 0x00, // YUV 422
    // // Input clock = 24Mhz
    // 0x3035, 0x21, // PLL
    // 0x3036, 0x69, // PLL
    // 0x3c07, 0x07, // lightmeter 1 threshold[7:0]
    // 0x3820, 0x46, // flip
    // 0x3821, 0x20, // mirror
    // 0x3814, 0x11, // timing X inc
    // 0x3815, 0x11, // timing Y inc
    // 0x3800, 0x00, // HS
    // 0x3801, 0x00, // HS
    // 0x3802, 0x00, // VS
    // 0x3803, 0x00, // VS
    // 0x3804, 0x0a, // HW (HE)
    // 0x3805, 0x3f, // HW (HE)
    // 0x3806, 0x07, // VH (VE)
    // 0x3807, 0x9f, // VH (VE)

    // 0x3808, 0x02, // DVPHO
    // 0x3809, 0x80, // DVPHO
    // 0x380a, 0x01, // DVPVO
    // 0x380b, 0xe0, // DVPVO

    // 0x380c, 0x0b, // HTS 		//
    // 0x380d, 0x1c, // HTS
    // 0x380e, 0x07, // VTS 		//
    // 0x380f, 0xb0, // VTS
    // 0x3813, 0x04, // timing V offset   04
    // 0x3618, 0x04,
    // 0x3612, 0x2b,
    // 0x3709, 0x12,
    // 0x370c, 0x00,

    // 0x3a02, 0x02, // 60Hz max exposure
    // 0x3a03, 0xe0, // 60Hz max exposure
    // 0x3a14, 0x02, // 50Hz max exposure
    // 0x3a15, 0xe0, // 50Hz max exposure

    // 0x4004, 0x06, // BLC line number
    // 0x3002, 0x00, // enable JFIFO, SFIFO, JPG
    // 0x3006, 0xff, // enable clock of JPEG2x, JPEG
    // 0x4713, 0x02, // JPEG mode 3
    // 0x4407, 0x04, // Quantization sacle
    // 0x460b, 0x35,
    // 0x460c, 0x22,
    // 0x4837, 0x16, // MIPI global timing
    // 0x3824, 0x02, // PCLK manual divider
    // 0x5001, 0xA3, // SDE on, Scaling on, CMX on, AWB on
    // 0x3503, 0x00, // AEC/AGC on

    {OV5640_FORMAT_CTRL00, 0x30},
    {OV5640_FORMAT_MUX_CTRL, 0x00},
    // {0x3002, 0x00},//0x1c to 0x00 !!!
    // {0x3006, 0xff},//0xc3 to 0xff !!!
    // {0x471c, 0x50},//0xd0 to 0x50

};

const uint16_t format_rgb565[][2] = {
    {OV5640_FORMAT_CTRL00, 0x6F},
    {OV5640_FORMAT_MUX_CTRL, 0x01},
};

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

#endif /* INC_OV5640_REG_SETTINGS_H_ */
