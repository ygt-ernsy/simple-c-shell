#ifndef TEST
#define TEST

#include <stdio.h>

#define TEST_ASSERT(message, test)                                             \
  if (!test) {                                                                 \
    printf("[FAILED] %s\n", message);                                          \
    tests_failed++;                                                            \
  } else {                                                                     \
    printf("[PASSED] %s \n", message);                                         \
  }                                                                            \
  tests_run++;

#endif
