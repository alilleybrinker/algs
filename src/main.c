// SPDX-License-Identifier: MIT

#include <alg_sorts.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef bool (*test_fn)();
typedef void (*sort_fn)(char *, size_t);

typedef struct {
  const char *name;
  test_fn f;
} test_t;

bool sort_selection_succeeds();
bool sort_insertion_succeeds();
bool test_sort_function(sort_fn);
bool is_sorted(const char *, const size_t);

int main(int argc, char **argv) {
  const test_t tests[] = {{
                              .name = "sort_selection_succeeds",
                              .f = sort_selection_succeeds,
                          },
                          {
                              .name = "sort_insertion_succeeds",
                              .f = sort_insertion_succeeds,
                          }};

  const size_t num_tests = sizeof(tests) / sizeof(tests[0]);

  for (size_t i = 0; i < num_tests; ++i) {
    const test_t test = tests[i];
    const int result = test.f();

    char *outcome;
    if (result == EXIT_SUCCESS) {
      outcome = "PASSED";
    } else {
      outcome = "FAILED";
    }

    printf("test: %s... %s\n", test.name, outcome);
  }
}

bool sort_selection_succeeds() { return test_sort_function(selection_sort); }

bool sort_insertion_succeeds() { return test_sort_function(insertion_sort); }

bool test_sort_function(sort_fn f) {
  const char *expected = "abcdeeefghhijklmnoooopqrrsttuuvwxyz";

  const char *text = "thequickbrownfoxjumpsoverthelazydog";
  const char len = strlen(text);

  char *s = (char *)malloc(sizeof(char) * len);
  strncpy(s, text, len);

  // Sort the string in-place.
  f(s, len);

  int result = EXIT_FAILURE;
  if (strncmp(expected, s, len) == 0)
    result = EXIT_SUCCESS;

  free(s);
  return result;
}

bool is_sorted(const char *s, const size_t len) {
  for (size_t i = 0; i < len - 1; ++i) {
    if (s[i] > s[i + 1])
      return false;
  }

  return true;
}
