t = int(input())

for i in range(t):
    flags = [0 for i in range(int(input()) + 1)]
    arr = [int(el) for el in input().split(' ')]
    for a in arr:
        if flags[a] != 1:
            print(a, end=' ')
            flags[a] = 1
    print()

