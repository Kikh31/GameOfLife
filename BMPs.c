#include "BMPs.h"
#include <stdio.h>
#include <stdlib.h>


BMPfile *openBMP(char *file) {
    FILE *f = fopen(file, "r");
    BMPfile *bmp = (BMPfile *) malloc(sizeof(BMPfile));
    fread(&bmp->bmphd, sizeof(BMPheader), 1, f);
    fread(&bmp->bmpinf, sizeof(BMPinfo), 1, f);
    bmp->data = (unsigned char *) malloc(bmp->bmpinf.sizeImage);
    fseek(f, bmp->bmphd.offsetBits, SEEK_SET);
    fread(bmp->data, bmp->bmpinf.sizeImage, 1, f);

    fclose(f);

    return bmp;
}

void closeBMP(BMPfile *bmp) {
    free(bmp);
}

void printBMPinfo(BMPfile *bmp) {
    printf("type[2]=%c%c\nsize=%d\noffsetBits=%d\n",
           bmp->bmphd.type[0], bmp->bmphd.type[1],
           bmp->bmphd.size,
           bmp->bmphd.offsetBits);

    printf("size=%d\nwidth=%d\nheight=%d\nplanes=%d\nbitCount=%d\ncompression=%d\nsizeImage=%d\nxPPM=%d\nyPPM=%d\ncolorsUsed=%d\ncolorsImp=%d\n",
           bmp->bmpinf.size,
           bmp->bmpinf.width,
           bmp->bmpinf.height,
           bmp->bmpinf.planes,
           bmp->bmpinf.bitCount,
           bmp->bmpinf.compression,
           bmp->bmpinf.sizeImage,
           bmp->bmpinf.xPPM,
           bmp->bmpinf.yPPM,
           bmp->bmpinf.colorsUsed,
           bmp->bmpinf.colorsImp);
}

int **getBitsMatrix(BMPfile *bmp) {
    int sBytes = 0;
    int byteCount = bmp->bmpinf.bitCount / 8;
    int rowBytes = bmp->bmpinf.width * byteCount;
    int padBytes = (4 - (rowBytes % 4)) % 4;

    int a = bmp->bmpinf.height + 2;
    int b = bmp->bmpinf.width + 2;
    int **m = malloc(sizeof(int *) * a);
    for (int i = 0; i < a; i++) {
        m[i] = malloc(sizeof(int) * b);
    }
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            m[i][j] = 0;
        }
    }

    int arrBytes[bmp->bmpinf.height * bmp->bmpinf.width];
    int j = 0;

    for (int i = 0; i < bmp->bmpinf.sizeImage - padBytes; i += byteCount) {
        if (sBytes == bmp->bmpinf.width) {
            i += padBytes;
            sBytes = 0;
        }

        if (bmp->data[i] == 0xff) arrBytes[j] = 0;
        else arrBytes[j] = 1;
        j++;

        sBytes++;
    }

    j = 0;
    for (int mi = a-2; mi >= 1; mi--) {
        for (int mj = 1; mj < b-1; mj++) {
            m[mi][mj] = arrBytes[j];
            j++;
        }
    }
    return m;
}
