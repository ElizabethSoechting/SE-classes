#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "brighten.h"
//#include "brightc.c"


void main(int argc, char *argv[])
{
  char header[512];
  char File[20];
  int index = 1; //counter variable
  unsigned char img[640*480*3], newimg[640*480*3];
  int bufflen, hdrlen; unsigned row=0, col=0, chan=0, pix; int i, j, k;
  double alpha=1.25;  unsigned char beta=25;

  if(argc < 2)
  {
      printf("Use: brighten inputfile\n");
      exit(-1);
  }

  // TEST CASE #0
  //
  // Basic PPM file read, scaling and bias test, and write-back
  //
  header[0]='\0';
  readppm(img, &bufflen, header, &hdrlen, &row, &col, &chan, argv[1]);

for(alpha = 1.0; alpha <= 4.0; alpha++)
{
    for(beta = 0; beta <= 100; beta+=25)
    {
        brighten();
        scaleImage(img, newimg, row, col, chan, alpha, beta);
        // Change the file name each time
        sprintf(File, "brighter%d.ppm", index);
        writeppm(newimg, bufflen, header, hdrlen, File);
        
        index++;
    }
}

}

