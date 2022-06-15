#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
#include "testutils.h"

#define DATATYPE short int
#define NARGS 2
#define FMTSTR "%hd"


#define READ_BODY(DATATYPE, FMTSTR, NARGS) \
    FILE *f;															\
  size_t alloc_size = 1024;												\
  size_t alloc_entries = alloc_size / sizeof(DATATYPE);					\
  size_t entry = 0;														\
																		\
  f = fopen(filename, "r");												\
  if(!f) {																\
	fprintf(stderr, "ERROR: Could not open file %s, %s\n", filename, strerror(errno)); \
	return 0;															\
  }																		\
																		\
  *args = malloc(alloc_size);											\
  if(*args == NULL) {													\
	fprintf(stderr, "ERROR: Could not allocate memory: %s\n", strerror(errno));	\
	return 0;															\
  }																		\
																		\
  DATATYPE *array = *args;												\
																		\
  while(!feof(f)) {														\
	int r;																\
	r = fscanf(f, FMTSTR, &array[entry]);								\
																		\
	if(r != 1) {														\
	  if(r == EOF) break;												\
	  fprintf(stderr, "ERROR: entry %lu: Could not read from stream %s: %s\n", entry, filename, strerror(errno)); \
																		\
	  free(array);														\
	  fclose(f);														\
																		\
	  return 0;															\
	}																	\
																		\
	entry++;															\
																		\
	if(entry >= alloc_entries) {										\
	  *args = realloc(*args, alloc_size * 2);							\
	  if(*args == NULL) {												\
		fprintf(stderr, "ERROR: Could not re-allocate memory: %s\n", strerror(errno)); \
		fclose(f);														\
		free(array);													\
		return 0;														\
	  }																	\
																		\
	  array = *args;													\
	  alloc_size *= 2;													\
	  alloc_entries = alloc_size / sizeof(DATATYPE);					\
	}																	\
  }																		\
																		\
  fclose(f);															\
																		\
  if(entry % NARGS != 0) {												\
	fprintf(stderr, "ERROR: Found %ld numbers in a %d argument input file (not divisible!)\n", entry, NARGS); \
	free(*args);														\
	return 0;															\
  }																		\
																		\
  return entry / NARGS;

#define WRITE_BODY(FMTSTR) \
  FILE *f;																\
																		\
  f = fopen(filename, "w");												\
  if(!f) {																\
	fprintf(stderr, "ERROR: Could not open file %s, %s\n", filename, strerror(errno)); \
	return 0;															\
  }																		\
																		\
  int i, r;																\
  for(i = 0; i < noutput; i++) {										\
	r = fprintf(f, FMTSTR "\n", output[i]);								\
	if(r ==  0) {														\
	  fprintf(stderr, "ERROR: Could not write output: %s\n", strerror(errno)); \
	  return 0;															\
	}																	\
  }																		\
																		\
  fclose(f);															\
  return 1;


size_t read_s16_1(const char *filename, int16_t **args) {
  READ_BODY(int16_t, "%hd", 1);
}

size_t read_s16_2(const char *filename, int16_t **args) {
  READ_BODY(int16_t, "%hd", 2);
}

size_t read_s16_3(const char *filename, int16_t **args) {
  READ_BODY(int16_t, "%hd", 3);
}

int write_s16(const char *filename, int16_t *output, size_t noutput) {
  WRITE_BODY("%hd");
}

size_t read_u16_1(const char *filename, uint16_t **args) {
  READ_BODY(uint16_t, "%hu", 1);
}

size_t read_u16_2(const char *filename, uint16_t **args) {
  READ_BODY(uint16_t, "%hu", 2);
}

size_t read_u16_3(const char *filename, uint16_t **args) {
  READ_BODY(uint16_t, "%hu", 3);
}

int write_u16(const char *filename, uint16_t *output, size_t noutput) {
  WRITE_BODY("%hu");
}

size_t read_s32_1(const char *filename, int32_t **args) {
  READ_BODY(int32_t, "%d", 1);
}

size_t read_s32_2(const char *filename, int32_t **args) {
  READ_BODY(int32_t, "%d", 2);
}

size_t read_s32_3(const char *filename, int32_t **args) {
  READ_BODY(int32_t, "%d", 3);
}

int write_s32(const char *filename, int32_t *output, size_t noutput) {
  WRITE_BODY("%d");
}

size_t read_u32_1(const char *filename, uint32_t **args) {
  READ_BODY(uint32_t, "%u", 1);
}

size_t read_u32_2(const char *filename, uint32_t **args) {
  READ_BODY(uint32_t, "%u", 2);
}

size_t read_u32_3(const char *filename, uint32_t **args) {
  READ_BODY(uint32_t, "%u", 3);
}

size_t read_u32_4(const char *filename, uint32_t **args) {
  READ_BODY(uint32_t, "%u", 4);
}

int write_u32(const char *filename, uint32_t *output, size_t noutput) {
  WRITE_BODY("%u");
}

size_t read_s64_1(const char *filename, int64_t **args) {
  READ_BODY(int64_t, "%ld", 1);
}

size_t read_s64_2(const char *filename, int64_t **args) {
  READ_BODY(int64_t, "%ld", 2);
}

size_t read_s64_3(const char *filename, int64_t **args) {
  READ_BODY(int64_t, "%ld", 3);
}

int write_s64(const char *filename, int64_t *output, size_t noutput) {
  WRITE_BODY("%ld");
}


size_t read_u64_1(const char *filename, uint64_t **args) {
  READ_BODY(uint64_t, "%lu", 1);
}

size_t read_u64_2(const char *filename, uint64_t **args) {
  READ_BODY(uint64_t, "%lu", 2);
}

size_t read_u64_3(const char *filename, uint64_t **args) {
  READ_BODY(uint64_t, "%lu", 3);
}

