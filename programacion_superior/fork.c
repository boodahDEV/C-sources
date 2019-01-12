#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/wait.h>
#include  <sys/mman.h>

int main()
{
  pid_t child;
 // int *number = (int*)malloc(sizeof(int));
  int *number = (int*)mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
               MAP_SHARED | MAP_ANONYMOUS, -1, 0);

  *number = 5;

  child = fork();

  if (child==-1){
      exit(1);
    } else if (child==0){
      for (int i=0; i<10; ++i){
      usleep(70000);
      printf ("CHILD -- Number: %d\n", *number);
      *number=i;
     }
     printf("\n\n\tID del HIJO: %d y el papa es: %d\n",getpid(),getppid());
      exit(0);
}else{
      for (int i=20; i<30; ++i){
      usleep(70000);
      printf ("*****MAIN -- Number: %d\n", *number);
      *number=i;
    }

    printf("\n\n\tID del PADRE: %d y el padre es: %d\n",getpid(),getppid());

}
printf("Test: %d",getpid());
  wait(NULL);
  //free(number);
  munmap(number, sizeof(int));

}
