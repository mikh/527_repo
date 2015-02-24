/*****************************************************************************/
// gcc -O1 -o test_combine8 test_combine8.c -lrt -lm
// 
// combine4   -- base scalar code
// combine6_5 -- unrolled 5 times with 5 accumulators -- best scalar code
// combine8   -- base vector code
// combine8_2 -- unrolled 2 times with 2 accumulators  NEED TO ADD
// combine8_4 -- unrolled 4 times with 4 accumulators
// combine8_8 -- unrolled 8 times with 8 accumulators  NEED TO ADD

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define GIG 1000000000
#define CPG 2.0           // Cycles per GHz -- Adjust to your computer

#define SIZE 10000000
#define ITERS 30
#define DELTA 32
#define BASE 0

#define OPTIONS 4       // NEED TO MODIFY
#define IDENT 1.0
#define OP *

typedef double data_t;

/* Create abstract data type for vector */
typedef struct {
  long int len;
  data_t *data;
} vec_rec, *vec_ptr;

/* Number of bytes in a vector */
#define VBYTES 16

/* Number of elements in a vector */
#define VSIZE VBYTES/sizeof(data_t)

typedef data_t vec_t __attribute__ ((vector_size(VBYTES)));
typedef union {
  vec_t v;
  data_t d[VSIZE];
} pack_t;

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

  void combine4(vec_ptr v, data_t *dest);
  void combine6_5(vec_ptr v, data_t *dest);
  void combine8(vec_ptr v, data_t *dest);
  void combine8_4(vec_ptr v, data_t *dest);

  long int i, j, k;
  long long int time_sec, time_ns;
  long int MAXSIZE = BASE+(ITERS+1)*DELTA;

  printf("\n Hello World -- vector examples\n");

  // declare and initialize the vector structure
  vec_ptr v0 = new_vec(MAXSIZE);
  data_holder = (data_t *) malloc(sizeof(data_t));
  init_vector(v0, MAXSIZE);

  // execute and time ... options from B&O 
  OPTION = 0;
  for (i = 0; i < ITERS; i++) {
    set_vec_length(v0,BASE+(i+1)*DELTA);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    combine4(v0, data_holder);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
    time_stamp[OPTION][i] = diff(time1,time2);
  }

  OPTION++;
  for (i = 0; i < ITERS; i++) {
    set_vec_length(v0,BASE+(i+1)*DELTA);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    combine6_5(v0, data_holder);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
    time_stamp[OPTION][i] = diff(time1,time2);
  }

  OPTION++;
  for (i = 0; i < ITERS; i++) {
    set_vec_length(v0,BASE+(i+1)*DELTA);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    combine8(v0, data_holder);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
    time_stamp[OPTION][i] = diff(time1,time2);
  }

  OPTION++;
  for (i = 0; i < ITERS; i++) {
    set_vec_length(v0,BASE+(i+1)*DELTA);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);
    combine8_4(v0, data_holder);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
    time_stamp[OPTION][i] = diff(time1,time2);
  }

  /* output times */
  printf("\nsize, c4, c6_5,  c8,  c8_4");
  for (i = 0; i < ITERS; i++) {
    printf("\n%d, ", BASE+(i+1)*DELTA);
    for (j = 0; j < OPTIONS; j++) {
      if (j != 0) printf(", ");
      printf("%ld", (long int)((double)(CPG)*(double)
		 (GIG * time_stamp[j][i].tv_sec + time_stamp[j][i].tv_nsec)));
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

/*************************************************/
/* Combine4:  Accumulate result in local variable
 * Example of --> Eliminate unneeded memory references */
void combine4(vec_ptr v, data_t *dest)
{
  long int i;
  long int get_vec_length(vec_ptr v);
  data_t *get_vec_start(vec_ptr v);
  long int length = get_vec_length(v);
  data_t *data = get_vec_start(v);
  data_t acc = IDENT;

  for (i = 0; i < length; i++) {
    acc = acc OP data[i];
  }
  *dest = acc;
}

/* Combine6_5:  Unroll loop by 5, 5 accumulators
 * Example of --> parallelism */
void combine6_5(vec_ptr v, data_t *dest)
{
  long int i;
  long int get_vec_length(vec_ptr v);
  data_t *get_vec_start(vec_ptr v);
  long int length = get_vec_length(v);
  long int limit = length - 1;
  data_t *data = get_vec_start(v);
  data_t acc0 = IDENT;
  data_t acc1 = IDENT;
  data_t acc2 = IDENT;
  data_t acc3 = IDENT;
  data_t acc4 = IDENT;

  /* Combine 5 elements at a time w/ 5 acculators */
  for (i = 0; i < limit-4; i+=5) {
    acc0 = acc0 OP data[i];
    acc1 = acc1 OP data[i+1];
    acc2 = acc2 OP data[i+2];
    acc3 = acc3 OP data[i+3];
    acc4 = acc4 OP data[i+4];
  }

  /* Finish remaining elements */
  for (; i < length; i++) {
    acc0 = acc0 OP data[i];
  }
  *dest = acc0 OP acc1 OP acc2 OP acc3 OP acc4;
}

/* Combine8:  Vector version */
void combine8(vec_ptr v, data_t *dest)
{
  long int i;
  pack_t xfer;
  vec_t accum;
  data_t *data = get_vec_start(v);
  long int cnt = get_vec_length(v);
  data_t result = IDENT;

  /* Initialize accum entries to IDENT */
  for (i = 0; i < VSIZE; i++) xfer.d[i] = IDENT;
  accum = xfer.v;

  /* Single step until we have memory alignment */
  while (((long) data) % VBYTES && cnt) {
    result = result OP *data++;
    cnt--;
  }

  /* Step through data with VSIZE-way parallelism */
  while (cnt >= VSIZE) {
    vec_t chunk = *((vec_t *) data);
    accum = accum OP chunk;
    data += VSIZE;
    cnt -= VSIZE;
  }

  /* Single-step through the remaining elements */
  while (cnt) {
    result = result OP *data++;
    cnt--;
  }

  /* Combine elements of accumulator vector */
  xfer.v = accum;
  for (i = 0; i < VSIZE; i++)
    result = result OP xfer.d[i];

  /* store result */
  *dest = result;
}

/* Combine8_4:  Vector 4x unrolled version */
void combine8_4(vec_ptr v, data_t *dest)
{
  long int i;
  pack_t xfer;
  vec_t accum0;
  vec_t accum1;
  vec_t accum2;
  vec_t accum3;
  data_t *data = get_vec_start(v);
  long int cnt = get_vec_length(v);
  data_t result = IDENT;

  /* Initialize accum entries to IDENT */
  for (i = 0; i < VSIZE; i++) xfer.d[i] = IDENT;
  accum0 = xfer.v;
  accum1 = xfer.v;
  accum2 = xfer.v;
  accum3 = xfer.v;

  /* Single step until we have memory alignment */
  while (((long) data) % (4*VBYTES) && cnt) {
    result = result OP *data++;
    cnt--;
  }

  /* Step through data with VSIZE-way parallelism */
  while (cnt >= 4*VSIZE) {
    vec_t chunk0 = *((vec_t *) data);
    vec_t chunk1 = *((vec_t *) data+VSIZE);
    vec_t chunk2 = *((vec_t *) data+2*VSIZE);
    vec_t chunk3 = *((vec_t *) data+3*VSIZE);
    accum0 = accum0 OP chunk0;
    accum1 = accum1 OP chunk1;
    accum2 = accum2 OP chunk2;
    accum3 = accum3 OP chunk3;
    data += 4*VSIZE;
    cnt -= 4*VSIZE;
  }

  /* Single-step through the remaining elements */
  while (cnt) {
    result = result OP *data++;
    cnt--;
  }

  /* Combine elements of accumulator vectors */
  xfer.v = (accum0 OP accum1) OP (accum2 OP accum3);

  for (i = 0; i < VSIZE; i++)
    result = result OP xfer.d[i];

  /* store result */
  *dest = result;
}

