#include "BMPs.h"
#include "GoL.h"
#include <stdio.h>
#include <windows.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    BMPfile *bmp = openBMP(argv[1]);
    int** m = getBitsMatrix(bmp);

    while (0) {
        printGoL(bmp, m);
        usleep(10 * 1000);
        system("cls");

        int l = bmp->bmpinf.height + 2;
        int f = bmp->bmpinf.width + 2;
        int **nm = malloc(sizeof(int *) * l);
        for (int i = 0; i < l; i++) {
            nm[i] = malloc(sizeof(int) * f);
        }
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < f; j++) {
                nm[i][j] = 0;
            }
        }

        for (int i = 1; i <= bmp->bmpinf.height; i++) {
            for (int j = 1; j <= bmp->bmpinf.width; j++) {
                checkField(bmp, i, j, m, nm);
            }
        }

        for (int i = 0; i < l; i++) {
            for (int j = 0; j < f; j++) {
                m[i][j] = nm[i][j];
            }
        }

        printGoL(bmp, m);
        usleep(10 * 1000);
        system("cls");
    }
    printBMPinfo(bmp);
}
