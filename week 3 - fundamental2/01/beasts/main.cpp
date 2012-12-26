#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;
int prev_run;
int counter_fallof;
bool recursion(vector<int>& grid, int depth, int n) {
//    cout << depth << endl;
    if (depth > n) {
        return true;
    }
    // Reuse the values
    if (prev_run > n && depth <= prev_run) {
        if (recursion(grid, depth+1, n)) {
            return true;
        }
        prev_run = -1;
    }
    if (depth == 1) {
        for (int i=1; i<= n; i++) {
            grid[depth] = i;
            if (recursion(grid, depth+1, n)) {
                return true;
            }
        }
        return false;
    }
    int counter = 0;
    for (int i=1; i<= n; i++) {
//        grid[depth] = i;
//        if (grid[depth-1] == (i-1) || grid[depth-1] == (i+1)) {
//            // i++;
//            continue;
//        }
        bool cont = false;
        for (int j=1; j < depth; j++) {
            int l = grid[depth-j];
            if (grid[j] == i || l == (i-j) ||l == (i+j)) {
                cont = true;
                break;
            }
        }
        if (cont) {
            if (n > 40) {
                if (counter > counter_fallof) {
                    return false;
                }
                counter++;
                i = rand()%(n+1);
            } else if (n > 20) {
                if (counter > 30) {
                    return false;
                }
                counter++;
                i = rand()%(n+1);
            }
            continue;
        }
        grid[depth] = i;

        if (recursion(grid, depth+1, n)) {
            return true;
        }
    }
    return false;
}

void testcase(vector<int>& grid) {
    int n;
    cin >> n;
//    vector<int> grid(n+1,0);
    counter_fallof = int(double(n)*0.8);
    if (recursion(grid, 1, n)) {
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
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int testcases;
    cin >> testcases;
    prev_run = -1;
    vector<int> grid(101,0);

    for (int i=0; i<testcases; i++) {
        testcase(grid);
    }
    return 0;
}
