// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <alg_sorts.h>

typedef int (*test_fn)();

typedef struct {
    const char *name;
    test_fn f;
} test_t;

int selection_sort_succeeds();
int insertion_sort_succeeds();
bool is_sorted(const char *, const size_t);

int main(int argc, char **argv) {
    const test_t tests[] = {
        {
            .name = "selection_sort_succeeds",
            .f = selection_sort_succeeds,
        },
        {
            .name = "insertion_sort_succeeds",
            .f = insertion_sort_succeeds,
        }
    };

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

int selection_sort_succeeds() {
    const char *text = "THISQUESTION";
    const size_t len = strlen(text);
    const char *sorted_text = selection_sort(text, len);

    int result = EXIT_FAILURE;
    if (is_sorted(sorted_text, len)) {
        result = EXIT_SUCCESS;
    }

    free((char *) sorted_text);
    return result;
}

int insertion_sort_succeeds() {
    const char *text = "THISQUESTION";
    const size_t len = strlen(text);
    const char *sorted_text = insertion_sort(text, len);

    int result = EXIT_FAILURE;
    if (is_sorted(sorted_text, len)) {
        result = EXIT_SUCCESS;
    }

    free((char *) sorted_text);
    return result;
}

bool is_sorted(const char *s, const size_t len) {
    for (size_t i = 0; i < len - 1; ++i) {
        if (s[i] > s[i + 1]) return false;
    }

    return true;
}

