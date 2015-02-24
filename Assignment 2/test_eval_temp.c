/*****************************************************************************/

// gcc -o test_combine1-7 test_combine1-7.c -lrt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define SIZE 10000000
#define ITERS 20
#define DELTA 10
#define BASE 0

#define OPTIONS 1
#define IDENT 0
#define OP +


typedef double data_t;

/* Create abstract data type for vector */
typedef struct {
  long int len;
  data_t *data;
} vec_rec, *vec_ptr;

//struct timespec {
//  time_t tv_sec; /* seconds */
//  long tv_nsec;  /* nanoseconds */
//};

/*****************************************************************************/
main(int argc, char *argv[])
{
  int OPTION;
  int LENGTH = 50;
  int X = 5;
  struct timespec diff(struct timespec start, struct timespec end);
  struct timespec time1, time2;
  struct timespec time_stamp[OPTIONS][LENGTH];
  int clock_gettime(clockid_t clk_id, struct timespec *tp);
  data_t *data_holder;
  double a[LENGTH];

  long int i, j, k;
  long long int time_sec, time_ns;
  long int MAXSIZE = BASE+(ITERS+1)*DELTA;

  // declare and initialize the vector structure
  data_holder = (data_t *) malloc(sizeof(data_t));

  for(i = 0; i < LENGTH; i++)
    a[i] = i;




  // execute and time all 7 options from B&O 
  OPTION = 0;
  for (i = 0; i < LENGTH; i++) {
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    poly(a, X, i);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
    time_stamp[OPTION][i] = diff(time1,time2);
  }

  /* output times */
  for (i = 0; i < ITERS; i++) {
    printf("\n%d,  ", BASE+(i+1)*DELTA);
    for (j = 0; j < OPTIONS; j++) {
      if (j != 0) printf(", ");
      printf("%d%d", time_stamp[j][i].tv_sec, time_stamp[j][i].tv_nsec);
    }
  }


  printf("\n");
  
}/* end main */


/*************************************************/
struct timespec diff(struct timespec start, struct timespec end)
{
  struct timespec temp;
  if ((end.tv_nsec-start.tv_nsec)<0) {
    temp.tv_sec = end.tv_sec-start.tv_sec-1;
    temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
  } else {
    temp.tv_sec = end.tv_sec-start.tv_sec;
    temp.tv_nsec = end.tv_nsec-start.tv_nsec;
  }
  return temp;
}


double poly(double a[], double x, int degree){
  long int i;
  double result = a[0];
  double xpwr = x;  /* equals x^i at start of loop */
  for(i = 1; i <= degree; i++){
    result += a[i] * xpwr;
    xpwr = x * xpwr;
  }
  return result;
}

