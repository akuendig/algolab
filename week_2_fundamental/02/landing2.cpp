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

    vector<vector<char> > area(w+1, vector<char>(h+1,  0));

    // Fill in trees
    for (int k=0; k<n; k++) {
        int x,y;
        cin >> x;
        cin >> y;
        area[x][y] =  1;
    }

    for (int i=0; i<=(w-r); i++) {
//        cout << "i: " << i << "\n";
        int j=0;
        while (j <= (h-s)) {
            int notempty = 0;
            for (int k=1; k<r; k++) {
                for (int l=1; l<s; l++) {
                    if (area[i+k][j+l] > 0) {
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
