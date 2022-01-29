// SPDX-License-Identifier: MIT

#ifndef ALG_SORTS_H
#define ALG_SORTS_H

#include <stdlib.h>

/**
 * Sorts the provided array using the selection sort algorithm.
 *
 * This function sorts the array in-place, modifying the buffer
 * passed-in directly. `len` must be equal to or less than the
 * actual length of the buffer.
 **/
void selection_sort(char *s, const size_t len);

/**
 * Sorts the provided array using the insertion sort algorithm.
 *
 * This function sorts the array in-place, modifying the buffer
 * passed-in directly. `len` must be equal to or less than the
 * actual length of the buffer.
 **/
void insertion_sort(char *s, const size_t len);

/**
 * Sorts the provided array using the Shell sort algorithm.
 *
 * This function sorts the array in-place, modifying the buffer
 * passed-in directly. `len` must be equal to or less than the
 * actual length of the buffer.
 **/
void shell_sort(char *s, const size_t len);

#endif
