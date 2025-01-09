/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef EINK_DISPLAY_H
    #define EINK_DISPLAY_H

    #include "project.h"
    #include "eink_lut_data.h"
    #include <stdlib.h>
    #include <stdio.h>

    // Display resolution
    #define EPD_WIDTH       800
    #define EPD_HEIGHT      480
    #define SCREEN_WIDTH 800
    #define SCREEN_HEIGHT 480
    #define BYTES_PER_ROW (SCREEN_WIDTH / 8)
    #define POWER_ON_TIME 140 // ms, e.g. 129018us
    #define POWER_OFF_TIME 42 // ms, e.g. 40430us
    #define FULL_REFRESH_TIME 1200 // ms, e.g. 1171000us
    #define PARTIAL_REFRESH_TIME 450 // ms, e.g. 435000us
    #define BUSY_TIMEOUT 3000 // ms
    #define DEBUGG

    // Command and setting definitions
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
    #define DUAL_SPI_MODE                               0x15
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
    #define PARTIAL_WINDOW                              0x90
    #define PARTIAL_IN                                  0x91
    #define PARTIAL_OUT                                 0x92
    #define CASCADE_SETTING                             0xE0
    #define PWS                                         0xE3
    #define FORCE_TEMPERATURE                           0xE5
        
    extern bool powerIsOn;
    extern bool usingPartialMode;
    extern bool hibernating;
    extern bool hasPartialUpdate;
    extern bool hasFastPartialUpdate; // set this false to force full refresh always
    extern bool useFastFullUpdate; // set false for extended (low) temperature range
    extern bool usePartialUpdateWindow; // set false for better image
    extern bool useFastPartialUpdateFromOTP; // set this false for earlier batches, such as the panel I have (1580258us)
    
    extern bool initialWrite;
    extern bool initialRefresh;
    extern bool initDisplayDone;
    
    // Function declarations
    void eink_reset(void);
    void eink_send_cmd(uint8_t command);
    void eink_send_data(uint8_t data);
    void eink_send_data2(uint8_t data, bool debugg);
    void eink_send_dataArray(uint8_t src[][100], size_t row, size_t start_col, size_t length);
    void eink_wait_until_idle(uint16_t busy_time);
    void eink_set_lut_by_host(uint8_t *lut_vcom, uint8_t *lut_ww, uint8_t *lut_bw,
                              uint8_t *lut_wb, uint8_t *lut_bb);
    void eink_set_partial_lut_by_host(uint8_t *lut_vcom, uint8_t *lut_ww, uint8_t *lut_bw,
                              uint8_t *lut_wb, uint8_t *lut_bb, uint8_t *lut_bd);
    void eink_hibernate(void);
    void eink_init(void);
    void eink_init_full();

    void SetPartialWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
    void eink_clear(void);
    void convert2DTo1D_2(uint8_t **src, uint8_t *dest, int width, int height);
    void eink_init_part(void);
    void eink_PowerOn();
    void eink_PowerOff();
    void eink_update_full();
    void eink_update_part();
    void eink_writeScreenBuffer();
    void eink_writeImage(uint8_t data[][BYTES_PER_ROW], int16_t x_start, int16_t y_start, int16_t width, int16_t height);
    void eink_setPartialRamArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h);
    void eink_refresh(int16_t x, int16_t y, int16_t w, int16_t h);

#endif // EINK_DISPLAY_H

/* [] END OF FILE */
