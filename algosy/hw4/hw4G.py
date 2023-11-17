n = int(input())
arr = [int(el) for el in input().split(' ')]

for i in range(1, n):
    if arr[i] < arr[(i-1) // 2]:
        print('NO')
        exit(0)
print('YES')