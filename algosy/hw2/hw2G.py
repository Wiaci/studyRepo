def merge(l1, l2):
    l = []
    i, j = 0, 0
    inv = 0
    while i < len(l1) or j < len(l2):
        if i == len(l1):
            l.append(l2[j])
            j += 1
        elif j == len(l2):
            l.append(l1[i])
            i += 1
        elif l1[i] <= l2[j]:
            l.append(l1[i])
            i += 1
        else:
            l.append(l2[j])
            j += 1
            inv += len(l1) - i
    return inv, l


def merge_sort(a, begin, end):
    if begin == end:
        return 0, [a[begin]]
    m = int((begin + end) / 2)
    inv1, l1 = merge_sort(a, begin, m)
    inv2, l2 = merge_sort(a, m + 1, end)
    inv3, l = merge(l1, l2)
    return inv1 + inv2 + inv3, l
 
n = int(input())
arr = [int(el) for el in input().split(' ')]
 
inv, _ = merge_sort(arr, 0, n - 1)
print(inv)