#include <iostream>
#include <vector>
#include <set>
#include <cassert>
#include <algorithm>

using namespace std;

set<int> unknown;
set<int> unequal;
set<int> eq;
bool valfind(int v, set<int>& vec) {
    if (find(vec.begin(), vec.end(), v) == vec.end())
        return false;
    return true;
}

void check(int c, vector<int>& values) {
    for (unsigned int i=0; i<values.size(); i++) {
        if ((i+1) == values.size()/2)
            c *= -1;
        int value = values[i];
        if (c == 0) {
            if (valfind(value, unequal)) {
                // Remove from unequal and add it to equal
                unequal.erase(value);
            }
            eq.insert(eq.end(), value);
        } else {
            if (!valfind(value, eq))
                unequal.insert(unequal.end(), value);
        }
        unknown.erase(value);
    }
}

void testcase() {
    int coins;
    int weightings;
    cin >> coins;
    cin >> weightings;
    unequal.clear();
    unknown.clear();
    eq.clear();
    for (int i=1;i<=coins;i++) {
        unknown.insert(unknown.end(),i);
    }
    for (int i=0; i<weightings; i++) {
        int values;
        cin >> values;
        vector<int> input(values*2);
        for (int i=0; i<values*2; i++) {
            cin >> input[i];
        }
        char c;
        cin >> c;
        int wcase = 0; // 0  => "="
                       // <0 => "<"
                       // >0 => ">"
        if (c == '<')
            wcase = -1;
        else if (c == '>')
            wcase = 1;
        else
            wcase = 0;

        check(wcase, input);
    }
}

int main() {
    int testcases;
    cin >> testcases;
    for (int i=0; i<testcases;i++) {
        testcase();
        if (unequal.size() == 1) {
            cout << *unequal.begin();
        }
        else if (unequal.size() == 0 && unknown.size() == 1)
            cout << *unknown.begin();
        else
            cout << 0;

        cout << "\n";

    }
    return 0;
}
