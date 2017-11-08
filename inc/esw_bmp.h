#ifndef __ESW_BMP_H__
#define __ESW_BMP_H__

typedef unsigned char   BYTE;
typedef unsigned short  WORD;
typedef unsigned int   DWORD;
typedef int   	        LONG;

#pragma pack(push, 1)
typedef struct tagBITMAPFILEHEADER {
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagBITMAPINFOHEADER {
    DWORD   biSize;
    LONG    biWidth;
    LONG    biHeight;
    WORD    biPlanes;
    WORD    biBitCount;
    DWORD   biCompression;
    DWORD   biSizeImage;
    LONG    biXPelsPerMeter;
    LONG    biYPelsPerMeter;
    DWORD   biClrUsed;
    DWORD   biClrImportant;
} BITMAPINFOHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagRGBQUAD {
    BYTE    rgbBLUE;
    BYTE    rgbGreen;
    BYTE    rgbRED;
    BYTE    rgbReserved;
} RGBQUAD;
#pragma pack(pop)

unsigned char *LoadBitmapFile(char *filename, BITMAPFILEHEADER* bitmapFileHeader, BITMAPINFOHEADER *bitmapInfoHeader);
void WriteBitmapFile(char* filename, unsigned char* bitmapImage, BITMAPFILEHEADER* bitmapFileHeader, BITMAPINFOHEADER* bitmapInfoHeader);


#endif
