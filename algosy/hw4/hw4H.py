import sys
def input():
    return sys.stdin.readline()

heap = []

def swap(a, b):
    m = heap[a]
    heap[a] = heap[b]
    heap[b] = m

def insert(val):
    i = len(heap)
    heap.append(val)
    parent = int((i-1) / 2)
    while heap[i] > heap[parent]:
        swap(i, parent)
        i = parent
        parent = int((i-1) / 2)

def down(i):
    left_child = i * 2 + 1
    right_child = i * 2 + 2
    if right_child < len(heap):
        mx = left_child
        if heap[right_child] > heap[mx]:
            mx = right_child
        if heap[mx] <= heap[i]:
            return
        swap(i, mx)
        down(mx)
    elif left_child < len(heap):
        if heap[left_child] > heap[i]:
            swap(i, left_child)
        return
    else:
        return

def extract():
    swap(0, -1)
    val = heap.pop(-1)
    down(0)
    return val

n = int(input())
for i in range(n):
    inp = input().split(' ')
    if len(inp) == 2:
        insert(int(inp[1]))
    else:
        print(extract())
