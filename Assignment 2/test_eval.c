#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>


main(int argc, char *argv[]){
	int OPTION;
	struct timespec diff(struct timespec start, struct timespec end);
	struct timespec time1, time2;
	struct timespec time_stamp[OPTIONS][ITERS+1];
}

double poly(double a[], double x, int degree){
	long int i;
	double result = a[0];
	double xpwr = x;	/* equals x^i at start of loop */
	for(i = 1; i <= degree; i++){
		result += a[i] * xpwr;
		xpwr = x * xpwr;
	}
	return result;
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