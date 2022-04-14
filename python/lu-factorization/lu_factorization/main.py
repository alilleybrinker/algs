import numpy as np

def lu_decomposition(mat):
    n, m = mat.shape
    
    if n != m:
        raise Exception("matrix must be square") 
    
    for k in range(n):
        for i in range(k + 1, n):
            mat[i, k] = mat[i, k] / mat[k, k]

        for i in range(k + 1, n):
            for j in range(k + 1, n):
                mat[i, j] = mat[i, j] - mat[i, k] * mat[k, j]

mat = np.array([
    [ 1.,  0.,  0.],
    [ 4.,  1.,  0.],
    [-6.,  5.,  1.],
])

print("original")
print(mat)
print()
lu_decomposition(mat)
print("decomposed")
print(mat)
