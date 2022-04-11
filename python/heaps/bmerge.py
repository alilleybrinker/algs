
def smallest_bmerge(arrs):
    sequence = []

    current = arrs

    # While there's at least 2 remaining to process...
    while len(current) >= 2:
        next = []

        # Go through them in pairs...
        for idx in range(0, len(current), 2):
            # Get the two arrays.
            arr_1 = current[idx]
            arr_2 = current[idx + 1]

            # Add them to the sequence.
            sequence.append((str(arr_1), str(arr_2)))
            # Record their result for the next round...
            next.append(f"({arr_1})({arr_2})")

        # Replace "current" with the "next" round.
        current = next

    return sequence

print(smallest_bmerge([7, 3, 4, 3]))
