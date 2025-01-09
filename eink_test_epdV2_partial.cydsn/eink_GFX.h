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

#ifndef EINK_GFX_H
    #define EINK_GFX_H

    #include "project.h"
    #include <stdlib.h>
    #include "eink_fonts.h"
    
    #define SCREEN_WIDTH 800
    #define SCREEN_HEIGHT 480
    #define BYTES_PER_ROW (SCREEN_WIDTH / 8)

    uint8_t frameBuffer[SCREEN_HEIGHT][BYTES_PER_ROW];
    
    typedef struct {
        const int (*glyphs)[6]; // Pointer to glyphs array
        const uint8_t *bitmaps;  // Pointer to bitmaps array
    } Font;
    
    void convert2DTo1D2(uint8_t src[SCREEN_HEIGHT][BYTES_PER_ROW], uint8_t dest[SCREEN_HEIGHT * BYTES_PER_ROW]);
    void setPixel(int x, int y, bool color);
    void drawLine(int x0, int y0, int x1, int y1, bool color);
    void drawRect(int x, int y, int width, int height, bool color, bool fill);
    void clearFrameBuffer();
    void drawChar(int x, int y, char c, bool color, Font font);
    void drawString(int x, int y, const char *str, bool color, Font font);
    void insertImg(int x, int y, int w, int h, const uint8_t *img);
    
    void extractPartialUpdate(uint8_t src[SCREEN_HEIGHT][BYTES_PER_ROW], 
                          uint8_t dest[], 
                          uint32_t x_start, 
                          uint32_t y_start, 
                          uint32_t width, 
                          uint32_t height);
    
#endif // EINK_GFX_H

/* [] END OF FILE */
