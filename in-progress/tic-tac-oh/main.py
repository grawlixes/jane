# mask i numbers
masks = [0b0, 0b11, 0b1111, 0b111111]

def flip3(n):
    ret = 0
    bi = 0
    for i in range(2, -1, -1):
        ret |= ((n >> 2*i) & masks[1]) << bi
        bi += 2
    return ret 

def rot90(n):
    return (n >> 4) | ((n & masks[2]) << 12)


def fh(n):
    left3 = flip3(((n & masks[1]) << 4) | ((n >> 12) & masks[2]))
    right3 = flip3((n >> 4) & masks[3])

    first1, last2 = (right3 >> 4) & masks[1], right3 & masks[2]
    return first1 + (left3 << 4) + (last2 << 12) + (n & 0b110000001100)

print(bin(0b0100101010000101)[2:], bin(fh(0b0100101010000101))[2:])

def fv(n):
    bot3 = flip3((n & (masks[3] << 8)) >> 8)
    top3 = flip3(n & masks[3]) << 8

    return bot3 + top3 + (n & 0b1100000011000000) 

dp = {}
# returns a number if we found a transposition of the box in dp, else none.
def checkTranspositions(bs):
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
