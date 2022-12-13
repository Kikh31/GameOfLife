#pragma once

#pragma pack(1)
typedef struct {
    unsigned char type[2];
    unsigned int size;
    unsigned char reserved1[2];
    unsigned char reserved2[2];
    unsigned int offsetBits;
} BMPheader;

typedef struct {
    unsigned int size;
    unsigned int width;
    unsigned int height;
    unsigned short planes;
    unsigned short bitCount;
    unsigned int compression;
    unsigned int sizeImage;
    unsigned int xPPM;
    unsigned int yPPM;
    unsigned int colorsUsed;
    unsigned int colorsImp;
} BMPinfo;
#pragma pop


typedef struct {
    BMPheader bmphd;
    BMPinfo bmpinf;
    unsigned char *data;
} BMPfile;

BMPfile* openBMP(char*);
void closeBMP(BMPfile*);
void printBMPinfo(BMPfile*);
int** getBitsMatrix(BMPfile*);