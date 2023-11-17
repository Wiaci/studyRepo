class Stack():
 
    stack = []
    pointer = -1
 
    def __init__(self):
        for i in range(100000):
            self.stack.append('')
    
    def push(self, val):
        self.pointer += 1
        self.stack[self.pointer] = val
    
    def pop(self):
        if self.pointer < 0:
            return '-'
        ret = self.stack[self.pointer]
        self.pointer -= 1 
        return ret
 
stack = Stack()
str = input()
 
for c in str:
    if c in ['(', '[', '{']:
        stack.push(c)
    else:
        if not (c == ')' and stack.pop() == '(' or c == ']' and stack.pop() == '[' or c == '}' and stack.pop() == '{'):
            print('NO')
            exit(0)

print('YES') if stack.pointer < 0 else print('NO')