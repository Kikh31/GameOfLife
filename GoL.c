#include "GoL.h"

#include <stdio.h>
#include <stdlib.h>

void checkField(BMPfile *bmp, int x, int y, int **m, int **nm) {
    int lifeC = 0;
    for (int i = x - 1; i < x + 2; i++) {
        for (int j = y - 1; j < y + 2; j++) {
            lifeC += m[i][j];
        }
    }
    lifeC -= m[x][y];

    if (lifeC == 3 && m[x][y] == 0) nm[x][y] = 1;
    if ((lifeC < 2 || lifeC > 3) && m[x][y] == 1) nm[x][y] = 0;
    if((lifeC == 2 || lifeC == 3) && m[x][y] == 1)nm[x][y] = 1;
}

void printGoL(BMPfile *bmp, int **m) {
    for (int i = 1; i <= bmp->bmpinf.height; i++) {
        for (int j = 1; j <= bmp->bmpinf.width; j++) {
            if (m[i][j] == 1) printf("@");
            else printf(" ");
        }
        puts("\n");
    }
}


