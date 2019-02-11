// Elizabeth Soechting
// CS 420 Hw 2
// Version 1
// Due: October 9
// Compile with -lpthread

#include <pthread.h>
pthread_t pthread_self(void);
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

void *myThreadFcn(void *var)
{
 printf("\n\rHello I am thread 2, PID: %l, TID: %lu \n\r", getppid(), pthread_self());
}

int main()
{
 pid_t PID;
 pthread_t TID;
 
 // Error Handling
 int errCode;	// this stores the errorno; 0 if successful, 1 if failed
 char *str; 	// this gives us the char value of the errCode
 str = strerror(EINVAL);	// EINVAL is an invalid argument character

 // print out in main
 printf("\n\rMain Thread, PID: %lu, TID: %lu \n\r", getpid(), pthread_self());
 		 
 // errCode stores the value returned by pthread_create
 errCode = pthread_create(&TID, NULL, myThreadFcn, NULL);	
 if(errCode != 0)
 {
  printf("\n\rError %s \n\r", strerror(errCode));
 }

  printf("\n\rMain has succussfully created a second thread with TID: %lu \n\r", TID);
 
}
