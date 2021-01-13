from math import factorial

for F in range(2, 12 + 1):
    tot = (F * (F + 1)) // 2

    # Cache nCr values for quick calculation in the p function, since the hypergeometric distribution uses them.
    ncrCache = [[factorial(i) // ((factorial(j) * factorial(i - j))) for j in range(i + 1)] for i in range(F + 1)]
    totalCache = [factorial(tot) // (factorial(i) * factorial(tot - i)) for i in range(tot)]

    # This function uses the multivariate hypergeometric distribution to determine the probability that we get N[i] figurines of type i in sum(N) pulls. "bs" is N serialized as a long integer.
    def p(bs):
        N = []
        for _ in range(F):
            N.append(bs & 15)
            bs >>= 4
        ret = 1
        s = 0
        for i,Ni in enumerate(N):
            # N starts at i = 2 because the 0th and 1st figurines don't matter to this function.
            i += 2
            ret *= ncrCache[i][Ni]
            s += Ni
        return ret / totalCache[s]

    # Final expected value
    e = 0
    for m in range(1, F + 1):
        for f2 in range(2 + 1):
            for f3 in range(3 + 1):
                if max(f2, f3) == m:
                    N = [0, 0, f2, f3]
                    #print(m, N, p(N), 1 / sum(N))
                    e += m * p(N) * (1 / (tot - sum(N)))

    print("Expected value for F =", F, "is", e)
