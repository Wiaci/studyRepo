t = int(input())
ans = []

for i in range(t):
    n = int(input())
    s = input()
    c = s[n-1]
    ans.append(c*n)

[print(an) for an in ans]