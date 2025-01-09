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
#include "eink_GFX.h"

// Function to convert a 2D framebuffer to a 1D array
void convert2DTo1D2(uint8_t src[SCREEN_HEIGHT][BYTES_PER_ROW], uint8_t dest[SCREEN_HEIGHT * BYTES_PER_ROW]) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < BYTES_PER_ROW; x++) {
            dest[y * BYTES_PER_ROW + x] = src[y][x];
        }
    }
}

// Function to set a pixel (dot) in the frame buffer
void setPixel(int x, int y, bool color) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;

    if (color) {
        frameBuffer[y][x / 8] |= (1 << (7 - (x % 8))); // Set pixel to black
    } else {
        frameBuffer[y][x / 8] &= ~(1 << (7 - (x % 8))); // Set pixel to white
    }
}

// Function to draw a line using Bresenham's algorithm
void drawLine(int x0, int y0, int x1, int y1, bool color) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        setPixel(x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Function to draw a rectangle
void drawRect(int x, int y, int width, int height, bool color, bool fill) {
    
    y -= height; // set origin to lower left corner
    
    if (fill) {
        // Fill the rectangle
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                setPixel(x + j, y + i, color);
            }
        }
    } else {
        // Draw the outline
        drawLine(x, y, x + width - 1, y, color);          // Top side
        drawLine(x, y, x, y + height - 1, color);         // Left side
        drawLine(x, y + height - 1, x + width - 1, y + height - 1, color); // Bottom side
        drawLine(x + width - 1, y, x + width - 1, y + height - 1, color); // Right side
    }
}

// Function to clear the frame buffer
void clearFrameBuffer() {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < BYTES_PER_ROW; x++) {
            frameBuffer[y][x] = 0xFF; // Set all pixels to white
        }
    }
}

void insertImg(int x, int y, int w, int h, const uint8_t *img) {
    unsigned int counter = 0;
    int bytesPerRow = (w + 7) / 8; // Round up to the nearest byte
    for (int row = 0; row < h; row++) {
        for (int col = 0; col < w; col++) {
            int byteIndex = row * bytesPerRow + (col / 8);
            // Calculate the bit index within the current byte
            int bitIndex = 7 - (col % 8);
            if (counter > 7) { counter = 0; }
            // Check the bit corresponding to the current pixel
            if (img[byteIndex] & (1 << bitIndex)) {
                // Set the pixel in the framebuffer at the correct position
                setPixel(x + col, y + row, false); // Adjust for offsets
            }
            counter++;
        }
    }
}

// Function to draw a character 
void drawChar(int x, int y, char c, bool color, Font font) {
    int index = c - 0x20; // ASCII offset for space
    
    int bitmapOffset = font.glyphs[index][0]; // Get bitmap offset
    int width = font.glyphs[index][1]; // Get width
    int height = font.glyphs[index][2]; // Get height
    int xAdvance = font.glyphs[index][3]; // Get x advance
    int xOffset = font.glyphs[index][4]; // Get x offset
    int yOffset = font.glyphs[index][5]; // Get y offset

    // Iterate through each row and column of the character
    int num_bit = 0;
    int counter = 0;
    
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int byteIndex = bitmapOffset + (num_bit) / 8;
            num_bit++;
            // Check the bit corresponding to the current pixel
            if (font.bitmaps[byteIndex] & (0x80 >> (counter % 8))) {
                // Set the pixel in the framebuffer at the correct position
                int xPixel = x + col;
                int yPixel = y + row + yOffset;
                setPixel(xPixel, yPixel, color); // Adjust for offsets
            }
            counter++;
            if (counter > 7) { counter = 0; }
        }
    }
}

void drawString(int x, int y, const char *str, bool color, Font font) {
    while (*str) {
        char c = *str++;
        int index = c - 0x20; // ASCII offset for space
        
        int bitmapOffset = font.glyphs[index][0]; // Get bitmap offset
        int width = font.glyphs[index][1]; // Get width
        int height = font.glyphs[index][2]; // Get height
        int xAdvance = font.glyphs[index][3]; // Get x advance
        int xOffset = font.glyphs[index][4]; // Get x offset
        int yOffset = font.glyphs[index][5]; // Get y offset

        // Iterate through each row and column of the character
        int num_bit = 0;
        int counter = 0;
        
        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                int byteIndex = bitmapOffset + (num_bit) / 8;
                num_bit++;
                // Check the bit corresponding to the current pixel
                if (font.bitmaps[byteIndex] & (0x80 >> (counter % 8))) {
                    // Set the pixel in the framebuffer at the correct position
                    int xPixel = x + col + xOffset;
                    int yPixel = y + row + yOffset;
                    setPixel(xPixel, yPixel, color); // Adjust for offsets
                }
                counter++;
                if (counter > 7) { counter = 0; }
            }
        }
        // Move x position for the next character
        x += xAdvance; 
    }
}

void extractPartialUpdate(uint8_t src[SCREEN_HEIGHT][BYTES_PER_ROW], 
                          uint8_t dest[], 
                          uint32_t x_start, 
                          uint32_t y_start, 
                          uint32_t width, 
                          uint32_t height) {
    // Ensure the parameters are within bounds
    if (x_start + width > SCREEN_WIDTH || y_start + height > SCREEN_HEIGHT) {
        return; // Out of bounds
    }

    // Loop through the specified area and extract bits
    for (uint32_t y = 0; y < height; y++) {
        for (uint32_t x = 0; x < width; x++) {
            // Calculate the byte and bit position in the original frame buffer
            uint32_t byte_index = (y_start + y) * BYTES_PER_ROW + (x_start + x) / 8;
            uint32_t bit_index = (x_start + x) % 8;

            // Extract the specific bit and set it in the destination buffer
            if ((src[y_start + y][byte_index] >> (7 - bit_index)) & 0x01) {
                // Set bit to 0 (black) in dest
                dest[(y * width + x) / 8] |= (0x80 >> (x % 8));
            } else {
                // Set bit to 1 (white) in dest
                dest[(y * width + x) / 8] &= ~(0x80 >> (x % 8));
            }
        }
    }
}

/* [] END OF FILE */
