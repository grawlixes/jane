#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

// bad practice? yes. lazy? maybe. but I don't want to write std:: over and over, lol
using namespace std;

// bitmasks with 7 bits and 4 ones
vector<int> sevenChooseFour = {15,23,27,29,30,39,43,45,46,51,53,54,57,58,60,71,75,77,78,83,85,86,89,90,92,99,101,102,105,106,108,113,114,116,120};
// combinations of 4 numbers, 1-7, such that the sum of each number is 20 
vector<vector<int>> combs = {
    {1,5,7,7},{1,6,6,7},{1,6,7,6},{1,7,5,7},{1,7,6,6},{1,7,7,5},{2,4,7,7},{2,5,6,7},{2,5,7,6},{2,6,5,7},{2,6,6,6},{2,6,7,5},{2,7,4,7},{2,7,5,6},{2,7,6,5},{2,7,7,4},{3,3,7,7},{3,4,6,7},{3,4,7,6},{3,5,5,7},{3,5,6,6},{3,5,7,5},{3,6,4,7},{3,6,5,6},{3,6,6,5},{3,6,7,4},{3,7,3,7},{3,7,4,6},{3,7,5,5},{3,7,6,4},{3,7,7,3},{4,2,7,7},{4,3,6,7},{4,3,7,6},{4,4,5,7},{4,4,6,6},{4,4,7,5},{4,5,4,7},{4,5,5,6},{4,5,6,5},{4,5,7,4},{4,6,3,7},{4,6,4,6},{4,6,5,5},{4,6,6,4},{4,6,7,3},{4,7,2,7},{4,7,3,6},{4,7,4,5},{4,7,5,4},{4,7,6,3},{4,7,7,2},{5,1,7,7},{5,2,6,7},{5,2,7,6},{5,3,5,7},{5,3,6,6},{5,3,7,5},{5,4,4,7},{5,4,5,6},{5,4,6,5},{5,4,7,4},{5,5,3,7},{5,5,4,6},{5,5,5,5},{5,5,6,4},{5,5,7,3},{5,6,2,7},{5,6,3,6},{5,6,4,5},{5,6,5,4},{5,6,6,3},{5,6,7,2},{5,7,1,7},{5,7,2,6},{5,7,3,5},{5,7,4,4},{5,7,5,3},{5,7,6,2},{5,7,7,1},{6,1,6,7},{6,1,7,6},{6,2,5,7},{6,2,6,6},{6,2,7,5},{6,3,4,7},{6,3,5,6},{6,3,6,5},{6,3,7,4},{6,4,3,7},{6,4,4,6},{6,4,5,5},{6,4,6,4},{6,4,7,3},{6,5,2,7},{6,5,3,6},{6,5,4,5},{6,5,5,4},{6,5,6,3},{6,5,7,2},{6,6,1,7},{6,6,2,6},{6,6,3,5},{6,6,4,4},{6,6,5,3},{6,6,6,2},{6,6,7,1},{6,7,1,6},{6,7,2,5},{6,7,3,4},{6,7,4,3},{6,7,5,2},{6,7,6,1},{7,1,5,7},{7,1,6,6},{7,1,7,5},{7,2,4,7},{7,2,5,6},{7,2,6,5},{7,2,7,4},{7,3,3,7},{7,3,4,6},{7,3,5,5},{7,3,6,4},{7,3,7,3},{7,4,2,7},{7,4,3,6},{7,4,4,5},{7,4,5,4},{7,4,6,3},{7,4,7,2},{7,5,1,7},{7,5,2,6},{7,5,3,5},{7,5,4,4},{7,5,5,3},{7,5,6,2},{7,5,7,1},{7,6,1,6},{7,6,2,5},{7,6,3,4},{7,6,4,3},{7,6,5,2},{7,6,6,1},{7,7,1,5},{7,7,2,4},{7,7,3,3},{7,7,4,2},{7,7,5,1}
};

const int E = 0;

