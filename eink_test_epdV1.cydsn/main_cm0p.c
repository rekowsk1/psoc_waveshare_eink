/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * Microcontroller: CY8CPROTO-063-BLE (CYBLE-416045-02)
 * Eink display: waveshare 7.5inch e-Paper V1 black/white 640 x 384
 * The code used in this project originates mostly from the waveshare example sketch for Arduino
 *
 * ========================================
 */
#include "project.h"

// Display resolution
#define EPD_WIDTH       640
#define EPD_HEIGHT      384

#define PANEL_SETTING                               0x00
#define POWER_SETTING                               0x01
#define POWER_OFF                                   0x02
#define POWER_OFF_SEQUENCE_SETTING                  0x03
#define POWER_ON                                    0x04
#define POWER_ON_MEASURE                            0x05
#define BOOSTER_SOFT_START                          0x06
#define DEEP_SLEEP                                  0x07
#define DATA_START_TRANSMISSION_1                   0x10
#define DATA_STOP                                   0x11
#define DISPLAY_REFRESH                             0x12
#define IMAGE_PROCESS                               0x13
#define LUT_FOR_VCOM                                0x20 
#define LUT_BLUE                                    0x21
#define LUT_WHITE                                   0x22
#define LUT_GRAY_1                                  0x23
#define LUT_GRAY_2                                  0x24
#define LUT_RED_0                                   0x25
#define LUT_RED_1                                   0x26
#define LUT_RED_2                                   0x27
#define LUT_RED_3                                   0x28
#define LUT_XON                                     0x29
#define PLL_CONTROL                                 0x30
#define TEMPERATURE_SENSOR_COMMAND                  0x40
#define TEMPERATURE_CALIBRATION                     0x41
#define TEMPERATURE_SENSOR_WRITE                    0x42
#define TEMPERATURE_SENSOR_READ                     0x43
#define VCOM_AND_DATA_INTERVAL_SETTING              0x50
#define LOW_POWER_DETECTION                         0x51
#define TCON_SETTING                                0x60
#define TCON_RESOLUTION                             0x61
#define SPI_FLASH_CONTROL                           0x65
#define REVISION                                    0x70
#define GET_STATUS                                  0x71
#define AUTO_MEASUREMENT_VCOM                       0x80
#define READ_VCOM_VALUE                             0x81
#define VCM_DC_SETTING                              0x82

