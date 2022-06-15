This is an repository containing implementations of a stratified
sampler for floats for RQ9 in our FUZZING 2022 submission.

RQ9 attempts to discover inputs that are witnesses to the differences
between the oracle version and the buggy version. These witnesses --
two float numbers --have the characteristics that they are normal, but
when added together produce a subnormal number.

We use libFuzzer from Clang 12. We run everything from an empty
corpus. We evaluate three strategies, each outlined in a section below.

# nocustom.c

This is the simplest strategy with no custom fuzzing mutators.

```
mkdir -p empty-corpus
make nocustom
./nocustom empty-corpus
```

If it crashes and finds an input, then you can use `dumpfloats.py` to
look at the input.

```
./dumpfloats.py crash-fc80251c6950c1cd22ae18636db21156f0e73781
-0x1.ffcc000000000p-126 0x1.fffe000000000p-126
```

In this case it finds witnesses. You can test these witnesses by running:

```
./nocustom_test -0x1.ffcc000000000p-126 0x1.fffe000000000p-126
```

which will yield:

```
a: -0x1.ffccp-126, b: 0x1.fffep-126, oracle: 0x0p+0, buggy_result: 0x1.9p-137, comparison: 0
```

# custom_adapted.c

This strategy uses a custom mutator which is based (poorly) on
Rigtorp's [Fuzzing floating point
code](https://rigtorp.se/fuzzing-floating-point-code/) translated into
C.

```
mkdir -p empty-corpus
./custom_adapted empty-corpus
```

In our experiments, this does not find the witnesses.

# custom_strata.c

This strategy also uses a custom mutator, but generates input using
stratified sampling contained in `float_sampler.c` and
`float_sampler.h`.

```
mkdir -p empty-corpus
./custom_strata empty-corpus
```

This seems to find witnesses too, and possibly faster than the first,
no custom mutator strategy.


# CBMC

Use `make cbmc` to run CBMC on `nocustom.c`, assuming you have CBMC installed.

Here are the relevant excerpts of the trace:

```
  a=8.522334e-37f (00000011 10010001 00000000 00000000)

  b=-8.463575e-37f (10000011 10010000 00000000 00010001)

  oracle_result=0.0f (00000000 00000000 00000000 00000000)

  buggy_result=5.875947e-39f (00000000 00111111 11111011 11000000)

Violated property:
  file nocustom.c function CBMCtest line 43 thread 0
  assertion oracle_result == buggy_result
  IEEE_FLOAT_EQUAL(oracle_result, buggy_result)



** 1 of 2 failed (2 iterations)
VERIFICATION FAILED
```

# Legalese

All code in this repository is Copyright (C) 2022, University of Rochester. 
