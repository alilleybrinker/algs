// SPDX-License-Identifier: MIT

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void selection_sort(char *, const size_t);
void insertion_sort(char *, const size_t);
void shell_sort(char *, const size_t);
void bubble_sort(char *, const size_t);
void merge_sort(char *, const size_t);
void quick_sort(char *, const size_t);

static void merge_sort_inner(char *, char *, const size_t, const size_t,
                             const size_t);
static void merge(char *, char *, const size_t, const size_t, const size_t);
static void quick_sort_inner(char *, const size_t, const size_t);
static const size_t partition(char *, const size_t, const size_t);
static void exchange(char *, const size_t, const size_t);
static const size_t min_index(const char *, const size_t, const size_t);

void selection_sort(char *s, const size_t len) {
  for (size_t i = 0; i < len; ++i) {
    exchange(s, i, min_index(s, i, len));
  }
}

void insertion_sort(char *s, const size_t len) {
  for (size_t i = 1; i < len; ++i) {
    for (size_t j = i; j > 0; --j) {
      if (s[j] < s[j - 1]) {
        exchange(s, j, j - 1);
      } else {
        break;
      }
    }
  }
}

void shell_sort(char *s, const size_t len) {
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

  for (size_t g = 0; g < n_gaps; ++g) {
    const size_t gap = gaps[g];

    for (size_t offset = 0; offset < gap; ++offset) {
      for (size_t i = offset; i < len; i += gap) {
        const char temp = s[i];
        size_t j = i;

        while (j >= gap && s[j - gap] > temp) {
          s[j] = s[j - gap];

          j -= gap;
        }

        s[j] = temp;
      }
    }
  }
}

void bubble_sort(char *s, const size_t len) {
  bool swapped;
  size_t n = len;

  do {
    swapped = false;

    for (size_t i = 1; i < n; ++i) {
      if (s[i - 1] > s[i]) {
        exchange(s, i - 1, i);
        swapped = true;
      }
    }

    n -= 1;
  } while (swapped);
}

void merge_sort(char *s, const size_t len) {
  char *temp = (char *)malloc(len * sizeof(char));
  merge_sort_inner(s, temp, len, 0, len);
  free(temp);
}

void quick_sort(char *s, const size_t len) { quick_sort_inner(s, 0, len - 1); }

static void merge_sort_inner(char *s, char *temp, const size_t len,
                             const size_t low, const size_t high) {
  if ((high - low) <= 1)
    return;
  const size_t mid = (high + low) / 2;
  merge_sort_inner(s, temp, len, low, mid);
  merge_sort_inner(s, temp, len, mid, high);
  merge(s, temp, low, mid, high);
}

static void merge(char *s, char *temp, const size_t low, const size_t mid,
                  const size_t high) {
  for (size_t i = low; i < high; ++i)
    temp[i] = s[i];

  size_t i = low;
  size_t j = mid;

  for (size_t k = low; k < high; ++k) {
    if (i >= mid) {
      for (; j < high; ++j) {
        s[k] = temp[j];
        k += 1;
      }
      break;
    } else if (j >= high) {
      for (; i < mid; ++i) {
        s[k] = temp[i];
        k += 1;
      }
      break;
    } else if (temp[i] < temp[j]) {
      s[k] = temp[i];
      i += 1;
    } else {
      s[k] = temp[j];
      j += 1;
    }
  }
}

static void quick_sort_inner(char *s, const size_t low, const size_t high) {
  if (high <= low)
    return;

  const size_t mid = partition(s, low, high);
  quick_sort_inner(s, low, mid - 1);
  quick_sort_inner(s, mid + 1, high);
}

static const size_t partition(char *s, const size_t low, const size_t high) {
  size_t i = low;
  size_t j = high + 1;

  while (true) {
    const char pivot = s[low];

    while (s[++i] < pivot) {
      if (i == high)
        break;
    }

    while (pivot < s[--j]) {
      if (j == low)
        break;
    }

    if (i >= j)
      break;

    exchange(s, i, j);
  }

  exchange(s, low, j);

  return j;
}

static void exchange(char *a, const size_t i1, const size_t i2) {
  char tmp = a[i1];
  a[i1] = a[i2];
  a[i2] = tmp;
}

static const size_t min_index(const char *a, const size_t s, const size_t len) {
  size_t v = s;

  for (size_t i = s + 1; i < len; ++i) {
    if (a[i] < a[v])
      v = i;
  }

  return v;
}
