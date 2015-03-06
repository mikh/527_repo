/*************************************************************************/
// gcc -pthread -o test_param test_param1.c

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

/************************************************************************/
void *PrintHello(void *threadid)
{
  printf("%d\n", threadid);
  long unsigned int tid = (long unsigned int) threadid;
  
  printf(" Hello World!  It's me, thread # %lx ! \n", tid);

  pthread_exit(NULL);
}

/*************************************************************************/
int main(int argc, char *argv[])
{
  int arg,i,j,k,m;   	              /* Local variables. */
  pthread_t threads[NUM_THREADS];
  int rc;
  long unsigned int t;
  signed char t_c = -4;

  printf("\n Hello World!  It's me, MAIN!\n");

  for (t = 0; t < NUM_THREADS; t++) {
    printf("In main:  creating thread %ld\n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello, (void*) t_c);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
  }

  for (i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(threads[i],NULL)){ exit(19);
    }
  }

  printf("\n It's me MAIN -- Good Bye World!\n");

  pthread_exit(NULL);

}/* end main */

