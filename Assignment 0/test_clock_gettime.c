/******************************************************************************/

// gcc -O0 -o test_clock_gettime test_clock_gettime.c -lrt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define SIZE 10000000

//struct timespec {
//  time_t tv_sec; /* seconds */
//  long tv_nsec;  /* nanoseconds */
//};

/******************************************************************************/
main(int argc, char *argv[])
{
  struct timespec time1, time2;
  int clock_gettime(clockid_t clk_id, struct timespec *tp);

  // read the clock
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);

  // some stuff that takes one second

  // read the clock again
  clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);

  // call diff to find the elapsed time and print it.


}/* end main */


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

