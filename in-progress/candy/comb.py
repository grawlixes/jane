from itertools import permutations
import numpy as np

def main():
    poss = [(5, 0, 0, 0, 0), \
            (4, 1, 0, 0, 0), (3, 2, 0, 0, 0), \
            (3, 1, 1, 0, 0), (2, 2, 1, 0, 0), \
            (2, 1, 1, 1, 0), \
            (1, 1, 1, 1, 1)]
    a = list(set(p for el in poss for p in permutations(el)))
    
    ct = 0
    for i in range(126):
        for j in range(126):
            for k in range(126):
                for l in range(126):
                    for m in range(126):
                        ct += 1
                        mat = [a[i], a[j], a[k], a[l], a[m]]
                        cols = [0, 0, 0, 0, 0]
                        rows = [0, 0, 0, 0, 0]

                        for i in range(5):
                            for j in range(5):
                                cols[j] += mat[i][j]
                                rows[i] += mat[i][j]

                        for i in range(5):
                            if rows[i] != 5 or cols[i] != 5:
                                break
                        
                        if ct % 100000 == 0:
                            print(ct)

if __name__ == "__main__":
    main()
