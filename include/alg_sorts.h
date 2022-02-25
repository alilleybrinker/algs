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

/**
 * Sorts the provided array using the bubble sort algorithm.
 *
 * This function sorts the array in-place, modifying the buffer
 * passed-in directly. `len` must be equal to or less than the
 * actual length of the buffer.
 **/
void bubble_sort(char *s, const size_t len);

/**
 * Sorts the provided array using the merge sort algorithm.
 *
 * This function sorts the array in-place, modifying the buffer
 * passed-in directly. `len` must be equal to or less than the
 * actual length of the buffer.
 **/
void merge_sort(char *s, const size_t len);

/**
 * Sorts the provided array using the quick sort algorithm.
 *
 * This function sorts the array in-place, modifying the buffer
 * passed-in directly. `len` must be equal to or less than the
 * actual length of the buffer.
 **/
void quick_sort(char *s, const size_t len);

/**
 * Select the kth-largest element from the array.
 *
 * This function implements the "quickselect" algorithm, using
 * the same `partition` function used to implement `quick_sort`.
 */
const int quick_select(int *s, const size_t len, const size_t k);

#endif
