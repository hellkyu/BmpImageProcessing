#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "esw_bmp.h"
#include "dithering.h"

unsigned char **dithering(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader)
{
  int HEIGHT = bitmapInfoHeader.biHeight;
  int WIDTH = bitmapInfoHeader.biWidth;
 
  char option[2];
  int size = 0;  

  printf(">> Enter the dithering option \n   $ d # d filter \n   $ d2 # d2 filter \n   $ f # Floyd-steinberg \n  : ");
  scanf("%s",option);

  int D[2][2] = {{0,128},{192,64}}; // filter D
  int D2[4][4] = {{0,128,32,160},{192,64,224,96}, \
                  {48,176,16,144},{240,112,208,80}}; // filter D2

  printf("%s filter\n",option);
  switch(option[0])
  {    
    case 0x64: // D or D2 filter
       if(option[1]-'0' == 2) // D2
          size = 4;
       else // D
          size = 2;
       break;
 
    case 0x66: // Floyd-steinberg
       
       break;
  }
  int R[128*size][128*size];

  for(int i = 0;i<size;i++)
  {   
     for(int j = 0;j<size;j++)
     {   
        for(int x = i;x<256;x =x+size)
        {
           for(int y = j;y<256;y = y+size)
           {
              // printf("x : %d ,y : %d, i: %d, j : %d\n",x,y,i,j); 
               if(size == 2) // D
                 R[x][y] = D[i][j];
               else 
                 R[x][y] = D2[i][j];
           }
        }
     }
  }

/*
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
*/

  int flag;
  for(int i = 0;i<256;i++)
  {   
     for(int j = 0;j<256;j++)
     {   
        output[i][j] = (output[i][j] > R[i][j]) ? 255:0;
     }
  }

  return output;
}
