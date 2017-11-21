#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#include"esw_bmp.h"

unsigned char *LoadBitmapFile(char *filename, BITMAPFILEHEADER* bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader) {
    int fd_input;
    unsigned char *bitmapImage;

    fd_input = open(filename, O_RDONLY);
    if (fd_input == -1) {
	printf("there is no such file\n");
        return NULL;
    }
    read(fd_input, bitmapFileHeader, sizeof(BITMAPFILEHEADER));

    if (bitmapFileHeader->bfType != 0x4D42) {
        close(fd_input);
	printf("input file is not bmp format\n");
        return NULL;
    }

    read(fd_input, bitmapInfoHeader, sizeof(BITMAPINFOHEADER));  
    lseek(fd_input, bitmapFileHeader->bfOffBits, SEEK_SET);
                        
                      
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);
    
    if (bitmapImage == NULL){
        free(bitmapImage);
        close(fd_input);  
        printf("memory allocation failed\n");      
        return NULL;    
    }
     
    read(fd_input, bitmapImage, bitmapInfoHeader->biSizeImage);
    
    if (bitmapImage == NULL) {  
        free(bitmapImage);  
        close(fd_input);
        printf("failed to read pixels\n");
        return NULL;
    }

    close(fd_input); 
    return bitmapImage;
}


RGBPIXEL** pixelVecToArray(BITMAPINFOHEADER* bitmapInfoHeader, unsigned char* vecRGBPixels){
    int width = bitmapInfoHeader->biWidth;
    int height = bitmapInfoHeader->biHeight;
    int i;
    RGBPIXEL** rgbPixelArray = (RGBPIXEL**)malloc(sizeof(RGBPIXEL*)*height);
    for(i = 0; i < height; i++){
	rgbPixelArray[i] = (RGBPIXEL*)malloc(sizeof(RGBPIXEL)*width);
    }
    
    if(bitmapInfoHeader->biBitCount == 24){
    	for(i = 0; i < bitmapInfoHeader->biSizeImage; i += 3){
		RGBPIXEL tempPixel;
		tempPixel.rgbBlue = vecRGBPixels[i];
		tempPixel.rgbGreen = vecRGBPixels[i+1];
		tempPixel.rgbRed = vecRGBPixels[i+2]; 

		rgbPixelArray[(i/3)/width][(i/3)%width] = tempPixel;
        }
    }
    else{
        for(i = 0; i < bitmapInfoHeader->biSizeImage; i++){
            RGBPIXEL tempPixel;
            tempPixel.rgbBlue = tempPixel.rgbGreen = tempPixel.rgbRed = vecRGBPixels[i];
            rgbPixelArray[i/width][i%width] = tempPixel;
        }
    }
    return rgbPixelArray;
}


void WriteBitmapFile(char* filename, void** bmpdata, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader) {

    int fd_output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    
    write(fd_output, bitmapFileHeader, sizeof(BITMAPFILEHEADER));
    write(fd_output, bitmapInfoHeader, sizeof(BITMAPINFOHEADER));
    
    if(bitmapInfoHeader->biBitCount == 8){
        for (int i = 0; i < 256; i++) {
            RGBQUAD tempRGBQUAD;        
	        tempRGBQUAD.rgbBlue = tempRGBQUAD.rgbGreen = tempRGBQUAD.rgbRed = (BYTE)i;        
	        tempRGBQUAD.rgbReserved = 0;        
	        write(fd_output, &tempRGBQUAD, sizeof(RGBQUAD));
        }

        for(int i = 0; i < bitmapInfoHeader->biHeight; i++){
            write(fd_output, (unsigned char*)bmpdata[i], sizeof(unsigned char)*bitmapInfoHeader->biWidth);
        }
    }
    else{
        for(int i = 0; i < bitmapInfoHeader->biHeight; i++){
            write(fd_output, (RGBPIXEL*)bmpdata[i], sizeof(RGBPIXEL)*bitmapInfoHeader->biWidth);
        }
    }
    close(fd_output);
}
