// SPDX-License-Identifier: MIT

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DO_LOG
// By default, we don't log things.
#define DO_LOG false
#endif

// Track the number of operations done in a sorting algorithm.
static unsigned int N_OPS = 0;

char *selection_sort(const char *, const size_t);
char *insertion_sort(const char *, const size_t);
char *shell_sort(const char *, const size_t);
static void exchange(char *, const size_t, const size_t);
static size_t min_index(const char *, const size_t, const size_t);

char *selection_sort(const char *input, const size_t len) {
  N_OPS = 0;
  char *s = (char *)malloc(sizeof(char) * len);
  strncpy(s, input, len);

  for (size_t i = 0; i < len; ++i) {
    if (DO_LOG)
      printf("%s\n", s);
    exchange(s, i, min_index(s, i, len));
  }

  return s;
}

char *insertion_sort(const char *input, const size_t len) {
  N_OPS = 0;
  char *s = (char *)malloc(sizeof(char) * len);
  strncpy(s, input, len);

  if (DO_LOG)
    printf("%s\n", s);

  for (size_t i = 1; i < len; ++i) {
    for (size_t j = i; j > 0; --j) {
      if (DO_LOG) {
        N_OPS += 1;
        printf("comp: %c %c (%u)\n", s[j], s[j - 1], N_OPS);
      }

      if (s[j] < s[j - 1]) {
        exchange(s, j, j - 1);
        if (DO_LOG)
          printf("%s\n", s);

      } else {
        break;
      }
    }
  }

  return s;
}

char *shell_sort(const char *input, const size_t len) {
  N_OPS = 0;
  char *s = (char *)malloc(sizeof(char) * len);
  strncpy(s, input, len);

  /*
   * https://en.wikipedia.org/wiki/Shellsort#Pseudocode
   * */

  return s;
}

void exchange(char *a, const size_t i1, const size_t i2) {
  if (DO_LOG) {
    N_OPS += 1;
    printf("swap: %c %c (%u)\n", a[i1], a[i2], N_OPS);
  }

  char tmp = a[i1];
  a[i1] = a[i2];
  a[i2] = tmp;
}

static size_t min_index(const char *a, const size_t s, const size_t len) {
  size_t v = s;

  for (size_t i = s + 1; i < len; ++i) {
    if (DO_LOG) {
      N_OPS += 1;
      printf("comp: %c %c (%u)\n", a[i], a[v], N_OPS);
    }

    if (a[i] < a[v])
      v = i;
  }

  return v;
}
