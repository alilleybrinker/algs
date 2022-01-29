// SPDX-License-Identifier: MIT

#ifndef ALG_SORTS_H
#define ALG_SORTS_H

#include <stdlib.h>

/**
 * Produces a sorted equivalent of the input array.
 *
 * Requires len be large enough to contain the input array.
 *
 * The returned array must be freed by the caller.
 **/
char *selection_sort(const char *s, const size_t len);

/**
 * Produces a sorted equivalent of the input array.
 *
 * Requires len be large enough to contain the input array.
 *
 * The returned array must be freed by the caller.
 **/
char *insertion_sort(const char *s, const size_t len);

/**
 * Produces a sorted equivalent of the input array.
 *
 * Requires len be large enough to contain the input array.
 *
 * The returned array must be freed by the caller.
 **/
char *shell_sort(const char *s, const size_t len);

#endif