uint8_t IMAGE_DATA[3096] = {
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XC0, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X01, 0XFF, 0XC0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XFF, 0XC0, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X01, 0XFF, 0XC0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X01, 0XFF, 0XC0, 0X00, 0X00,
    0X00, 0X00, 0X01, 0XF8, 0X78, 0X0F, 0X00, 0X0F, 0XFF, 0XFF, 0XFF, 0XC0,
    0X00, 0X01, 0XF0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X01, 0XFF, 0XC0, 0X00, 0X00, 0X00, 0X00, 0X01, 0XF8, 0X78, 0X0F,
    0X00, 0X0F, 0XFF, 0XFF, 0XFF, 0XC0, 0X00, 0X01, 0XF0, 0X00, 0X00, 0X1F,
    0XFF, 0XFF, 0XF0, 0X00, 0X00, 0X00, 0X00, 0X01, 0XF8, 0X3F, 0XFF, 0XFF,
    0XFF, 0XFC, 0X03, 0XF0, 0X78, 0X0F, 0X00, 0X0F, 0XFF, 0XFF, 0XFF, 0XC0,
    0X00, 0X01, 0XF0, 0X00, 0X00, 0X3F, 0XFF, 0XFF, 0XF8, 0X00, 0X00, 0X00,
    0X00, 0X01, 0XF8, 0X3F, 0XFF, 0XFF, 0XFF, 0XFC, 0X07, 0XEF, 0X7B, 0XCF,
    0X00, 0X0F, 0XFF, 0XFF, 0XFF, 0XC0, 0X00, 0X01, 0XF0, 0X00, 0X00, 0X3F,
    0XFF, 0XFF, 0XFC, 0X00, 0X00, 0X00, 0X00, 0X01, 0XF8, 0X3F, 0XFF, 0XFF,
    0XFF, 0XFC, 0X0F, 0XEF, 0X7B, 0XCF, 0X00, 0X00, 0X00, 0X7C, 0X00, 0X00,
    0X00, 0X03, 0XF0, 0X00, 0X00, 0X3F, 0XFF, 0XFF, 0XFE, 0X00, 0X00, 0X00,
    0X00, 0X01, 0XF8, 0X3F, 0XFF, 0XFF, 0XFF, 0XFC, 0X1F, 0XCF, 0X7B, 0XDF,
    0X00, 0X3F, 0XFF, 0XFF, 0XFF, 0XF0, 0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X3F,
    0XFF, 0XFF, 0XFC, 0X00, 0X00, 0X00, 0X00, 0X01, 0XF8, 0X3F, 0XFF, 0XFF,
    0XFF, 0XFC, 0X3F, 0X8F, 0X7B, 0XDF, 0X00, 0X3F, 0XFF, 0XFF, 0XFF, 0XF0,
    0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X1F, 0XFF, 0XFF, 0XF8, 0X00, 0X00, 0X00,
    0X00, 0X00, 0XFF, 0XFF, 0XFF, 0XFE, 0XFF, 0XFC, 0X3F, 0X0F, 0X7B, 0XDF,
    0XFE, 0X3F, 0XFF, 0XFF, 0XFF, 0XF0, 0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00,
    0X00, 0X1F, 0XF0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFC,
    0XFF, 0XFC, 0X1E, 0XFF, 0XFF, 0XFF, 0XFE, 0X3F, 0XFF, 0XFF, 0XFF, 0XF0,
    0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00, 0X00, 0X7F, 0XC0, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XF8, 0XFF, 0XFC, 0X1D, 0XFF, 0XFF, 0XFF,
    0XFE, 0X3C, 0X00, 0X7C, 0X01, 0XF0, 0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00,
    0X00, 0XFF, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XF0,
    0XFF, 0XFC, 0X09, 0XFF, 0XFF, 0XFF, 0XFE, 0X3D, 0XFE, 0X7F, 0XFF, 0XF0,
    0X1F, 0X01, 0XF0, 0X1F, 0X00, 0X00, 0X03, 0XFF, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XE0, 0XFF, 0XFC, 0X03, 0XFF, 0XFF, 0XFE,
    0XF8, 0X3D, 0XFE, 0X7F, 0XFF, 0XF0, 0X1F, 0X01, 0XF0, 0X1F, 0X00, 0X00,
    0X03, 0XFE, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XE0,
    0XFF, 0XFC, 0X03, 0XF0, 0X00, 0X7E, 0XF8, 0X3D, 0XFE, 0X7F, 0XFF, 0XF0,
    0X1F, 0X01, 0XF0, 0X1F, 0X00, 0X00, 0X03, 0XF0, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XE0, 0XFF, 0XFC, 0X07, 0XE0, 0X00, 0XFE,
    0XF8, 0X3C, 0X00, 0X7C, 0X01, 0XF0, 0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00,
    0X03, 0XE0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0E, 0X0F, 0X0F, 0XC1,
    0XF1, 0XFC, 0X0F, 0XEF, 0XFF, 0XFE, 0XF8, 0X3D, 0XFE, 0X7F, 0XFF, 0XF0,
    0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00, 0X03, 0XE0, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0E, 0X0F, 0X07, 0XC3, 0XE0, 0XFC, 0X1F, 0XEF, 0XFF, 0XFE,
    0XF8, 0X3D, 0XFE, 0X7F, 0XFE, 0XF0, 0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00,
    0X03, 0XE0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0E, 0X0F, 0X07, 0X83,
    0XE0, 0XFC, 0X3F, 0XEF, 0XFF, 0XFE, 0XF8, 0X01, 0XFE, 0X7F, 0XFE, 0X00,
    0X1F, 0XFF, 0XFF, 0XFF, 0X03, 0XFF, 0XFF, 0XFF, 0XFF, 0XC0, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0X07, 0X07, 0X83, 0XC0, 0X7C, 0X3F, 0XEF, 0XFF, 0XFF,
    0XF8, 0X00, 0X00, 0X7C, 0X00, 0X00, 0X1F, 0X03, 0XF0, 0X1F, 0X03, 0XFF,
    0XFF, 0XFF, 0XFF, 0XC0, 0X00, 0X00, 0X00, 0X00, 0X0F, 0X07, 0X03, 0X87,
    0XC0, 0X7C, 0X3F, 0XE0, 0X00, 0X3F, 0XF8, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X1F, 0X01, 0XF0, 0X1F, 0X03, 0XFF, 0XFF, 0XFF, 0XFF, 0XC0, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0X06, 0X03, 0X07, 0X80, 0X3C, 0X3F, 0XE3, 0XFF, 0X0F,
    0XF0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X1F, 0X01, 0XF0, 0X1F, 0X03, 0XFF,
    0XFF, 0XFF, 0XFF, 0XC0, 0X00, 0X00, 0X00, 0X00, 0X0F, 0X00, 0X01, 0X0F,
    0X80, 0X3C, 0X1F, 0XE3, 0XFF, 0X0F, 0XF0, 0X07, 0XFF, 0XFF, 0XFF, 0X80,
    0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00, 0X07, 0XE0, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0X80, 0X00, 0X0F, 0X80, 0X3C, 0X19, 0XE3, 0XFF, 0X0F,
    0XF0, 0X07, 0XFF, 0XFF, 0XFF, 0X80, 0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00,
    0X03, 0XE0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0X80, 0X60, 0X0F,
    0X04, 0X1C, 0X01, 0XE3, 0XFF, 0X0F, 0XE0, 0X07, 0XFF, 0XFF, 0XFF, 0X80,
    0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00, 0X03, 0XE0, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0X80, 0X60, 0X1E, 0X04, 0X1C, 0X01, 0XE3, 0XCF, 0X0F,
    0XE0, 0X03, 0XFF, 0XFF, 0XFF, 0X80, 0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00,
    0X03, 0XE0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XC0, 0X70, 0X1E,
    0X0E, 0X0C, 0X01, 0XE3, 0XCF, 0XF7, 0XE0, 0X00, 0X00, 0X00, 0X0F, 0X80,
    0X1F, 0XFF, 0XFF, 0XFF, 0X00, 0X00, 0X03, 0XE0, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XC0, 0XF0, 0X3C, 0X1F, 0X04, 0X01, 0XE3, 0XCF, 0XF7,
    0XC0, 0X03, 0XFF, 0XFF, 0XFF, 0X80, 0X1F, 0X01, 0XF0, 0X01, 0XC0, 0X00,
    0X03, 0XE0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XE0, 0XF0, 0X78,
    0X1F, 0X0C, 0X01, 0XE7, 0XCF, 0XFF, 0XE0, 0X03, 0XFF, 0XFF, 0XFF, 0X80,
    0X1F, 0X01, 0XF0, 0X03, 0XF0, 0X00, 0X03, 0XE0, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XE0, 0XF0, 0X78, 0X3E, 0X0C, 0X01, 0XE7, 0XCF, 0XFF,
    0XF0, 0X03, 0XFF, 0XFF, 0XFF, 0X80, 0X1F, 0X01, 0XF0, 0X03, 0XF0, 0X00,
    0X03, 0XE0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XE0, 0XF8, 0X78,
    0X3E, 0X1C, 0X01, 0XE7, 0XCF, 0XFF, 0XF0, 0X01, 0XFF, 0XFF, 0XFF, 0X80,
    0X00, 0X01, 0XF0, 0X03, 0XF0, 0X00, 0X03, 0XE0, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XF1, 0XF8, 0X78, 0X3C, 0X1C, 0X01, 0XEF, 0X8F, 0XBF,
    0XF8, 0X00, 0X00, 0X00, 0X0F, 0X80, 0X00, 0X01, 0XF0, 0X03, 0XE0, 0X00,
    0X03, 0XE0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF,
    0XFC, 0X3C, 0X01, 0XEF, 0X8F, 0XFF, 0XFC, 0X07, 0XFF, 0XFF, 0XFF, 0X80,
    0X00, 0X01, 0XFF, 0XFF, 0XE0, 0X03, 0XFF, 0XE0, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF, 0XF0, 0X3C, 0X01, 0XFF, 0X8F, 0XFE,
    0XFF, 0X07, 0XFF, 0XFF, 0XFF, 0X80, 0X00, 0X01, 0XFF, 0XFF, 0XE0, 0X01,
    0XFF, 0XE0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF,
    0XF0, 0X7C, 0X01, 0XFF, 0X01, 0XFC, 0X7E, 0X07, 0XFF, 0XFF, 0XFF, 0X80,
    0X00, 0X01, 0XFF, 0XFF, 0XC0, 0X01, 0XFF, 0XE0, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF, 0XF0, 0X7C, 0X01, 0XE7, 0X00, 0XF8,
    0X3C, 0X07, 0XFF, 0XFF, 0XFF, 0X80, 0X00, 0X00, 0XFF, 0XFF, 0XC0, 0X01,
    0XFF, 0XC0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF,
    0XF0, 0X7C, 0X01, 0XE6, 0X00, 0XF0, 0X18, 0X00, 0X00, 0X00, 0X0F, 0X80,
    0X00, 0X00, 0X7F, 0XFF, 0X80, 0X01, 0XFF, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF, 0XF0, 0XFC, 0X01, 0XE0, 0X00, 0X60,
    0X00, 0X00, 0X00, 0X00, 0X0F, 0X80, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0XF0, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF,
    0XF1, 0XFC, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF, 0XF3, 0X83, 0XFF, 0XFF, 0XFF, 0XFF,
    0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    0XFF, 0XFF, 0XFF, 0XFE, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF,
    0XF7, 0X83, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFE, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF, 0XFF, 0X83, 0XFF, 0XFF, 0XFF, 0XFF,
    0XFF, 0XF8, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0X3F, 0XFF, 0XFF, 0XFF, 0XFF,
    0XFF, 0XFF, 0XFF, 0XFE, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF,
    0XFF, 0X83, 0XCE, 0X71, 0XFF, 0XFF, 0XFF, 0XF8, 0XFF, 0XFF, 0XFF, 0XFF,
    0X03, 0X3F, 0XFF, 0XFF, 0XFF, 0XFF, 0XFE, 0X3F, 0XFF, 0XFE, 0X00, 0X00,
    0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF, 0XFF, 0X83, 0XC6, 0X33, 0XFF, 0XFF,
    0XFF, 0XF8, 0XFF, 0XFF, 0XFF, 0XFF, 0X3F, 0X3F, 0XFF, 0XF3, 0XFF, 0XFF,
    0XFF, 0XFF, 0XFF, 0XFE, 0X00, 0X00, 0X00, 0X00, 0X0F, 0XFF, 0XFF, 0XFF,
    0XFF, 0XFF, 0XC6, 0X23, 0X8E, 0X79, 0X8F, 0X80, 0X1F, 0X1E, 0X1E, 0X3F,
    0X3F, 0X3C, 0X7C, 0X20, 0X83, 0X8E, 0X4F, 0X3C, 0X30, 0XFE, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XC4, 0X23, 0X07, 0X33,
    0X07, 0X08, 0X0E, 0X0C, 0X18, 0X1F, 0X3F, 0X30, 0X38, 0X20, 0X82, 0X06,
    0X06, 0X30, 0X30, 0XFE, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0XFF, 0XE4, 0X03, 0X33, 0X32, 0X32, 0X78, 0XC6, 0X44, 0X39, 0X9F,
    0X07, 0X31, 0XB1, 0XF3, 0X8E, 0X66, 0X22, 0X31, 0XE7, 0XFE, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XE0, 0X07, 0XC3, 0X02,
    0X03, 0X18, 0XC7, 0X84, 0X70, 0X1F, 0X3F, 0X30, 0X13, 0XF3, 0X9C, 0X62,
    0X62, 0X33, 0XE1, 0XFE, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0XFF, 0XE1, 0X87, 0X03, 0X06, 0X03, 0X88, 0XC6, 0X04, 0X70, 0X1F,
    0X3F, 0X30, 0X13, 0XF3, 0X9C, 0X62, 0X62, 0X33, 0XF0, 0XFE, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XE1, 0X86, 0X33, 0X06,
    0X7F, 0XC0, 0XC4, 0X44, 0X71, 0XFF, 0X3F, 0X33, 0XF3, 0XF3, 0X9C, 0X62,
    0X62, 0X33, 0XFC, 0XFE, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0XFF, 0XE1, 0X8E, 0X23, 0X8F, 0X3F, 0XC8, 0XC4, 0X44, 0X78, 0XFF,
    0X3F, 0X31, 0XF9, 0XF1, 0X9E, 0X06, 0X62, 0X31, 0XFC, 0XFE, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XF1, 0X8F, 0X03, 0X8F,
    0X86, 0X18, 0XC6, 0X04, 0X7C, 0X1F, 0X03, 0X3C, 0X3C, 0X30, 0X9F, 0X0E,
    0X62, 0X3C, 0X61, 0XFE, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFE, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    0XFF, 0XFF, 0XFF, 0XFE, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF,
    0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFE, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
    0X00, 0X00, 0X00, 0X00, 0X00, 0X00,
};

