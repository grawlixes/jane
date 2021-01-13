#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm>

// bad practice? yes. lazy? maybe. but I don't want to write std:: over and over, lol
using namespace std;

int main() {
    vector<int> thing;
    
    for (int i = 0; i < 300000000; i++) {
        thing.push_back((5*i + 3 - 3) / 2);
    }
    return 0;
}
