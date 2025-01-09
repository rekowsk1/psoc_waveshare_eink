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
#include "eink_display.h"

bool powerIsOn = false;
bool usingPartialMode = false;
bool hibernating = false;
bool useFastFullUpdate = true; // set false for extended (low) temperature range
bool hasFastPartialUpdate = true; // set this false to force full refresh always
bool hasPartialUpdate = true;
bool initialWrite = true;
bool initialRefresh = true;
bool initDisplayDone = false;
bool usePartialUpdateWindow = false; // set false for better image

uint8_t frameBuffer[SCREEN_HEIGHT][BYTES_PER_ROW];

void eink_reset(void) {
    Cy_GPIO_Write(EINK_RST_PORT, EINK_RST_NUM, 1);
    CyDelay(10);
    Cy_GPIO_Write(EINK_RST_PORT, EINK_RST_NUM, 0);
    CyDelay(10);
    Cy_GPIO_Write(EINK_RST_PORT, EINK_RST_NUM, 1);
    CyDelay(10);
    
    hibernating = false;
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
    // only for single bytes. Do not use for large arrays. Use eink_send_dataArray
    Cy_GPIO_Write(EINK_DC_PORT, EINK_DC_NUM, 1);
    uint8_t txbuffer[1] = {data};
    uint8_t rxbuffer[1];
    volatile uint32_t res = EINK_SPI_Transfer(&txbuffer, &rxbuffer, 1);
    /* Blocking wait for transfer completion */
    while (0UL != (CY_SCB_SPI_TRANSFER_ACTIVE & EINK_SPI_GetTransferStatus())) {
        // wait
    }
}

void eink_send_dataArray(uint8_t src[][100], size_t row, size_t start_col, size_t length) {
    Cy_GPIO_Write(EINK_DC_PORT, EINK_DC_NUM, 1);

    // Send data from the specified row and starting column
    uint8_t rxbuffer[length];
    volatile uint32_t res = EINK_SPI_Transfer(&src[row][start_col], rxbuffer, length);
    
    /* Blocking wait for transfer completion */
    while (0UL != (CY_SCB_SPI_TRANSFER_ACTIVE & EINK_SPI_GetTransferStatus())) {
        // wait
    }
}

void eink_wait_until_idle(uint16_t busy_time) {
    CyDelay(1); // add some margin to become active
    uint16_t time_passed = 0;
    while (Cy_GPIO_Read(EINK_BUSY_PORT, EINK_BUSY_NUM) == 0) { //0: busy, 1: idle
        if (time_passed > BUSY_TIMEOUT) 
        {
            break;
            printf("...timeout!");
        }
        CyDelay(1);
        time_passed++;
    }
}

