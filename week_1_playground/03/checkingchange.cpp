#include <iostream>
#include <vector>
#include <cassert>
#include <climits>
using namespace std;
#define MAXCOINS 101
#define MAXCURRENCY 10001

vector<int> visited(MAXCURRENCY+1, 0);
vector<int> possible(MAXCURRENCY+1, 0);
vector<vector<int> > db(MAXCURRENCY+1, vector<int>(MAXCOINS, 0));

int countCoins(vector<int>& coins, int value) {
    int r = 0;
    assert(value >= 0);
    assert(db[value].size() >= coins.size());
    for (unsigned int i=0; i<coins.size();i++) {
        r+= db[value][i];
    }
    return r;
}

int checkValue(vector<int>& coins, int value) {
    int r = 0;
    assert(value >= 0);
    assert(db[value].size() >= coins.size());
    for (unsigned int i=0; i<coins.size();i++) {
        r+= db[value][i]*coins[i];
    }
    return r;
}
// Broken

void recursion(vector<int>& coins, int value) {
    if (value <= 0)
        return;
    if (visited[value])
        return;
    visited[value] = 1;
    if (value < coins[0]) {
        possible[value] = 0;
        return;
    }
    if (value <= coins.back()) {
        for (unsigned int i=0; i<coins.size(); i++) {
            if (value == coins[i]) {
                possible[value] = 1;
                fill(db[value].begin(), db[value].end(), 0);
                db[value][i] = 1;
                return;
            }
        }
//        possible[value] = 0;
//        return;
    }

    int min = -1;
    int minCoins = INT_MAX;
    // Search for minimum
    for (unsigned int i=0; i < coins.size(); i++) {
        int checkVal = value-coins[i];
        if (checkVal < 0)
            continue;
        recursion(coins, checkVal);
        if (possible[checkVal]) {
            int numCoins = countCoins(coins, checkVal);
            if (numCoins < minCoins) {
                min = i;
                minCoins = numCoins;
            }
        }
    }

    if (min == -1) {
        possible[value] = 0;
        return;
    }
    assert(min >= 0);
    // Update
//    for (unsigned int i=0; i < coins.size(); i++) {
//        copy(db[value].begin(), db[value].end(), db[value-coins[min]].begin());
//        db[value][i] += db[value][i];
//    }
    possible[value] = 1;
    copy( db[value-coins[min]].begin(), db[value-coins[min]].end(), db[value].begin());
    db[value][min] += 1;
}

void test(vector<int>& coins, int value) {

    recursion(coins, value);
    int numCoins = 0;
    for (unsigned int i=0; i<coins.size();i++) {
        numCoins += db[value][i];
    }
    if (!possible[value])
        cout << "not possible\n";
    else
        cout << numCoins << "\n";
}

void testcase() {
    int nCoins;
    int nTestValues;
    cin >> nCoins;
    cin >> nTestValues;

    vector<int> coins(nCoins);
    // Read coins
    for (int i=0; i<nCoins;i++)
        cin >> coins[i];
    // Read and process test values
    int testval;
    fill(visited.begin(), visited.end(), 0);
    possible[0] = 1;
    for (int i=0; i<nTestValues;i++) {
        //cin >> testvalues[i];
        cin >> testval;
        test(coins, testval);
    }
}

int main() {
    int nTestcases;
    cin >> nTestcases;

    for (int i=0; i < nTestcases; i++) {
        testcase();
    }
}
