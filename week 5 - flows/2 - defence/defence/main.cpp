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

class Location {
public:
    int have;
    int need;
    Location(int have, int need):
        have(have),
        need(need)
    {  }
};

void testcase() {
    int l;
    int p;
    cin >> l >> p;

    Graph g(l+2);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap rev_edge = get(edge_reverse, g);
    ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);
    int source_edge = l;
    int sink_edge = l+1;

    int overall_need = 0;

    vector<Location> locations;
    for (int i=0; i<l; i++) {
        int g;
        int d;
        cin >> g >> d;
        locations.push_back(Location(g,d));
    }

    for (int i=0; i<p; i++) {
        int a;
        int b;
        int cmin;
        int cmax;

        cin >> a >> b >> cmin >> cmax;
        // adapt locations
        locations[a].need += cmin;
        locations[b].need -= cmin;

        // add delta as flow
        Edge e, rev_e;
        bool success;
        // Set edge from source to match
        tie(e, success) = add_edge(a, b, g);
        tie(rev_e, success) = add_edge(b, a, g);
        capacity[e] = cmax-cmin;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
    }

    // Add have to graph
    for (int i=0; i<l; i++) {
        Edge e, rev_e;
        bool success;
        // Set edge from source to match
        tie(e, success) = add_edge(source_edge, i, g);
        tie(rev_e, success) = add_edge(i, source_edge, g);
        capacity[e] = locations[i].have;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
    }
    // Add need to graph
    for (int i=0; i<l; i++) {
        Edge e, rev_e;
        bool success;
        // Set edge from source to match
        tie(e, success) = add_edge(i, sink_edge, g);
        tie(rev_e, success) = add_edge(sink_edge, i, g);
        capacity[e] = locations[i].need;
        if (locations[i].need < 0) {
            locations[i].need = 0;
            continue;
        }
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
        overall_need += locations[i].need;
    }

    int max = push_relabel_max_flow(g, source_edge, sink_edge);
    // use sum_points to check if we got the maximum and all edges are used
    if (max >= overall_need) {
        cout << "yes" << endl;
        return;
    }
    cout << "no" << endl;
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

