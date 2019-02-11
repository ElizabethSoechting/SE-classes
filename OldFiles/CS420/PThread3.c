// Elizabeth Soechting
// CS 420 Hw 2 
// Pthreads Version 3
// Due: October 9
// Compile with -lpthread

#include <unistd.h> 
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
pthread_t pthread_self(void);

void *myThreadFcn(void *var)
{
 printf("\n\tI am thread2 TID: %lu PID: %lu,\n\t\t I recieved a '%c' when I was created.\n\r", pthread_self(), getpid(), *((char*)var));
 return NULL;
}

int main()
{
 pid_t PID;
 pthread_t TID;
 char b = 'b';
 
 /* Error handling */
 int errCode;	// stores the errno; 0 if successful, 1 if failed
 char * str;	// gives us the char value of the errCode
 str = strerror(EINVAL);	// EINVAL is an invalid argument char

 /* Prints the main fcn pid & tid */
 printf("\n\rI am main thread1 PID: %lu, TID: %lu \n\r", getpid(), pthread_self());

 /**** Before Thread ****/

 /* Making the new Thread & Error handling */
 errCode = pthread_create(&TID, NULL, myThreadFcn, &b);	// stores the evalue returned by pthread_create
 if(errCode != 0)
 {
  printf("\n\rError %s \n\r", strerror(errCode));
 } 

 /* prints that a new thread was created */
 printf("\n\rMain has successfully created a new thread with TID: %lu \n\r", TID);

 errCode = pthread_join(TID, NULL);	// errCode stores the value returned by pthread_join
 if(errCode != 0)
 {
  printf("\n\rError %s \n\r", strerror(errCode));
 } 

 /**** After Thread ****/

 printf("\n\rMain: Second thread had terminated, main will now exit.\n\r");
 
} 
