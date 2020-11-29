import functools
@functools.lru_cache(None)
def dfs(i, last):
    if i >= 100:
        return True

    ret = [((j + last == 11) or dfs(i + j, j)) for j in range(1, 10 + 1)]
    print("at", i, ':')
    for j, el in enumerate(ret):
        if el:
            pass
        else:
            print("j =", j + 1, "leads unbeatable.")

    if all(ret):
        print("cannot win.")
    return not all(ret)

print(dfs(0, 0))
