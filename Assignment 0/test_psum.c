/******************************************************************************/

// gcc -O0 -o test_psum test_psum.c -lrt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define SIZE 10000000

/******************************************************************************/
main(int argc, char *argv[])
{
  int clock_gettime(clockid_t clk_id, struct timespec *tp);
  struct timespec diff(struct timespec start, struct timespec end);
  void psum1(float a[], float p[], long int n);
  void psum2(float a[], float p[], long int n);
  float *in, *out;
  long int i, j, k;
  struct timespec time1, time2, time_psum1, time_psum2;

  // initialize
  in = (float *) malloc(SIZE * sizeof(*in));
  out = (float *) malloc(SIZE * sizeof(*out));
  for (i = 0; i < SIZE; i++) in[i] = (float)(i);
  

  for(i = 0; i < 301; i += 50){
	  // process psum1 for various array sizes and collect timing
	  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	  psum1(in, out, i);
	  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
	  time_psum1 = diff(time1, time2);

	  // process psum2 for various array sizes and collect timing
	  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
	  psum2(in, out, i);
	  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
	  time_psum2 = diff(time1, time2);

	  // output timing
	  printf("%d,\t%d,\t%d\n", i, time_psum1.tv_sec*1000000000+time_psum1.tv_nsec, time_psum2.tv_sec*1000000000+time_psum2.tv_nsec)
  }

  
}/* end main */


void psum1(float a[], float p[], long int n)
{
  long int i;

  p[0] = a[0];
  for (i = 1; i < n; i++)
    p[i] = p[i-1] + a[i];

}

void psum2(float a[], float p[], long int n)
{
  long int i;

  p[0] = a[0];
  for (i = 1; i < n-1; i+=2) {
    float mid_val = p[i-1] + a[i];
    p[i] = mid_val;
    p[i+1] = mid_val + a[i+1];
  }

  /* For odd n, finish remaining element */
  if (i < n)
    p[i] = p[i-1] + a[i];
}

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

