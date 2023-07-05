#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <utility>
#include <numeric>

using namespace std;

const int E = 0;
const int N = 5; 
//const int N = 9;
const int Z = 10e7;

/*
 * for every configuration of hooks
 *  for every number assignable to each hook
 *   for each row
 *     check the current horizontal config, and the
 *     previous vertical config for all spaces, and
 *     move on to the next row
 *     
 *     also check 4x4s and the number of assigned #s
 *     
 *     at the end, check for connectivity
 */

int grid[N][N] = 
{
    { E, E, E, E, E },
    { E, E, E, E, E },
    { E, E, E, E, E },
    { E, E, E, E, E },
    { E, E, E, E, E }
    /*
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    { E, E, E, E, E, E, E, E, E },
    */
};

// keeps track of the current hook configuration
int hookConfig[N][N] =
{
    { 4, 4, 4, 4, 4 },
    { E, E, E, E, 4 },
    { E, E, E, E, 4 },
    { E, E, E, E, 4 },
    { E, E, E, E, 4 }
    /*
    { 5, 5, 5, 5, 5, 5, 5, 5, 5 },
    { 5, E, E, E, E, E, E, E, E },
    { 5, E, E, E, E, E, E, E, E },
    { 5, E, E, E, E, E, E, E, E },
    { 5, E, E, E, E, E, E, E, E },
    { 5, E, E, E, E, E, E, E, E },
    { 5, E, E, E, E, E, E, E, E },
    { 5, E, E, E, E, E, E, E, E },
    { 5, E, E, E, E, E, E, E, E },
    */
};

// init is 0 if there is no initial value set (example),
// or 1 if there is (actual, we put a 5 in)
int INIT = 1;
vector<bool> INITS = {false, false, false, false, true, false, false, false, false, false};

// for each i, the numbers assignable to an i x i hook
// some of these include observations I made offline
vector<vector<int>> assignable =
{
    {},
    {1},
    {2, 3},
    {2, 3, 4, 5},
    {2, 3, 4, 5},
    {2, 3, 4, 5}
/*
    {},
    {1},
    {2, 3},
    {2, 3, 4, 5},
    {2, 3, 4, 5, 6, 7},
    {2, 3, 4, 5, 6, 7, 8, 9},
    {2, 3, 4, 5, 6, 7, 8, 9},
    {2, 3, 4, 5, 6, 7, 8, 9},
    {2, 3, 4, 5, 6, 7, 8, 9},
    {2, 3, 4, 5, 6, 7, 8, 9}
*/
};
// keeps track of the count of each assigned number
vector<int> rem = { Z, 1, 2, 3, 4, 5 };
//vector<int> rem = { Z, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

// keeps track of the gcd for all rows and columns
vector<int> gr = { E, 5, 3, 123, 1 };
vector<int> gc = { E, 1, 1,   5, 4 }; 
/*
vector<int> gr = { 55, 1, 6, 1, 24, 3,  6, 7, 2 };
vector<int> gc = {  5, 1, 6, 1,  8, 1, 22, 7, 8 };
*/

// maps a GCD to a set of integers representing a
// config that could possibly result in that GCD
// this is populated at runtime and it takes a while
unordered_map<int, unordered_set<int>> goodConfigs;
vector<int> allGcds = {1, 3, 4, 5, 123};
//vector<int> allGcds = {1, 2, 3, 5, 6, 7, 8, 22, 24, 5}; 

// Prints out a grid. For debugging and successful cases
void printGrid() 
{
    cout << "Hooks" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << hookConfig[i][j] << ' ';
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
bool conn() {
    bool seen[N][N];
    memset(seen, false, N*N);
    vector<vector<int>> cur;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != E) {
                cur.push_back({ i, j });
                break;
            }
        }
        if (cur.size() == 1) break;
    }

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

