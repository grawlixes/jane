# p[i] = number of ways to end up with *i* maximum number of some figures
p = [1, 2047, 175099, 2968581, 20291772, 77339460, 195698520, 364127400, 529824960, 623972160, 600566400, 459043200, 239500800]
# I didn't end up using this, but look at it anyway lol

# This program is really slow. I suggest running the c++ one instead, it should only take 30 seconds or so.
from math import factorial

def p(N, ncrCache):
    ret = 1
    s = 0
    
    for i in range(len(N)):
        Ni = N[i]
        s += Ni
        ret *= ncrCache[i+2][Ni]

    F = len(N) + 1
    tot = (F * (F + 1)) // 2
    selectFirstHere = 1 / (tot - s)
    #print("in func", ret, s, ncrCache[tot][s], selectFirstHere)
    return (ret / ncrCache[tot][s]) * selectFirstHere

def main():
    ncrCache = [[factorial(i) // (factorial(j) * factorial(i - j)) for j in range(i + 1)] for i in range(78 + 1)]

    for F in range(2, 12 + 1):
        e = 0
        for M in range(1, F + 1):
            for l in range(max(M, 2), F + 1):
                config = [0 for _ in range(F-1)]
                config[l-2] = M
                res = p(config, ncrCache)
                e += res * M

                while True:
                    i = 0
                    found = False
                    while i < F - 1:
                        if i != l - 2:
                            n = i + 2
                            lim = min(n, M - (i < l - 2))
                            if config[i] >= lim:
                                config[i] = 0
                            else:
                                config[i] += 1
                                found = True
                                break

                        i += 1

                    if found:
                        e += p(config, ncrCache) * M
                    else:
                        break

        print("E[F = " + str(F) + "] = " + str(e))
if __name__ == "__main__":
    main()
