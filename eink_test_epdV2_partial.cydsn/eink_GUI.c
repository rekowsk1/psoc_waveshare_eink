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
#include "eink_GUI.h"

// Create a font instance
Font FreeMono12pt7b = {FreeMono12pt7bGlyphs, FreeMono12pt7bBitmaps};
Font FreeMono18pt7b = {FreeMono18pt7bGlyphs, FreeMono18pt7bBitmaps};
Font FreeMonoBold12pt7b = {FreeMonoBold12pt7bGlyphs, FreeMonoBold12pt7bBitmaps};
Font FreeMonoBold18pt7b = {FreeMonoBold18pt7bGlyphs, FreeMonoBold18pt7bBitmaps};

u_int16_t x_test = 0;

void GUI_TestSequence() {
    clearFrameBuffer(); // Clear the frame buffer
    drawString(x_test, 200, "Test", false, FreeMonoBold18pt7b); // false for drawing in black
    
    x_test += 20;
    if (x_test+40 > EPD_WIDTH) x_test = 0;
    
    eink_writeImage(frameBuffer, 0, 0, 800, 480);
    eink_refresh(0, 0, 800, 480);
}


/* [] END OF FILE */