void eink_reset(void) {
    Cy_GPIO_Write(EINK_RST_PORT, EINK_RST_NUM, 0);
    CyDelay(200);
    Cy_GPIO_Write(EINK_RST_PORT, EINK_RST_NUM, 1);
    CyDelay(200);
}

void eink_send_cmd(uint8_t command) {
    Cy_GPIO_Write(EINK_DC_PORT, EINK_DC_NUM, 0);
    uint8_t txbuffer[1] = {command};
    uint8_t rxbuffer[1] = {command};
    volatile uint32_t res = EINK_SPI_Transfer(&txbuffer, &rxbuffer, 1);
    /* Blocking wait for transfer completion */
    while (0UL != (CY_SCB_SPI_TRANSFER_ACTIVE & EINK_SPI_GetTransferStatus())) {
        // wait
    }
}

void eink_send_data(uint8_t data) {
    Cy_GPIO_Write(EINK_DC_PORT, EINK_DC_NUM, 1);
    uint8_t txbuffer[1] = {data};
    uint8_t rxbuffer[1];
    volatile uint32_t res = EINK_SPI_Transfer(&txbuffer, &rxbuffer, 1);
    /* Blocking wait for transfer completion */
    while (0UL != (CY_SCB_SPI_TRANSFER_ACTIVE & EINK_SPI_GetTransferStatus())) {
        // wait
    }
}