void eink_set_lut_by_host(uint8_t *lut_vcom, uint8_t *lut_ww, uint8_t *lut_bw,
                          uint8_t *lut_wb, uint8_t *lut_bb) {
    uint8_t count;
    eink_send_cmd(0x20); // VCOM
    for (count = 0; count < 42; count++)
        eink_send_data(lut_vcom[count]);

    eink_send_cmd(0x21); // LUTWW
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

void eink_set_partial_lut_by_host(uint8_t *lut_vcom, uint8_t *lut_ww, uint8_t *lut_bw,
                          uint8_t *lut_wb, uint8_t *lut_bb, uint8_t *lut_bd) {
    uint8_t count;
    eink_send_cmd(0x20); // VCOM LUTC
    for (count = 0; count < 42; count++) {
        if (count < 6) eink_send_data(lut_vcom[count]);
        else eink_send_data(0x00);
    }
    eink_send_cmd(0x21); // LUTWW LUTWW
    for (count = 0; count < 42; count++) {
        if (count < 6) eink_send_data(lut_ww[count]);
        else eink_send_data(0x00);
    }
    eink_send_cmd(0x22); // LUTBW LUTKW
    for (count = 0; count < 42; count++) {
        if (count < 6) eink_send_data(lut_bw[count]);
        else eink_send_data(0x00);
    }
    eink_send_cmd(0x23); // LUTWB LUTWK
    for (count = 0; count < 42; count++) {
        if (count < 6) eink_send_data(lut_wb[count]);
        else eink_send_data(0x00);
    }
    eink_send_cmd(0x24); // LUTBB LUTKK
    for (count = 0; count < 42; count++) {
        if (count < 6) eink_send_data(lut_bb[count]);
        else eink_send_data(0x00);
    }
    eink_send_cmd(0x25); // LUTBD
    for (count = 0; count < 42; count++) {
        if (count < 6) eink_send_data(lut_bd[count]);
        else eink_send_data(0x00);
    }
}
                        
void eink_hibernate(void) {
    eink_PowerOff();
    eink_send_cmd(DEEP_SLEEP);
    eink_send_data(0xa5);
    hibernating = true;
}

void eink_init(void) {
    if (hibernating) eink_reset();
    
    eink_send_cmd(PANEL_SETTING);      //PANNEL SETTING
    eink_send_data(0x1F);   //KW-3f   KWR-2F  BWROTP 0f BWOTP 1f
    
    eink_send_cmd(POWER_SETTING);  // power setting
    eink_send_data(0x07);
    eink_send_data(0x07); // VGH=20V,VGL=-20V
    eink_send_data(0x3f); // VSH=15V
    eink_send_data(0x3f); // VDL=-15V
    eink_send_data(0x09); // VDHR=4.2V
    
    eink_send_cmd(BOOSTER_SOFT_START);  // Booster Setting
    eink_send_data(0x17);
    eink_send_data(0x17);
    eink_send_data(0x28);
    eink_send_data(0x17);
    
    eink_send_cmd(TCON_RESOLUTION);  //tres
    eink_send_data(0x03);   //source 800
    eink_send_data(0x20);
    eink_send_data(0x01);   //gate 480
    eink_send_data(0xE0);
    
    eink_send_cmd(DUAL_SPI_MODE);
    eink_send_data(0x00);
    
    eink_send_cmd(VCOM_AND_DATA_INTERVAL_SETTING);      //VCOM AND DATA INTERVAL SETTING
    eink_send_data(0x29);
    eink_send_data(0x07);
    
    eink_send_cmd(TCON_SETTING);      //TCON SETTING
    eink_send_data(0x22);
    
    eink_send_cmd(PWS);      //TCON SETTING
    eink_send_data(0x22);
}

void eink_init_part(void) {
    eink_init();
    
    if (hasFastPartialUpdate)
    {
        eink_send_cmd(CASCADE_SETTING); // Cascade Setting (CCSET)
        eink_send_data(0x02);    // TSFIX
    
        eink_send_cmd(FORCE_TEMPERATURE); // Force Temperature (TSSET)
        eink_send_data(0x6E);    // 110
    }
    
    eink_PowerOn();
    usingPartialMode = true;
}

void eink_init_full() {
    eink_init();
    eink_send_cmd(PANEL_SETTING); // panel setting
    eink_send_data(0x1f);    // full update LUT from OTP
    eink_PowerOn();
    usingPartialMode = false;
}

void eink_PowerOn() {
    if (!powerIsOn)
    {
        eink_send_cmd(POWER_ON);
        eink_wait_until_idle(POWER_ON_TIME);
    }
    powerIsOn = true;
}

void eink_PowerOff() {
    eink_send_cmd(POWER_OFF);
    eink_wait_until_idle(POWER_OFF_TIME);
    powerIsOn = false;
    usingPartialMode = false;
}
                    
void convert2DTo1D(uint8_t src[SCREEN_HEIGHT][BYTES_PER_ROW], uint8_t dest[SCREEN_HEIGHT * BYTES_PER_ROW]) {
    // Function to convert a 2D framebuffer to a 1D array
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < BYTES_PER_ROW; x++) {
            dest[y * BYTES_PER_ROW + x] = src[y][x];
        }
    }
}

void convert2DTo1D_2(uint8_t **src, uint8_t *dest, int width, int height) {
    // Calculate the number of bytes per row based on width
    int bytes_per_row = (width + 7) / 8; // Round up to the nearest byte

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < bytes_per_row; x++) {
            dest[y * bytes_per_row + x] = src[y][x];
        }
    }
}

void SetPartialWindow(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
    uint16_t xe = (x + width - 1) | 0x0007; // byte boundary inclusive (last byte)
    uint16_t ye = y + height - 1;
    x &= 0xFFF8; // byte boundary
    
    // Send the command for partial window
    eink_send_cmd(PARTIAL_WINDOW); // Command for partial update 0x90

    // Set the coordinates and dimensions of the update area
    eink_send_data(x / 256);
    eink_send_data(x % 256);
    eink_send_data(xe / 256);
    eink_send_data(xe % 256);
    eink_send_data(y / 256);
    eink_send_data(y % 256);
    eink_send_data(ye / 256);
    eink_send_data(ye % 256);
    eink_send_data(0x01); // don't see any difference
    //eink_send_data(0x00); // don't see any difference
}
                    
void eink_clear(void) {
    eink_send_cmd(0x13);
    for(unsigned long i=0; i<EPD_HEIGHT*EPD_WIDTH/8; i++) {
        eink_send_data(0x00);
    }
    eink_send_cmd(0x12);
    eink_wait_until_idle(FULL_REFRESH_TIME);
}

void eink_writeScreenBuffer() {
    uint8_t value = 0xFF;
    uint8_t tempRowArray[1][100] = {0xFF};
    if (!usingPartialMode) eink_init_part();
    eink_send_cmd(0x13);
    for (uint32_t row = 0; row < 480; row++)
    {
        eink_send_dataArray(tempRowArray, 0, 0, 100);
    }
    
    for (int i = 0; i < 100; i++) tempRowArray[0][i] = 0x00; // clear temp array
    
    if (initialRefresh) {
        eink_send_cmd(0x10);
        for (uint32_t row = 0; row < 480; row++)
        {
            eink_send_dataArray(tempRowArray, 0, 0, 100);
        }
    }
    initialWrite = false; // initial full screen buffer clean done
}

