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

    vector<vector<int> > area(w+1, vector<int>(0));

    // Fill in trees
    for (int k=0; k<n; k++) {
        int x,y;
        cin >> x;
        cin >> y;
        area[x].push_back(y);
    }

    for (vector<vector<int> >::iterator it=area.begin(); it!=area.end(); it++) {
        sort(it->begin(), it->end());
    }

    for (int i=0; i<=(w-r); i++) {
//        cout << "i: " << i << "\n";
        int j=0;
        while (j <= (h-s)) {
            int notempty = 0;
            for (int k=1; k<r; k++) {
                for (int l=1; l<s; l++) {
                    vector<int>& loc = area[i+k];
//                    if (find(loc.begin(), loc.end(), j+l) != loc.end()) {
//                     if (binary_search(loc.begin(), loc.end(), j+l)) {
//                    if (area[i+k][j+l] > 0) {
                    int foundtree = 0;
                    int maxRange = j+s;
                    for (vector<int>::iterator it=loc.begin(); it!=loc.end(); it++) {
                        int v = *it;
                        if (v > j && v < maxRange ) {
                            foundtree = 1;
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
                if (notempty)
                    break;
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
