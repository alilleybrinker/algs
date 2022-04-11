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
		self.swim(self.last_leaf())

	def insert_all(self, arr):
		for item in arr:
			self.insert(item)

	def peekroot(self):
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

def avg(vals):
	return sum(vals) / len(vals)

def l_medians(stream):
	if len(stream) <= 0:
		yield None

	max_small = MaxHeap()
	min_large = MinHeap()
	median = stream[0]

	for elem in stream:
		mh_len = len(max_small.data)
		ml_len = len(min_large.data)

		# Min-large is smaller...
		if ml_len < mh_len:
			if elem < median:
				top = max_small.poproot()
				min_large.insert(top)
				max_small.insert(elem)
			else:
				min_large.insert(elem)

			median = max_small.peekroot()
			yield median

		# Max-small is smaller...
		elif mh_len < ml_len:
			if elem > median:
				top = min_large.poproot()
				max_small.insert(top)
				min_large.insert(elem)
			else:
				max_small.insert(elem)

			median = max_small.peekroot()
			yield median

		# They're the same size...
		else:
			if elem < median:
				max_small.insert(elem)
				median = max_small.peekroot()
				yield median
			else:
				min_large.insert(elem)
				median = min_large.peekroot()
				yield median

stream = [2, 9, -1, 7, 55]

for median in l_medians(stream):
	print(median)
