#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include "testutils.h"
#include "ptxc.h"
#include "ptxc_utils.h"

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

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
 // get floats from *Data
  float a;
  float b;

  if(Size != 8) return 0;

  a = *(float *) Data;
  b = *((float *) Data + 1);

  float oracle_result = oracle(a, b);
  float buggy_result = buggy(a, b);

  // this ignores -nan and nan differences
  assert((oracle_result == buggy_result) || (isnan(oracle_result) && isnan(buggy_result)));

  return 0;  // Non-zero return values are reserved for future use.
}

#ifdef ROCETTA_STANDALONE
int main(int argc, char *argv[]) {
  float a, b;

  if(argc != 3) {
    fprintf(stderr, "Usage: %s float1 float2\n", argv[0]);
    return 1;
  }

  a = atof(argv[1]);
  b = atof(argv[2]);

  float oracle_result = oracle(a, b);
  float buggy_result = buggy(a, b);

  printf("a: %a, b: %a, oracle: %a, buggy_result: %a, comparison: %d\n",
         a, b, oracle_result, buggy_result,
         (oracle_result == buggy_result) || (isnan(oracle_result) && isnan(buggy_result)));
}
#endif
