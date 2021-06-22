from math import gcd

# Returns (n, d), representing the fraction that results when you add f1 and f2.
def add(f1, f2):
    g = gcd(f1[1], f2[1])
    d = (f1[1] * f2[1]) // g

    n1 = f1[0] * (d // f1[1])
    n2 = f2[0] * (d // f2[1])
    n = n1 + n2

    gRet = gcd(n, d)

    return (n // gRet, d // gRet)

# Returns (n, d), representing the fraction that results when you multiply f1 by f2.
def multiply(f1, f2):
    n, d = f1[0] * f2[0], f1[1] * f2[1]
    g = gcd(n, d)

    return (n // g, d // g)

# Returns true if the fraction represented by tuple new is greater than that represented by cur, false otherwise.
def isGreater(cur, new):
    return (new[0] / new[1]) > (cur[0] / cur[1])

# Returns a tuple representing a fraction as a string.
def fractionString(f):
    return str(f[0]) + '/' + str(f[1])

