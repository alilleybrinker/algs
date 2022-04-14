
def karatsuba_multiplication(x, y):
    x_digits = len(str(x))
    y_digits = len(str(y))

    # Base case for the recursion.
    if (x_digits == 1 or y_digits == 1):
        return x * y

    # Figure out where to split.
    n2 = max(x_digits, y_digits) / 2
    factor = int(10 ** n2)

    # Break up the number into parts.
    a = x // factor
    b = x % factor
    c = y // factor
    d = y % factor

    # Calculate the result.
    z2 = karatsuba_multiplication(a, c)
    z0 = karatsuba_multiplication(b, d)
    z1 = karatsuba_multiplication(a + b, c + d) - z2 - z0
    return (z2 * (factor ** 2)) + (z1 * factor) + z0

x = 5822
y = 4104
z = karatsuba_multiplication(x, y)
print(f"{x} * {y} = {z}")
