#define PIXIDX ((i*col*chan)+(j*chan)+k)
#define SAT (255)

int pix, i, j, k, row=480, col=640, chan=3;
unsigned char img[640*480*3], newimg[640*480*3];
double alpha=1.25;  unsigned char beta=25;


int brighten(void)
{

    for(i=0; i < row; i++)
      for(j=0; j < col; j++)
        for(k=0; k < chan; k++)
        {
            newimg[PIXIDX] = (pix=(unsigned)((img[PIXIDX])*alpha)+beta) > SAT ? SAT : pix;
        }
}


