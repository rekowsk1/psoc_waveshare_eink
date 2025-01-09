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
#ifndef EINK_GUI_H
    #define EINK_GUI_H
    
    #include "project.h"
    #include "eink_display.h"
    #include "eink_GFX.h"
    #include "eink_fonts.h"
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    
    void GUI_moveCursor(int8_t x, int8_t y);
    void GUI_TestSequence(void);
    
    extern u_int16_t x_test;
    
#endif
/* [] END OF FILE */