size_t read_u64_4(const char *filename, uint64_t **args) {
  READ_BODY(uint64_t, "%lu", 4);
}

int write_u64(const char *filename, uint64_t *output, size_t noutput) {
  WRITE_BODY("%lu");
}

size_t read_f32_1(const char *filename, float **args) {
  READ_BODY(float, "%a", 1);
}

size_t read_f32_2(const char *filename, float **args) {
  READ_BODY(float, "%a", 2);
}

size_t read_f32_3(const char *filename, float **args) {
  READ_BODY(float, "%a", 3);
}

#define HEXDIGITS "0.13"

int write_f32(const char *filename, float *output, size_t noutput) {
  // emulate hex in python
  WRITE_BODY("%" HEXDIGITS "a");
}

size_t read_f64_1(const char *filename, double **args) {
  READ_BODY(double, "%la", 1);
}

size_t read_f64_2(const char *filename, double **args) {
  READ_BODY(double, "%la", 2);
}

size_t read_f64_3(const char *filename, double **args) {
  READ_BODY(double, "%la", 3);
}

int write_f64(const char *filename, double *output, size_t noutput) {
  WRITE_BODY("%" HEXDIGITS "a"); // remains the same as float, since floats are upconverted to doubles
}

int read_custom(const char *filename, void **args, size_t sz_arg, int (*reader)(const char *,
																				void *,
																				size_t)) {
  FILE *f;
  size_t alloc_size = 1024;
  size_t alloc_entries = alloc_size / sz_arg;
  size_t entry = 0;

  f = fopen(filename, "r");
  if(!f) {
	fprintf(stderr, "ERROR: Could not open file %s, %s\n", filename, strerror(errno));
	return 0;
  }

  *args = malloc(alloc_size);
  if(*args == NULL) {
	fprintf(stderr, "ERROR: Could not allocate memory: %s\n", strerror(errno));
	return 0;
  }

  void *array = *args;
  char line[1024];

  while(!feof(f)) {
	char *r;
	r = fgets(line, 1024, f);
	if(r == NULL) {
	  if(!ferror(f) && feof(f))
		break;

	  fprintf(stderr, "ERROR: entry %lu: Could not read from stream %s\n", entry, filename);
	  free(*args);
	  fclose(f);

	  return 0;
	}

	errno = 0;

	if(!reader(line, array, entry)) {
	  fprintf(stderr, "ERROR: entry %lu: Could not parse line '%s'\n", entry, line);
	  free(*args);
	  fclose(f);

	  return 0;
	}

	if(errno != 0) {
	  fprintf(stderr, "ERROR: entry %lu: reader set errno to '%s (%d)' line '%s'\n", entry,
			  strerror(errno), errno, line);

	  return 0;
	}

	entry++;

	if(entry >= alloc_entries) {
	  *args = realloc(*args, alloc_size * 2);
	  if(*args == NULL) {
		fprintf(stderr, "ERROR: Could not re-allocate memory: %s\n", strerror(errno));
		fclose(f);
		free(array);
		return 0;
	  }

	  array = *args;
	  alloc_size *= 2;
	  alloc_entries = alloc_size / sz_arg;
	}
  }

  fclose(f);

  return entry;
}

int write_custom(const char *filename, void *output, size_t noutput,
				 int (*writer)(char *, size_t, void *, size_t))
{
  FILE *f;
  char line[1024];

  f = fopen(filename, "w");
  if(!f) {
	fprintf(stderr, "ERROR: Could not open file %s, %s\n", filename, strerror(errno));
	return 0;
  }

  int i, r;
  for(i = 0; i < noutput; i++) {
	r = writer(line, 1024, output, i);
	if(r == 0) {
	  fprintf(stderr, "ERROR: entry %d: Could not create custom output: %s\n", i, strerror(errno));
	  return 0;
	} else {
	  if(fputs(line, f) == EOF) {
		fprintf(stderr, "ERROR: Could not write output: %s\n", strerror(errno));
		return 0;
	  }
	}
  }

  fclose(f);
  return 1;
}

int write_custom_inout(const char *filename, void *output, size_t noutput,
                       void *args,
                       int (*writer)(char *, size_t, void *, void *, size_t))
{
  FILE *f;
  char line[1024];

  f = fopen(filename, "w");
  if(!f) {
	fprintf(stderr, "ERROR: Could not open file %s, %s\n", filename, strerror(errno));
	return 0;
  }

  int i, r;
  for(i = 0; i < noutput; i++) {
	r = writer(line, 1024, output, args, i);
	if(r == 0) {
	  fprintf(stderr, "ERROR: entry %d: Could not create custom output: %s\n", i, strerror(errno));
	  return 0;
	} else {
	  if(fputs(line, f) == EOF) {
		fprintf(stderr, "ERROR: Could not write output: %s\n", strerror(errno));
		return 0;
	  }
	}
  }

  fclose(f);
  return 1;
}

/* these are bitwise sorts, not value sorts. This should suffice for normalization. */
int normsort_cmp16(const void *a, const void *b) {
  const uint16_t *a16 = (const uint16_t *) a;
  const uint16_t *b16 = (const uint16_t *) b;

  return (*a16 > *b16) - (*b16 > *a16);
}

int normsort_cmp32(const void *a, const void *b) {
  const uint32_t *a32 = (const uint32_t *) a;
  const uint32_t *b32 = (const uint32_t *) b;

  return (*a32 > *b32) - (*b32 > *a32);
}

int normsort_cmp64(const void *a, const void *b) {
  const uint64_t *a64 = (const uint64_t *) a;
  const uint64_t *b64 = (const uint64_t *) b;

  return (*a64 > *b64) - (*b64 > *a64);
}
