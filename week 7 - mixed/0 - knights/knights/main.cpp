#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/edmonds_karp_max_flow.hpp>

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

int m, n, k;
inline int get_index(int i, int j) {
    return m*j+i;
}

void madd_edge(Graph& g,
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
    capacity[rev_e] = 0;
    rev_edge[e] = rev_e;
    rev_edge[rev_e] = e;
}

void testcase() {
    cin >> m >> n >> k;
    int source_edge = 2*m*n;
    int sink_edge = 2*m*n+1;
    int offset = m*n;
    Graph g(2*m*n+2);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap rev_edge = get(edge_reverse, g);
    ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

    // Connect left and right outgoing edges to sink
    for (int i=0; i<m; i++) {
        int src;
        // left
        src = get_index(i, 0) + offset;
        madd_edge(g, capacity, rev_edge, res_capacity, 1, src, sink_edge);

        // right
        src = get_index(i,n-1) + offset;
        madd_edge(g, capacity, rev_edge, res_capacity, 1, src, sink_edge);
    }

    // Connect upper and lower edges to sink
    for (int j=0; j<n; j++) {
        int src;

        // upper
        src = get_index(0, j)+offset;
        madd_edge(g, capacity, rev_edge, res_capacity, 1, src, sink_edge);

        // lower
        src = get_index(m-1, j)+offset;
        madd_edge(g, capacity, rev_edge, res_capacity, 1, src, sink_edge);
    }

    // Insert knights
    for (int i=0; i<k; i++) {
        int x, y;
        cin >> x >> y;

        int end = get_index(x, y);
        // Create edge from edge to sink
        madd_edge(g, capacity, rev_edge, res_capacity, 1, source_edge, end);

    }

    for (int i=0; i<m; i++) {
        for (int j=0; j<n; j++) {
            int a, b;
            int c, d;
            a = get_index(i, j);
            c = a+offset;
            madd_edge(g, capacity, rev_edge, res_capacity, 1, a, c);

            if (i+1 < m) {
                b = get_index(i+1, j);
                d = b + offset;

                madd_edge(g, capacity, rev_edge, res_capacity, 1, c, b);
                madd_edge(g, capacity, rev_edge, res_capacity, 1, d, a);
            }
            if (j+1 < n) {
                b = get_index(i, j+1);
                d = b + offset;

                madd_edge(g, capacity, rev_edge, res_capacity, 1, c, b);
                madd_edge(g, capacity, rev_edge, res_capacity, 1, d, a);
            }
        }
    }


    int max = push_relabel_max_flow(g, source_edge, sink_edge);
    cout << max << endl;
//    long flow = edmonds_karp_max_flow(g, source_edge, sink_edge);
      //capacity, res_capacity, rev_edge, &end_color[0], &pred[0]);
//    cout << flow << endl;
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
