from functools import reduce

# I did this one by hand, so this will just verify whether your grid
# is valid. It's valid if all regions of size N have numbers 1-N in
# them, and the nearest K via Manhattan distance is exactly K away.

# the correct grid
GRID = [ \
        [4, 3, 6, 5, 3, 7, 4, 9, 6, 5],\
        [8,10, 2, 4, 1, 1, 2, 3, 8, 2],\
        [9, 2, 3, 2, 1, 2, 5, 1, 2, 4],\
        [5, 7, 2, 1, 2, 6, 3, 1, 1, 3],\
        [6, 3, 1, 1, 3, 2, 1, 4, 2, 7],\
        [1, 1, 4, 5, 1, 1, 1, 3, 5, 6],\
        [3, 1, 2, 3, 2, 4, 2, 1, 2, 3],\
        [4, 2, 1, 1, 1, 1, 3, 1, 4, 9],\
        [5, 8, 3, 4, 2, 1, 6, 2, 3, 8],\
        [7, 6, 9,10, 5, 3, 4, 7, 2, 5]\
       ]

# the regions
REGIONS = [ \
            [0, 5, 5, 5, 6, 6, 6, 6, 6, 6],\
            [0, 0, 5, 5, 5, 6, 7, 7, 6, 6],\
            [0, 0, 8, 8,10,10,18, 7,17,17],\
            [0, 0, 4, 8, 9,18,18,18,17,17],\
            [0, 4, 4, 9, 9,20,19,18,18,17],\
            [0, 2, 4,11,21,20,15,15,17,17],\
            [0, 1, 3,11,11,11,15,16,16,16],\
            [1, 1, 3,12,11,22,13,14,14,13],\
            [1, 1, 1,12,12,13,13,14,14,13],\
            [1, 1, 1, 1,12,12,13,13,13,13]\
          ]
NUM_REGIONS = max(el for row in REGIONS for el in row) + 1

good = True
# check neighbor distances
for i,row in enumerate(GRID):
    for j,v in enumerate(row):
        others = [(k, l) for k in range(10) for l in range(10) if GRID[k][l] == v and (k, l) != (i, j)]
        comp = min(abs(i - k) + abs(j - l) for k,l in others) if others else None
        if comp != v:
            if good is True:
                print("BAD GRID!")
            
            if comp is None:
                print("Only one instance of element %i at index %s. All elements should have a least one neighbor." % (v, str((i, j))))
            else:
                print("Element %i at index %s has a closest neighbor of distance %i, which is wrong." % (v, str((i, j)), comp))
            good = False

# check regions
for r in range(NUM_REGIONS):
    v = [(i, j) for i in range(10) for j in range(10) if REGIONS[i][j] == r]
    n = len(v)
    vals = set(GRID[i][j] for i,j in v)
    if len(vals) != n or any(i not in vals for i in range(1, n + 1)):
        if good is True:
            print("BAD GRID!")
        print("Nums 1-N not present in region %i." % r)
        good = False

if good:
    print("GOOD GRID!")
    print("SOLUTION: %i" % sum(reduce(lambda x,y: x*y, row) for row in GRID))
else:
    pass
