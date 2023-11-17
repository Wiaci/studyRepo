t = int(input())

for i in range(t):
    n = int(input())
    a = [int(e) for e in input().split()]
    mx = max(a)
    ans = n
    for ai in a:
        if ai != mx:
            ans = 1
            break
    print(ans)
