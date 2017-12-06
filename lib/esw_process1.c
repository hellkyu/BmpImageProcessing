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

unsigned char** unsharpMasking(unsigned char** bmpdata, BITMAPINFOHEADER* bitmapInfoHeader){
    int width = bitmapInfoHeader->biWidth;
    int height = bitmapInfoHeader->biHeight;
    float alpha = 0.2;
    float** unsharped = (float**)malloc(sizeof(float*)*height);
    for(int y = 0; y < height; y++){
        unsharped[y] = (float*)malloc(sizeof(float)*width);
    }

    int dir1[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
    int dir2[4][2] = { {1,1}, {1,-1}, {-1,1}, {-1,-1} };

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            float filtered_sum = (float)bmpdata[y][x]*(alpha+5);
            for(int i = 0; i < 4; i++){
                int next_x = x + dir1[i][0];
                int next_y = y + dir1[i][1];
                if(next_x < 0 || next_x >= width || next_y < 0 || next_y >=height)
                    continue;
                filtered_sum += (float)bmpdata[next_y][next_x] * (alpha - 1);
            }
            for(int i = 0; i < 4 ;i++){
                int next_x = x + dir2[i][0];
                int next_y = y + dir2[i][1];     
                if(next_x < 0 || next_x >= width || next_y < 0 || next_y >=height)
                    continue;
                filtered_sum += (float)bmpdata[next_y][next_x] * (-alpha);           
            }
            filtered_sum = filtered_sum / (alpha+1);
            unsharped[y][x] = filtered_sum;
        }
    }

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            bmpdata[y][x] = (unsigned char)unsharped[y][x];
        }
    }
    return bmpdata;
}
