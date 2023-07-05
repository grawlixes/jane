from math import gcd
from functools import reduce

def genAllRows(target, n, allowed):
    # generate all possible rows of length n
    # of numbers [1, n], such that the gcd of the
    # concatenation of each unique number is equal
    # to target
    
    ret = set()
    curNums = []
    cur = []
    def check(nums, target, final):
        if final:
            return len(nums) == 0 or reduce(lambda x,y: gcd(x, y), nums) == target
        else:
            return all(num % target == 0 for num in nums)

    def recurse(i, num):
        if i == n:
            if (num != 0):
                curNums.append(num)
            if check(curNums, target, True):
                ret.add(''.join(cur))
            if (num != 0):
                curNums.pop()
        else:
            # blank here
            if num == 0 or num % target == 0:
                if num != 0:
                    curNums.append(num)
                if check(curNums, target, False):
                    cur.append(" ")
                    recurse(i + 1, 0)
                    cur.pop()
                if num != 0:
                    curNums.pop()

            for j in range(1, n + 1):
                cur.append(str(j))
                recurse(i + 1, num * 10 + j)
                cur.pop()
    recurse(0, 0)
    return ret



present = {2, 3, 5, 6, 7, 8, 22, 24, 55}

for target in present:
    res = genAllRows(target, 9, [5 for _ in range(9)])
    print(target, len(res))
    

def recurseWithLimits(i, num):
    if i == n:
        curNums.append(num)
        if check(curNums, target):
            ret.add(''.join(cur))
        curNums.pop()
    else:
        # blank here
        if num == 0 or target % num == 0:
            if num != 0:
                curNums.append(num)
            if check(curNums, target):
                cur.append(" ")
                recurseWithLimits(i + 1, 0)
                cur.pop()
            if num != 0:
                curNums.pop()

        cur.append(str(allowed[i]))
        recurseWithLimits(i + 1, num * 10 + allowed[i])
        cur.pop()
