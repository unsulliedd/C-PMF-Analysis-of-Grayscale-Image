/* PMF Analysis of Grayscale Image */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#pragma pack(push, 1)                       // Alignment

typedef struct {    // BMP HEADER 
    char            bfType[2];              // BM
    unsigned int    bfSize;                 // File Size
    unsigned short  reserved1;              // 0
    unsigned short  reserved2;              // 0
    unsigned int    bfOffBits;              // Offset of Pixel data
} BMP_HEADER;

typedef struct {    // BMP INFO HEADER
    unsigned int    size;                   // Info Header (40bayt)
    int             width;                  // Horizontal Pixel
    int             height;                 // Vertical Pixel
    unsigned short  planes;                 // 1
    unsigned short  bitsPerPixel;           // Bits per Pixel
    unsigned int    compression;            // 0
    unsigned int    imageSize;              // 0
    int             xPixelsPerMeter;        //
    int             yPixelsPerMeter;        // 
    unsigned int    colorsUsed;             // 0
    unsigned int    colorsImportant;        // 0
} BMP_INFO_HEADER;

#pragma pack(pop)                           // Clear Alignment

int main() {

    char bmp_file_name[10];

    printf("\nPlease Enter Name of the Bitmap File. \n(test.bmp etc...)\n\n");
    scanf("%[^\n]%*c", bmp_file_name);

    FILE* fp_image, * fp_hist, * fp_pmf, * fp_norm;
    fp_image = fopen(bmp_file_name, "rb");

    if (fp_image == NULL) {
        printf("File not found\n");
        return 1;
    }

    BMP_HEADER header;
    BMP_INFO_HEADER infoHeader;

    fread(&header, sizeof(BMP_HEADER), 1, fp_image);
    fread(&infoHeader, sizeof(BMP_INFO_HEADER), 1, fp_image);

    // Print the header information
    printf("\nType: %c%c\n", header.bfType[0], header.bfType[1]);
    printf("File size: %u\n", header.bfSize);
    printf("Offset: %u\n", header.bfOffBits);
    printf("Width: %d\n", infoHeader.width);
    printf("Height: %d\n", infoHeader.height);
    printf("Bits per pixel: %d\n", infoHeader.bitsPerPixel);
    printf("X pixels per meter: %d\n", infoHeader.xPixelsPerMeter);
    printf("Y pixels per meter: %d\n", infoHeader.yPixelsPerMeter);
    printf("Colors used: %u\n", infoHeader.colorsUsed);
    printf("Colors important: %u\n\n\n", infoHeader.colorsImportant);

    // Move the file pointer to the pixel data
    fseek(fp_image, header.bfOffBits, SEEK_SET);

    // Read the pixel data
    int rowSize = (int)ceil((double)infoHeader.bitsPerPixel * infoHeader.width / 32) * 4; // row size is padded to a multiple of 4 bytes
    unsigned char* pixelData = (unsigned char*)malloc(rowSize * infoHeader.height);
    fread(pixelData, rowSize * infoHeader.height, 1, fp_image);
    fclose(fp_image);

    int total_pixel = (infoHeader.width * infoHeader.height);
    int histogram[256] = { 0 };
    double mean = 0, sum = 0;
    double std_dev = 0, variance = 0;

    // Histogram
    for (int i = 0; i < total_pixel; i++) {
        histogram[pixelData[i]]++;
    }

    // Mean 
    for (int i = 0; i < 256; i++) {
        sum += i * histogram[i];
    }
    mean = sum / total_pixel;

    // Standard Deviation
    for (int i = 0; i < 256; i++) {
        variance += pow((double)i - mean, 2) * histogram[i];
    }
    variance /= total_pixel;
    std_dev = sqrt(variance);

    // PMF
    double pmf[256] = { 0 };
    for (int i = 0; i < 256; i++) {
        pmf[i] = (double)histogram[i] / total_pixel;
    }

    // Normal
    double normal[256] = { 0 };
    for (int i = 0; i < 256; i++) {
        normal[i] = exp(-(i - mean) * (i - mean) / (2.0 * variance)) / (std_dev * sqrt(2.0 * 3.14));
    }

    // Write histogram values to file
    fp_hist = fopen("histogram.txt", "w");
    for (int i = 0; i < 256; i++) {
        fprintf(fp_hist, "%d %d\n", i, histogram[i]);
    }
    fclose(fp_hist);

    // Write the PMF values to a file
    fp_pmf = fopen("pmf.txt", "w");
    for (int i = 0; i < 256; i++) {
        fprintf(fp_pmf, "%d %lf\n", i, pmf[i]);
    }
    fclose(fp_pmf);

    // Write the Normal Distruption values to a file
    fp_norm = fopen("normal.txt", "w");
    for (int i = 0; i < 256; i++) {
        fprintf(fp_norm, "%d %f\n", i, normal[i]);
    }
    fclose(fp_norm);

    // Print statistics
    printf("Mean: %f\n", mean);
    printf("Variance: %f\n", variance);
    printf("Standard Deviation: %f\n", std_dev);
    printf("Total Pixel: %d\n", total_pixel);

    // Free the pixel data memory
    free(pixelData);

    return 0;
}