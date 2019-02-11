/**********************
* Elizabeth Soechting *			
* CS420   Homework 5  *
* Due: December 5     *
***********************/


#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main()
{
	int memID;		// Holds shared memory identifier 
	int *shared;		// Pointer to shared memory location 
	pid_t parent;		// Holds PID 

	// Create shared memory for an integer
	memID = shmget(IPC_CREAT, sizeof(int), IPC_CREAT | 0666);
		/* Check error status of shmget() */
		if( memID == -1)		
		{
			printf("\n\rshmget() Error: %s \n\r", strerror(memID));
			exit(1);
		}

	printf("\n\rParent Process: Successfully created shared memory segment\n\r");
	printf("\n\tShared memory ID: %d \n\r", memID);

	/* Get address for process */
	shared = (int*)shmat(memID, (void*)NULL, 0);
		if( *shared == -1)	
		{
			printf("\n\rshmat() Error: %s \n\r", strerror(shared));
			exit(1);
		}
	
	/* Set shared variable to 0 */
	*shared = 0;					

	/* Print parent PID */
	printf("\n\rParent Process: PID is %d\n\r", getpid());
	printf("\n\tShared Integer is set to 0 and a child process is now spawning\n\r");
	
	/* Spawn child proces */
	parent = fork();				

	/*  Parent Process  */
	if (parent > 0)																	
	{
		printf("\n\rParent Process: PID is %d -- spawned child with PID %d\n\r", getpid(), parent);

		/* Prompt user for new integer value */
		printf("\n\rEnter a non-zero value to be stored in shared memory: \n\r");
		scanf("%d", shared);
			if( shared == 0)
			{
				printf("\n\rEnter a non-zero value to be stored in shared memory: \n\r");
				scanf("%d", shared);
			}
		
		/* Spin in parent process until shared is set back to 0 by the child process */
		while(*shared != 0);		
		printf("\n\rParent Process: Child reset shared the integer to 0 . \n\r");

		/* Detach shared memory segment */
		shmdt(&memID);
	}	

	/*  Child Process  */
	else if ( parent == 0)
	{
		printf("\n\tChild Process: PID is: %d -- Parent PID is: %d \n", getpid(), getppid());
		printf("\n\t\tThe shared integer value is currently 0 .\n\r");

		while(*shared == 0);

		/* Reset shared integer to 0 */
		*shared = 0;
		printf("\n\tChild Process: The shared integer was set to %d -- I will reset to 0\n\r", *shared);
		
		/* Terminating child process */
		printf("\n\tChild Process: Terminating\n\r");
	}

	else
	{
		printf("\n\rFailed fork!\n\r");
		exit(1);
	}
	
	if (parent > 0)	
	{
		/* Return shared memory segment */
		shmctl(memID, IPC_RMID, NULL);

		printf("\n\rParent Process: Child terminated -- shared memory segment # %d successfully removed.\n\r", memID);

	}

}

