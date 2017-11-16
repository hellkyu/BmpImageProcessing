#include<stdio.h>
#include<stdlib.h>
#include "init.h"
#include "esw_bmp.h"
#include "rgb2gray.h"
#include "bit_plane.h"

int main(int argc, char* argv[]){

 BITMAPFILEHEADER bitmapFileHeader;
 BITMAPINFOHEADER bitmapInfoHeader;
 unsigned char* bitmapRawData;
 RGBPIXEL** rgbPixelArray;
 unsigned char** bmpdata;
 void** outputData;

 if(argc != 2)
 {
   fprintf(stderr,"COMMAND FORMAT\n $ exefile bmpfile\n");
   exit(0);
 }
 else
 { 
   bitmapRawData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
   rgbPixelArray = pixelVecToArray(&bitmapInfoHeader, bitmapRawData);
   bmpdata = rgb2gray(rgbPixelArray,bitmapInfoHeader); // bitmap grayscale

   init();

   char opt_n;
	
   printf(">> Enter the image processing option number : ");
   scanf("%c",&opt_n);
   //opt_n = getch();
   int n;
   /* some processing */
   switch(opt_n)
   {
      case 0x31:
           bmpdata = bitPlane(bmpdata,bitmapInfoHeader);
           break;
      case 0x32:
           printf("2\n");
           break;
      case 0x33:
           printf("3\n");
           break;
      case 0x34:
           printf("4\n");
           break;
      case 0x35:
           printf("5\n");
           break;
      case 'q':
	   printf("EXIT\n");
	   exit(0);
           break;
   }

 if(bitmapInfoHeader.biBitCount == 24){
   outputData = (void**)gray2rgb(bmpdata, bitmapInfoHeader);
 }
 else
   outputData = (void**)bmpdata;
 
   WriteBitmapFile("output.bmp", outputData, &bitmapFileHeader, &bitmapInfoHeader);
   printf("Success output.\n");


	}

}