// ensures the row gcd is correct; just divisible if not last, else gcd
bool passesRowGcd(int target, vector<int> &curNums, bool last) {
    if (curNums.size() == 0 or target == 0) return true;

    int g = curNums[0];
    int cn = curNums.size();
    for (int i = 0; i < cn; i++) {
        g = gcd(g, curNums[i]);
        if (curNums[i] % target != 0) return false;
    }
    return not last or g == target;
}

// makes sure that column j is aligned with its gcd
// up to this point; just divisible if i < N, gcd otherwise
bool passesColGcd(int i, int j) {
    int target = gc[j];
    if (target == 0) return true;

    int g = -1;
    int cur = 0;
    for (int k = 0; k < i; k++) {
        if (grid[k][j] == E) {
            if (cur > 0) {
                if (g == -1) g = cur;
                else g = gcd(g, cur);
                if (cur % target != 0) return false;
                cur = 0;
            }
        } else {
            cur = (cur * 10) + grid[k][j];
        }
    }

    if (cur > 0) {
        if (g == -1) g = cur;
        else g = gcd(g, cur);
        if (cur % target != 0) return false;
    }

    return i < N or g == gc[j];
}

// checks if we can insert this row at i and updates 
// remaining values. if we can't insert, rolls back 
// the remaining values to maintain consistency
// does *not* check cols because we do that elsewhere 
bool verifyCanInsertRow(int i) {
    for (int j = 0; j < N; j++) {
        int num = grid[i][j];
        if (num > 0 and violatesTwoByTwo(i, j)) { 
            return false;
        } else if (rem[num] < 0) {
            return false;
        }
    }
    return true;
}

// given a target number, returns all possible
// rows that could go here; they must have gcd
// equal to target altogether
// returns *bitsets* identifying which cells
// are filled, and which aren't
// also checks column gcd
void genRows(int curBs, int i, int j, int num, vector<int> &ret, vector<int> &curNums) {
    int target = gr[i];
    if (j == N) {
        if (curBs == 0) return; // no empty rows
        
        if (num != 0) curNums.push_back(num);
        if (passesRowGcd(target, curNums, true)) {
            ret.push_back(curBs);
        }
        if (num != 0) curNums.pop_back();
    } else {
        // try to insert an empty
        if (target == 0 or num % target == 0) {
            if (num != 0) curNums.push_back(num);
            if (passesRowGcd(target, curNums, false) and passesColGcd(i, j)) {
                genRows(curBs*2, i, j + 1, 0, ret, curNums);
            }
            if (num != 0) curNums.pop_back();
        }
        
        // try to insert this number
        genRows(curBs*2 + 1, i, j + 1, num * 10 + hookConfig[i][j], ret, curNums);
    }
}

// recursive backtracking function at row-level
// assumes the grid's expected hooks are filled in
// gets all rows that obey the hooks and gcd rule,
// verifies that it obeys all other rules, and
// moves on to the next row
// at the end, it checks connectivity
bool dfs(int i) {
    if (i == N) {
        for (int j = 0; j < N; j++) {
            if (not passesColGcd(N, j)) {
                return false;
            }
        }
        
        if (conn()) {
            cout << "SUCCESS!" << endl;
            printGrid();
            return true;
        } else {
            return false;
        }
    }
    vector<int> goodRows;
    vector<int> curNums;
    genRows(0, i, 0, 0, goodRows, curNums);
   
    for (int rowBs: goodRows) {
        int tbs = rowBs;
        for (int j = N - 1; j >= 0; j--) {
            grid[i][j] = (tbs & 1) ? hookConfig[i][j] : E;
            rem[grid[i][j]]--;
            tbs >>= 1;
        }
        
        if (verifyCanInsertRow(i)) {
            if (dfs(i+1)) return true;
        }

        for (int j = 0; j < N; j++) {
            rem[grid[i][j]]++;
            grid[i][j] = E;
        }
    }

    return false;
}

