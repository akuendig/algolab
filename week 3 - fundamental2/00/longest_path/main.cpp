#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
//#include <pair.h>
#include <algorithm>
using namespace std;

int max_depth(vector<vector<int> >& graph, int origin, int source) {
    int maxdepth = 1;
    for (vector<int>::iterator it=graph[origin].begin(); it != graph[origin].end(); it++) {
        int c = *it;

        if (c != source) {
            int depth = max_depth(graph, c, origin);
            if (depth > maxdepth) {
                maxdepth = depth;
            }
        }
    }
//    std::cout << "in: " << origin << " source: " << source << " distance: " << maxdepth <<  endl;
    return maxdepth;
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

    // Make a bfs
    vector<int> distance(v, 0);
    queue<pair<int, int> > bfs;
    for (vector<int>::iterator it=graph[0].begin(); it != graph[0].end(); it++) {
        int c = *it;
        bfs.push(make_pair(0, c));
        distance[c] = 1;
    }
    while (bfs.size() > 0) {
        pair<int, int> el = bfs.front();
        bfs.pop();
        int l = el.second;
        int o = el.first;
        for (vector<int>::iterator it=graph[l].begin(); it != graph[l].end(); it++) {
            int c = *it;
            if (c != o) {
                bfs.push(make_pair(l, c));
                distance[c]++;
            }
        }
    }
    int max = distance[0];
    int maxVertice = 0;
    for (int i=1; i < v; i++) {
        if (distance[i] > max) {
            max = distance[i];
            maxVertice = i;
        }
    }
    // Make a dfs

    int maxdepth = 1;
    int origin = maxVertice;
    for (vector<int>::iterator it=graph[origin].begin(); it != graph[origin].end(); it++) {
        int c = *it;
        maxdepth += max_depth(graph, c, origin);
    }
    cout << maxdepth << endl;

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

