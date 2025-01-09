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
 * Eink display: waveshare 7.5inch e-Paper V2 black/white 800 x 480
 * The code used in this project originates mostly from the GxEPD2 library (GxEPD2_750_GDEY075T7)
 *
 * ========================================
 */
#include "project.h"
#include <stdio.h>
#include "eink_display.h"
#include "eink_GFX.h"
#include "eink_fonts.h"
#include <stdlib.h>
#include "eink_GUI.h"

int main(void) {
    __enable_irq(); /* Enable global interrupts. */
    /* Enable CM4.  CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory
     * layout is changed. */
    Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);
    
    EINK_SPI_Start();
    eink_reset();
    
    CyDelay(500);
    GUI_TestSequence();
    
    for (;;) {
        GUI_TestSequence();
    }
}

/* [] END OF FILE */