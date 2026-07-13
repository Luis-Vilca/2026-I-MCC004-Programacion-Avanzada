import os
import sys
import matrix1

A = matrix1.Matrix1Int(2,2)
A.Create()

A[0,0] = 10
A[1,1] = 20

print(A[0,0])
print(A[0,1])
print(A[1,0])
print(A[1,1])

print(A)

m2 = matrix1.Matrix1Int()
m2.read("""
2 2
1 2
3 4
""")

m3 = matrix1.Matrix1Int()
m3.read("""
2 2
5 6
7 8
""")

print("m2")
print(m2)

print("m3")
print(m3)

print("m2 + m3")
print(m2 + m3)

print("m2 - m3")
print(m2 - m3)

print("2 * m2")
print(2 * m2)

print("m2 * 2")
print(m2 * 2)

m4 = m2 - m3

Matrix = 5 * m2 + m3 * m4
print(Matrix)
print(Matrix.transpose())

m5 = matrix1.Matrix1Double()
m5.read("""
3 3
1 2 3
0 2 4
5 6 0
""")

print(f"{m5.determinant():.6f}")