from enum import Enum, unique, auto

@unique
class HeapMode(Enum):
	MIN = auto()
	MAX = auto()

class Heap:
	def __init__(self, mode):
		self.data = []
		self.mode = mode

	def insert(self, val):
		self.data.append(val)
		self.swim(self.last_leaf())\

	def insert_all(self, arr):
		for item in arr:
			self.insert(item)

	def peekroot(self):
		if len(self.data) == 0:
			return None
		
		return self.data[self.root()]

	def poproot(self):
		root = self.peekroot()
		self.rmroot()
		return root

	def rmroot(self):
		last_leaf = self.last_leaf()
		root = self.root()
		self.exchange(root, last_leaf)
		self.data.pop()
		self.sink(root)

	def sink(self, idx):
		root = idx

		while True:
			left = self.left_child(root)
			right = self.right_child(root)
			swap = root
			end = len(self.data)

			if (left < end) and (self.compare(self.data[swap], self.data[left])):
				swap = left

			if (right < end) and (self.compare(self.data[swap], self.data[right])):
				swap = right

			if swap == root:
				return

			self.exchange(root, swap)
			root = swap

	def swim(self, idx):
		child = idx

		while True:
			parent = self.parent(child)

			if parent < 0:
				return

			if self.compare(self.data[child], self.data[parent]):
				return

			self.exchange(child, parent)
			child = parent

	def compare(self, a, b):
		if self.mode is HeapMode.MAX:
			return a < b
		elif self.mode is HeapMode.MIN:
			return a > b
		else:
			return False

	def parent(self, idx):
		return (idx - 1) // 2

	def left_child(self, idx):
		return (idx * 2) + 1

	def right_child(self, idx):
		return self.left_child(idx) + 1

	def last_leaf(self):
		return len(self.data) - 1

	def root(self):
		return 0

	def size(self):
		return len(self.data)

	def exchange(self, a, b):
		temp = self.data[a]
		self.data[a] = self.data[b]
		self.data[b] = temp

class MaxHeap(Heap):
	def __init__(self):
		super().__init__(HeapMode.MAX)

class MinHeap(Heap):
	def __init__(self):
		super().__init__(HeapMode.MIN)

def max_m(stream, m):
	largest = MinHeap()

	for val in stream:
		root = largest.peekroot()

		if root is None:
			largest.insert(val)
			continue
		
		if root < val:
			if largest.size() >= m:
				largest.poproot()
			
			largest.insert(val)

	return largest.data

stream = [2, 9, -1, 7, 55]

print(max_m(stream, 2))
