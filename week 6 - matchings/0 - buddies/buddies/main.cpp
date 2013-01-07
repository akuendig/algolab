#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

#include <algorithm>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> Traits;

typedef adjacency_list<vecS, vecS, directedS, no_property,
                            property<edge_capacity_t, long,
                            property<edge_residual_capacity_t, long,
                            property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;


typedef graph_traits<Graph>::vertex_descriptor VertexDescriptor;
typedef graph_traits<Graph>::edge_descriptor EdgeDescriptor;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
inline int get_characteristics_index(vector<string>& characteristics, string& c) {
    int i;
    for (i=0; i<characteristics.size();i++) {
        if (c.compare(characteristics[i]) == 0) {
            return i;
        }
    }
    characteristics.push_back(c);
    return i;
}

void testcase() {
    int n, c, f;
    cin >> n >> c >> f;

    vector<string> characteristics(c);
    Graph g(n+c+2);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap rev_edge = get(edge_reverse, g);
    ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

    vector<int> characteristics_capacity(c,0);
    int source_edge = n+c;
    int sink_edge = n+c+1;
    for (int i=0; i<n; i++) {
        // Create edges from source to student
        Edge e, rev_e;
        bool success;
        // Set edge from source to match
        tie(e, success) = add_edge(source_edge, i, g);
        tie(rev_e, success) = add_edge(i, source_edge, g);
        capacity[e] = f;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;

        for (int j=0; j<f; j++) {
            // Create edges from student to characteristics
            string s;
            cin >> s;
            int idx = get_characteristics_index(characteristics, s);
            characteristics_capacity[idx]++;

            tie(e, success) = add_edge(i, n+idx, g);
            tie(rev_e, success) = add_edge(n+idx, i, g);
            capacity[e] = 1;
            capacity[rev_e] = 0;
            rev_edge[e] = rev_e;
            rev_edge[rev_e] = e;
        }
    }

    // Create edges from characteristics to sink
    for (int i=0; i<c; i++) {
        Edge e, rev_e;
        bool success;
        // Set edge from source to match
        tie(e, success) = add_edge(n+i, sink_edge, g);
        tie(rev_e, success) = add_edge(sink_edge, n+i, g);
        capacity[e] = characteristics_capacity[i];
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
    }
    // Compute max cardinality matching

    vector<VertexDescriptor> mate(n);
    edmonds_maximum_cardinality_matching(g, &mate[0]);
    const VertexDescriptor NULL_VERTEX = graph_traits<Graph>::null_vertex();
    int m=0;
    for(int i = 0; i < n; ++i) {
        if(mate[i] == NULL_VERTEX) {
//            cout << i << " -- " << mate[i] << endl;
//            m++;
            cout << "optimal" << endl;
            return;
        }
    }
    cout << "not optimal" << endl;
}

int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int testcases;
    cin >> testcases;

    for (int i=0; i<testcases; i++) {
//        testcase(grid);
        testcase();
    }
    return 0;
}

