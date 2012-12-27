#include <iostream>
#include <vector>
using namespace std;

inline int compute(vector<int>& values, vector<int>& sums, int Sn, int i, int j) {
    return Sn-(sums[j]-sums[i-1])+(j-i+1)*values[j];
}

void testcase() {
    vector<int> values;
    values.push_back(0);
    vector<int> sums;
    sums.push_back(0);

    int n;
    cin >> n;
    if (n==0) {
        cout << 0 << endl;
        return;
    }

    int sum = 0;
    for (int i=0; i<n; i++) {
        int t;
        cin >> t;
        values.push_back(t);
        sum += t;
        sums.push_back(sum);
    }

    int Sn = sums.back();
    int r = compute(values, sums, Sn, 1,2);

    for (int i=1; i<=n; i++) {
        for (int j=i+1; j<=n; j++) {
            int k = compute(values, sums, Sn, i,j);
            if (k>r) {
                r = k;
            }

        }
    }
    cout << r << endl;
//    cout << recursion(map, values, 0, n-1) << endl;
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

