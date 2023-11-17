from collections import deque
import sys

def input():
    return sys.stdin.readline()

class Queue():

    qq = deque()

    def push(self, val):
        self.qq.appendleft(val)
    
    def pop(self):
        return self.qq.pop()

n = int(input())
q = Queue()
for i in range(n):
    inp = input().split()
    if len(inp) > 1:
        q.push(int(inp[1]))
    else:
        print(q.pop())
