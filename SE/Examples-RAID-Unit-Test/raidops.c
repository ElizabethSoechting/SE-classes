#include <sys/time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#define ITERATIONS 100000
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define OK 0
#define SECTOR_SIZE (512)
#define MAX_LBAS (1000)
#define TEST_ITERATIONS (1000)


#define TEST_RAID_STRING "#0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ##0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ##0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ##0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ##0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ##0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ##0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ##0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ#"

#define NULL_RAID_STRING "#FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF#"

static char testRebuild4[MAX_LBAS][512]=
{NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING};

static char testRebuild5[MAX_LBAS][512]=
{NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING, NULL_RAID_STRING};

static char testLBA1[MAX_LBAS][512]= {TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING};

static char testLBA2[MAX_LBAS][512]= {TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING};

static char testLBA3[MAX_LBAS][512]= {TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING};

static char testLBA4[MAX_LBAS][512]= {TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING};

static char testLBA5[MAX_LBAS][512]= {TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING, TEST_RAID_STRING};

char testPLBA[MAX_LBAS][512];




// RAID-5 encoding
//
// Do XOR 64 bits at a time for efficiency - so 512 byte LBA is 64 long long
// XOR operations in C
//
// This is 80% capacity with 1/5 LBAs used for parity.
//
// Only handles single faults.
//
/*
void xorLBA(unsigned long long *LBA1,
	    unsigned long long *LBA2,
	    unsigned long long *LBA3,
	    unsigned long long *LBA4,
	    unsigned long long *PLBA)
{
    int i;
    unsigned long long *ptrLBA1=LBA1;
    unsigned long long *ptrLBA2=LBA2;
    unsigned long long *ptrLBA3=LBA3;
    unsigned long long *ptrLBA4=LBA4;
    unsigned long long *ptrPLBA=PLBA;

    for(i=0;i<64;i++)
    {
        *ptrPLBA=0;
        *ptrPLBA=(*ptrLBA1)^(*ptrLBA2)^(*ptrLBA3)^(*ptrLBA4);
        ptrPLBA++;ptrLBA1++;ptrLBA2++;ptrLBA3++;ptrLBA4++;
    }
}
*/


// RAID-5 Rebuild
//
// Provide any 3 of the original LBAs and the Parity LBA to rebuild the RLBA
//
// If the Parity LBA was lost, then it can be rebuilt by simply re-encoding.
// 
/*
void rebuildLBA(unsigned long long *LBA1,
	        unsigned long long *LBA2,
	        unsigned long long *LBA3,
	        unsigned long long *PLBA,
	        unsigned long long *RLBA)
{
    int i;
    unsigned long long checkParity;
    unsigned long long *ptrLBA1=LBA1;
    unsigned long long *ptrLBA2=LBA2;
    unsigned long long *ptrLBA3=LBA3;
    unsigned long long *ptrPLBA=PLBA;
    unsigned long long *ptrRLBA=RLBA;

    for(i=0;i<64;i++)
    {
       *ptrRLBA=0;

        // Parity check word is simply XOR of remaining good LBAs
        checkParity=(*ptrLBA1)^(*ptrLBA2)^(*ptrLBA3);

        // Rebuilt LBA is simply XOR of original parity and parity check word
        // which will preserve original parity computed over the 4 LBAs
        *ptrRLBA =(*ptrPLBA)^(checkParity);
	    
        ptrPLBA++;ptrLBA1++;ptrLBA2++;ptrLBA3++;ptrRLBA++;
    }
}


int checkEquivLBA(unsigned long long *LBA1,
		  unsigned long long *LBA2)
{
    int i;
    unsigned long long *ptrLBA1=LBA1;
    unsigned long long *ptrLBA2=LBA2;

    for(i=0;i<64;i++)
    {
        if((*ptrLBA1) != (*ptrLBA2))
	{
            printf("EQUIV CHECK MISMATCH @ word %d: LBA1=0x%llx, LBA2=0x%llx\n", i, (*ptrLBA1), (*ptrLBA2));
	    return ERROR;
	}

	ptrLBA1++;ptrLBA2++;
    }

    return OK;
}
*/

#define MODIFY
#define REBUILD
#define VERIFY


