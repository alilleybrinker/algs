
def h(i):
    return (2 * i + 5) % 11

input = [12, 14, 34, 88, 23, 94, 11, 39, 20, 16, 5]
output = [h(i) for i in input]

print(input)
print(output)
print(len(input))

