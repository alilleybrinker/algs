
import copy

def d5_idx(arr, low, high):
    return max((len(sorted(copy.deepcopy(arr[low:high]))) // 5) - 1, low)

def quicksort(arr):
	def exchange(arr, a, b):
		temp = arr[a]
		arr[a] = arr[b]
		arr[b] = temp

	def partition(arr, low, high):
		i = low
		j = high - 1

		while True:
			pivot = arr[low]

			while arr[i] < pivot:
				i += 1
				if i == high:
					break

			while pivot < arr[j]:
				j -= 1

				if j == low:
					break

			if i >= j:
				break

			exchange(arr, i, j)

		exchange(arr, low, j)
		return j

	def quick_sort_inner(arr, low, high):
		if high <= low:
			return

        # Find d5(S) (the index of the 1st-quintile value in S slice)
        # Swap the value at that index with the start of the slice.
		d5i = d5_idx(arr, low, high)
		exchange(arr, low, d5i)

		mid = partition(arr, low, high)
		quick_sort_inner(arr, low, mid - 1)
		quick_sort_inner(arr, mid + 1, high)

	quick_sort_inner(arr, 0, len(arr))

arr      = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]
expected = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

quicksort(arr)

print(arr)
print(expected)
