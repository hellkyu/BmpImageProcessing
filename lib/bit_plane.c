#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "esw_bmp.h"
#include "bit_plane.h"

unsigned char **bitPlane(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader)
{
  int HEIGHT = bitmapInfoHeader.biHeight;
  int WIDTH = bitmapInfoHeader.biWidth;
  double c;
  int level;
  
  while(1)
  {
    printf("Select bit plane Level[0~7] : "); scanf("%d",&level);

    if (level >7 || level <-1)
       printf("Range of level 0~7\n");
    else
    {
      printf("start bitplane .. \n");
      for (int i = 0; i<HEIGHT;i++)
      {
        for (int j = 0; j<WIDTH;j++)
        {
          c = ((int)output[i][j]/(int)pow(2,level))%2;
 	  c = c*255;
	  output[i][j]=c;
        }
      }
      break;
    }   
  }

   
  

 
  return output;
}
