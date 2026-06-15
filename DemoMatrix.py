import os
import sys

print(os.getcwd())
print(sys.path)

import matrix1

A = matrix1.Matrix1(2,2)
A.Create()

A[0,0] = 10
A[1,1] = 20

print(A[0,0])
print(A[0,1])
print(A[1,0])
print(A[1,1])

print(A)

m2 = matrix1.Matrix1()
m2.read("""
2 2
1 2
3 4
""")

m3 = matrix1.Matrix1()
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

A = matrix1.Matrix1()
A.read("""
2 2
1 2
3 4
""")

B = matrix1.Matrix1()
B.read("""
2 2
5 6
7 8
""")

C = A * B

print(C)

Matrix = 5 * m2 + m3 * B
print(Matrix)