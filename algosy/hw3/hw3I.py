import sys
def input():
    return sys.stdin.readline()

class Stack():
 
    stack = []
    pointer = -1
 
    def __init__(self):
        for i in range(1000000):
            self.stack.append(10000000000)
    
    def push(self, val):
        self.pointer += 1
        self.stack[self.pointer] = val
    
    def pop(self):
        ret = self.stack[self.pointer]
        self.pointer -= 1 
        return ret
    
    def top(self):
        return self.stack[self.pointer]


class MinStack():
    stack = Stack()
    min_stack = Stack()

    def push(self, val):
        self.stack.push(val)
        if val <= self.min_stack.top():
            self.min_stack.push(val)

    def pop(self):
        if self.min_stack.top() == self.stack.pop():
            self.min_stack.pop()
    
    def min(self):
        return self.min_stack.top()

n = int(input())
st = MinStack()

for i in range(n):
    inp = input().split(' ')
    if len(inp) > 1:
        st.push(int(inp[1]))
    elif inp[0] == '2\n':
        st.pop()
    else:
        print(st.min())