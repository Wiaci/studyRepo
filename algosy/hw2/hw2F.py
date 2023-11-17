import functools

n = int(input())
teams = []
for i in range(n):
    s, t = map(int, input().split(' '))
    teams.append((i+1, s, t))

def comparator(team1, team2):
    i1, s1, t1 = team1
    i2, s2, t2 = team2
    if s1 < s2:
        return 1
    elif s1 > s2:
        return -1
    elif t1 < t2:
        return -1
    elif t1 > t2:
        return 1
    elif i1 < i2:
        return -1
    else:
        return 1

[print(t[0], end=' ') for t in sorted(teams, key=functools.cmp_to_key(comparator))]