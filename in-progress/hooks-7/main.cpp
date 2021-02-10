#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

// bad practice? yes. lazy? maybe. but I don't want to write std:: over and over, lol
using namespace std;

const int E = 0;
const int N = 9;

int grid[N][N] = 
{
    /*
    { E, E, E, 3, E },
    { E, E, E, E, E },
    { E, E, E, E, 4 },
    { E, E, E, E, E },
    { E, E, E, E, 5 }
    */
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, 4, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, 5, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
};

// keeps track of the indices that were already filled in
vector<int> save = { 2*9 + 4, 6*9 + 4 };

class Group {
    public:
        int sum = 15;
};

Group g[19];
// keeps track of the remaining sum for each group
Group * groups[N][N] = 
{
    /*
    { &g[0], &g[1], &g[1], &g[1], &g[1] },
    { &g[0], &g[0], &g[2], &g[3], &g[1] },
    { &g[4], &g[4], &g[2], &g[3], &g[1] },
    { &g[4], &g[4], &g[2], &g[3], &g[1] },
    { &g[4], &g[4], &g[2], &g[3], &g[3] }
    */
    { &g[0], &g[0], &g[0], &g[0], &g[1], &g[2], &g[2], &g[3], &g[3] },
    { &g[0], &g[0], &g[4], &g[0], &g[1], &g[2], &g[3], &g[3], &g[5] },
    { &g[6], &g[0], &g[4], &g[0], &g[0], &g[5], &g[5], &g[5], &g[5] },
    { &g[6], &g[6], &g[4], &g[4], &g[0], &g[5], &g[7], &g[8], &g[8] },
    { &g[9], &g[9], &g[4], &g[10],&g[0], &g[5], &g[7], &g[8], &g[11]},
    { &g[12],&g[9], &g[10],&g[10],&g[13],&g[7], &g[7], &g[11],&g[11]},
    { &g[12],&g[12],&g[10],&g[13],&g[13],&g[13],&g[7], &g[14],&g[14]},
    { &g[15],&g[15],&g[10],&g[13],&g[16],&g[17],&g[17],&g[18],&g[18]},
    { &g[15],&g[15],&g[10],&g[13],&g[16],&g[17],&g[17],&g[18],&g[18]}
};

// ---- below structure will be filled at runtime
// this size-11 vector will hold all values (2N - 1 choose N) for N in [1, 9] (with an empty vector at 0). 
// we'll use these bitsets to represent different configurations of placing N numbers in a 2N - 1 sized hook.
vector<vector<int>> bitsets;

// ---- functions

void bitsetHelper(int i, int n, int bitsLeft, int cur) {
    if (i == n) {
        if (bitsLeft == 0)
            bitsets[bitsets.size() - 1].push_back(cur);
    } else {
        bitsetHelper(i + 1, n, bitsLeft, cur);
        if (bitsLeft != 0) {
            bitsetHelper(i + 1, n, bitsLeft - 1, cur | (1 << i));
        }
    }
}

void initializeBitsets()
{
    for (int i = 0; i <= N; i++) {
        vector<int> empty;
        bitsets.push_back(empty);
        if (i > 0) {
            bitsetHelper(0, 2*i - 1, i, 0);
        }
    }   
} 

// Prints out a grid. For debugging and successful cases
void printGrid() 
{
    cout << "Groups" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << groups[i][j]->sum << ' ';
        } cout << endl;
    } cout << endl;
    cout << "Current grid" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                cout << "E ";
            } else {
                cout << grid[i][j] << ' ';
            }
        } cout << endl;
    } cout << endl;
}

// checks if we have a fully connected grid
bool conn(int i, int j) {
    bool seen[N][N];
    for (int ti = 0; ti < N; ti++) {
        for (int tj = 0; tj < N; tj++) {
            seen[ti][tj] = false;
        }
    }
    vector<vector<int>> cur;
    cur.push_back({ i, j });

    int numSeen = 0;
    while (cur.size() > 0) {
        vector<int> ij = cur.back();
        cur.pop_back();
        int ti = ij[0];
        int tj = ij[1];
        if (seen[ti][tj]) continue;
        seen[ti][tj] = true;
        numSeen += 1;

        if (ti != 0 and grid[ti-1][tj] > 0) {
            cur.push_back({ ti-1, tj });   
        }
        if (tj != 0 and grid[ti][tj-1] > 0) {
            cur.push_back({ ti, tj-1 });   
        }
        if (ti != N - 1 and grid[ti+1][tj] > 0) {
            cur.push_back({ ti+1, tj });   
        }
        if (tj != N - 1 and grid[ti][tj+1] > 0) {
            cur.push_back({ ti, tj+1 });   
        }
    }

    return numSeen == 45;
}

