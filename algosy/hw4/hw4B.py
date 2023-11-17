t = int(input())
for i in range(t):
    l = list(input())
    count = 0
    found = True
    while len(l) > 1 and found:
        found = False
        i = 0
        while i < len(l)-1:
            if l[i] != l[i+1]:
                found = True
                l.pop(i)
                l.pop(i)
                count += 1
                i -= 1
            i += 1
    print('DA') if count % 2 == 1 else print('NET')
    