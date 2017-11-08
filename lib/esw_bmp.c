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
    //int imageIdx = 0;
    //unsigned char tempRGB;

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
printf("%d\n",sizeof(BITMAPINFOHEADER));
	printf("%lu\n",bitmapInfoHeader->biSizeImage);    
    lseek(fd_input, bitmapFileHeader->bfOffBits, SEEK_SET);
                        
                      
    bitmapImage = (unsigned char*)malloc(bitmapInfoHeader->biSizeImage);
    

    if (bitmapImage == NULL)    
    {
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

void WriteBitmapFile(char* filename, unsigned char* bitmapImage, BITMAPFILEHEADER *bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader) {

    int fd_output = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    
    write(fd_output, bitmapFileHeader, sizeof(BITMAPFILEHEADER));
    write(fd_output, bitmapInfoHeader, sizeof(BITMAPINFOHEADER));
    
    for (int i = 0; i < 256; i++) {
    
        RGBQUAD tempRGBQUAD;        
        tempRGBQUAD.rgbBLUE = tempRGBQUAD.rgbGreen = tempRGBQUAD.rgbRED = (BYTE)i;        
        tempRGBQUAD.rgbReserved = 0;        
	write(fd_output, &tempRGBQUAD, sizeof(RGBQUAD));
    }
    write(fd_output, bitmapImage, bitmapInfoHeader->biSizeImage);
    close(fd_output);
}