// checks if inserting any number at grid[i][j] would cause any containing 2x2 square to lack a blank space
bool violatesTwoByTwo(int i, int j) {
    if (i > 0 and j > 0 and 
        grid[i-1][j-1] > 0 and 
        grid[i-1][j] > 0 and 
        grid[i][j-1] > 0) {
        return true;
    }

    if (i > 0 and j < N - 1 and
        grid[i-1][j+1] > 0 and 
        grid[i-1][j] > 0 and 
        grid[i][j+1] > 0) {
        return true;
    }
    
    if (i < N - 1 and j > 0 and
        grid[i+1][j-1] > 0 and 
        grid[i+1][j] > 0 and 
        grid[i][j-1] > 0) {
        return true;
    }
    
    if (i < N - 1 and j < N - 1 and
        grid[i+1][j+1] > 0 and 
        grid[i+1][j] > 0 and 
        grid[i][j+1] > 0) {
        return true;
    }

    return false;
}

// high-level: checks if we can insert num at grid[i][j]
bool canInsert(int i, int j, int num) {
    bool notViolatingTwoByTwo = not violatesTwoByTwo(i, j);
    bool notViolatingSum = grid[i][j] == num or groups[i][j]->sum >= num;
    
    return notViolatingTwoByTwo and notViolatingSum;
}

// recursive backtracking function
// We do this at the num level - we try every possible hook for number <num> constrained within the bounds by <right, top, left, bottom>. 
// The hook must be in one of the four corners since its size is 2*<num> - 1.
bool dfs(int num, int right, int top, int left, int bottom) {
    // i, di, j, dj
    int hooksConfigs[4][4] = 
    {
        { top, -1, left, 1 },
        { bottom, 1, left, 1 },
        { bottom, 1, right, -1 },
        { top, -1, right, -1 }
    };

    for (auto& hook: hooksConfigs) {
        int i = hook[0];
        int di = hook[1];
        int j = hook[2];
        int dj = hook[3];

        // bitsets[num] is full of integers with 2*<num> - 1 bits, where exactly <num> bits are activated (1). This represents the number of ways to place copies of <num> in this hook
        for (auto bs: bitsets[num]) {
            // indicates whether this placement of nums was unsuccessful
            bool rollback = false;
            // place vertical numbers
            for (int ni = i; ni != i + num*di; ni += di) {
                bool inserting = bs & 1;
                // there might already be a number here since we're given a couple numbers to start
                bool blocked = grid[ni][j] > 0 and (not inserting or grid[ni][j] != num);
                if (not blocked and (inserting and canInsert(ni, j, num))) {
                    if (grid[ni][j] == 0) {
                        grid[ni][j] = num;
                        groups[ni][j]->sum -= num;
                    }
                } else if (blocked or inserting) {
                    rollback = true;
                    break;
                }
                bs >>= 1;
            }
            
            // place horizontal numbers
            if (not rollback) {
                for (int nj = j + dj; nj != j + num*dj; nj += dj) {
                    bool inserting = bs & 1;
                    bool blocked = grid[i][nj] > 0 and (not inserting or grid[i][nj] != num);
                    if (not blocked and (inserting and canInsert(i, nj, num))) {
                        if (grid[i][nj] == 0) {
                            grid[i][nj] = num;
                            groups[i][nj]->sum -= num;
                        }
                    } else if (blocked or inserting) {
                        rollback = true;
                        break;
                    }
                    bs >>= 1;
                }
            }
         
            // go to the next number if we succeeded 
            if (not rollback) {
                if (num == 1) {
                    if (conn(top, left)) {
                        cout << "SUCCESS!" << endl;
                        printGrid();
                        return true; 
                    }
                } else {
                    int newRight = right - (j == right);
                    int newTop = top - (i == top);
                    int newLeft = left + (j == left);
                    int newBottom = bottom + (i == bottom);
                    if (dfs(num - 1, newRight, newTop, newLeft, newBottom)) {
                        return true;
                    }
                }
            }
            
            // roll back at this point - we wouldn't be here if we succeeded
            for (int ni = i; ni != i + num*di; ni += di) {
                int c = N*ni + j;
                if (find(save.begin(), save.end(), c) == save.end()) {
                    groups[ni][j]->sum += grid[ni][j];
                    grid[ni][j] = 0;
                }
            }

            for (int nj = j + dj; nj != j + num*dj; nj += dj) {
                int c = N*i + nj;
                if (find(save.begin(), save.end(), c) == save.end()) {
                    groups[i][nj]->sum += grid[i][nj];
                    grid[i][nj] = 0;
                }
            }
        }
    }

    return false;
}

int main() 
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] > 0) {
                groups[i][j]->sum -= grid[i][j];
            }
        }
    }

    initializeBitsets();
    // start with 9 in the unconstrained grid 
    dfs(N, N - 1, N - 1, 0, 0);
    
    return 0;
}
