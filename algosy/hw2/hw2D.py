n = int(input())
arr = [int(el) for el in input().split(' ')]

m = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

for a in arr:
    m[a] += 1

for i in range(9, -1, -1):
    print(str(i)*m[i], end='')
print()