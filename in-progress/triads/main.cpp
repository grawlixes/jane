#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

// bad practice? yes. lazy? maybe. but I don't want to write std:: over and over, lol
using namespace std;

/* strategy
 * create a graph for N = 39, and move from the top to bottom, left to right trying to connect triads. every dot starts with value 0, and they must end up with 1. A dot can connect with any two adjacent dots that are also adjacent; if there are <2 adjacent dots that are also adjacent, the current configuration is infeasible.
 *
 * the key is to "settle up" the row above the current one. we can't leave anything 0, and if we move on to row i + 1 when i - 1 has 0s, then we'll violate that rule.
 * Additionally, we don't necessarily have to "settle up" row i before moving on to row i + 1; however, if we do, then we have a success for N = i + 1. If we do this, then we'll mark successes[i] = true. after our dfs all we have to do is add up i + 1 for every i s.t. successes[i] == true.
 */

// number of rows to check up to 
const int N = 39;
// successes[i] = true means that we were able to build the triangle up to row i + 1 with disjoint triads. false means we failed
bool successes[N];
// for row i, only dots 0 <= j <= i + 1 will be used. don't feel like using a vector. lol
// 0 = no triad containing this dot yet, 1 = triad exists for this dot
bool grid[N][N];
// number of taken dots in the next row
// if we finish row i and this is 0, then we know we can make the current triangle of size i+1 out of disjoint triads
int nextUsed = 0;

/*     .   .
 *   .   ,   .
 * .   .   .   .
 *
 * let the comma represent dot (i, j). it can connect to:
 *  (i - 1, j - 1)
 *  (i - 1, j)
 *  (i, j - 1)
 *  (i, j + 1)
 *  (i + 1, j)
 *  (i + 1, j + 1)
 *
 *  this function will return all pairs (of pairs of indices) that we can make a triad out of. the dots at those pairs must not belong to a different triad already 
 */

void prettyPrint(int lim = N - 1) {
    for (int i = 0; i <= lim; i++) {
        for (int k = lim; k > i; k--) {
            cout << ' ';
        }
        for (int j = 0; j <= i; j++) {
            cout << grid[i][j] << ' ';
        } cout << endl;
    }
}

typedef vector<vector<vector<int>>> CONN_LIST;
CONN_LIST getConnections(int i, int j) {
    
    vector<vector<int>> canConnect =
        {
            {
                i, j + 1,
                j < i and
                grid[i][j + 1] == 0
            },
            {
                i + 1, j + 1,
                i < N - 1 and
                grid[i + 1][j + 1] == 0
            },
            {
                i + 1, j,
                i < N - 1 and
                grid[i + 1][j] == 0
            },
        };

    CONN_LIST ret;

    for (int k = 0; k < 3 - 1; k++) {
        vector<int> here = canConnect[k];
        vector<int> next = canConnect[(k + 1) % 
                                      3];

        if (here[2] and next[2]) {
            ret.push_back({
                              { here[0], here[1] },
                              { next[0], next[1] }
                          });
        }
    }    

    return ret;
}

void dfs(int i, int j);

void callNext(int i, int j) {
    if (j == i) {
        if (nextUsed == 0) {
            if (not successes[i]) {
                cout << "Success at row " << i + 1 << endl;
                successes[i] = true;
            } else {
                return;
            }
        }
        
        if (i != 17 and i != N - 1) {
            int oldNextUsed = nextUsed;
            nextUsed = 0;

            dfs(i + 1, 0);
            nextUsed = oldNextUsed;
        }
    } else {
        dfs(i, j + 1);
    }
}

void dfs(int i, int j) {
    if (grid[i][j] == 0) {
        CONN_LIST cList = getConnections(i, j);
        grid[i][j] = 1;
        
        for (auto& c: cList) {
            vector<int> f = c[0];
            vector<int> s = c[1];
            
            grid[f[0]][f[1]] = 1;
            grid[s[0]][s[1]] = 1;
     
            nextUsed += (f[0] > i) +
                        (s[0] > i);
            
            callNext(i, j);
            
            nextUsed -= (f[0] > i) +
                        (s[0] > i);
            grid[f[0]][f[1]] = 0;
            grid[s[0]][s[1]] = 0;
        }
        
        grid[i][j] = 0;
    } else {
        callNext(i, j);
    }

    return;
}

int main() {
    dfs(0, 0);

    int ret = 0;
    for (int i = 0; i < N; i ++) {
        ret += successes[i] * (i + 1);
    }

    cout << "The answer is " << ret << '.' << endl;;
    return 0;
}
