t = int(input())

for i in range(t):
    n = int(input())
    if n <= 30:
        print('NO')
    elif n == 36:
        print('YES')
        print('5 6 10 15')
    elif n == 40:
        print('YES')
        print('6 9 10 15')
    elif n == 44:
        print('YES')
        print('6 10 13 15')
    else:
        print('YES')
        print('6 10 14', n-30)