void eink_wait_until_idle(void) {
    while (Cy_GPIO_Read(EINK_BUSY_PORT, EINK_BUSY_NUM) == 0) { //0: busy, 1: idle
        CyDelay(100);
    }
}

void eink_set_lut_by_host(uint8_t *lut_vcom, uint8_t *lut_ww, uint8_t *lut_bw,
                          uint8_t *lut_wb, uint8_t *lut_bb) {
    uint8_t count;
    eink_send_cmd(0x20); // VCOM
    for (count = 0; count < 42; count++)
        eink_send_data(lut_vcom[count]);

    eink_send_cmd(0x21); // LUTBW
    for (count = 0; count < 42; count++)
        eink_send_data(lut_ww[count]);

    eink_send_cmd(0x22); // LUTBW
    for (count = 0; count < 42; count++)
        eink_send_data(lut_bw[count]);

    eink_send_cmd(0x23); // LUTWB
    for (count = 0; count < 42; count++)
        eink_send_data(lut_wb[count]);

    eink_send_cmd(0x24); // LUTBB
    for (count = 0; count < 42; count++)
        eink_send_data(lut_bb[count]);
}
                        
void eink_sleep(void) {
    eink_send_cmd(POWER_OFF);
    eink_wait_until_idle();
    eink_send_cmd(DEEP_SLEEP);
    eink_send_data(0xa5);
}
                        
