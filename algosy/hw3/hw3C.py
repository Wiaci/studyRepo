import sys

def binary_search_left(arr, x, l, r):
    while l < r:
        m = int((l + r) / 2)
        if arr[m] < x:
            l = m + 1
        else:
            r = m - 1
    return l

def binary_search_right(arr, x, l, r):
    while l < r:
        m = int((l + r) / 2)
        if arr[m] <= x:
            l = m + 1
        else:
            r = m - 1
    return l

def read():
    return sys.stdin.readline()

n = int(read())
arr = [int(el) for el in read().split(' ')]
arr.sort()
k = int(read())

for i in range(k):
    l, r = map(int, read().split(' '))
    if n == 1:
        print(1 if arr[0] >= l and arr[0] <= r else 0)
        continue
    pl, pr = binary_search_left(arr, l, 0, n-1), binary_search_right(arr, r, 0, n-1)
    if arr[pl] < l:
        pl += 1
    if arr[pr] > r:
        pr -= 1
    print(pr - pl + 1 if pl <= pr else 0)
