#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <algorithm>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> Traits;

typedef adjacency_list<vecS, vecS, directedS, no_property,
                            property<edge_capacity_t, long,
                            property<edge_residual_capacity_t, long,
                            property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef graph_traits<Graph>::edge_descriptor Edge;

inline int get_index(int m, int i, int j) {
    return m*i+j;
}

inline int madd_edge(Graph& g,
                     EdgeCapacityMap& capacity,
                     ReverseEdgeMap& rev_edge,
                     ResidualCapacityMap& res_capacity,
                     int w, int src, int end) {
    Edge e, rev_e;
    bool success;
    // Create edge from source to player
    tie(e, success) = add_edge(src, end, g);
    tie(rev_e, success) = add_edge(end, src, g);
    capacity[e] = w;
    capacity[rev_e] = w;
    rev_edge[e] = rev_e;
    rev_edge[rev_e] = e;
}

void testcase() {
    int m, n, k;
    cin >> m >> n >> k;
    int source_edge = m*n;
    int sink_edge = m*n+1;
    Graph g(m*n+2);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap rev_edge = get(edge_reverse, g);
    ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            int idx = get_index(m, i, j);
            if (i+1 < m) {
                int end = get_index(m, i+1, j);
                madd_edge(g, capacity, rev_edge, res_capacity, 1, idx, end);
            }
            if (j+1 < m) {
                int end = get_index(m, i, j+1);
                madd_edge(g, capacity, rev_edge, res_capacity, 1, idx, end);
            }
        }
    }
    for (int i=0; i<m; i++) {
        int j, src, end;
        j=0;
        src = get_index(m, i,j);
        Edge e, rev_e;
        bool success;
        // Create edge from edge to sink
        tie(e, success) = add_edge(src, sink_edge, g);
        tie(rev_e, success) = add_edge(sink_edge, src, g);
        capacity[e] = 1;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
        j=m-1;
        src = get_index(m, i,j);
        tie(e, success) = add_edge(src, sink_edge, g);
        tie(rev_e, success) = add_edge(sink_edge, src, g);
        capacity[e] = 1;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
    }

    for (int j=0; j<n; j++) {
        int i, src, end;
        i=0;
        src = get_index(m, i,j);
        Edge e, rev_e;
        bool success;
        // Create edge from edge to sink
        tie(e, success) = add_edge(src, sink_edge, g);
        tie(rev_e, success) = add_edge(sink_edge, src, g);
        capacity[e] = 1;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
        j=n-1;
        src = get_index(m, i,j);
        tie(e, success) = add_edge(src, sink_edge, g);
        tie(rev_e, success) = add_edge(sink_edge, src, g);
        capacity[e] = 1;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
    }
    // Insert knights
    for (int i=0; i<k; i++) {
        int x, y;
        cin >> x >> y;

        int end = get_index(m, y, x);
        Edge e, rev_e;
        bool success;
        // Create edge from edge to sink
        tie(e, success) = add_edge(source_edge, end, g);
        tie(rev_e, success) = add_edge(end, source_edge, g);
        capacity[e] = 1;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
    }
    int max = push_relabel_max_flow(g, source_edge, sink_edge);
    cout << max << endl;
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
