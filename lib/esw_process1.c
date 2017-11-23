#include<stdio.h>
#include<stdlib.h>

#include"esw_bmp.h"
#include"esw_process1.h"

unsigned char** histogramEqualization(unsigned char** bmpdata, BITMAPINFOHEADER* bitmapInfoHeader){
    int histogram[256] = {0};
    int cumulative_histogram[256] = {0};
    float normalized_cumulative_histogram[256] = {0.0};
    int width = bitmapInfoHeader->biWidth;
    int height = bitmapInfoHeader->biHeight;
    int image_size = width * height;
    unsigned char** output;

    // calculate histogram
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            histogram[bmpdata[y][x]]++;
        }
    }

    // calculate cumulative histogram
    cumulative_histogram[0] = histogram[0];
    for(int i = 1; i<256; i++){
        cumulative_histogram[i] = cumulative_histogram[i-1] + histogram[i];
    }

    // normalize cumulative histogram
    for(int i = 0; i < 256; i++){
        normalized_cumulative_histogram[i] = cumulative_histogram[i] / (float)image_size;
    }

    output = (unsigned char**)malloc(sizeof(unsigned char*)*height);
    for(int y = 0; y < height; y++){
        output[y] = (unsigned char*)malloc(sizeof(unsigned char)*width);
    }

    // apply histogram equalization
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            output[y][x] = normalized_cumulative_histogram[bmpdata[y][x]] * 255;
        }
    }
    return output;
}

unsigned char** quantization(unsigned char** bmpdata, BITMAPINFOHEADER* bitmapInfoHeader){
    int width = bitmapInfoHeader->biWidth;
    int height = bitmapInfoHeader->biHeight;
    unsigned char level;
    printf(">> Enter the quantization level : ");
    scanf("%u", &level);

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            bmpdata[y][x] = (bmpdata[y][x] / level) * level;
        }
    }
    return bmpdata;
}
