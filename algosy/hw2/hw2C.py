def merge(l1, l2):
    l = []
    i, j = 0, 0
    while i < len(l1) or j < len(l2):
        if i == len(l1):
            l.append(l2[j])
            j += 1
        elif j == len(l2):
            l.append(l1[i])
            i += 1
        elif l1[i] < l2[j]:
            l.append(l1[i])
            i += 1
        else:
            l.append(l2[j])
            j += 1
    return l


def merge_sort(a, begin, end):
    if begin == end:
        return [a[begin]]
    m = int((begin + end) / 2)
    return merge(merge_sort(a, begin, m), merge_sort(a, m + 1, end))
 
n = int(input())
arr = [int(el) for el in input().split(' ')]
 
[print(i, end=' ') for i in merge_sort(arr, 0, n - 1)]