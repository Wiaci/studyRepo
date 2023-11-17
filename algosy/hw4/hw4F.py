import sys
from collections import deque

def input():
    return sys.stdin.readline()

n = int(input())
left = deque()
right = deque()

for i in range(n):
    inp = input().split(' ')
    if len(inp) > 1:
        val = int(inp[1])
        if inp[0] == '+':
            if len(right) > len(left):
                left.append(right.popleft())
            right.append(val)
        else:
            if len(right) > len(left):
                left.append(right.popleft())
            right.appendleft(val)
    else:
        if len(right) > len(left):
            left.append(right.popleft())
        print(left.popleft())    
