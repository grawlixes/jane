from random import randint

S = 100
D = 1
N = 20

BUY = 98
SELL = 100

prof = 0
for i in range(100000):
    p = S
    prof1 = 0
    b = False
    for j in range(20):
        r = randint(-1, 1)
        if r == -1:
            p -= D
            if p == BUY and not b:
                b = True
        elif r == 0:
            pass
        else:
            p += D
            if p == SELL and b:
                b = False
                prof1 += (SELL - BUY)

    prof1 -= b * (BUY - p)
    
    prof += float(prof1) / 100000

print(prof)
print(prof * 100000)