void *simpleRAID(int LBAIdx)
{
    int i;
    struct timeval StartTime, StopTime;
    unsigned int microsecs;
    double rate;



    gettimeofday(&StartTime, 0);

    for(i=0;i<TEST_ITERATIONS;i++)
    {

	// Precheck for equivalence
        if(checkEquivLBA((unsigned long long *)&testLBA1[LBAIdx], (unsigned long long *)&testLBA2[LBAIdx]) < 0)
	{
	    printf("PRECHECK ERROR\n");
	    exit(-1);
	}


#ifdef MODIFY
	// Compute XOR from 4 LBAs for RAID-5
        xorLBA((unsigned long long *)&testLBA1[LBAIdx],
	       (unsigned long long *)&testLBA2[LBAIdx],
	       (unsigned long long *)&testLBA3[LBAIdx],
	       (unsigned long long *)&testLBA4[LBAIdx],
	       (unsigned long long *)&testPLBA[LBAIdx]);
#endif

#ifdef REBUILD
	// Now rebuild LBA into test to verify
        rebuildLBA((unsigned long long *)&testLBA1[LBAIdx],
	           (unsigned long long *)&testLBA2[LBAIdx],
	           (unsigned long long *)&testLBA3[LBAIdx],
	           (unsigned long long *)&testPLBA[LBAIdx],
	           (unsigned long long *)&testRebuild4[LBAIdx]);
#endif

#ifdef VERIFY
	// Now verify the rebuilt LBA4 using the test rebuild LBA
        if(checkEquivLBA((unsigned long long *)&testRebuild4[LBAIdx], (unsigned long long *)&testLBA4[LBAIdx]) < 0)
	{
	    printf("REBUILD ERROR\n");
	    exit(-1);
	}
#endif


    }

    gettimeofday(&StopTime, 0);

    microsecs=((StopTime.tv_sec - StartTime.tv_sec)*1000000);

    if(StopTime.tv_usec > StartTime.tv_usec)
	microsecs+=(StopTime.tv_usec - StartTime.tv_usec);
    else
	microsecs-=(StartTime.tv_usec - StopTime.tv_usec);

    rate=((double)ITERATIONS)/(((double)microsecs)/1000000.0);


}


/*
int main(int argc, char *argv[])
{
	int idx, LBAidx, numTestIterations, rc;
	double rate=0.0;
	double totalRate=0.0, aveRate=0.0;
	struct timeval StartTime, StopTime;
	unsigned int microsecs;


        if(argc < 2)
	{
		numTestIterations=TEST_ITERATIONS;
		printf("Will default to %d iterations\n", TEST_ITERATIONS);
        }
        else
        {
            sscanf(argv[1], "%d", &numTestIterations);
       	    printf("Will start %d test iterations\n", numTestIterations);
        }


	printf("\nRAID Test\n");

	gettimeofday(&StartTime, 0);

#if 1
	for(idx=0;idx<numTestIterations;idx++)
	{
            LBAidx = idx % MAX_LBAS;

	    // Compute XOR from 4 LBAs for RAID-5
            xorLBA((unsigned long long *)&testLBA1[LBAidx],
	           (unsigned long long *)&testLBA2[LBAidx],
	           (unsigned long long *)&testLBA3[LBAidx],
    	           (unsigned long long *)&testLBA4[LBAidx],
	           (unsigned long long *)&testPLBA[LBAidx]);

	    // Now rebuild LBA into test to verify
            rebuildLBA((unsigned long long *)&testLBA1[LBAidx],
	               (unsigned long long *)&testLBA2[LBAidx],
	               (unsigned long long *)&testLBA3[LBAidx],
	               (unsigned long long *)&testPLBA[LBAidx],
	               (unsigned long long *)&testRebuild4[LBAidx]);
	}
#endif

	gettimeofday(&StopTime, 0);

        microsecs=((StopTime.tv_sec - StartTime.tv_sec)*1000000);

	if(StopTime.tv_usec > StartTime.tv_usec)
		microsecs+=(StopTime.tv_usec - StartTime.tv_usec);
	else
		microsecs-=(StartTime.tv_usec - StopTime.tv_usec);

	printf("Test Done in %u microsecs for %d iterations\n", microsecs, ITERATIONS);

	rate=((double)ITERATIONS)/(((double)microsecs)/1000000.0);
	printf("%lf RAID ops computed per second\n", rate);
}
*/

