#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "init.h"
#include "esw_bmp.h"
#include "rgb2gray.h"
#include "esw_process1.h"
#include "esw_process2.h"

int main(int argc, char* argv[]){

 BITMAPFILEHEADER bitmapFileHeader;
 BITMAPINFOHEADER bitmapInfoHeader;
 unsigned char* bitmapRawData;
 RGBPIXEL** rgbPixelArray;
 unsigned char** bmpdata;
 void** outputData;

 if( argc != 2 && argc != 3)
 {
   fprintf(stderr,"COMMAND FORMAT\n $ exefile bmpfile option \
                  \nOPTION PAGE\n $ exefile --help\n");
   
   exit(0);
 }
 else
 { 
   if(!strcmp(argv[1],"--help")) // help
      init();
      
   else
   {
	   bitmapRawData = LoadBitmapFile(argv[1], &bitmapFileHeader, &bitmapInfoHeader);
	   rgbPixelArray = pixelVecToArray(&bitmapInfoHeader, bitmapRawData);
	   bmpdata = rgb2gray(rgbPixelArray,bitmapInfoHeader); // bitmap grayscale
	   
	   /* some processing */
	   if(argv[2][0]=='-')
	   {
		  switch(argv[2][1])
		  {
		     case 'b':  // bit plane
		          bmpdata = bitPlane(bmpdata,bitmapInfoHeader);
		          break;
		     case 'r':  // resolution 
		          bmpdata= resolution(bmpdata,bitmapInfoHeader);
		          break;     
		     case 'd':  // Dithering
		          bmpdata = dithering(bmpdata,bitmapInfoHeader);
		          break; 
		     case 'h':  // histogram
		          bmpdata = histogramEqualization(bmpdata, &bitmapInfoHeader);
		          break;
		     case 'q':  // quantization
		          bmpdata = quantization(bmpdata, &bitmapInfoHeader);
		          break;
		     case 'e':  // edge sharping
		         // num = 6;
		          break;
		     default:
		          //num = -1;
		          break;
		  }
	   }
	   else
		 printf("OPION FORMAT -opt \n");
	  
	   if(bitmapInfoHeader.biBitCount == 24){
		   outputData = (void**)gray2rgb(bmpdata, bitmapInfoHeader);
	   }
	   else
		   outputData = (void**)bmpdata;
	 
	   WriteBitmapFile("output.bmp", outputData, &bitmapFileHeader, &bitmapInfoHeader);
	   free(bitmapRawData);
	   free(rgbPixelArray);
	   free(bmpdata);
	 }
  }
}
