t = int(input())
ans = []

for i in range(t):
    n, k = map(int, input().split())
    a = [int(e) for e in input().split()]
    mx = max(a)
    for i in range(len(a)):
        a[i] = mx - a[i]
    if k % 2 == 0:
        mx = max(a)
        for i in range(len(a)):
            a[i] = mx - a[i]
    print(*a)
    #ans.append(" ".join(a))

#print('\n'.join(ans))