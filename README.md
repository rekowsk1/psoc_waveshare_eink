# psoc_waveshare_eink
This PSoC workspace contains code examples demonstrating the basic functionalities of a 7.5" Waveshare E-Ink display using a CY8CPROTO-063-BLE developement board based on the CYBLE-416045-02 IC. 

This project utilizes the Waveshare 7.5-inch e-ink displays: V1 with a resolution of 640 × 384 and V2 with a resolution of 800 × 480. Both displays are black and white; however, only the V2 supports partial updates.

There are three projects in the psoc workspace. The first two projects are based on Waveshare's Arduino code examples. The third project leverages the GxEPD2 library and utilizes fonts from the Adafruit_GFX library to animate text moving from left to right using partial updates.
