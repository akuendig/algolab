#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
//#include <pair.h>
#include <algorithm>
using namespace std;

int dfs(vector<vector<int> >& graph, int origin, int source) {
    int maxdepth = 1;
    for (vector<int>::iterator it=graph[origin].begin(); it != graph[origin].end(); it++) {
        int c = *it;

        if (c != source) {
            int depth = dfs(graph, c, origin)+1;
            if (depth > maxdepth) {
                maxdepth = depth;
            }
        }
    }
//    std::cout << "in: " << origin << " source: " << source << " distance: " << maxdepth <<  endl;
    return maxdepth;
}

pair<int, int> dfs_maxdist(vector<vector<int> >& graph, int origin, int source) {
    pair<int, int> res = make_pair(origin, 0);
    for (vector<int>::iterator it=graph[origin].begin(); it != graph[origin].end(); it++) {
        int c = *it;

        if (c != source) {
            pair<int, int> k = dfs_maxdist(graph, c, origin);
            k.second += 1;
            if (k.second > res.second) {
               res = k;
            }
        }
    }
    return res;
}

void testcase() {
    int v;
    cin >> v;
    vector<vector<int> > graph(v, vector<int>());
    for (int i=0; i < (v-1); i++) {
        int p1, p2;
        cin >> p1;
        cin >> p2;
        graph[p1].push_back(p2);
        graph[p2].push_back(p1);
    }


    // Make a dfs

    int maxdepth = 1;
    int origin = dfs_maxdist(graph, 0,0).first;
    for (vector<int>::iterator it=graph[origin].begin(); it != graph[origin].end(); it++) {
        int c = *it;
        maxdepth += dfs(graph, c, origin);
    }
    cout << maxdepth << endl;

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

