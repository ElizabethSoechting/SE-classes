#include <stdio.h>
#include <unistd.h>
// #include <"child2replacment.exe">


main()
{ 

  // loop counting variable
  int count = 1;

  // start child number at 1
  int child = 1;
 
  // set parent number at 1 becasue we will only have 1 parent
  int parent = 1;
  
  // parent PID
  int parentPID = getpid();

  // childPID will be generated using getpid()
  int child1PID = getpid();
  int child2PID = getpid();
  int child3PID = getpid();

  // parent spawning loop//

  /* this loop will use fork() to spawn a child then will print out the parent process *
   * that labels itself as parent, puts PID, number of child, and child's PID which is *
   * generated using setpgid() function. We then print out the child statements that   *
   * state what child number it is, its pid (for that time through the loop), and also *
   * re-states the parentPID. Child */
 
  for(child = 1; child <= 3; child++;)
  {
    fork();	// spawns a new child
    // childPID = setpgid(2); 	//gets a new pid
    printf("Parent, my PID is %d Spawned child # %d with PID %d", parentPID, child, childPID);	
        
  }
  
 
 }


