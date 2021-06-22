import util
from functools import reduce

# Bracket placement of each team.
brackets = [[1, 16], [8, 9], [5, 12], [4, 13], [6, 11], [3, 14], [7, 10], [2, 15]]
# Location of each team in the brackets 2d array for swapping.
loc = {}
for i in range(8):
    for j in range(2):
        loc[brackets[i][j]] = (i, j)

# odds that team t wins game g in the current bracket
def simulate(t, g):
    if g == 1:
        opp = brackets[loc[t][0]][1 - loc[t][1]]
        return (opp, t + opp)
    else:
        i, j = loc[t]
        opps = []
        # make a list of *all* the teams that team t may have to play against in game g
        if g == 2:
            mul = -1 if i % 2 else 1
            opps = brackets[i + mul]
        elif g == 3:
            # welcome to hell
            mul = -1 if (i // 2) % 2 else 1
            offset = mul * (1 if (mul == 1) ^ (i % 2) else 0)
            opps = brackets[i + offset + mul] + brackets[i + offset + mul*2]
        else:
            r = range(4) if i >= 4 else range(4, 8)
            opps = list(brackets[ind][jnd] for ind in r for jnd in range(2))

        # todo figure out why this is greater than 1, probably because I'm reducing incorrectly
        return reduce(util.add, (util.multiply((opp, opp + t), simulate(opp, g - 1)) for opp in opps))

# Returns (n, d) where the odds of 2 winning the tournament are n/d given the current bracket configuration.
def p():
    return reduce(util.multiply, (simulate(2, l) for l in range(1, 4 + 1)))

initial = p()
best = initial
swapped = (None, None)
# Try every permutation and keep the one that gives 2 the highest odds of success.
for t1 in range(1, 16 + 1):
    for t2 in range(t1 + 1, 16 + 1):
        if loc[t1][0] == loc[t2][0]:
            continue

        i1, j1 = loc[t1]
        i2, j2 = loc[t2]

        brackets[i1][j1], brackets[i2][j2] = brackets[i2][j2], brackets[i1][j1]

        new = p()
        if util.isGreater(best, new):
            best = new
            swapped = (str(t1), str(t2))

        brackets[i1][j1], brackets[i2][j2] = brackets[i2][j2], brackets[i1][j1]

print("Started with odds " + util.fractionString(initial))
print("ended with odds " + util.fractionString(best))
print("--------")
print("We should switch " + swapped[0] + " with " + swapped[1])
diff = util.add(best, (-initial[0], initial[1]))
print("This will increase probability by " + util.fractionString(diff))
