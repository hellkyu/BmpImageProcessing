#include<stdio.h>
#include<stdlib.h>

#include "esw_bmp.h"

// 0.299*R + 0.587*G + 0.114*B
// 24bit -> color 8-> gray


// RGB to GRAY 
unsigned char **rgb2gray(RGBPIXEL **rgbPixelArray,BITMAPINFOHEADER bitmapInfoHeader)
{
   int HEIGHT = bitmapInfoHeader.biHeight;
   int WIDTH = bitmapInfoHeader.biWidth;
   unsigned char grayscale = 0;   
 
   unsigned char **output = ( unsigned char **)malloc(sizeof( unsigned char *)*HEIGHT);
 
   for (int i = 0; i<HEIGHT;i++)
   {
	   output[i] = (unsigned char *)malloc(sizeof(unsigned char)*WIDTH);
   }

   if(bitmapInfoHeader.biBitCount == 24)
   {
        printf("rgb to grayscale..\n");
        for (int i = 0; i<HEIGHT;i++)   
        {
	   for (int j = 0; j<WIDTH;j++)
	   {
		 grayscale = 0.299*rgbPixelArray[i][j].rgbRed + 
			     0.587*rgbPixelArray[i][j].rgbGreen +
			     0.114*rgbPixelArray[i][j].rgbBlue;

		 output[i][j] = grayscale;
	   }
        }
   }
   else
   {
        for (int i = 0; i<HEIGHT;i++)   
        {
	   for (int j = 0; j<WIDTH;j++)
	   {
		 grayscale = rgbPixelArray[i][j].rgbRed;
		 output[i][j] = grayscale;
	   }
        }
   }  

  
 
   return output;
}

// GRAY original
RGBPIXEL **gray2rgb(unsigned char **rgbPixelArray,BITMAPINFOHEADER bitmapInfoHeader)
{
   int HEIGHT = bitmapInfoHeader.biHeight;
   int WIDTH = bitmapInfoHeader.biWidth;
   unsigned char grayscale = 0;   
 
   RGBPIXEL **output = (RGBPIXEL **)malloc(sizeof(RGBPIXEL *)*HEIGHT);
 
   for (int i = 0; i<HEIGHT;i++)
   {
	   output[i] = (RGBPIXEL *)malloc(sizeof(RGBPIXEL)*WIDTH);
   }


   for (int i = 0; i<HEIGHT;i++)   
   {
	  for (int j = 0; j<WIDTH;j++)
	  {
		 grayscale = rgbPixelArray[i][j];
		 output[i][j].rgbRed = output[i][j].rgbGreen = output[i][j].rgbBlue = grayscale;
	  }
   }
 
   return output;
}