int grids[4][7][7] = 
{
    {
        { E, E, 4, E, E, E, E },
        { E, E, E, 6, E, E, E },
        { 5, E, E, E, E, E, E },
        { E, 3, E, E, E, 6, E },
        { E, E, E, E, E, E, 2 },
        { E, E, E, 1, E, E, E },
        { E, E, E, E, 4, E, E }
    },
    {
        { E, 2, E, E, E, E, E },
        { 2, E, E, E, E, E, E },
        { E, E, E, E, E, E, E },
        { E, E, E, E, E, 3, E },
        { E, E, E, E, 3, E, E },
        { E, E, E, 3, E, E, E },
        { E, E, E, E, E, E, 1 }
    },
    {
        { E, E, E, E, 4, E, E },
        { E, 6, E, E, E, E, E },
        { 4, E, E, E, E, E, 6 },
        { E, E, E, E, E, E, E },
        { 6, E, E, E, E, E, 4 },
        { E, E, E, E, E, 6, E },
        { E, E, 4, E, E, E, E }
    },
    {
        { E, E, E, E, E, E, E },
        { E, E, E, E, E, E, E },
        { E, E, E, E, E, E, 3 },
        { E, E, E, E, E, E, E },
        { E, E, E, E, 4, E, E },
        { E, E, E, E, E, E, E },
        { E, E, 3, E, E, E, E }
    }
};

int firstCols[4][7] =
{
    { 5, 4, E, E, E, 7, 5 },
    { E, E, 5, 6, E, 6, 7 },
    { 7, E, E, 5, E, 7, E },
    { E, E, E, E, E, E, E },
};

int firstRows[4][7] =
{
    { 5, 7, E, E, E, 5, 7 },
    { E, E, 5, 6, E, 7, 6 },
    { E, E, E, 7, E, E, E },
    { 1, 2, 3, 4, 5, 6, 7 },
};

int lastCols[4][7] =
{
    { 5, 7, E, E, E, 3, 6 },
    { 6, 7, 5, E, E, E, E },
    { E, 7, E, 3, E, E, 5 },
    { E, 6, E, 5, E, 4, E },
};

int lastRows[4][7] =
{
    { 7, 4, E, E, E, 7, 6 },
    { 6, 6, 4, E, E, E, E },
    { E, E, E, 5, E, E, E },
    { E, 6, E, 4, E, 2, E },
};

// ---- below structures will be filled at runtime

// current grid
int grid[7][7]; 
// final grid with all the sums
int sumGrid[7][7];

// number of cells that are pre-filled in each row
// (does not change throughout DFS, only when switching grids)
int ogRowCount[7];
// first and last numbers in each row (blue numbers)
int firstCol[7];
int lastCol[7];
// first and last numbers in each column (blue numbers)
int firstRow[7];
int lastRow[7]; 


// number of cells that we need to insert
// 28 - the number of given cells
int totAvail = 28;

// numAvail[i] = # of i we still need in grid
int numAvail[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
// sum that we still need in each row
int rowSums[7] = { 20, 20, 20, 20, 20, 20, 20 };
// number of cells that we need to fill in each row
int rowAvail[7] = { 4, 4, 4, 4, 4, 4, 4 };
// sum that we still need to fill in each column 
int colSums[7] = { 20, 20, 20, 20, 20, 20, 20 };
// number of nums that we need in each column
int colAvail[7] = { 4, 4, 4, 4, 4, 4, 4 };

// returns all data structures to prepare for the next grid dfs
void zeroOut() {
    totAvail = 28; 
    for (int i = 0; i < 7; i++) {
        numAvail[i + 1] = i + 1;
        rowSums[i] = 20;
        colSums[i] = 20;
        rowAvail[i] = 4;
        colAvail[i] = 4;
        ogRowCount[i] = 0;
    }
}

void printSumGrid() {
    cout << "Here's the final grid!" << endl; 
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            cout << sumGrid[i][j] << ' ';
        } cout << endl;
    } cout << endl;
}

