#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


int recursion(vector<vector<int > >& map, vector<int>& values, int left, int right) {
    if (left==right) {
        return values[left];
    }
    if (map[left][right] > 0) {
        return map[left][right];
    }
    int d = right-left;
    if (d <= 2) {
        // Case [left|right]
        int l = values[left];
        int m = values[left+1];
        int r = values[right];
        if (d == 1) {
            if (l>r) {
                return l;
            }
            return r;
        }
        // Case [left|middle|right]
        int v;
        if (l>r) {
            v = l;
            if (m > r) {
                v += r;
            } else {
                v += m;
            }
        } else {
            v = r;
            if (m > l) {
                v += l;
            } else {
                v += m;
            }
        }
        return v;
    }

    // We choose the left value:
    int ll = recursion(map, values, left+2, right);   // He chose the left value as well
    int lr = recursion(map, values, left+1, right-1); // Chose the right value

    // We choose the right value
    int rl = lr;
    int rr = recursion(map, values, left, right-2);

    int k = max(values[left]+min(ll, lr),
                values[right]+min(rl, rr));
    map[left][right] = k;
    //    return make_pair(r.first+values[right], r.second);
    return k;
}


void testcase() {
    vector<int> values;

    int n;
    cin >> n;
    if (n==0) {
        cout << 0 << endl;
        return;
    }
    vector<vector<int > > map(n+1,  vector<int>(n+1, -1));

    for (int i=0; i<n; i++) {
        int t;
        cin >> t;
        values.push_back(t);
    }

//    int max = recursion(map, values, 0, n-1);
    cout << recursion(map, values, 0, n-1) << endl;
//    pair<int, int> ret = me(map, values, 0, n-1);
//    cout << ret.first << endl;
}

int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int testcases;
    cin >> testcases;

    for (int i=0; i<testcases; i++) {
        testcase();
    }
    return 0;
}
