#ifndef __ESW_BMP_H__
#define __ESW_BMP_H__

typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned int   DWORD;
typedef int   	        LONG;

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER {
    WORD    bfType; //identify the BMP (BM)
    DWORD   bfSize; //size of the BMP file in bytes
    WORD    bfReserved1; //Reserved
    WORD    bfReserved2; //Reserved
    DWORD   bfOffBits; //starting address of the byte where the bitmap image data can be found
} BITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagBITMAPINFOHEADER {
    DWORD   biSize; //the size of this header
    LONG    biWidth; //the bitmap width in pixels
    LONG    biHeight; //the bitmap height in pixels
    WORD    biPlanes; //the number of color planes
    WORD    biBitCount; //the number of bits per pixel
    DWORD   biCompression; //the compression method being used
    DWORD   biSizeImage; //the image size
    LONG    biXPelsPerMeter; //the horizontal resolution of the image
    LONG    biYPelsPerMeter; //the vertical resolution of the image
    DWORD   biClrUsed; //the number of colors in the color palette
    DWORD   biClrImportant; //the number of important colors used
} BITMAPINFOHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagRGBQUAD {
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
    BYTE    rgbReserved;
} RGBQUAD;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagRGBPIXEL {
    BYTE    rgbBlue;
    BYTE    rgbGreen;
    BYTE    rgbRed;
} RGBPIXEL;
#pragma pack(pop)

unsigned char *LoadBitmapFile(char *filename, BITMAPFILEHEADER* bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader);

RGBPIXEL** pixelVecToArray(BITMAPINFOHEADER* bitmapInfoHeader, unsigned char* vecRGBPixels);

void WriteBitmapFile(char* filename, unsigned char* bitmapImage, BITMAPFILEHEADER* bitmapFileHeader, BITMAPINFOHEADER* bitmapInfoHeader);


#endif
