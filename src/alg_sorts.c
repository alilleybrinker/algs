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

void selection_sort(char *, const size_t);
void insertion_sort(char *, const size_t);
void shell_sort(char *, const size_t);

static void exchange(char *, const size_t, const size_t);
static size_t min_index(const char *, const size_t, const size_t);

void selection_sort(char *s, const size_t len) {
  N_OPS = 0;

  for (size_t i = 0; i < len; ++i) {
    if (DO_LOG)
      printf("%s\n", s);
    exchange(s, i, min_index(s, i, len));
  }
}

void insertion_sort(char *s, const size_t len) {
  N_OPS = 0;

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
}

void shell_sort(char *s, const size_t len) {
  N_OPS = 0;

  /**
   * This code is adapted from the pseudocode in the Wikipedia article
   * for Shell sort. Strangely, most other resources for implementing Shell
   * sort solely cover the original Shell sequence of N/2, N/4, ..., 1,
   * which isn't a very good sequence, and which is implemented in a
   * slightly different manner from the sequence shown here.
   *
   * https://en.wikipedia.org/wiki/Shellsort#Pseudocode
   * */

  const size_t gaps[] = {5, 3, 1};
  const size_t n_gaps = sizeof(gaps) / sizeof(gaps[0]);

  if (DO_LOG) {
    printf("%s\n", s);
  }

  for (size_t g = 0; g < n_gaps; ++g) {
    const size_t gap = gaps[g];

    for (size_t offset = 0; offset < gap; ++offset) {
      for (size_t i = offset; i < len; i += gap) {
        const char temp = s[i];
        size_t j = i;

        while (j >= gap && s[j - gap] > temp) {
          if (DO_LOG) {
            N_OPS += 1;
            printf("comp: %c %c (%u)\n", temp, s[j - gap], N_OPS);
            N_OPS += 1;
            printf("swap: %c %c (%u)\n", s[j], s[j - gap], N_OPS);
          }

          s[j] = s[j - gap];

          if (DO_LOG) {
            printf("%s\n", s);
          }

          j -= gap;
        }

        s[j] = temp;
      }
    }
  }
}

void bubble_sort(char *s, const size_t len) {

}

static void exchange(char *a, const size_t i1, const size_t i2) {
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
