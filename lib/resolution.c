#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "esw_bmp.h"
#include "resolution.h"

unsigned char **resolution(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader)
{
  int HEIGHT = bitmapInfoHeader.biHeight;
  int WIDTH = bitmapInfoHeader.biWidth;
  int level;
 
  while(1)
  {
    printf("Select resolution reduction Level[1~9] : "); scanf("%d",&level);
    if (level >9 || level <1)
        printf("Range of level 1~9\n");
    else
    {
      level = level+1;
       printf("start resolution reduction .. \n");
      // resolution reduction
      for(int i = 0; i<HEIGHT;i= i+level)
      {
         for(int j = 0;j<WIDTH;j= j+level)
         {
   	    int temp = output[i][j];
            for(int x = i;x<i+level;x++)
            {
               if(x>=HEIGHT) break;
	       for(int y = j;y<j+level;y++)
               {
                  if(y>=WIDTH) break;
 	  	  output[x][y] = temp;
               }
            }
         }
      }
      break;
    }
    
    
  }
  
 	
  return output;
}
