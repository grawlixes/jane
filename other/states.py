STATES = "Alabama, Alaska, Arizona, Arkansas, California, Colorado, Connecticut, Delaware, Florida, Georgia, Hawaii, Idaho, Illinois, Indiana, Iowa, Kansas, Kentucky, Louisiana, Maine, Maryland, Massachusetts, Michigan, Minnesota, Mississippi, Missouri, Montana, Nebraska, Nevada, New Hampshire, New Jersey, New Mexico, New York, North Carolina, North Dakota, Ohio, Oklahoma, Oregon, Pennsylvania, Rhode Island, South Carolina, South Dakota, Tennessee, Texas, Utah, Vermont, Virginia, Washington, West Virginia, Wisconsin, Wyoming".lower()
STATES = STATES.split(", ")
STATES = [el.replace(' ', '') for el in STATES]

grid = [[None for _ in range(5)] for _ in range(5)]
bestGrid = grid
bestScore = 0
openSpaces = set((i, j) for i in range(5) for j in range(5))
score = 0

def copyGrid():
    bestGrid = [grid[i].copy() for i in range(5)]

def dfs(    
