// unsolved for now

int perms[126][5] = {{2, 0, 1, 1, 1}, {0, 1, 0, 1, 3}, {2, 1, 0, 0, 2}, {0, 1, 0, 2, 2}, {0, 2, 3, 0, 0}, {1, 0, 4, 0, 0}, {1, 1, 0, 0, 3}, {0, 3, 0, 1, 1}, {3, 2, 0, 0, 0}, {0, 1, 4, 0, 0}, {0, 0, 2, 0, 3}, {4, 0, 0, 1, 0}, {0, 1, 2, 2, 0}, {2, 2, 0, 0, 1}, {1, 0, 0, 0, 4}, {0, 2, 1, 1, 1}, {2, 0, 0, 2, 1}, {0, 1, 3, 1, 0}, {0, 2, 2, 1, 0}, {0, 3, 0, 0, 2}, {0, 2, 2, 0, 1}, {1, 0, 3, 0, 1}, {1, 0, 1, 3, 0}, {0, 0, 5, 0, 0}, {1, 0, 0, 2, 2}, {0, 0, 0, 4, 1}, {3, 0, 0, 0, 2}, {2, 0, 0, 1, 2}, {1, 4, 0, 0, 0}, {1, 1, 2, 1, 0}, {0, 0, 3, 2, 0}, {0, 0, 1, 4, 0}, {2, 0, 1, 2, 0}, {1, 0, 1, 2, 1}, {0, 1, 0, 3, 1}, {3, 0, 1, 1, 0}, {0, 1, 1, 2, 1}, {2, 0, 2, 0, 1}, {0, 0, 0, 1, 4}, {0, 0, 4, 0, 1}, {0, 0, 3, 1, 1}, {0, 2, 0, 1, 2}, {0, 0, 2, 2, 1}, {1, 3, 1, 0, 0}, {0, 4, 0, 1, 0}, {3, 1, 0, 1, 0}, {0, 1, 2, 0, 2}, {1, 2, 1, 0, 1}, {3, 0, 0, 1, 1}, {0, 1, 1, 0, 3}, {1, 0, 1, 0, 3}, {0, 1, 0, 4, 0}, {0, 3, 2, 0, 0}, {1, 1, 2, 0, 1}, {2, 2, 1, 0, 0}, {2, 0, 2, 1, 0}, {1, 1, 1, 1, 1}, {2, 1, 0, 2, 0}, {2, 0, 3, 0, 0}, {2, 1, 1, 0, 1}, {1, 3, 0, 0, 1}, {0, 1, 2, 1, 1}, {0, 0, 0, 3, 2}, {0, 0, 1, 2, 2}, {1, 1, 0, 1, 2}, {1, 2, 0, 2, 0}, {4, 1, 0, 0, 0}, {1, 0, 0, 4, 0}, {2, 1, 0, 1, 1}, {1, 2, 0, 0, 2}, {0, 0, 1, 1, 3}, {0, 2, 0, 3, 0}, {1, 0, 3, 1, 0}, {0, 3, 1, 0, 1}, {1, 1, 1, 2, 0}, {1, 0, 2, 2, 0}, {2, 2, 0, 1, 0}, {3, 0, 2, 0, 0}, {1, 1, 0, 2, 1}, {4, 0, 1, 0, 0}, {1, 1, 3, 0, 0}, {1, 0, 0, 3, 1}, {0, 0, 4, 1, 0}, {5, 0, 0, 0, 0}, {2, 0, 1, 0, 2}, {0, 1, 0, 0, 4}, {0, 0, 2, 3, 0}, {0, 0, 1, 3, 1}, {3, 0, 0, 2, 0}, {0, 0, 2, 1, 2}, {4, 0, 0, 0, 1}, {0, 2, 1, 0, 2}, {1, 2, 1, 1, 0}, {0, 1, 1, 3, 0}, {0, 0, 0, 0, 5}, {0, 5, 0, 0, 0}, {0, 1, 3, 0, 1}, {0, 0, 0, 5, 0}, {1, 2, 2, 0, 0}, {2, 0, 0, 3, 0}, {0, 0, 1, 0, 4}, {1, 0, 1, 1, 2}, {2, 1, 2, 0, 0}, {2, 0, 0, 0, 3}, {2, 1, 1, 1, 0}, {1, 3, 0, 1, 0}, {0, 4, 1, 0, 0}, {0, 2, 0, 2, 1}, {3, 1, 1, 0, 0}, {1, 2, 0, 1, 1}, {1, 0, 2, 1, 1}, {1, 0, 2, 0, 2}, {3, 0, 1, 0, 1}, {1, 1, 0, 3, 0}, {1, 0, 0, 1, 3}, {0, 1, 1, 1, 2}, {0, 3, 0, 2, 0}, {0, 2, 0, 0, 3}, {0, 2, 1, 2, 0}, {1, 1, 1, 0, 2}, {0, 3, 1, 1, 0}, {0, 4, 0, 0, 1}, {3, 1, 0, 0, 1}, {0, 0, 0, 2, 3}, {0, 0, 3, 0, 2}, {2, 3, 0, 0, 0}};
// perms is up here ^

#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

int main(int argv, char ** argc) {
    unsigned long long successful = 0;
    unsigned long long valid = 0;
    
    for (int kid1 = 0; kid1 < 126; kid1++) {
    for (int kid2 = kid1; kid2 < 126; kid2++) {
    for (int kid3 = kid2; kid3 < 126; kid3++) {
    for (int kid4 = kid3; kid4 < 126; kid4++) {
    for (int kid5 = kid4; kid5 < 126; kid5++) {
        // I know that this indentation is weird, but it'd waste too much space otherwise.
        int indices[5] = {kid1, kid2, kid3, kid4, kid5};
        int colsAddTo[5] = {0, 0, 0, 0, 0};
        int thisPerm[5][5];

        for (int kid = 0; kid < 5; kid++) {
            for (int candy = 0; candy < 5; candy++) {
                int c = perms[indices[kid]][candy];
                colsAddTo[candy] += c;
                thisPerm[kid][candy] = c; 
            }
        }

        bool addTo5 = true;
        for (int candy = 0; candy < 5; candy++) {
            if (colsAddTo[candy] != 5) {
                addTo5 = false;
                break;
            }
        }
        if (not addTo5) {
            continue;
        }

        bool singularMax = true;
        bool childMax[5] = {false, false, false, false, false};
        for (int candy = 0; candy < 5; candy++) {
            int maxKid = 0;
            int maxCt = thisPerm[0][candy];
            int withTwo = 0;
            for (int kid = 0; kid < 5; kid++) {
                if (thisPerm[kid][candy] == 2) {
                    withTwo += 1;
                }
                if (maxCt < thisPerm[kid][candy]) {
                    maxKid = kid;
                    maxCt = thisPerm[kid][candy];
                }
            }
            
            // fails if the current child already has a maximum, the max count is 1, or there's more than 1 kid with two candies.
            if (childMax[maxKid] or 
                maxCt == 1 or 
                (withTwo > 1 and maxCt == 2)) {
                singularMax = false;
                break;
            }
            childMax[maxKid] = true;
        }

        if (singularMax) {
            successful += 1;
        }
        valid += 1;
    }
    }
    }
    }
    cout << kid1 << "/126" << endl;
    }

    cout << successful << endl;
    cout << valid << endl;
    return 0;
}
