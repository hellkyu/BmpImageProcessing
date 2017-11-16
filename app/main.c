#include<stdio.h>

#include"esw_bmp.h"

int main(int argc, char* argv[]){
 BITMAPFILEHEADER bitmapFileHeader;
 BITMAPINFOHEADER bitmapInfoHeader;
 unsigned char *bitmapData;
 RGBPIXEL** rgbPixelArray;

 bitmapData = LoadBitmapFile("cameraman.bmp", &bitmapFileHeader, &bitmapInfoHeader);
 printf("%d\n",bitmapInfoHeader.biBitCount);
 rgbPixelArray = pixelVecToArray(&bitmapInfoHeader, bitmapData);

/*
 for(int i = 0; i <bitmapInfoHeader.biHeight;i++){
	for(int j = 0; j< bitmapInfoHeader.biWidth;j++){
		printf("%d ", (rgbPixelArray[i][j].rgbBlue+rgbPixelArray[i][j].rgbGreen+rgbPixelArray[i][j].rgbRed)/3);
	}
	printf("   %d\n\n\n\n",i);
}a*/


 

 WriteBitmapFile("output.bmp", bitmapData, &bitmapFileHeader, &bitmapInfoHeader);
}


