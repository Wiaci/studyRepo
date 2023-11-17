def inv2(l1, l2):
    i, j = 0, 0
    inv = 0
    while i < len(l1) or j < len(l2):
        if i == len(l1):
            j += 1
        elif j == len(l2):
            i += 1
        elif l1[i] <= l2[j]:
            i += 1
        else:
            j += 1
            inv += len(l1) - i
    return inv

def merge(l1, l2, l3):
    i, j, k = 0, 0, 0
    l = []
    inv = 0
    while i < len(l1) or j < len(l2) or k < len(l3):
        if j == len(l2) and k == len(l3):
            l.append(l1[i])
            i += 1
        elif j == len(l2) and i == len(l1):
            l.append(l3[k])
            k += 1
        elif i == len(l1) and k == len(l3):
            l.append(l2[j])
            j += 1
        elif i == len(l1):
            if l2[j] <= l3[k]:
                l.append(l2[j])
                j += 1
            else:
                l.append(l3[k])
                k += 1
        elif j == len(l2):
            if l1[i] <= l3[k]:
                l.append(l1[i])
                i += 1
            else:
                l.append(l3[k])
                k += 1
        elif k == len(l3):
            if l1[i] <= l2[j]:
                l.append(l1[i])
                i += 1
            else:
                l.append(l2[j])
                j += 1
        elif l1[i] <= l2[j] and l1[i] <= l3[k]:
            l.append(l1[i])
            i += 1
        elif l2[j] <= l1[i] and l2[j] <= l3[k]:
            l.append(l2[j])
            j += 1
        else:
            inv += inv2(l1[i:], l2[j:])
            l.append(l3[k])
            k += 1
    return inv, l  

def merge_sort(a, begin, end):
    if begin == end:
        return 0, [a[begin]]
    if end - begin == 1:
        return 0, sorted([a[begin], a[end]])

    m1 = int((begin + end) / 3)
    m2 = int((m1 + 1 + end) / 2)
    inv1, l1 = merge_sort(a, begin, m1)
    inv2, l2 = merge_sort(a, m1 + 1, m2)
    inv3, l3 = merge_sort(a, m2 + 1, end)
    inv4, l = merge(l1, l2, l3)
    return inv1 + inv2 + inv3 + inv4, l

n = int(input())
arr = [int(el) for el in input().split(' ')]

inv, _ = merge_sort(arr, 0, n - 1)
print(inv)