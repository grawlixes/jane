def flip3(n):
    ret = 0
    bi = 0
    for i in range(2, -1, -1):
        ret |= ((n >> 2*i) & 3) << bi
        bi += 2
    return ret 

def rot90(n):
    return (n >> 4) | ((n & 15) << 12)


def fh(n):
    pass     

def fv(n):
    bot3 = flip3((n & (15 << 8)) >> 8)
    top3 = flip3(n & 15) << 8

    return bot3 + top3 + (n & 0b1100000011) 

dp = {}
# returns a number if we found a transposition of the box in dp, else none.
def checkTransposition(bs):
    nop = lambda x: x
    # check rotations
    for i in range(4):
        if bs in dp:
            return dp[bs]
        bs = rot90(bs)

    # check reflections
    for op1, op2 in [(nop, fv), (fh, nop), (fh, fv)]:
        newBs = op1(op2(bs))
        if newBs in dp:
            return dp[newBs]


    return None

def dfs(bs = 0):
    t = checkTranspositions(bs)
    if t is not None:
       return t
   
    
    
print(dfs())