void eink_init(void) {
    eink_reset();

    eink_send_cmd(POWER_SETTING); 
    eink_send_data(0x37);
    eink_send_data(0x00);

    eink_send_cmd(PANEL_SETTING);
    eink_send_data(0xCF);
    eink_send_data(0x08);
    
    eink_send_cmd(BOOSTER_SOFT_START);
    eink_send_data(0xc7);     
    eink_send_data(0xcc);
    eink_send_data(0x28);

    eink_send_cmd(POWER_ON);
    eink_wait_until_idle();

    eink_send_cmd(PLL_CONTROL);
    eink_send_data(0x3c);        

    eink_send_cmd(TEMPERATURE_CALIBRATION);
    eink_send_data(0x00);

    eink_send_cmd(VCOM_AND_DATA_INTERVAL_SETTING);
    eink_send_data(0x77);

    eink_send_cmd(TCON_SETTING);
    eink_send_data(0x22);

    eink_send_cmd(TCON_RESOLUTION);
    eink_send_data(0x02);     //source 640
    eink_send_data(0x80);
    eink_send_data(0x01);     //gate 384
    eink_send_data(0x80);

    eink_send_cmd(VCM_DC_SETTING);
    eink_send_data(0x1E);      //decide by LUT file

    eink_send_cmd(0xe5);           //FLASH MODE            
    eink_send_data(0x03);  
}

