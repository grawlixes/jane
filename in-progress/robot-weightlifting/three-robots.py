from math import log10

lower = 0
higher = 1
printThird = True 
printSecond = not True
N = 100
N2 = 100000000
best = 0
ret = 0

# rN = the Nth robot
# pN = probability that the Nth robot succeeds its lift
# wN = probability that the Nth robot wins the championship

def probFirstWins(p1, p2, p3):
    win = None
    tie = (1 - p1) * (1 - p2) * (1 - p3)
    # r1 is lifting the most
    if p1 <= min(p2, p3):
        win = p1
    # r1 is lifting the middle amount
    elif min(p2, p3) < p1 and p1 <= max(p2, p3):
        win = p1 * (1 - min(p2, p3))
        #print("1st correct")
    # r1 is lifting 0, hoping r2 and r3 both fail
    # no tie because r1 can't possibly fail to lift 0
    else:
        win = p1 * (1 - p2) * (1 - p3)

    return win * (1 / (1 - tie))

def probSecondWins(p1, p2, p3, coeff = 1):
    win = None
    tie = (1 - p1) * (1 - p2) * (1 - p3)
    
    # p2 is less than both, could be equal to p3
    if p2 < p1 and p2 <= p3:
        win = p2
    # p2 is greater than both, or equal to p1
    elif p2 > p3 and p2 >= p1:
        #print("2nd correct")
        win = p2 * (1 - p1) * (1 - p3)
    # p2 is in the middle, and p1 is at the lower end, so we don't want it to succeed
    elif p1 <= p3:
        win = p2 * (1 - p1)
    # p2 in the middle and p3 is at the lower end
    else:
        win = p2 * (1 - p3)

    return win * (1 / (1 - tie))

# Idea
# First of all, we don't care about the actual value of any robot's weight at all. We can think solely in terms of the probability that each robot can lift that weight, because we have a vague idea about its distribution (continuous and strictly decreasing).
# we want a probability to six significant figures. Since it must be between 0 and 1, that means 10**6 = 1 million real numbers in the solution space. 
# Given p2 and p3, we can find both p1 and r1 in essentially O(1) time. However, we can't just try every value for p3 and p2, because there are over 5*10**11 = 500 billion elements in that space accounting for symmetry. That'd be too slow even with a perfect O(1) calculation for the third robot.
# 1 million elements isn't bad to try for one robot, though - so let's try every possible value for p3. If we know p3, r2 has 2 choices for p2: p2 < p3 or p2 >= p3. Quick side note: I say p2 >= p3 because r2 can lift an amount of weight that makes p2 arbitrarily smaller than p3, since r2 decides its weight after r3 and both p2 and p3 are real numbers. r1 can do this to r2 and r3 too, which puts r3 at a pretty major disadvantage. Intuitively, the answer (w3) will probably be low because of this.
# Back on topic - for both of r2's choices, if you consider the graph of w2 against a domain of p2, it would look like an upside-down V. 
pw = 0
bestWin = 0
for p3 in map(lambda n: n / N, range(1, N + 1)):
    if p3 < lower:
        continue
    if p3 > higher:
        break
    
    bestW2 = 0
    curW3 = 0
    bestP2 = 0
    for p2 in map(lambda n: n / N2, range(1, N2 + 1)):
        bestW1 = 0
        worstW2 = 0
        bp1 = None
        for p1 in (0, p3, p2):
            w1 = probFirstWins(p1, p2, p3)
            if w1 > bestW1:
                bestW1 = w1
                worstW2 = probSecondWins(p1, p2, p3)
                bp1 = p1

        if worstW2 > bestW2:
            bestW2 = worstW2
            curW3 = 1 - bestW2 - w1
            bestP2 = p2

        if printSecond and len(str(p2)) <= log10(N2) + 2:
            print("r2", format(p2, "." + str(int(log10(N2))) + "f"), worstW2)
            

    if bestWin < curW3:
        bestWin = curW3
        pw = p3

    if printThird and len(str(p3)) <= log10(N) + 2:
        print("r3", format(p3, "." + str(int(log10(N))) + "f"), curW3, "r2 chose", bestP2)
        print('\n')

print('\n')
print(pw, bestWin)
