#include <iostream>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/breadth_first_search.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
                        no_property, property <edge_weight_t, int > > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef graph_traits<Graph>::vertex_descriptor Vertex;


int color_one_counter;
class coloring_visitor: public default_bfs_visitor {
public:
    vector<int> &coloring;
    coloring_visitor(vector<int> &colors):
        coloring(colors) {

    }

    void tree_edge(Edge e, const Graph& g) {
        Vertex sn = source(e,g);
        Vertex en = target(e,g);
        if (coloring[sn] == 0) {
            coloring[en] = 1;
            color_one_counter++;
        } else {
            coloring[en] = 0;
        }
    }


};

void testcase() {
    int n; // students
    cin >> n;
    int m; // pairs
    cin >> m;
    Graph g(n);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u;
        cin >> v;
        Edge e;
        bool success;
        tie(e, success) = add_edge(u,v,g);
    }
    if (n < 3) {
        cout << "no" << endl;
        return;
    }

    // Compute connected components
    vector<int> components(n);
    if (connected_components(g, &components[0]) > 1) {
        cout << "no" << endl;
        return;
    }

    // Create MST
    vector<Vertex> predecessors(n);
    prim_minimum_spanning_tree(g, &predecessors[0]);

    Graph mst(n);
    for (int i=0; i<n; i++) {
        Edge e;
        bool success;
        if (predecessors[i] != i) {
            // Upon completion of the algorithm, the edges (p[u],u)
            // for all u in V are in the minimum spanning tree.
            // If p[u] = u then u is either the root of the tree or is
            // a vertex that is not reachable from the root.
            tie(e, success) = add_edge(predecessors[i], i, mst);
        }
    }

    // Make graph coloring
    vector<int> coloring_groups(n,0);
    color_one_counter = 0;
    // initialize visitor
    coloring_visitor vis(coloring_groups);
    breadth_first_search(mst, vertex(0, mst), visitor(vis));
    // Make first color 2:
    coloring_groups[0] = 2;
    // the first color is at the center of the star, so we make the second vertex a 0,
    if (color_one_counter == (n-1)) {
        coloring_groups[1] = 0;
    }
    cout << "yes" << endl;

    // 0 has it's own color
    cout << "1 0" << endl;

    int c0 = 0;
    for (int i=0; i<n; i++) {
        if (coloring_groups[i] == 0) {
            c0++;
        }
    }
    cout << c0;
    for (int i=0; i<n; i++) {
        if (coloring_groups[i] == 0) {
            cout << " " << i;
        }
    }
    cout << endl;

    int c1 = 0;
    for (int i=0; i<n; i++) {
        if (coloring_groups[i] == 1) {
            c1++;
        }
    }
    cout << c1;
    for (int i=0; i<n; i++) {
        if (coloring_groups[i] == 1) {
            cout << " " << i;
        }
    }
    cout << endl;
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
