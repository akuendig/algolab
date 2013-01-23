#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

pair<int, int>* db;
vector<int> visited;

int gcd(int a, int b) {
    if (b==0) {
        return a;
    }
    return gcd(b, a % b);
}

pair<int, int> shelves(unsigned int wall, unsigned int n, unsigned int m){
    assert(wall > 0);
    assert(n <= m);
    pair<unsigned int,unsigned int> result(0,0);
    if (wall < n)
        return result;
//    if (wall == n) {
//        if (n==m)
//            result.second = 1;
//        else
//            result.first = 1;
//        return result;
//    }
//    if (wall < m) {
//        result.first = 1;
//        return result;
//    }
    unsigned int i = 0;
    unsigned int j = (wall/m);
    unsigned int bestValue = j*m;
    pair<unsigned int, unsigned int> best(i,j);
    for (i=0; i*n <=wall; i++) {
        unsigned int remainder = wall - i*n;
        j = remainder/m;

        unsigned int val = n*i+m*j;
        //cout << i << " " << remainder << " " << val << " " << wall << "\n";

        if (val == wall) {
            bestValue = val;
            best = make_pair(i,j);
            break;
        }
        if (val > bestValue) {
            bestValue = val;
            best = make_pair(i,j);
        }
        if (i > m)
            break;
    }

    result.first = best.first;
    result.second = best.second;
    return result;
}

int main() {

    int testcases;
    unsigned int length, n, m;
    cin >> testcases;
    for (int i=0;i<testcases;i++) {
        cin >> length;
        cin >> n;
        cin >> m;
        pair<unsigned int, unsigned int> result = shelves(length, n, m);
        cout << result.first << " " << result.second << " " << (length-result.first*n-result.second*m) << "\n";
    }
    return 0;
}
