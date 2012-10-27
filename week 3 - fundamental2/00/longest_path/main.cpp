#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
void testcase() {
    int v;
    cin >> v;
    vector<vector<int> > graph(v, vector<int>());
    vector<int> stack;

    for (int i=0; i < (v-1); i++) {
        int p1, p2;
        cin >> p1;
        cin >> p2;
        if (find(graph[p1].begin(), graph[p2].end(), p2) == graph[p2].end())
            continue;
        graph[p1].push_back(p2);
        graph[p2].push_back(p1);
    }
}

int search_graph(vector<vector<int> >& graph, int start, int origin) {
    if (graph[start].size() == 1)
        return 1;
    for(vector<int>::iterator it = graph[start].begin(); it != graph[start].end(); it++) {
        if (*it == origin)
            continue;
    }
    return 0;
}

int main()
{
    int testcases;
    cin >> testcases;
    for (int i=0; i<testcases; i++) {
        testcase();
    }
    return 0;
}

