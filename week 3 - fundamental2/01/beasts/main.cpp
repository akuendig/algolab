#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>

using namespace std;

int prev_run;
int counter_fallof;

#define MAX_GRID 100
bool tried[MAX_GRID+1][MAX_GRID+1];
int grid[MAX_GRID+1];
int n;
// Recursive Method: Slow
bool recursion(int depth) {
    if (depth > n) {
        return true;
    }

    int irun;
    tried[depth][0] = true;
    fill(&tried[depth][1], &tried[depth][n+1],false);
    int z = n+1;
    for (int i=0; i<n; i++) {
        while(true) {
            irun = (rand())%(z);
            if (!tried[depth][irun]) {
                break;
            }
//            cout << depth << " " << irun << endl;
        }
        tried[depth][irun] = true;

        bool cont = false;
        for (int j=1; j < depth; j++) {
            int l = grid[depth-j];
            if (grid[j] == irun || l == (irun-j) ||l == (irun+j)) {
                cont = true;
                break;
            }
        }
        if (cont) {
            continue;
        }

        grid[depth] = irun;

        if (recursion(depth+1)) {
            return true;
        }
    }
    return false;
}

void testcase() {
//    int n;
    cin >> n;
//    vector<int> grid(n+1,0);
//    for (int i=0; i < n+1; i++) {
//        grid[i] = i;
//    }
    if (recursion(1)) {
        for (int i=1; i<=n; i++) {
            cout << grid[i] << " ";
        }
        cout << endl;
        return;
    }
    cout << "Impossible" << endl;
    prev_run = n;
}

int main()
{
    srand(time(NULL));
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int testcases;
    cin >> testcases;
    prev_run = -1;

    for (int i=0; i<testcases; i++) {
//        testcase(grid);
        testcase();
    }
    return 0;
}
