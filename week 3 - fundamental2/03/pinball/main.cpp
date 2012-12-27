#include <iostream>
#include <vector>
using namespace std;

/**
SPOILER <<<

    First find the optimal placement for the median of S.
    This gives an upper bound for every element in S which
    is smaller than the median, and a lower bound for every
    element which is larger then the median. Then try to recursively
    continue in this manner. Hope this helps!

>>>
*/
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
    sums.reserve(n+1);
    values.reserve(n+1);
    for (int i=0; i<n; i++) {
        int t;
        cin >> t;
        values.push_back(t);
        sum += t;
        sums.push_back(sum);
    }

    // Set active values
    vector<int> active(n+1,0);
    int a = 0;
    for (int i=1; i<n; i++) {
        if (values[i] > values[i+1]) {
            if (a == 0) {
                active[i] = 1;
            }
            a++;
        } else {
            if (a > 0) {
                active[i-1] = 1;
            }
            a=0;
        }
    }
    if (a > 0) {
        active[n-1] = 1;
    }
    active[n] = 1;
//    for (vector<int>::iterator it=active.begin(); it!=active.end(); it++) {
//        cout << *it << " ";
//    }
//    cout << endl;

    int Sn = sums.back();
    int r = compute(values, sums, Sn, 1,2);

    for (int j=n; j>0; j--) {

        int Sj = sums[j];
        int SnSj = Sn-Sj;
        int vj = values[j];
        if (active[j]) {
            for (int i=1; i<j; i++) {
                if (!(active[i] || active[i-1])) {
                    continue;
                }
                int k = SnSj+sums[i-1]+(j-i+1)*vj;
                if (k>r) {
                    r = k;
//                    cout << i << " " << j << endl;
                }
            }
        }
    }
    cout << r << endl;
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

