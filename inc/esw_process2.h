#ifndef __ESW_PROCESS2_H__
#define __ESW_PROCESS2_H__

unsigned char **bitPlane(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader);

unsigned char **dithering(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader);
unsigned char **floyd(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader);
unsigned char **Dfilter(unsigned char **output, char opt[2]);

unsigned char **resolution(unsigned char **output,BITMAPINFOHEADER bitmapInfoHeader);
#endif
