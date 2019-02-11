// Elizabeth Soechting
// CS 420 Hw 3
// Due: October 19
// Compile with -lpthread

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

/* Global Variable */
int var = 0;

void *myThreadFcn(void *args)
{
 printf("\n\tSecond Thread: TID: %lu still in process: %lu\n\r", pthread_self(), getpid());
 printf("\n\t\tSecond Thread: I'm going to spin until Main enters a non-zero value into the global variable.\n\r");
 while(var == 0);	// Infinite loop - spinning
 printf("\n\tSecond Thread: Main set the global to %d . I'm going to reset it to zero then I'm done. \n\r", var);
 var = 0;

 return NULL;
}

int main()
{
 pid_t PID;
 pthread_t TID;
 
 // Error Handling
 int errCode;	// this stores the errorno; 0 if successful, 1 if failed 		 
 // errCode stores the value returned by pthread_create
 errCode = pthread_create(&TID, NULL, myThreadFcn, NULL);	
 if(errCode != 0)
 {
  printf("\n\rError %s \n\r", strerror(errCode));
 }
 
 // print out in main
 printf("\n\rMain Thread, PID: %lu \n\r", getpid());
 printf("\n\rMain: Successfully created a new thread TID: %lu \n\r", pthread_self());
 printf("\n\rEnter a non-zero value so the other thread can stop spinning.\n\r");
 scanf("%d", &var);
 
 while(var != 0);
 
 printf("\n\rMain: The Second Thread reset the global variable to zero so I'm done. \n\r");

}
