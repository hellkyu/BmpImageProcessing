#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "esw_bmp.h"
#include "dithering.h"

unsigned char **dithering(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader)
{
  int HEIGHT = bitmapInfoHeader.biHeight;
  int WIDTH = bitmapInfoHeader.biWidth;

  int D[2][2] = {{0,128},{192,64}}; // filter D
  int D2[4][4] = {{0,128,32,160},{192,64,224,96},{48,176,16,144},{240,112,208,80}}; // filter D2

  int R[4][4]={0};

  for(int i = 0;i<2;i++)
  {   
     for(int j = 0;j<2;j++)
     {   
        for(int x = i;x<i+2+1;x =x+2)
        {
           for(int y = j;y<j+2+1;y = y+2)
           {
              // printf("x : %d ,y : %d, i: %d, j : %d\n",x,y,i,j); 
               R[x][y] = D[i][j];
           }
        }
     }
  }

  for(int i = 0;i<4;i++)
  {   
     for(int j = 0;j<4;j++)
     {   
        printf("%d ",R[i][j]);
     }
     printf("\n");
  }
  printf("\n\n");
  for(int i = 0;i<4;i++)
  {   
     for(int j = 0;j<4;j++)
     {   
        printf("%d ",output[i][j]);
     }
     printf("\n");
  }
  printf("\n\n");
  for(int i = 0;i<4;i++)
  {   
     for(int j = 0;j<4;j++)
     {   
        if(ouput[i][j] > R[i][j])
           printf("1");
        
     }
     printf("\n");
  }
  

  
  return 0;
}
