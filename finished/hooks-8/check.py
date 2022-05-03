E = 0
x = [[5, 7, 8, E, 6, E, 6, E, 6],[5, E, E, 9, 9, 9, 9, 9, 6],[5, 7, 8, 4, E, 4, E, 9, E],[E, E, E, 4, 2, 2, 3, 9, 6],[E, E, 8, 4, E, 1, E, 9, E],[E, E, E, 3, E, E, 3, 9, 6],[E, 7, 8, 8, 8, E, 8, E, 8],[E, E, 7, E, 7, E, 7, E, 7],[E, E, E, E, E, 5, 5, E, E]]

search = set((i, j) for i in range(9) for j in range(9) if x[i][j] == E)
seen = set()
ret = 1
while search:
    k = search.pop()
    if k in seen:
        continue
    this = 0
    dfs = set([k])
    while dfs:
        cur = dfs.pop()
        print(cur)
        if cur in seen:
            continue 
        seen.add(cur)
        i,j = cur
        this += 1

        neigh = [(i - 1, j), (i, j - 1), (i, j + 1), (i + 1, j)]
        for t2 in filter(lambda t: min(t) >= 0 and t[0] < 9 and t[1] < 9 and x[t[0]][t[1]] == 0, neigh):
           dfs.add(t2)

    ret *= this

print(ret)
