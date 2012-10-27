#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
typedef struct {
    int weight;
    int capacity;
    int cost;
} floor;

floor make_floor(int weight, int capacity, int cost) {
    floor f = {weight, capacity, cost};
    return f;
}

void testcase() {
    int n;
    cin >> n;
    vector<floor> building;
    for (int i=0; i<n; i++) {
        int weight, capacity, cost;
        cin >> weight;
        cin >> capacity;
        cin >> cost;
        building.push_back(make_floor(weight, capacity, cost));
    }
}

int main() {
    int testcases;
    cin >> testcases;
    for (int k=0; k<testcases; k++) {
        testcase();
    }
    return 0;
}
