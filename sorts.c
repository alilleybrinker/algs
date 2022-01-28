
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef DO_LOG
#define DO_LOG false
#endif

char*  selection_sort(const char*, const size_t);
char*  insertion_sort(const char*, const size_t);
void   exchange(char* a, const size_t, const size_t);
size_t min_index(const char*, const size_t, const size_t);

int main(int argc, char** argv) {
    const char* text = "THISQUESTION";
    const size_t len = strlen(text);

    char* sorted_text_ss = selection_sort(text, len);
    printf("using:    selection sort\n");
    printf("original: %s\n", text);
    printf("sorted:   %s\n", sorted_text_ss);
    free(sorted_text_ss);

    printf("\n");

    char* sorted_text_is = insertion_sort(text, len);
    printf("using:    insertion sort\n");
    printf("original: %s\n", text);
    printf("sorted:   %s\n", sorted_text_is);
    free(sorted_text_is);

    return EXIT_SUCCESS;
}

/**
 * Produces a sorted equivalent of the input array.
 *
 * Requires len be large enough to contain the input array.
 *
 * The returned array must be freed by the caller.
 **/
char* selection_sort(const char* input, const size_t len) {
    char* s = (char *) malloc(sizeof(char) * len);
    strcpy(s, input);

    for (size_t i = 0; i < len; ++i)
        exchange(s, i, min_index(s, i, len));

    return s;
}

/**
 * Produces a sorted equivalent of the input array.
 *
 * Requires len be large enough to contain the input array.
 *
 * The returned array must be freed by the caller.
 **/
char* insertion_sort(const char* input, const size_t len) {
    char* s = (char *) malloc(sizeof(char) * len);
    strcpy(s, input);

    for (size_t i = 1; i < len; ++i) {
        for (size_t j = i; j > 0; --j) {
            if (DO_LOG) printf("comp: %c %c\n", s[j], s[j - 1]);

            if (s[j] < s[j - 1]) {
                exchange(s, j, j - 1);
            } else {
                break;
            }
        }
    }

    return s;
}

/**
 * Swap the elements at the two indices in the array.
 **/
void exchange(char* a, const size_t i1, const size_t i2) {
    if (DO_LOG) printf("> swap: %c %c\n", a[i1], a[i2]);

    char tmp = a[i1];
    a[i1] = a[i2];
    a[i2] = tmp;
}

/**
 * Compute the index of the minimum in the given range from s to len
 * in the array.
 **/
size_t min_index(const char* a, const size_t s, const size_t len) {
    size_t v = s;

    for (size_t i = s + 1; i < len; ++i) {
        if (DO_LOG) printf("comp: %c %c\n", a[i], a[v]);
        if (a[i] < a[v]) v = i;
    }

    return v;
}

