// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alg_sorts.h>

int main(int argc, char **argv) {
  const char *text = "THISQUESTION";
  const size_t len = strlen(text);

  char *sorted_text_ss = selection_sort(text, len);
  printf("using:    selection sort\n");
  printf("original: %s\n", text);
  printf("sorted:   %s\n", sorted_text_ss);
  free(sorted_text_ss);

  printf("\n");

  char *sorted_text_is = insertion_sort(text, len);
  printf("using:    insertion sort\n");
  printf("original: %s\n", text);
  printf("sorted:   %s\n", sorted_text_is);
  free(sorted_text_is);

  return EXIT_SUCCESS;
}

