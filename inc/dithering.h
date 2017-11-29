#ifndef __DITHERING__
#define __DITHERING__

unsigned char **dithering(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader);
unsigned char **floyd(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader);
unsigned char **Dfilter(unsigned char **output, char opt[2]);

#endif
