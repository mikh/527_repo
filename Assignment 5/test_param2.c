/*************************************************************************/
// gcc -pthread -o test_param2 test_param2.c

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define NUM_THREADS 10

/********************/
void *work(void *i)
{
  long int j, k;
  int f = *((int*)(i));  // get the value being pointed to
  int *g = (int*)(i);    // get the pointer itself

  *g = (*g)++;

  for (j; j < 10000000; j++) k += j;  // busy work

  // printf("\nHello World from %lu with value %d\n", pthread_self(), f);
  printf("\nHello World! %d  %d",  f, *g);

  pthread_exit(NULL);
}

/*************************************************************************/
int main(int argc, char *argv[])
{
  int arg,i,j,k,m, t, len = 0;   	              /* Local variables. */
  pthread_t id[NUM_THREADS];
  int values[NUM_THREADS];
  for(i = 0; i < NUM_THREADS; i++)
    values[i] = i;

  for (i = 0; i < NUM_THREADS; ++i) {
    if ((i < NUM_THREADS) && pthread_create(&id[i], NULL, work, (void *)(values+i))) {
      printf("ERROR creating the thread\n");
      exit(19);
    }
    len++;
  }

  for (j; j < 100000000; j++) k += j;  // busy work

  printf("\nAfter creating the thread.  My id is %lu, i = %d\n",
	 pthread_self(), i);


  for (t = 0; t < len; t++) {
    if (pthread_join(id[t],NULL)){ exit(19);
    }
  }

  printf("\n\nValues:");
  for(i = 0; i < NUM_THREADS; i++){
    printf("%d\t", values[i]);
  }

  return(0);

}/* end main */


