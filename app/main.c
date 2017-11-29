#include<stdio.h>
#include<stdlib.h>

#include "init.h"
#include "esw_bmp.h"
#include "rgb2gray.h"
#include "bit_plane.h"
#include "esw_process1.h"
#include "resolution.h"
#include "dithering.h"

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
   opt_n = getchar();
    //printf("%c\n",opt_n[1]);

   /* some processing */
   switch(opt_n)
   {
      case 0x31: // bit plane
           bmpdata = bitPlane(bmpdata,bitmapInfoHeader);
           break;
      case 0x32: // resolution 
          bmpdata= resolution(bmpdata,bitmapInfoHeader);
           break;
      case 0x33: // Dithering
           bmpdata = dithering(bmpdata,bitmapInfoHeader);
           break;
      case 0x34: // histogram
	   bmpdata = histogramEqualization(bmpdata, &bitmapInfoHeader);
           break;
      case 0x35: // quantization
           bmpdata = quantization(bmpdata, &bitmapInfoHeader);
           break;
      case 0x36: // edge sharping
           
           break;
      case 'q':
	   printf("EXIT\n");
	   exit(0);
           break;
      default:
           printf("Error Option Number 1~6\n");
           break;
 }
   if(bitmapInfoHeader.biBitCount == 24){
       outputData = (void**)gray2rgb(bmpdata, bitmapInfoHeader);
   }
   else
       outputData = (void**)bmpdata;
 
   WriteBitmapFile("output.bmp", outputData, &bitmapFileHeader, &bitmapInfoHeader);
   //free(bitmapRawData);
   //free(rgbPixelArray);
   //free(bmpdata);
 }
}
