#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include "testutils.h"
#include "ptxc.h"
#include "ptxc_utils.h"
#include <float.h>

float oracle (float src1, float src2) {
  float tmp_dst;
  float dst;

  src1 = FTZ(src1);
  src2 = FTZ(src2);
  tmp_dst = SATURATE(ADD_ROUND(src1, src2, FE_DOWNWARD));
  tmp_dst = FTZ(tmp_dst);
  dst = tmp_dst;
  return dst;
}

float buggy (float src1, float src2) {
  float tmp_dst;
  float dst;

  src1 = FTZ(src1);
  src2 = FTZ(src2);
  tmp_dst = SATURATE(ADD_ROUND(src1, src2, FE_DOWNWARD));
  tmp_dst = tmp_dst;
  dst = tmp_dst;
  return dst;
}

void CBMCtest() {
  float a;
  float b;

  float oracle_result = oracle(a, b);
  float buggy_result = buggy(a, b);

  assert(oracle_result == buggy_result);
}

/* adapted from: https://rigtorp.se/fuzzing-floating-point-code/ */
float get_float(int choice) {
  float t;

  //float TODO SUBFLOATS
  choice = choice % 14;

  switch (choice)
    {
    case 0:
      return 0.0f;
    case 1:
      return FLT_MIN;
    case 2:
      return FLT_MAX;
    case 3:
      return -FLT_MIN;
    case 4:
      return -FLT_MAX;
    case 5:
      return FLT_EPSILON;
    case 6:
      return -FLT_EPSILON;
    case 7:
      return INFINITY;
    case 8:
      return -INFINITY;
    case 9:
      return -0.0f;
    case 10:
      return NAN;
    case 11:
      return -NAN;
    case 12:
      t = (double) rand() / RAND_MAX; /* use double since RAND_MAX may not fit exactly in float */
      return FLT_MIN + t * (FLT_MAX - FLT_MIN);
    case 13:
      t = (double) rand() / RAND_MAX;
      return -(FLT_MIN + t * (FLT_MAX - FLT_MIN));

    default:
    abort();
  }
}

size_t LLVMFuzzerCustomMutator(uint8_t *Data, size_t Size,
                               size_t MaxSize, unsigned int Seed)
{
  if(MaxSize < 8)
    return 0;

  srand(Seed);

  int choice1 = rand();
  int choice2 = rand();

  float *a = (float *) Data;
  float *b = ((float *) Data) + 1;

  *a = get_float(choice1);
  *b = get_float(choice2);

  return 8;
}

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
 // get floats from *Data
  float a;
  float b;

  a = *(float *) Data;
  b = *((float *) Data + 1);

  float oracle_result = oracle(a, b);
  float buggy_result = buggy(a, b);

  assert((oracle_result == buggy_result) || (isnan(oracle_result) && isnan(buggy_result)));

  return 0;  // Non-zero return values are reserved for future use.
}

#include "standalone.h"
