#ifndef BRIGHTEN_H
#define BRIGHTEN_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SAT (255)

void readppm(unsigned char *buffer, int *bufferlen, 
             char *header, int *headerlen,
             unsigned *rows, unsigned *cols, unsigned *chans,
             char *file);

void writeppm(unsigned char *buffer, int bufferlen,
              char *header, int headerlen,
              char *file);

void scaleImage(unsigned char *img, unsigned char *newimg, unsigned row, unsigned col, unsigned chan, double alpha, double beta);

#endif
