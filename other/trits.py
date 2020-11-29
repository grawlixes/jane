NUM = 524293
def numberToBase(n, b):
    if n == 0:
        return [0]
    digits = []
    while n:
        digits.append(int(n % b))
        n //= b
    return digits[::-1]

# 4**i - sum(4**j) through sum(4**j) + 4**i are good
def isTrit(n, p = False):
    b4 = numberToBase(n, 4)
    if p:
        print(n, b4)
    carry = 0
    for i in range(len(b4) - 1, -1, -1):
        b4[i] += carry
        og = b4[i]
        if b4[i] >= 3:
            b4[i] -= 4
        
        carry = 1 if og >= 3 else 0

    if p:
        print("new", n, b4)
    return 2 not in b4  
print(isTrit(NUM, True))
exit()
bad = 0
for NUM in range(3, 4000):
    if isTrit(NUM):
        continue

    i = 2
    while True:
        if isTrit(i) and \
           isTrit(i * NUM):
               break
        i += 1
        if i == 20000:
            break

    if not (isTrit(i) and isTrit(i * NUM)):
        bad += 1
        print("NOT", NUM, isTrit(NUM, True))
    else:
        pass
    #print("YES", NUM, "TO",i, i*NUM, isTrit(NUM, True))

print("BAD: ", bad)