// given a bitset representing the other 8 hooks
// and a vector representing which number is at
// each hook, builds the hook config matrix
void buildHookConfig(int hookBs, vector<int> &hookVals) {
    int top = 0, bottom = N - 1;
    while (hookConfig[top][2] != E) top++;
    while (hookConfig[bottom][2] != E) bottom--;
    
    int left = 0, right = N - 1;
    while (hookConfig[2][left] != E) left++;
    while (hookConfig[2][right] != E) right--;
    
    for (int hi = 0; hi < N - INIT; hi++) {
        int thisHook = hookBs & 3;
        // 0 = top left, 1 = top right, 2 = bottom left, 3 = bottom right
        int i = (thisHook < 2) ? top : bottom;
        for (int j = left; j <= right; j++) {
            hookConfig[i][j] = hookVals[hi];
        }
        
        int j = (thisHook & 1) ? right : left;
        for (int i = top; i <= bottom; i++) {
            hookConfig[i][j] = hookVals[hi];
        }

        if (thisHook < 2) top++;
        else bottom--;
        
        if (thisHook & 1) right--;
        else left++;

        hookBs >>= 2;
    }
}

// for every row and column, make sure the gcds are 
// achievable before going through the hook config
bool gcdsPossible() {
    for (int i = 0; i < N; i++) {
        vector<int> good;
        vector<int> curNums;
        // reuse Genrows
        genRows(0, i, 0, 0, good, curNums);
        if (good.size() == 0) return false;
    }
    
    int bsLim = 1 << N;
    for (int j = 0; j < N; j++) {
        // reuse gcdsPossible
        bool passes = false;
        for (int bs = 1; bs < bsLim; bs++) {
            int tbs = bs;
            for (int i = 0; i < N; i++) {
                if (tbs & 1) grid[i][j] = hookConfig[i][j];
                else grid[i][j] = E;
                tbs >>= 1;
            }
            
            if (passesColGcd(N, j)) {
                passes = true;
                break;
            }
        }
            
        for (int i = 0; i < N; i++) grid[i][j] = E;
        if (not passes) return false;
    }
    return true;
}

// create hook config and invoke dfs
bool getHooksAndTry(int i, int hookBs, vector<int> &hookVals) {
    if (i == 0) {
        buildHookConfig(hookBs, hookVals);
        bool res = false;
        if (gcdsPossible()) res = dfs(0);
            
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (not INITS[hookConfig[i][j]]) {
                    hookConfig[i][j] = E;
                }
            }
        }
        
        return res;
    }
    
    for (auto &num: assignable[i]) {
        if (not INITS[num] and find(hookVals.begin(), hookVals.end(), num) == hookVals.end()) {
            hookVals.push_back(num);
            if (getHooksAndTry(i - 1, hookBs, hookVals)) return true;
            hookVals.pop_back();
        }
    }
    return false;
}
/*
void initializeConfigsHelper(int cur, vector<int> &curNums, int num, int i, int target, int bs) {
    if (i == N) {
        if (num != 0) curNums.push_back(num);
        if (passesRowGcd(target, curNums, true)) {
            goodConfigs[target].insert(cur);
        }
        if (num != 0) curNums.pop_back();
    } else {
        if (num == 0 or num % target == 0) {
            if (num != 0) curNums.push_back(num);
            if (passesRowGcd(target, curNums, true)
        }

        for (int j = 1; j <= N; j++) {
            if (((bs >> j) & 1) == 0) {
                initializeConfigsHelper(cur*10 + j, curNums, num*10 + j, i + 1, target, bs | (1 << j));
            }
        }
    }
}
*/
int main() 
{
    int hookBsLim = pow(4, N - INIT - 1);
    for (int hookBs = 0; hookBs < hookBsLim; hookBs++) {
        vector<int> hookVals;
        if (getHooksAndTry(N - INIT, hookBs, hookVals)) break;
    }
    return 0;
}
