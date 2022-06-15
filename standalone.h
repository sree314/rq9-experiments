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
