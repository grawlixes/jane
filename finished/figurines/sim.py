trials = 100000
from random import randint

# This program simulates a lot of actual trials to give me an idea of what the answer should be.
for N in range(1, 12 + 1):
    tot = 0
    N = 12
    for t in range(trials):
        have = [[i for _ in range(i)] \
                for i in range(1, N+1)]
        h = []
        for r in have:
            for el in r:
                h.append(el)
        have = h
        gave = {}
        while True:
            sel = have.pop(randint(0, len(have) - 1))
            if sel == 1:
                break
            else:
                gave[sel] = gave.get(sel, 0) + 1
        tot += max(gave.values()) if gave else 0
    print("Answer for N = " + str(N) + " is approximately " + str(tot / trials))
