// Elizabeth Soechting
// CS 420 Hw 2 
// Version 2
// Due: Oct9, 2018
// Compile with -lpthread

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

// starting function for thread
void *myThreadFcn(void *var)
{
 printf("\n\tHello I'm the second thread, my TID is %lu and I'm still in Process:%lu \n\r", pthread_self(), getpid());
 return NULL;  
}

int main()
{
 pid_t PID;
 pthread_t TID; 

 // Error Handling
 int errCode;	// this stores the errorno; 0 if successful, 1 if failed
 char *str; 	// this gives us the char value of the errCode
 str = strerror(EINVAL);	// EINVAL is an invalid argument character
 
 /* Prints the main fcn pid & tid */
 printf("\n\rI am Main Thread 1. PID: %lu , TID: %lu \n\r",getpid(), pthread_self());

 /* Making the new Thread and Error handling */
 errCode = pthread_create(&TID, NULL, myThreadFcn, NULL);	// Stores the value returned by errno	
 if(errCode != 0)
 {
  printf("\n\rError %s \n\r", strerror(errCode));
 }
 
 /* Prints out that new thread was created */
 printf("\n\rMain has succussfully created a second thread with TID: %lu \n\r", TID);
 
 errCode = pthread_join(TID, NULL);	// errCode will store the value returned by pthread_join
 if(errCode != 0)
 {
  printf("\n\rError %s \n\r", strerror(errCode));	
 }
 
 /**** After Thread ****/

 printf("\n\rMain: Second thread has terminated, main will now exit.\n\r"); 

}
