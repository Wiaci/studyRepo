import sys
def input():
    return sys.stdin.readline()

t = int(input())

for j in range(t):
    n = int(input())
    arr = [int(el) for el in input().split(' ')]

    begin = 0
    end = n-1
    found = False
    for i in range(n, 0, -1):
        if arr[begin] == i:
            begin += 1
            continue
        if arr[end] == i:
            end -= 1
            continue
        found = True
        print('YES')
        for k in range(n):
            if arr[k] == i:
                print(k, k+1, k+2)
                break
        break
    if not found:
        print('NO')