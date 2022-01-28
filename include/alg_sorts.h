
#ifndef SORTS_H
#define SORTS_H

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
 * Swap the elements at the two indices in the array.
 **/
void exchange(char *a, const size_t i1, const size_t i2);

/**
 * Compute the index of the minimum in the given range from s to len
 * in the array.
 **/
size_t min_index(const char *s, const size_t i1, const size_t i2);

#endif

