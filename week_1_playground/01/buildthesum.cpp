#include <iostream>
using namespace std;
int main() {
    int numTestcases;

    cin >> numTestcases;

    for (int i=0; i < numTestcases; i++) {
        int numValues;
        cin >> numValues;
        double sum = 0, summand;
        for (int j=0; j < numValues; j++) {
            cin >> summand;
            sum += summand;
        }
        cout << sum << "\n";
    }
    return 0;
}
