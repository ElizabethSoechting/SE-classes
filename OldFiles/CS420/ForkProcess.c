#include <sys.types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
  pid_t pid;

  // Fork a child Process

  pid = fork();

  if(pid < 0)
  {
    /* Error occurred */
    fprintf(stderr, "Fork Failed!");
    return 1;
  }
  elseif(pid == 0)
  {
    execv{"/bin/ls", "ls", NULL};
  }
  else // Parent Process
  {
    wait(NULL);
    fprintf("Child Complete");
  }
  
  return 0;
} 
