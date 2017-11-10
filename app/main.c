#include<stdio.h>

#include"esw_bmp.h"
#include"rgb2gray.h"


int main(int argc, char* argv[]){
 BITMAPFILEHEADER bitmapFileHeader;
 BITMAPINFOHEADER bitmapInfoHeader;
 unsigned char *bitmapData;
 RGBPIXEL** rgbPixelArray;
 
 unsigned char **output;

 bitmapData = LoadBitmapFile("lenna.bmp", &bitmapFileHeader, &bitmapInfoHeader);
 printf("%d\n",bitmapInfoHeader.biBitCount);
 rgbPixelArray = pixelVecToArray(&bitmapInfoHeader, bitmapData);

 
 output = rgb2gray(rgbPixelArray,bitmapInfoHeader);

 for (int i = 0; i<bitmapInfoHeader.biHeight;i++)
   {
      for (int j = 0; j<bitmapInfoHeader.biWidth;j++)
      {
         printf("%d ",output[i][j]);
      }
      printf("\n");
   }
 WriteBitmapFile("output.bmp", bitmapData, &bitmapFileHeader, &bitmapInfoHeader);
}


