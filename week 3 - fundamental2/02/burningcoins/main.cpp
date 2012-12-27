#include <iostream>
#include <vector>
#include <cassert>

using namespace std;


pair<int, int> him(vector<vector<pair<int, int> > >& map, vector<int>& values, int left, int right);

pair<int, int> me(vector<vector<pair<int, int> > >& map, vector<int>& values, int left, int right) {
    if (left==right) {
        return make_pair(values[left], 0);
    }
    int d = right-left;
    if (d <= 2) {
        // Case [left|right]
        int l = values[left];
        int m = values[left+1];
        int r = values[right];
        if (d == 1) {
            if (l>r) {
                return make_pair(l,r);
            }
            return make_pair(r,l);
        }
        // Case [left|middle|right]
        int v;
        int v2 = 0;
        if (l>r) {
            v = l;
            if (m > r) {
                v += r;
                v2 += m;
            } else {
                v += m;
                v2 += r;
            }
        } else {
            v = r;
            if (m > l) {
                v += l;
                v2 += m;
            } else {
                v += m;
                v2 = l;
            }
        }
        return make_pair(v,v2);
    }

    pair<int, int> l = him(map, values, left+1, right);
    pair<int, int> r = him(map, values, left, right-1);
    if (l.first+values[left] > r.first+values[right]) {
        return make_pair(l.first+values[left], l.second);
    }
    map[left][right].first = r.first+values[right];
    map[left][right].second = r.second;
//    return make_pair(r.first+values[right], r.second);
    return map[left][right]
}

pair<int, int> him(vector<vector<pair<int, int> > >& map, vector<int>& values, int left, int right) {
    if (left==right) {
        return make_pair(0,values[left]);
    }
    int d = right-left;
    if (d <= 1) {
        // Case [left|right]
        int l = values[left];
        int r = values[right];
        if (d == 1) {
            if (l>r) {
                return make_pair(r,l);
            }
            return make_pair(l,r);
        }
        assert(false);
    }
    pair<int, int> l = me(map, values, left+1, right);
    pair<int, int> r = me(map, values, left, right-1);
    if (l.second+values[left] > r.second+values[right]) {
        return make_pair(l.first, l.second+values[left]);
    }
    return make_pair(r.first, r.second+values[right]);
}

void testcase() {
    vector<int> values;

    int n;
    cin >> n;
    if (n==0) {
        cout << 0 << endl;
        return;
    }
    vector<vector<pair<int, int> > > map(n+1,  vector<pair<int, int> >(n+1, make_pair(-1,-1)));

    for (int i=0; i<n; i++) {
        int t;
        cin >> t;
        values.push_back(t);
    }

//    int max = recursion(map, values, 0, n-1);
    pair<int, int> ret = me(map, values, 0, n-1);
    cout << ret.first << endl;
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
