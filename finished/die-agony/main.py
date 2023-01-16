import functools

grid = [ \
    [57, 33, 132, 268, 492, 732], \
    [81, 123, 240, 443, 353, 508], \
    [186, 42, 195, 704, 452, 228], \
    [-7, 2, 357, 452, 317, 395], \
    [5, 23, -4, 592, 445, 620], \
    [0, 77, 32, 403, 337, 452] \
]

# [6, 4, 2, 3, 5, 1] is a regular die w/ 6 facing up
# None on a die face means it can be anything, it'll be
# filled in once we get to it for the first time.
class Die:
    def __init__(self, faces):
        self.up = faces[0]
        self.sides = faces[1:5]
        self.down = faces[5]

    # Move a die on the board in any direction. "URDL"
    def move(self, direction):
        newUp = newSides = newDown = None
        up, sides, down = self.up, self.sides, self.down

        if direction == 'U':
            newUp, newDown = sides[2], sides[0]
            newSides = [up, sides[1], down, sides[3]]
        elif direction == 'R':
            newUp, newDown = sides[3], sides[1]
            newSides = [sides[0], up, sides[2], down]
        elif direction == 'D':
            newUp, newDown = sides[0], sides[2]
            newSides = [down, sides[1], up, sides[3]]
        elif direction == 'L':
            newUp, newDown = sides[1], sides[3]
            newSides = [sides[0], down, sides[2], up]
        else:
            raise Exception("Bad direction %s" % direction)

        self.up, self.sides, self.down = \
            newUp, newSides, newDown

    # Rotate the die left.
    def rotateLeft(self):
        newSides = self.sides[1:] + [self.sides[0]]
        self.sides = newSides

    # Return a deep copy of this die.
    def deepCopy(self):
        return Die([self.up] + self.sides + [self.down])

    def __hash__(self):
        return hash(tuple([self.up] + self.sides + [self.down]))

    def __eq__(self, other):
        return self.__hash__() == other.__hash__()

    def __str__(self):
        return "Up: %d; sides: %s; down: %d" % (self.up, ','.join(map(str, self.sides)), self.down)

# to be able to move, we need at least the following:
# 5 and 9, or
# 5 and -6, or
# 77 and 27

answers = set()
possibleFaces = [[None for _ in range(6)]]
done = False
for faces in possibleFaces:
    # initialDirections will give us something different facing up.
    # doesn't matter what's on the sides, we'll try everything
    for initialDirections in ("", "U", "L", "D", "R", "UU"):
        # rotations will give us different sides
        for rotations in (0, 1, 2, 3):
            die = Die(faces)
            for d in initialDirections:
                die.move(d)
            for _ in range(rotations):
                die.rotateLeft()

            @functools.lru_cache(None)
            def dfs(die, i, j, score, move, visited):
                visited |= 1 << (i*6 + j)
                if (i, j) == (0, 5):
                    print("MADE IT!")
                    print(die)
                    p = [['0' if not (visited >> (i*6 + j)) & 1 else '1' for j in range(6)] for i in range(6)]
                    for row in p:
                        print(''.join(row))
                    su = sum(grid[i][j] for i in range(6) for j in range(6) if p[i][j] == '0')
                    print("ANSWER: %d" % su)
                    return True 
                else:
                    dirs = [(i - 1, j, 'U'), (i, j - 1, 'L'), (i, j + 1, 'R'), (i + 1, j, 'D')]
                    for i2, j2, d in dirs:
                        if min(i2, j2) < 0 or max(i2, j2) > 5:
                            continue
                        newDie = die.deepCopy()
                        newDie.move(d)
                        if newDie.up is None:
                            if (grid[i2][j2] - score) % move: continue

                            # grid[i2][j2] = up * move + score
                            # up = (grid[i2][j2] - score) / move
                            newDie.up = (grid[i2][j2] - score) // move
                        
                        newScore = newDie.up * move + score

                        if newScore != grid[i2][j2]:
                            continue

                        if dfs(newDie, i2, j2, newScore, move + 1, visited):
                            done = True
                            return True

                    return False
        
            ogDie = die.deepCopy()
            if dfs(die, 5, 0, 0, 1, 0):
                done = True 
                break
            else:
                pass

        if done:
            break

    if done:
        break
