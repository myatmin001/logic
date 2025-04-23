#include <stdio.h>
#include <stdint.h>

#define BAND_COUNT 13
#define MAX_LEVEL 11  // bmp[0] to bmp[10]

// Struct definition
typedef struct {
    unsigned char Band[BAND_COUNT]; // Band values: 0 ~ 255
} BFG_DSP_SPN;

// Global variables
BFG_DSP_SPN spn;
uint16_t bmp[MAX_LEVEL];  // bmp array declaration without initialization

// Function prototypes
void initializeBFG_DSP_SPN(void);
void initializeBmp(void);  // Declare the initialization function for bmp
void renderBandsToBmp(void);
void printBmp(void);

int main() {
    // Initialize BFG_DSP_SPN data
    initializeBFG_DSP_SPN();

    // Initialize bmp array to zero
    initializeBmp();

    // Render the bands to the bmp array
    renderBandsToBmp();

    // Print the bmp array
    printBmp();

    return 0;
}

// Function to initialize BFG_DSP_SPN data
void initializeBFG_DSP_SPN(void) {
    spn = (BFG_DSP_SPN) {
        .Band = {0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 128, 64}
    };
}

// Function to initialize the bmp array
void initializeBmp(void) {
    for (int i = 0; i < MAX_LEVEL; i++) {
        bmp[i] = 0;  // Set each element of bmp to zero
    }
}

// Function to render the bands to the bmp array
void renderBandsToBmp(void) {
    for (int col = 0; col < BAND_COUNT; col++) {
        int level = (spn.Band[col] * MAX_LEVEL) / 256;

        // Rendering from bottom (bmp[10]) upward
        for (int row = MAX_LEVEL - 1; row >= MAX_LEVEL - 1 - level; row--) {
            bmp[row] |= (1 << (15 - col));
        }
    }
}

// Function to print the bmp array
void printBmp(void) {
    for (int row = 0; row < MAX_LEVEL; row++) {
        printf("bmp[%2d]: ", row);
        for (int col = 15; col >= (15 - (BAND_COUNT - 1)); col--) {
            printf((bmp[row] & (1 << col)) ? "█" : " ");
        }
        printf("\n");
    }
}
