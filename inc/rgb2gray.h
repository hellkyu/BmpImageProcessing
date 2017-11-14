#ifndef __RGB2GRAY__
#define __RGB2GRAY__


unsigned char **rgb2gray(RGBPIXEL **rgbPixelArray,BITMAPINFOHEADER bitmapInfoHeader);
RGBPIXEL **gray2rgb(unsigned char **rgbPixelArray,BITMAPINFOHEADER bitmapInfoHeader);

#endif
