from collections import deque
import sys

def input():
    return sys.stdin.readline()

n = int(input())
ds = [deque() for i in range(150000)]

for i in range(n):
    cmd = input().split(' ')
    if cmd[0] == 'pushfront':
        a = int(cmd[1]) - 1
        b = int(cmd[2])
        ds[a].appendleft(b)
    if cmd[0] == 'pushback':
        a = int(cmd[1]) - 1
        b = int(cmd[2])
        ds[a].append(b)
    if cmd[0] == 'popfront':
        a = int(cmd[1]) - 1
        print(ds[a].popleft())
    if cmd[0] == 'popback':
        a = int(cmd[1]) - 1
        print(ds[a].pop())