#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  printf("Process # %d now running program 'child2replacement.c' My parent pid is: %d", getpid(), getppid());
}
