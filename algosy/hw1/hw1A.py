t = int(input())

ans = []

for i in range(t):
    line = input().split(' ')
    a = int(line[0])
    b = int(line[1])
    turns = abs(a - b) // 10
    if (a - b) % 10 != 0:
        turns += 1
    ans.append(turns)

for a in ans:
    print(a)