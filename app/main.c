#include<stdio.h>

#include"esw_bmp.h"

int main(int argc, char* argv[]){
 BITMAPFILEHEADER bitmapFileHeader;
 BITMAPINFOHEADER bitmapInfoHeader;
 unsigned char *bitmapData;

 bitmapData = LoadBitmapFile("cameraman.bmp", &bitmapFileHeader, &bitmapInfoHeader);
 printf("%lu", bitmapInfoHeader.biSizeImage);
 WriteBitmapFile("output.bmp", bitmapData, &bitmapFileHeader, &bitmapInfoHeader);
}


