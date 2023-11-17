n, k = map(int, input().split(' '))
arr = [int(el) for el in input().split(' ')]
arr.sort()

total = 0

for i in range(k): 
    if total + arr[i] <= n:
        total += arr[i]
    else:
        print(i)
        break    
    if i == k - 1:
        print(k)