void eink_display_frame(const unsigned char* frame_buffer) {
    unsigned char temp1, temp2;
    eink_send_cmd(DATA_START_TRANSMISSION_1);
    for(long i = 0; i < EPD_WIDTH / 8 * EPD_HEIGHT; i++) {   
        temp1 = frame_buffer[i];
        for(unsigned char j = 0; j < 8; j++) {
            if(temp1 & 0x80)
                temp2 = 0x03;
            else
                temp2 = 0x00;
            
            temp2 <<= 4;
            temp1 <<= 1;
            j++;
            if(temp1 & 0x80)
                temp2 |= 0x03;
            else
                temp2 |= 0x00;
            temp1 <<= 1;
            eink_send_data(temp2); 
        }
    }
    eink_send_cmd(DISPLAY_REFRESH);
    CyDelay(100);
    eink_wait_until_idle();
}

void eink_display_part(uint8_t *elem, uint32_t x_start, uint32_t y_start,
                       uint32_t elem_w, uint32_t elem_h) {
    eink_send_cmd(0x13);
    for (uint32_t j = 0; j < EPD_HEIGHT; j++) {
        for (uint32_t i = 0; i < EPD_WIDTH / 8; i++) {
            if ((j >= y_start) && (j < y_start + elem_h) &&
                (i * 8 >= x_start) && (i * 8 < x_start + elem_w)) {
                eink_send_data(
                    ~(elem[i - x_start / 8 + (elem_w) / 8 * (j - y_start)]));
            } else {
                eink_send_data(0x00);
            }
        }
    }
    eink_send_cmd(0x12);
    CyDelay(100);
    eink_wait_until_idle();
}

void eink_clear(void) {
    eink_send_cmd(0x13);
    for (uint32_t i = 0; i < EPD_HEIGHT * 6; i++) {
        eink_send_data(0xFF);
    }
    eink_send_cmd(0x12); // <-- eink not comming out of busy state
    CyDelay(200);
    eink_wait_until_idle();
}

void eink_clean(void) {
    eink_send_cmd(DATA_START_TRANSMISSION_1);
    for (long i = 0; i < EPD_WIDTH / 8 * EPD_HEIGHT; i++) { 
        for(unsigned char J = 0; J < 4; J++) { 
        eink_send_data(0x00); 
        }
    }
    eink_send_cmd(DISPLAY_REFRESH);
    CyDelay(100);
    eink_wait_until_idle();
}

int main(void) {
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory
     * layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);
    CyDelay(500); // Wait for 500 milliseconds

    EINK_SPI_Start();
    CyDelay(100);
    eink_init();
    CyDelay(1000);

    eink_display_frame(IMAGE_DATA);
    eink_sleep();

    for (;;) {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
