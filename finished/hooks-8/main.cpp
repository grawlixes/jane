#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>

// bad practice? yes. lazy? maybe. but I don't want to write std:: over and over, lol
using namespace std;

const int E = 0;
const int N = 9;
const int GROUPS = 19;
const int GROUP_SUM = 15;

int grid[N][N] = 
{
    /*
    { E, 4, E, E, 3 },
    { E, E, E, E, E },
    { E, E, E, E, E },
    { E, E, E, E, E },
    { 5, E, E, 5, E }
    */
    { E, E, 8, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
};

// keeps track of the indices that were already filled in
//vector<int> save = { 0*N + 1, 0*N + 4, 4*N + 0, 4*N + 3 };
vector<int> save = { 0*N + 2 };

// keeps track of the count of each assigned number
//vector<int> rem = { 0, 1, 2, 2, 3, 3 };
vector<int> rem = { 0, 1, 2, 3, 4, 5, 6, 7, 7, 9 };

// keeps track of the sum of each group
class Group {
    public:
        int num;
        int sum = GROUP_SUM;
};

Group g[GROUPS];

// keeps track of the remaining sum for each group
Group * groups[N][N] = 
{
    /*
    { &g[0], &g[0], &g[0], &g[1], &g[1] },
    { &g[4], &g[4], &g[0], &g[1], &g[2] },
    { &g[4], &g[2], &g[2], &g[2], &g[2] },
    { &g[4], &g[3], &g[3], &g[3], &g[2] }, 
    { &g[4], &g[3], &g[2], &g[2], &g[2] }
    */
    { &g[0], &g[1], &g[1], &g[1], &g[2], &g[3], &g[3], &g[4], &g[4] },
    { &g[0], &g[1], &g[5], &g[5], &g[2], &g[6], &g[3], &g[4], &g[7] },
    { &g[0], &g[10],&g[10],&g[5], &g[5], &g[6], &g[6], &g[7], &g[7] },
    { &g[0], &g[10],&g[11],&g[11],&g[5], &g[6], &g[9], &g[8], &g[8] },
    { &g[0], &g[11],&g[11],&g[12],&g[12],&g[12],&g[9], &g[13],&g[13]},
    { &g[0], &g[18],&g[11],&g[11],&g[11],&g[12],&g[9], &g[9], &g[13]},
    { &g[0], &g[18],&g[18],&g[14],&g[15],&g[12],&g[16],&g[16],&g[17]},
    { &g[0], &g[0], &g[14],&g[14],&g[15],&g[12],&g[16],&g[16],&g[17]},
    { &g[0], &g[14],&g[14],&g[15],&g[15],&g[12],&g[12],&g[17],&g[17]}
};

// ---- below structure will be filled at runtime
// this size-10 vector will hold all values (2N - 1 choose i) for N in [1, 9] and i in [1, N] (with an empty vector at 0). 
// we'll use these bitsets to represent different configurations of placing N numbers in a 2N - 1 sized hook.

// bitsets[N][i] = {bs1, bs2, bs3...}
// means that bs1 - bs3 are all bitsets with i bits activated out of N total possible bits.
vector<vector<vector<int>>> bitsets;

// ---- functions

void bitsetHelper(int i, int n, int bitsGiven, int bitsLeft, int cur) {
    if (i == n) {
        if (bitsLeft == 0) {
            int s2 = bitsets[bitsets.size() - 1].size();
            bitsets[bitsets.size() - 1][s2 - 1].push_back(cur);
        }
    } else {
        bitsetHelper(i + 1, n, bitsGiven, bitsLeft, cur);
        if (bitsLeft != 0) {
            bitsetHelper(i + 1, n, bitsGiven, bitsLeft - 1, cur | (1 << i));
        }
    }
}

void initializeBitsets()
{
    for (int i = 0; i <= N; i++) {
        vector<vector<int>> empty;
        bitsets.push_back(empty);
        
        for (int j = 0; j <= N; j++) {
            vector<int> cur;
            bitsets[i].push_back(cur);
            if (j > 0 and j <= (2*i - 1)) {
                bitsetHelper(0, 2*i - 1, j, j, 0);
            }
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

    return numSeen == ((N * (N + 1)) / 2);
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

// checks whether we can still decrease all groups to 0 in this range
// rule: if any group not in this range has nonzero sum, we can't finish with this config
bool isFeasible(int right, int top, int left, int bottom) {
    unordered_set<int> canMake; 
    for (int i = bottom; i <= top; i++) {
        for (int j = left; j <= right; j++) {
            //cout << "inserted at " << i << ' ' << j << endl;
            canMake.insert(groups[i][j]->num);
        }
    }

    //for (auto &c: canMake) cout << c << endl;

    for (int gi = 0; gi < GROUPS; gi++) {
        if (canMake.find(gi) == canMake.end() and g[gi].sum != 0) {
            /*
            cout << "bad group " << gi << endl;
            cout << "for bottom left: " << bottom << ' ' << left << endl;
            cout << "top right: " << top << ' ' << right << endl;
            */
            return false;
        }
    }

    return true;
}

// recursive backtracking function
// We do this at the hook level - we try every possible hook of size 2*<num> - 1 constrained within the bounds by <right, top, left, bottom>. 
// The hook must be in one of the four corners since its size is 2*<num> - 1.
// used tells us which nums 1-9 we've used as a bitset 
bool dfs(int used, int right, int top, int left, int bottom) {
    if (not isFeasible(right, top, left, bottom)) return false;
    //cout << "bottom left " << bottom << ' ' << left << endl;
    //cout << "top right " << top << ' ' << right << endl;
    //printGrid();
    
    // we have a choice for the number in the hook, but the hook size is defined
    int size = top - bottom + 1;
    // i, di, j, dj
    int hooksConfigs[4][4] = 
    {
        { top, -1, left, 1 },
        { top, -1, right, -1 },
        { bottom, 1, left, 1 },
        { bottom, 1, right, -1 }
    };

    int hi = 0;
    for (auto& hook: hooksConfigs) {
        int i = hook[0];
        int di = hook[1];
        int j = hook[2];
        int dj = hook[3];
        for (int num = N; num >= 1; num--) {
            // bitsets[num] is full of integers with 2*<num> - 1 bits, where exactly <num> bits are activated (1). This represents the number of ways to place copies of <num> in this hook
            if ((used >> num) & 1) continue;
            if (((used >> 8) & 1) == 0 and num != 8 and hi > 1) break;

            for (auto bs: bitsets[size][num]) {
                // indicates whether this placement of nums was unsuccessful
                bool rollback = false;
                int placed = 0;
                // place vertical numbers
                for (int ni = i; ni != i + size*di; ni += di) {
                    bool inserting = bs & 1;
                    // there might already be a number here since we're given a couple numbers to start
                    bool blocked = grid[ni][j] > 0 and (not inserting or grid[ni][j] != num);
                    if (not blocked and (inserting and canInsert(ni, j, num))) {
                        if (grid[ni][j] == 0) {
                            grid[ni][j] = num;
                            groups[ni][j]->sum -= num;
                            placed++;
                        }
                    } else if (blocked or inserting) {
                        rollback = true;
                        break;
                    }
                    bs >>= 1;
                }
                
                // place horizontal numbers
                if (not rollback) {
                    for (int nj = j + dj; nj != j + size*dj; nj += dj) {
                        bool inserting = bs & 1;
                        bool blocked = grid[i][nj] > 0 and (not inserting or grid[i][nj] != num);
                        if (not blocked and (inserting and canInsert(i, nj, num))) {
                            if (grid[i][nj] == 0) {
                                grid[i][nj] = num;
                                groups[i][nj]->sum -= num;
                                placed++;
                            }
                        } else if (blocked or inserting) {
                            rollback = true;
                            break;
                        }
                        bs >>= 1;
                    }
                }
           
                rollback |= (placed != rem[num]);

                // go to the next number if we succeeded 
                if (not rollback) {
                    if (size <= 3) {
                        cout << "Finished " << size << " with " << num << endl;
                        printGrid();
                    }
                    if (size == 1) {
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
                        if (dfs(used | (1 << num), newRight, newTop, newLeft, newBottom)) {
                            return true;
                        }
                    }
                }
                
                // roll back at this point - we wouldn't be here if we succeeded
                for (int ni = i; ni != i + size*di; ni += di) {
                    int c = N*ni + j;
                    if (find(save.begin(), save.end(), c) == save.end()) {
                        groups[ni][j]->sum += grid[ni][j];
                        grid[ni][j] = 0;
                    }
                }

                for (int nj = j + dj; nj != j + size*dj; nj += dj) {
                    int c = N*i + nj;
                    if (find(save.begin(), save.end(), c) == save.end()) {
                        groups[i][nj]->sum += grid[i][nj];
                        grid[i][nj] = 0;
                    }
                }
            }
        }
        
        hi++;
    }

    return false;
}

int main() 
{
    for (int it = 0; it < GROUPS; it++)
        g[it].num = it;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] > 0) {
                groups[i][j]->sum -= grid[i][j];
            }
        }
    }

    initializeBitsets();
    /*
    for (int i = 0; i < bitsets.size(); i++) {
        cout << "i = " << i << endl;
        for (int j = 0; j < bitsets[i].size(); j++) {
            if (j == 0) continue;
            cout << "j = " << j << endl;
            for (int k = 0; k < bitsets[i][j].size(); k++) {
                cout << bitsets[i][j][k] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
    */

    // start with the unconstrained grid 
    dfs(0, N - 1, N - 1, 0, 0);
    
    return 0;
}
