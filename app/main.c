#include<stdio.h>

#include <math.h>
#include"esw_bmp.h"
#include"rgb2gray.h"
#include "bit_plane.h"

int main(int argc, char* argv[]){

 BITMAPFILEHEADER bitmapFileHeader;
 BITMAPINFOHEADER bitmapInfoHeader;
 unsigned char* bitmapRawData;
 RGBPIXEL** rgbPixelArray;
 unsigned char** bmpdata; 
 void** outputData;

 if(argc != 2)   
	fprintf(stderr,"format : exefile bmpfile\n");

 bitmapRawData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
 rgbPixelArray = pixelVecToArray(&bitmapInfoHeader, bitmapRawData);

 bmpdata = rgb2gray(rgbPixelArray,bitmapInfoHeader);


 /* some processing */
 bmpdata = bitPlane(bmpdata,bitmapInfoHeader,5);
 /* some processing */


 if(bitmapInfoHeader.biBitCount == 24){
    outputData = (void**)gray2rgb(bmpdata, bitmapInfoHeader);
 }
 else
    outputData = (void**)bmpdata;

 WriteBitmapFile("output.bmp", outputData, &bitmapFileHeader, &bitmapInfoHeader);
 printf("Success output.\n");
}
