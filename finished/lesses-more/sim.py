from functools import lru_cache

def diff(t):
    return abs(t[0] - t[1])

N = 80
@lru_cache(None)
def dfs(a, b, c, d):
    if max([a, b, c, d]) == 0:
        return [(0, 0, 0, 0)]
    else:
        na, nb, nc, nd = map(diff, ((a, b), (b, c), (c, d), (d, a)))
        return [(a, b, c, d)] + dfs(na, nb, nc, nd)

best = []
for a in range(N):
    for b in range(N):
        for c in range(N):
            for d in range(N):
                this = dfs(a, b, c, d)
                if len(this) > len(best) or (len(this) == len(best) and sum(this[0]) < sum(best[0])):
                    best = this

print(best)