void eink_setPartialRamArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    uint16_t xe = (x + w - 1) | 0x0007; // byte boundary inclusive (last byte)
    uint16_t ye = y + h - 1;
    x &= 0xFFF8; // byte boundary
    eink_send_cmd(0x90); // partial window
    eink_send_data(x / 256);
    eink_send_data(x % 256);
    eink_send_data(xe / 256);
    eink_send_data(xe % 256);
    eink_send_data(y / 256);
    eink_send_data(y % 256);
    eink_send_data(ye / 256);
    eink_send_data(ye % 256);
    eink_send_data(0x01);
}

void eink_refresh(int16_t x, int16_t y, int16_t w, int16_t h) {
    if (initialRefresh) {
        if (usingPartialMode) eink_init_full();
        eink_update_full();
        initialRefresh = false; // initial full update done
        return; // initial update needs be full update
    }
    // intersection with screen
    int16_t w1 = x < 0 ? w + x : w; // reduce
    int16_t h1 = y < 0 ? h + y : h; // reduce
    int16_t x1 = x < 0 ? 0 : x; // limit
    int16_t y1 = y < 0 ? 0 : y; // limit
    w1 = x1 + w1 < EPD_WIDTH ? w1 : EPD_WIDTH - x1; // limit
    h1 = y1 + h1 < EPD_HEIGHT ? h1 : EPD_HEIGHT - y1; // limit
    if ((w1 <= 0) || (h1 <= 0)) return;
    // make x1, w1 multiple of 8
    w1 += x1 % 8;
    if (w1 % 8 > 0) w1 += 8 - w1 % 8;
    x1 -= x1 % 8;
    if (!usingPartialMode) eink_init_part();
    if (usePartialUpdateWindow) eink_send_cmd(0x91); // partial in
    eink_setPartialRamArea(x1, y1, w1, h1);
    eink_update_part();
    if (usePartialUpdateWindow) eink_send_cmd(0x92); // partial out
}

void eink_writeImage(uint8_t data[][BYTES_PER_ROW], int16_t x_start, int16_t y_start, int16_t width, int16_t height) {
    if (initialWrite) eink_writeScreenBuffer(); // initial full screen buffer clean
    CyDelay(1); 
    uint16_t wb = (width + 7) / 8; // width bytes, bitmaps are padded
    x_start -= x_start % 8; // byte boundary
    width = wb * 8; // byte boundary
    int16_t x1 = x_start < 0 ? 0 : x_start; // limit
    int16_t y1 = y_start < 0 ? 0 : y_start; // limit
    int16_t w1 = x_start + width < EPD_WIDTH ? width : EPD_WIDTH - x_start; // limit
    int16_t h1 = y_start + height < EPD_HEIGHT ? height : EPD_HEIGHT - y_start; // limit
    int16_t dx = x1 - x_start;
    int16_t dy = y1 - y_start;
    w1 -= dx;
    h1 -= dy;
    if ((w1 <= 0) || (h1 <= 0)) return;
    if (!usingPartialMode) eink_init_part();
    eink_send_cmd(0x91); // partial in
    eink_setPartialRamArea(x1, y1, w1, h1);
    eink_send_cmd(0x13);
    for (size_t row = 0; row < 480; row++) {
        eink_send_dataArray(data, row, 0, 100);  // Send one entire row at a time
    }
  eink_send_cmd(0x92); // partial out
  CyDelay(1); // yield() to avoid WDT on ESP8266 and ESP32
}

void eink_update_full() {
    if (useFastFullUpdate)
    {
        eink_send_cmd(CASCADE_SETTING); // Cascade Setting (CCSET)
        eink_send_data(0x02);    // TSFIX
        eink_send_cmd(FORCE_TEMPERATURE); // Force Temperature (TSSET)
        eink_send_data(0x5A);    // 90
    }
    else
    {
        eink_send_cmd(CASCADE_SETTING); // Cascade Setting (CCSET)
        eink_send_data(0x00);    // no TSFIX, Temperature value is defined by internal temperature sensor
        eink_send_cmd(TEMPERATURE_CALIBRATION); // TSE, Enable Temperature Sensor
        eink_send_data(0x00);    // TSE, Internal temperature sensor switch
    }
    eink_send_cmd(DISPLAY_REFRESH); //display refresh
    eink_wait_until_idle(FULL_REFRESH_TIME);
}

void eink_update_part() {
    eink_send_cmd(DISPLAY_REFRESH); //display refresh
    eink_wait_until_idle(PARTIAL_REFRESH_TIME);
}

/* [] END OF FILE */
