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
    vector<int> activearr;
    int a = 0;
    for (int i=1; i<n; i++) {
        if (values[i] > values[i+1]) {
            if (a == 0) {
                activearr.push_back(i);
            }
            a++;
        } else {
            if (a > 0) {
                if (activearr.back() != (i-1)) {
                    activearr.push_back(i-1);
                }
            }
            a=0;
        }
    }
    if (a > 0) {
        if (activearr.back() != (n-1)) {
            activearr.push_back(n-1);
        }
    }
    if (!activearr.back() != (n)) {
        activearr.push_back(n);
    }

//    for (vector<int>::iterator it=active.begin(); it!=active.end(); it++) {
//        cout << *it << " ";
//    }
//    cout << endl;

//    cout << "Active Array" << endl;
//    for (vector<int>::iterator it=activearr.begin(); it!=activearr.end(); it++) {
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
            for (vector<int>::iterator it=activearr.begin(); it!=activearr.end(); it++) {
                int i = *it;
                int i2=i+1;
                if (i2 >= j) {
                    break;
                }
                int k2 = SnSj+sums[i2-1]+(j-i2+1)*vj;
                if (k2>r) {
                    r = k2;
//                    cout << i2 << " " << j << endl;
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

