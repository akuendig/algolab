#include <iostream>

#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
                        property<vertex_index_t, int>,
                        property<edge_index_t, int>
                      > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

int election_results[201][201];
void testcase() {
    int m;
    cin >> m;
    int n=m-1;
    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            cin >> election_results[i][j];
        }
    }
    if (m==1) {
        cout << 0 << endl;
        return;
    }
    Graph g(m);
    int k;
    for (k=0; k<n; k++) {
        for (int i=0; i<m; i++) {
            Edge e;
            bool success;
            tie(e, success) = add_edge(i, election_results[i][k], g);
        }
        bool is_planar = boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g);
        if (!is_planar) {
            cout << (k) << endl;
            return;
        }
    }
    cout << (n) << endl;
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

