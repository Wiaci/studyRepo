t = int(input())

for i in range(t):
    n, m = map(int, input().split(' '))
    ans = 0
    for j in range(n-1):
        if input()[-1] != 'D':
            ans += 1
    s = input()
    for j in range(m-1):
        if s[j] != 'R':
            ans += 1
    print(ans)