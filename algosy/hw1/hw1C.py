a = 'abcdefghijklmlnopqrstuvwxyz'
d = {}
for c in a:
    d[c] = 0

t = int(input())
ans = []

for i in range(t):
    n = int(input())
    d1 = d.copy()
    for i in range(n):
        s = input()
        for c in s:
            d1[c] += 1
    an = 1
    for c in d1.keys():
        if d1[c] % n != 0:
            an = 0
            break
    ans.append(an)

[print('YES') if an == 1 else print('NO') for an in ans]
