# This simulation shows us the best 
# choice assuming there were only two
# robots, which is much simpler.

N = 1000000
best = 0
ret = 0

for p in map(lambda n: n / N, range(N)):
    if p == 0:
        continue

    # Odds that the second robot wins
    # if it lifts zero: it'll always
    # succeed, so the second robot only
    # wins if the first robot fails.
    # Tying isn't possible.
    under = 1 - p

    # Odds that the second robot wins
    # if it chooses some real number
    # that is minimally larger to lift
    # than the second robot. Wins as 
    # long as it succeeds, potentially
    # ties if both robots fail.
    over = 0
    coeff = 1
    while coeff > 10**-9:
        over += coeff * p
        coeff *= (1 - p)**2

    probSecondWins = max(over, under)
    if best < (1 - probSecondWins):
        best = 1 - probSecondWins
        ret = p

    #print(p, 1 - probSecondWins)

print("BEST")
print(best)
print("p(w)")
print(ret)
