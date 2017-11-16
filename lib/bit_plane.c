#include <stdio.h>
#include <math.h>

#include "esw_bmp.h"
#include "bit_plane.h"

unsigned char **bitPlane(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader,int level)
{
  int HEIGHT = bitmapInfoHeader.biHeight;
  int WIDTH = bitmapInfoHeader.biWidth;
  double c;

  for (int i = 0; i<HEIGHT;i++)
  {
    for (int j = 0; j<WIDTH;j++)
    {
	
	c = ((int)output[i][j]/(int)pow(2,level))%2;
 	c = c*255;
	output[i][j]=c;
    }
  }

  return output;
}
