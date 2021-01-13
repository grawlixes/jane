# p[i] = number of ways to end up with *i* maximum number of some figures
# these obviously have different probabilities
p = [1, 2047, 175099, 2968581, 20291772, 77339460, 195698520, 364127400, 529824960, 623972160, 600566400, 459043200, 239500800]

from functools import lru_cache
from math import factorial

figs = [-1]

def pickedToBs(picked):
    ret = 0
    for i in range(len(picked) - 1, -1, -1):
        ret <<= 4
        el = picked[i]
        ret += el
    return ret

def bsToPicked(bs):
    ret = [0 for _ in range(figs[0] - 1)]
    i = 0
    while bs:
        ret[i] = bs & 15
        bs >>= 4
        i += 1

    return ret

def bsToDp(bs):
    ret = 0
    i = 2
    while bs:
        ct = i - (bs & 15)
        if ct: 
            ret += 1 << ((ct - 1) * 4)
        i += 1
        bs >>= 4

    return ret

sols = []
dp = {}
skipped = [0]
def dfs(bs, mag = 1):
    thisDp = bs
    if thisDp not in dp:
        picked = bsToPicked(bs)
        n, s = 0, 1
        for i in range(len(picked)):
            p = picked[i]
            n = max(i + 2 - p, n)
            s += p

        ret = n / s
        sub = 1
        for i in range(len(picked)):
            if picked[i]:
                prob = picked[i] / s
                bs -= sub
                ret += prob * dfs(bs, mag * prob)     
                bs += sub
            sub <<= 4

        dp[thisDp] = ret
    
    return dp[thisDp]

def main():
    for N in range(1, 11 + 1):
        bs = pickedToBs(list(i + 2 for i in range(N - 1)))
        figs[0] = N
        sol = dfs(bs)
        print("Solution for N =", N, "is", sol, "skipped", skipped[0])
        sols.append(sol)
        skipped[0] = 0
        dp.clear()

if __name__ == "__main__":
    main()
