#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

void testcase() {
    int w,h; // width, height
    cin >> w;
    cin >> h;

    int s,r; // strip height, strip length
    cin >> s;
    cin >> r;

    int n; // trees
    cin >> n;

    // Reversed indexing
    vector<vector<int> > area(h+1, vector<int>(0));
    vector<vector<int>::iterator > lt(h+1);
    // Fill in trees
    for (int k=0; k<n; k++) {
        int x,y;
        cin >> x;
        cin >> y;
        area[y].push_back(x);
    }

    for (vector<vector<int> >::iterator it=area.begin(); it!=area.end(); it++) {
        sort(it->begin(), it->end());
    }
    for (int i=0; i<(h+1); i++) {
        lt[i] = area[i].begin();
    }

    for (int i=0; i<=(w-r); i++) {
//        cout << "i: " << i << "\n";
        int j=0;
        while (j <= (h-s)) {
            int notempty = 0;
            for (int l=1; l<s; l++) {
                vector<int>& loc = area[j+l];
                int foundtree = 0;
                int maxRange = i+r;
                vector<int>::iterator it = lt[j+l];
                for (; it!=loc.end(); it++) {
                    int v = *it;
                    if (v > i) {
                        if (v < maxRange ) {
                            lt[j+l] = it;
                            foundtree = 1;
                        }
                        break;
                    }
                }

                if (foundtree) {
                    notempty = 1;
                    j += (l);
                    if (l==0)
                        j++;
                    break;
                }
            }

            if (!notempty) {
                cout << i << " " << j << "\n";
                return;
            }
        }
    }
    cout << "Impossible\n";

}

int main() {
    int testcases;
    cin >> testcases;
    for (int i=0; i<testcases; i++) {
        testcase();
    }
}
