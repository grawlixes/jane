# highest possible sum of elements in row/col/etc
MAX_SUM = 80
# highest possible element in grid
MAX_NUM = 40
firsts = {n: [] for n in range(1, MAX_NUM)}

for s in range(6, MAX_SUM + 1):
    for first in range(1, MAX_NUM):
        for second in range(1, MAX_NUM):
            third = s - (first + second)
            tot = {first, second, third}
            if third > 0 and third <= MAX_NUM and len(tot) == 3 and sum(tot) == s:
                t = (first, second, third)
                firsts[first].append(t)

print("Done precomputing sums up to %i" % MAX_SUM)
print("Total number of sums is %i" % sum(len(el) for el in firsts.values()))

def checkGrid(g, s):
    sums = set()
    for i in range(3):
        sums.add(sum(g[i][j] for j in range(3)))
    for j in range(3):
        sums.add(sum(g[i][j] for i in range(3)))
    sums.add(g[0][0] + g[1][1] + g[2][2])
    sums.add(g[2][0] + g[1][1] + g[0][2])

    return len(sums) <= 2 and max(sums) - min(sums) <= 1

def copyGrid(g):
    return [row[:] for row in g]

def solveDouble(t1, t2, top):
    ret = []
     
    for br, bm, bl, mr in ((t2[0], t2[1], t2[2], t1[2]), (t1[0], t1[1], t1[2], top)):
        s = br + bm + bl
        grid = [[0 for _ in range(3)] for _ in range(3)]
        grid[1][2] = mr 
        grid[2][0] = bl 
        grid[2][1] = bm 
        grid[2][2] = br 
        grids = []
        ret.append(grids)
        search = [(grid, 0)]
       
        nxtSec = [(0, 2), (1, 1), (1, 0), (0, 1), (0, 0)]
        comp = [[[(1, 2), (2, 2)]], [[(0, 2), (2, 0)]], [[(1, 1), (1, 2)]], [[(1, 1), (2, 1)]], [[(2, 2), (1, 1)], [(0, 2), (0, 1)], [(2, 0), (1, 0)]]]
        while search:
            cur, ind = search.pop()
            se = set(el for row in cur for el in row)
            if ind == len(nxtSec):
                if checkGrid(cur, s):
                    grids.append((cur, se))
            else:
                i, j = nxtSec[ind]
                poss = None 
                for l in comp[ind]:
                    fi,fj = l[0]
                    si,sj = l[1]
                    this = cur[fi][fj] + cur[si][sj]
                    last = s - this
                    if poss is None:
                        poss = {last-1, last, last+1}
                    else:
                        poss &= {last-1, last, last+1}
                
                for nxt in poss:
                    if nxt > 0 and nxt not in se and nxt <= MAX_NUM:
                        cur[i][j] = nxt
                        search.append((copyGrid(cur), ind + 1))
                        cur[i][j] = 0

    # todo make all 2-grids out of grids
    r = [] 
    for lower, ls in ret[0]:
        for upper, us in ret[1]:
            halfSet = ls | us
            if len(halfSet) == 16:
                #print(upper)
                l = []
                for j in range(2, -1, -1):
                    l.append([lower[i][j] for i in range(3)])
                #print(l)
                p = [['X'] + upper[0], \
                     ['X'] + upper[1], \
                     l[0] + [upper[2][2]], \
                     l[1] + ['X'], \
                     l[2] + ['X']]
                r.append((l, upper, p, halfSet))
    return r

globBest = [float('inf'), None, None]

def gen(l):
    left = []
    for t1 in firsts.get(l[1], []):
        t2 = (t1[1], l[2], l[3])
        for el in solveDouble(t1, t2, l[0]):
            left.append(el)
            
    right = []        
    for t1 in firsts.get(l[2], []):
        t2 = (t1[1], l[1], l[0])
        for el in solveDouble(t1, t2, l[3]):
            right.append(el)

    for ll, lu, lp, ls in left:
        for rl, ru, rp, rs in right:
            res = ls | rs
            if len(res) == 28:
                ts = sum(res)
                if ts < globBest[0]:
                    globBest[0] = ts
                    print("FOUND ONE WITH SUM %i" % ts)
                    print("LEFT")
                    for row in lp:
                        print(' '.join(map(str, row)))
                    print("RIGHT")
                    for row in rp:
                        print(' '.join(map(str, row)))
                    print()

seen = set()
for i in range(1, 11, 1):
    print('i left', i)
    for j in range(1, MAX_NUM + 1, 1):
        print('j left', j)
        for k in range(1, MAX_NUM + 1, 1):
            for l in range(1, MAX_NUM + 1, 1):
                this = tuple([l, k, j, i])
                if this not in seen and len(set(this)) == 4:
                    c = tuple([i, j, k, l])
                    seen.add(c)
                    gen([i, j, k, l])
