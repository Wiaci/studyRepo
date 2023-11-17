c = float(input())

def f(x):
    return x*x + x**(1/2) - c

l, r = 0, 100000

eps = 0.000001

while r - l > eps:
    m = (r + l) / 2
    if f(m) * f(l) < 0:
        r = m
    else:
        l = m

print((l + r) / 2)
