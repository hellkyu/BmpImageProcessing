#include<stdio.h>

#include"esw_bmp.h"
#include"rgb2gray.h"
#include "bit_plane.h"

int main(int argc, char* argv[]){

 BITMAPFILEHEADER bitmapFileHeader;
 BITMAPINFOHEADER bitmapInfoHeader;
 unsigned char *bitmapData;
 RGBPIXEL** rgbPixelArray;
 RGBPIXEL **output;

 if(argc != 2)
 {
   fprintf(stderr,"format : exefile bmpfile\n");
 }

 bitmapData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
 printf("%d\n",bitmapInfoHeader.biBitCount);
 rgbPixelArray = pixelVecToArray(&bitmapInfoHeader, bitmapData);
 
for (int i = 0; i<bitmapInfoHeader.biHeight;i++)
   {
      for (int j = 0; j<bitmapInfoHeader.biWidth;j++)
      {
         printf("%d ",rgbPixelArray[i][j].rgbRed+rgbPixelArray[i][j].rgbGreen+rgbPixelArray[i][j].rgbBlue);
      }
      printf("\n");
   }
 

 if(bitmapInfoHeader.biBitCount == 24)
 {
	printf("rgb to grayscale..\n");
	output = rgb2gray(rgbPixelArray,bitmapInfoHeader);
 }

 output = bitPlane(output,bitmapInfoHeader,1);

 for (int i = 0; i<bitmapInfoHeader.biHeight;i++)
 {
    for (int j = 0; j<bitmapInfoHeader.biWidth;j++)
    {
      printf("%d ",output[i][j].rgbRed+output[i][j].rgbGreen+output[i][j].rgbBlue);
    }
     printf("\n");
 }

 WriteBitmapFile("output.bmp", bitmapData, &bitmapFileHeader, &bitmapInfoHeader);
}
