import sys

def read():
    return sys.stdin.readline()

n, k = map(int, read().split(' '))
arr = []
for i in range(n):
    arr.append(int(read()))

arr.sort(reverse=True)

if sum(arr) < k:
    print(0)
    exit(0)

l = 1
r = sum(arr) // k

def ready_able(x):
    sm = 0
    for a in arr:
        sm += a // x
        if sm >= k:
            break
    return sm >= k


while r - l > 1:
    m = int((l + r) / 2)
    if l == m:
        break
    if ready_able(m):
        l = m
    else:
        r = m

if ready_able(r):
    print(r)
else:
    print(l)