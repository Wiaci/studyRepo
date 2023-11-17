t = int(input())
ans = []

for i in range(t):
    n = int(input())
    line = input().split(' ')
    a = [int(l) for l in line]
    if a[0] + a[1] <= a[-1]:
        ans.append("1 2 " + str(len(a)))
    else:
        ans.append("-1")

[print(i) for i in ans]
