// Elizabeth Soechting
// CS 420 Hw 3
// Due: October 19
// Compile with -lpthread

#include <unistd.h> 
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

/* Global Variables */
int var = 0;

void *myThreadFcn(void *args)
{
 printf("\n\tSecond Thread: My TID: %lu Still in process: %lu,\n\t\tI'm about to spin until Main enters a non-zero value into the shared variable\n\r", pthread_self(), getpid());  
 printf("Second Thread: Main set the variable to %d , I'll set it back to zero then I'm done.\n\r", var);
 var = 0;
 return NULL;
}

int main()
{
 pid_t PID;
 pthread_t TID;
 
 /* Error handling */
 int errCode;	// stores the errno; 0 if successful, 1 if failed
 char * str;	// gives us the char value of the errCode
 str = strerror(EINVAL);	// EINVAL is an invalid argument char

 /* Prints the main fcn pid & tid */
 printf("\n\rMain: PID: %lu\n\r", getpid());

 /**** Before Thread ****/

 /* Making the new Thread & Error handling */

 errCode = pthread_create(&TID, NULL, myThreadFcn, NULL);	// stores the evalue returned by pthread_create
 if(errCode != 0)
 {
  printf("\n\rError %s \n\r", strerror(errCode));
 } 

 /* prints that a new thread was created */
 printf("\n\rMain: Successfully created a thread with TID: %lu \n\r", TID);

 printf("\n\rEnter a non-zero value so the second function can stop spinning.\n\r");
 scanf("%d", &var);
  
} 
