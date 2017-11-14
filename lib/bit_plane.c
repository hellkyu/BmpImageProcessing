#include <stdio.h>
#include <math.h>

#include "esw_bmp.h"
#include "bit_plane.h"

RGBPIXEL **bitPlane(RGBPIXEL **output,BITMAPINFOHEADER bitmapInfoHeader,int level)
{
  int HEIGHT = bitmapInfoHeader.biHeight;
  int WIDTH = bitmapInfoHeader.biWidth;
double c;
  for (int i = 0; i<HEIGHT;i++)
  {
    for (int j = 0; j<WIDTH;j++)
    {
	output[i][j].rgbRed = (double)output[i][j].rgbRed;
	//c = (output[i][j].rgbRed/(int)pow(2,level))%2;
	c = (output[i][j].rgbRed/2*2)%2;
	output[i][j].rgbRed=c;
         output[i][j].rgbGreen=c;
         output[i][j].rgbBlue=c;
    }
  }

  return output;
}
