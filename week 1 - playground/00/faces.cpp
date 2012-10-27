#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;
void dfs(vector<int>& vertices, vector<vector<int> >& edges, int v, int component) {
    if (vertices[v] > 0)
        return;
    vertices[v] = component;
    for (vector<int >::iterator it=edges[v].begin(); it != edges[v].end(); it++) {
        dfs(vertices, edges, (*it), component);
    }

}
void add_edge(vector<vector<int> >& edges, int i, int j) {
    if (find(edges[i].begin(), edges[i].end(), j) != edges[i].end())
        return;
    edges[i].push_back(j);
    edges[j].push_back(i);
}

int compute_faces(int v, int e) {
    vector<int> vertices(v, 0);
    vector<vector<int> > edges(v, vector<int>(0));
    int i, j;
    for (int k=0; k<e; k++) {
        cin >> i;
        cin >> j;
        i--;
        j--;
//        edges[i][j] = 1;
//        edges[j][i] = 1;
        add_edge(edges, i,j);
    }
    int components = 0;
    for (unsigned int k=0; k< vertices.size(); k++) {
        if (vertices[k] == 0) {
            components++;
            dfs(vertices, edges, k, components);
        }
    }
    // V - E + F - C = 1
    int f = 1 - v + e + components;
    return f;
}

int main() {
    int n;
    while (cin >> n) {
        int vertices = n;
        int edges;
        cin >> edges;
        cout << compute_faces(vertices, edges) << "\n";
    }
    return 0;
}
