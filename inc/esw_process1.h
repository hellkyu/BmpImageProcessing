#ifndef __ESW_PROCESS1_H__
#define __ESW_PROCESS1_H__

unsigned char** histogramEqualization(unsigned char** bmpdata, BITMAPINFOHEADER* bitmapInfoHeader);
unsigned char** quantization(unsigned char** bmpdata, BITMAPINFOHEADER* bitmapInfoHeader);
#endif
