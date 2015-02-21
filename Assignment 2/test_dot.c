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
  struct timespec diff(struct timespec start, struct timespec end);
  struct timespec time1, time2;
  struct timespec time_stamp[OPTIONS][ITERS+1];
  int clock_gettime(clockid_t clk_id, struct timespec *tp);
  vec_ptr new_vec(long int len);
  int get_vec_element(vec_ptr v, long int index, data_t *dest);
  long int get_vec_length(vec_ptr v);
  int set_vec_length(vec_ptr v, long int index);
  int init_vector(vec_ptr v, long int len);
  data_t *data_holder;

  void dot_base(vec_ptr v0, vec_ptr v1, data_t *dest);


  long int i, j, k;
  long long int time_sec, time_ns;
  long int MAXSIZE = BASE+(ITERS+1)*DELTA;

  printf("\n Hello World -- psum examples\n");

  // declare and initialize the vector structure
  vec_ptr v0 = new_vec(MAXSIZE), v1 = new_vec(MAXSIZE);
  data_holder = (data_t *) malloc(sizeof(data_t));
  init_vector(v0, MAXSIZE);
  init_vector(v1, MAXSIZE);

  // execute and time all 7 options from B&O 
  OPTION = 0;
  for (i = 0; i < ITERS; i++) {
    set_vec_length(v0,BASE+(i+1)*DELTA);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    dot_base(v0, v1, data_holder);
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

/**********************************************/
/* Create vector of specified length */
vec_ptr new_vec(long int len)
{
  long int i;

  /* Allocate and declare header structure */
  vec_ptr result = (vec_ptr) malloc(sizeof(vec_rec));
  if (!result) return NULL;  /* Couldn't allocate storage */
  result->len = len;

  /* Allocate and declare array */
  if (len > 0) {
    data_t *data = (data_t *) calloc(len, sizeof(data_t));
    if (!data) {
	  free((void *) result);
	  return NULL;  /* Couldn't allocate storage */
	}
	result->data = data;
  }
  else result->data = NULL;

  return result;
}

/* Retrieve vector element and store at dest.
   Return 0 (out of bounds) or 1 (successful)
*/
int get_vec_element(vec_ptr v, long int index, data_t *dest)
{
  if (index < 0 || index >= v->len) return 0;
  *dest = v->data[index];
  return 1;
}

/* Return length of vector */
long int get_vec_length(vec_ptr v)
{
  return v->len;
}

/* Set length of vector */
int set_vec_length(vec_ptr v, long int index)
{
  v->len = index;
  return 1;
}

/* initialize vector */
int init_vector(vec_ptr v, long int len)
{
  long int i;

  if (len > 0) {
    v->len = len;
    for (i = 0; i < len; i++) v->data[i] = (data_t)(i);
    return 1;
  }
  else return 0;
}

data_t *get_vec_start(vec_ptr v)
{
  return v->data;
}

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


/* dot_base:  Dot product based on combine4 modifications
 * Example of --> Eliminate unneeded memory references */
void dot_base(vec_ptr v0, vec_ptr v1, data_t *dest)
{
  long int i;
  long int get_vec_length(vec_ptr v);
  data_t *get_vec_start(vec_ptr v);

  long int len_0 = get_vec_length(v0), len_1 = get_vec_length(v1);
  data_t *data0 = get_vec_start(v0), *data1 = get_vec_start(v1);
  data_t acc = IDENT;

  for (i = 0; i < length; i++) {
    acc = acc OP (data0[i] * data1[i]);
  }
  *dest = acc;
}

/* dot_1:  Dot product with loop unrolling x2
 * Example of --> Eliminate unneeded memory references */
void dot_1(vec_ptr v0, vec_ptr v1, data_t *dest)
{
  long int i;
  long int get_vec_length(vec_ptr v);
  data_t *get_vec_start(vec_ptr v);

  long int len_0 = get_vec_length(v0), len_1 = get_vec_length(v1);
  data_t *data0 = get_vec_start(v0), *data1 = get_vec_start(v1);
  data_t acc = IDENT;

  for (i = 0; i < length; i+=2) {
    acc = (acc OP (data0[i] * data1[i])) OP (data0[i+1] * data1[i+1]);
  }

  for(; i < length; i++){
    acc = acc OP (data0[i] * data1[i]);
  }
  *dest = acc;
}

/* dot_2:  Dot product with loop unrolling x4
 * Example of --> Eliminate unneeded memory references */
void dot_2(vec_ptr v0, vec_ptr v1, data_t *dest)
{
  long int i;
  long int get_vec_length(vec_ptr v);
  data_t *get_vec_start(vec_ptr v);

  long int len_0 = get_vec_length(v0), len_1 = get_vec_length(v1);
  data_t *data0 = get_vec_start(v0), *data1 = get_vec_start(v1);
  data_t acc = IDENT;

  for (i = 0; i < length; i+=4) {
    acc = (((acc OP (data0[i] * data1[i])) OP (data0[i+1] * data1[i+1])) OP (data0[i+2] * data1[i+2])) OP (data0[i+3] * data1[i+3]);
  }

  for(; i < length; i++){
    acc = acc OP (data0[i] * data1[i]);
  }
  *dest = acc;
}


/* dot_3:  Dot product with loop unrolling x8
 * Example of --> Eliminate unneeded memory references */
void dot_3(vec_ptr v0, vec_ptr v1, data_t *dest)
{
  long int i;
  long int get_vec_length(vec_ptr v);
  data_t *get_vec_start(vec_ptr v);

  long int len_0 = get_vec_length(v0), len_1 = get_vec_length(v1);
  data_t *data0 = get_vec_start(v0), *data1 = get_vec_start(v1);
  data_t acc = IDENT;

  for (i = 0; i < length; i+=8) {
    acc = (((((((acc OP (data0[i] * data1[i])) OP (data0[i+1] * data1[i+1])) OP (data0[i+2] * data1[i+2])) OP (data0[i+3] * data1[i+3])) OP (data0[i+4] * data1[i+4])) OP (data0[i+5] * data1[i+5])) OP (data0[i+6] * data1[i+6])) OP (data0[i+7] * data1[i+7]);
  }

  for(; i < length; i++){
    acc = acc OP (data0[i] * data1[i]);
  }
  *dest = acc;
}

/* dot_4:  Dot product with loop unrolling x10
 * Example of --> Eliminate unneeded memory references */
void dot_4(vec_ptr v0, vec_ptr v1, data_t *dest)
{
  long int i;
  long int get_vec_length(vec_ptr v);
  data_t *get_vec_start(vec_ptr v);

  long int len_0 = get_vec_length(v0), len_1 = get_vec_length(v1);
  data_t *data0 = get_vec_start(v0), *data1 = get_vec_start(v1);
  data_t acc = IDENT;

  for (i = 0; i < length; i+=10) {
    acc = (((((((((acc OP (data0[i] * data1[i])) OP (data0[i+1] * data1[i+1])) OP (data0[i+2] * data1[i+2])) OP (data0[i+3] * data1[i+3])) OP (data0[i+4] * data1[i+4])) OP (data0[i+5] * data1[i+5])) OP (data0[i+6] * data1[i+6])) OP (data0[i+7] * data1[i+7])) OP (data0[i+8] * data1[i+8])) OP (data0[i+9] * data1[i+9]);
  }

  for(; i < length; i++){
    acc = acc OP (data0[i] * data1[i]);
  }
  *dest = acc;
}

/* dot_5:  Dot product with parallelization x2
 * Example of --> Eliminate unneeded memory references */
void dot_4(vec_ptr v0, vec_ptr v1, data_t *dest)
{
  long int i;
  long int get_vec_length(vec_ptr v);
  data_t *get_vec_start(vec_ptr v);

  long int len_0 = get_vec_length(v0), len_1 = get_vec_length(v1);
  data_t *data0 = get_vec_start(v0), *data1 = get_vec_start(v1);
  data_t acc0 = IDENT, acc1 = IDENT;

  for (i = 0; i < length; i+=10) {
    acc0 = (((((((((acc OP (data0[i] * data1[i])) OP (data0[i+1] * data1[i+1])) OP (data0[i+2] * data1[i+2])) OP (data0[i+3] * data1[i+3])) OP (data0[i+4] * data1[i+4])) OP (data0[i+5] * data1[i+5])) OP (data0[i+6] * data1[i+6])) OP (data0[i+7] * data1[i+7])) OP (data0[i+8] * data1[i+8])) OP (data0[i+9] * data1[i+9]);
    acc1 =   }

  for(; i < length; i++){
    acc = acc OP (data0[i] * data1[i]);
  }
  *dest = acc;
}