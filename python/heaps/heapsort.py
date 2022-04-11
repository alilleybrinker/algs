import math

def heapsort(arr):
	# Turn the array into a heap.
	make_heap(arr)

	# Start at the end.
	end = len(arr) - 1

	# Until we've reached the beginning...
	while end > 0:
		# Swap the first element with the end.
		exchange(arr, 0, end)
		
		# Step forward one.
		end -= 1

		# Sink the new root to where it should be, which
		# maintains the heap property. The next iteration,
		# the root will once again be the largest element
		# in the array.
		sink(arr, 0, end)

def make_heap(arr):
	# Index of the last element.
	l = len(arr) - 1
	# Start at the parent of the last element.
	start = parent(l)

	# Everything from the parent of the last element to the
	# first element is a parent, so we just sink all of them,
	# working from the end.
	#
	# The result is a valid heap.
	while start >= 0:
		sink(arr, start, l)
		start -= 1

def sink(arr, start, end):
	# Start at the root.
	root = start

	while True:
		# Get the left and right child indices.
		left = left_child(root)
		right = right_child(root)
		
		# Track what we're planning to swap with.
		swap = root

		# If there's a left child, and it's larger, plan
		# to swap with it.
		if (left <= end) and (arr[swap] < arr[left]):
			swap = left
			
		# If there's a right child, and it's larger, plan
		# to swap with it.
		if (right <= end) and (arr[swap] < arr[right]):
			swap = right

		# If we're not swapping with a child, then we're done.
		if swap == root:
			return

		# Otherwise, swap the root with one of its children.
		# Make that child the new root, and go again.
		exchange(arr, root, swap)
		root = swap

def parent(idx):
	return math.floor((idx - 1) / 2)

def left_child(idx):
	return (2 * idx) + 1

def right_child(idx):
	return left_child(idx) + 1

def exchange(arr, start, end):
	temp = arr[start]
	arr[start] = arr[end]
	arr[end] = temp

arr = [9, 7, 3, 6, 2, 7, 3, 2, 1, 6, 7]
heapsort(arr)
print(arr)
