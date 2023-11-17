class Stack():

    stack = []
    pointer = -1

    def __init__(self):
        for i in range(100000):
            self.stack.append(0)
    
    def push(self, val):
        self.pointer += 1
        self.stack[self.pointer] = val
    
    def pop(self):
        print(self.stack[self.pointer])
        self.pointer -= 1

stack = Stack()
n = int(input())

for i in range(n):
    inp = input().split(' ')
    if len(inp) == 1:
        stack.pop()
    else:
        stack.push(int(inp[1]))
