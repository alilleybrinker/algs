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
bool sort_shell_succeeds();
bool sort_bubble_succeeds();
bool sort_merge_succeeds();
bool sort_quick_succeeds();
bool select_quick_succeeds();
bool test_sort_function(sort_fn);

int main(int argc, char **argv) {
  const test_t tests[] = {{
                              .name = "sort_selection_succeeds",
                              .f = sort_selection_succeeds,
                          },
                          {
                              .name = "sort_insertion_succeeds",
                              .f = sort_insertion_succeeds,
                          },
                          {
                              .name = "sort_shell_succeeds",
                              .f = sort_shell_succeeds,
                          },
                          {
                              .name = "sort_bubble_succeeds",
                              .f = sort_bubble_succeeds,
                          },
                          {
                              .name = "sort_merge_succeeds",
                              .f = sort_merge_succeeds,
                          },
                          {
                              .name = "sort_quick_succeeds",
                              .f = sort_quick_succeeds,
                          },
                          {
                              .name = "select_quick_succeeds",
                              .f = select_quick_succeeds,
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

bool sort_shell_succeeds() { return test_sort_function(shell_sort); }

bool sort_bubble_succeeds() { return test_sort_function(bubble_sort); }

bool sort_merge_succeeds() { return test_sort_function(merge_sort); }

bool sort_quick_succeeds() { return test_sort_function(quick_sort); }

bool select_quick_succeeds() {
  // Setup
  int orig[] = {9, 8, 6, 4, -100};
  const size_t len = sizeof(orig) / sizeof(orig[0]);
  const size_t blen = sizeof(int) * len;
  int *a = (int *)malloc(blen);
  memcpy(a, orig, blen);
  const size_t k = (len + 1) / 2;
  const int expected = 6;

  // Run the test
  int result = EXIT_FAILURE;
  int output = quick_select(a, len, k);
  if (output == expected)
    result = EXIT_SUCCESS;

  // Cleanup
  free(a);
  return result;
}

bool test_sort_function(sort_fn f) {
  const char *expected = "abcdeeefghhijklmnoooopqrrsttuuvwxyz";

  const char *text = "thequickbrownfoxjumpsoverthelazydog";
  const size_t len = strlen(text);

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
