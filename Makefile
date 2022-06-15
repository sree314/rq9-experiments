CLANG=clang-12
CBMC=cbmc

all: nocustom nocustom_test custom_adapted custom_adapted_test custom_strata custom_strata_test

%_test: %.c
	$(CLANG) -DROCETTA_STANDALONE -g -I. -O1 $< -lm -o $@

%: %.c
	$(CLANG) -g -fsanitize=fuzzer -I. -O1 $< -lm -o $@


.PHONY: cbmc

cbmc:
	$(CBMC) --trace --function CBMCtest nocustom.c