// Prints out a grid. For debugging and successful cases
void printGrid(bool debug) 
{
    if (debug) {
        cout << "Row sums" << endl;
        for (int i = 0; i < 7; i++) {
            cout << rowSums[i] << ' ';
        } cout << endl;
        
        cout << "Row avail" << endl;
        for (int i = 0; i < 7; i++) {
            cout << rowAvail[i] << ' ';
        } cout << endl;
        
        cout << "Col sums" << endl;
        for (int i = 0; i < 7; i++) {
            cout << colSums[i] << ' ';
        } cout << endl;
        
        cout << "Col avail" << endl;
        for (int i = 0; i < 7; i++) {
            cout << colAvail[i] << ' ';
        } cout << endl;
      
        cout << "Num avail" << endl;
        for (int i = 0; i < 7; i++) {
            cout << numAvail[i + 1] << ' ';
        } cout << endl;
    
    }

    cout << "Current grid" << endl;
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            cout << grid[i][j] << ' ';
        } cout << endl;
    } cout << endl;
}

// checks if we have a fully connected grid
// this would literally take 10 lines in python. I hate htis
bool conn(int i, int j) {
    bool seen[7][7];
    for (int ti = 0; ti < 7; ti++) {
        for (int tj = 0; tj < 7; tj++) {
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
        if (ti != 6 and grid[ti+1][tj] > 0) {
            cur.push_back({ ti+1, tj });   
        }
        if (tj != 6 and grid[ti][tj+1] > 0) {
            cur.push_back({ ti, tj+1 });   
        }
    }

    return numSeen == 28;
}

// checks if inserting any number at grid[i][j] would cause any containing 2x2 square to lack a blank space
bool violatesTwoByTwo(int i, int j) {
    if (i > 0 and j > 0 and 
        grid[i-1][j-1] > 0 and 
        grid[i-1][j] > 0 and 
        grid[i][j-1] > 0) {
        return true;
    }

    if (i > 0 and j < 6 and
        grid[i-1][j+1] > 0 and 
        grid[i-1][j] > 0 and 
        grid[i][j+1] > 0) {
        return true;
    }
    
    if (i < 6 and j > 0 and
        grid[i+1][j-1] > 0 and 
        grid[i+1][j] > 0 and 
        grid[i][j-1] > 0) {
        return true;
    }
    
    if (i < 6 and j < 6 and
        grid[i+1][j+1] > 0 and 
        grid[i+1][j] > 0 and 
        grid[i][j+1] > 0) {
        return true;
    }

    return false;
}

bool violatesBlues(int i, int j, int num) {
    if (firstRow[i] != 0) {
        bool found = false;
        for (int cj = 0; cj < j; cj++) {
            if (grid[i][cj] > 0) {
                found = true;
                break;
            }
        }
       
        if (!found and num != firstRow[i]) {
            return true;
        }
    }

    if (firstCol[j] != 0) {
        bool found = false;
        for (int ci = 0; ci < i; ci++) {
            if (grid[ci][j] > 0) {
                found = true;
                break;
            }
        }
        
        if (!found and num != firstCol[j]) {
            return true;
        }
    }
    
    if (rowAvail[i] == 1 and lastRow[i] != 0) {
        bool found = false;
        for (int cj = 6; cj > j; cj--) {
            if (grid[i][cj] > 0) {
                found = true;
                break;
            }
        }

        if (!found and num != lastRow[i]) {
            return true;
        }
    }
    
    if (colAvail[j] == 1 and lastCol[j] != 0) {
        bool found = false;
        for (int ci = 6; ci > i; ci--) {
            if (grid[ci][j] > 0) {
                found = true;
                break;
            }
        }

        if (!found and num != lastCol[j]) {
            return true; }
    }

    return false;
}

// high-level: checks if we can insert num at grid[i][j]
bool canInsert(int i, int j, int num) {
    bool numsAvail = numAvail[num] != 0;
    bool notViolatingTwoByTwo = not violatesTwoByTwo(i, j);
    bool notLeavingRowScore = (num == rowSums[i] and rowAvail[i] == 1) or
                              (num < rowSums[i] and rowAvail[i] > 1);
    bool notLeavingColScore = (num == colSums[j] and colAvail[j] == 1) or
                              (num < colSums[j] and colAvail[j] > 1);
    bool notViolatingBlues = not violatesBlues(i, j, num);
    
    return ((grid[i][j] == num) or (numsAvail and 
                                    notViolatingTwoByTwo and
                                    notLeavingColScore and
                                    notLeavingRowScore)) and
           notViolatingBlues; 
}

// recursive backtracking function
bool dfs(int i) {
    // for each bitmask of integer positions
    for (auto& bitmask: sevenChooseFour) {
        vector<int> mask;
        for (int mi = 0; mi < 7; mi++)
        {
            if ((bitmask >> mi) & 1) {
                mask.push_back(mi);
            }
        }
        
        // try to fit every valid combination of 1-7 into this mask 
        for (unsigned int ci = 0; ci < combs.size(); ci++) {
            vector<int> thisComb = combs[ci];
            vector<bool> notOccs;
            bool succ = true;
            int occs = 0;
            // assign values to the mask indices based on this combination
            for (int mi = 0; mi < 4; mi++) {
                int num = thisComb[mi];
                int j = mask[mi];
                bool notOcc = (grid[i][j] == 0);
                notOccs.push_back(notOcc);
                if (grid[i][j] == num or
                    (notOcc and canInsert(i, j, num))) {
                    if (notOcc) {
                        grid[i][j] = num;
                        numAvail[num] -= 1;
                        rowSums[i] -= num;
                        rowAvail[i] -= 1;
                        colSums[j] -= num;
                        colAvail[j] -= 1;
                    } else {
                        occs += 1;
                    }
                } else {
                    notOccs.pop_back();
                    succ = false;
                    break;
                }
            }

            // if we succeeded...
            if (succ and occs == ogRowCount[i]) {
                // if we're at the end, and we have a connected graph, we should be all done
                if (i == 6 and conn(i, mask[0])) {
                    cout << "Success! Final grid:" << endl;
                    
                    for (int si = 0; si < 7; si++) {
                        for (int sj = 0; sj < 7; sj++) {
                            sumGrid[si][sj] += grid[si][sj];
                        }
                    }

                    printGrid(false);
                    return true;
                // if we aren't at the end, keep going in the next row
                } else if (i < 6) {
                    if (dfs(i + 1)) return true;
                }
            }
            
            // undo changes and try the next combination 
            for (unsigned int it = 0; it < notOccs.size(); it++) {
                int j = mask[it];
                int num = grid[i][j];
                if (notOccs[it]) {
                    grid[i][j] = 0;
                    numAvail[num] += 1;
                    rowSums[i] += num;
                    rowAvail[i] += 1;
                    colSums[j] += num;
                    colAvail[j] += 1;
                }
            }
        }
    }

    return false;
}

int main() 
{
    /* Rules:
     * 1. There will be n instances of n in the board (i.e. 4 4's, 5 5's, etc).
     * 2. Every row and column should have exactly 4 numbers in it.
     * 3. Every row and column should add up to 20.
     * 4. The blue number in front of each row or column should be the first number seen in that row or column from that side.
     * 5. Every 2x2 square of cells should have at least one empty space.
     * 6. Every cell with a number in it should form a single connected component.
     */

    for (int si = 0; si < 7; si++) {
        for (int sj = 0; sj < 7; sj++) {
            sumGrid[si][sj] = 0;
        }
    }

    for (int g = 0; g < 4; g++) {
        for (int i = 0; i < 7; i++) {
            firstCol[i] = firstCols[g][i];
            firstRow[i] = firstRows[g][i];
            lastCol[i] = lastCols[g][i];
            lastRow[i] = lastRows[g][i];

            for (int j = 0; j < 7; j++) {
                grid[i][j] = grids[g][i][j];

                if (grid[i][j] > 0) {
                    ogRowCount[i] += 1;
                    totAvail -= 1;
                
                    rowAvail[i] -= 1;
                    rowSums[i] -= grid[i][j];

                    colAvail[j] -= 1;
                    colSums[j] -= grid[i][j];

                    numAvail[grid[i][j]] -= 1;
                }
            }
        }

        cout << "Solving grid #" << g + 1 << ":" << endl;
        printGrid(false);
        if (g == 3) 
            cout << "This one may take a while!" << endl;
        dfs(0);
        zeroOut();
        printSumGrid();
    }

    printSumGrid();

    unsigned int s = 0;
    for (int si = 0; si < 7; si++) {
        for (int sj = 0; sj < 7; sj++) {
            s += sumGrid[si][sj] * sumGrid[si][sj];
        }
    }

    cout << "The solution is " << s << endl;
    return 0;
}
