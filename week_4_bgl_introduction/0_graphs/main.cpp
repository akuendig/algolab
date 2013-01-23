#include <iostream>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
                        no_property, property <edge_weight_t, int > > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

typedef pair<int, int> E;

void testcase() {
    int n; // vertices
    int m; // edges
    cin >> n;
    cin >> m;
    Graph g(n);

    property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);

    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u;
        cin >> v;
        cin >> w;
        bool success;
        Edge e;
        tie(e, success) = add_edge(u, v, g);
        weightmap[e] = w;
    }

    property_map<Graph, edge_weight_t>::type weight = get(edge_weight, g);
    vector<Edge> spanning_tree;
    kruskal_minimum_spanning_tree(g, back_inserter(spanning_tree));

    int total_weight = 0;
    for (vector < Edge >::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
        total_weight += weight[*ei];
    }

    // Let's take out the hammer and compute dijkstra as well...
    std::vector<Vertex> predecessors(num_vertices(g));
    std::vector<int> distances(num_vertices(g));
    dijkstra_shortest_paths(g, 0,
      predecessor_map(&predecessors[0]).distance_map(&distances[0]));

    int d = 0;
    for (vector<int>::iterator it = distances.begin(); it != distances.end(); it++) {
        int i = *it;
        if (i > d)
            d = i;
    }
    cout << total_weight << " " << d << "\n";
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

