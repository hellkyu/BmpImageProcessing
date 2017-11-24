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

  int option=2;
  scanf("%d",&option);
  
  switch(option)
  {
    case 1: // D filter
       option = 2;
       break;
 
    case 2: // D2 filter
       option = 4;
       break;
    
  }
  int R[128*2][128*2];

  for(int i = 0;i<2;i++)
  {   
     for(int j = 0;j<2;j++)
     {   
        for(int x = i;x<256;x =x+2)
        {
           for(int y = j;y<256;y = y+2)
           {
              // printf("x : %d ,y : %d, i: %d, j : %d\n",x,y,i,j); 
               if(option == 2)
                 R[x][y] = D[i][j];
               else 
                 R[x][y] = D2[i][j];
           }
        }
     }
  }

  for(int i = 0;i<2*4;i++)
  {   
     for(int j = 0;j<2*4;j++)
     {   
        printf("%d ",R[i][j]);
     }
     printf("\n");
  }
  printf("\n\n");
  for(int i = 0;i<2*4;i++)
  {   
     for(int j = 0;j<2*4;j++)
     {   
        printf("%d ",output[i][j]);
     }
     printf("\n");
  }
  printf("\n\n");

  int flag;
  for(int i = 0;i<256;i++)
  {   
     for(int j = 0;j<256;j++)
     {   
        output[i][j] = (output[i][j] > R[i][j]) ? 255:0;
        printf("%d ",output[i][j]);
       
     }
     printf("\n");
  }
  

  
  return output;
}
