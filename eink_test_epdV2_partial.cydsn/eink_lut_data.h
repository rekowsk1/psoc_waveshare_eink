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

/* [] END OF FILE */
// eink_data.h
#ifndef EINK_LUT_DATA_H
    #define EINK_LUT_DATA_H
        
    #include "project.h"
        
    // experimental partial screen update LUTs with balanced charge
    // LUTs are filled with zeroes

    #define T1 30 // charge balance pre-phase
    #define T2  5 // optional extension
    #define T3 30 // color change phase (b/w)
    #define T4  5 // optional extension for one color

    extern unsigned char Voltage_Frame_7IN5_V2[];
    extern unsigned char Voltage_Frame_7IN5_V2[];
    extern unsigned char LUT_VCOM_7IN5_V2[];
    extern unsigned char LUT_WW_7IN5_V2[];
    extern unsigned char LUT_BW_7IN5_V2[];
    extern unsigned char LUT_WB_7IN5_V2[];
    extern unsigned char LUT_BB_7IN5_V2[];
    
    extern unsigned char lut_20_LUTC_partial[];
    extern unsigned char lut_21_LUTWW_partial[];
    extern unsigned char lut_22_LUTKW_partial[];
    extern unsigned char lut_23_LUTWK_partial[];
    extern unsigned char lut_24_LUTKK_partial[];
    extern unsigned char lut_25_LUTBD_partial[];
    

#endif // EINK_LUT_DATA_H