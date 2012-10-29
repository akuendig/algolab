#include <iostream>
#include <climits>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace std;

using namespace boost;

typedef adjacency_list<vecS, vecS, bidirectionalS,
                        no_property, property <edge_index_t, size_t > > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

// Obviously we need Dijkstra...
void testcase() {
    int v;
    int e;
    cin >> v;
    cin >> e;
    int s;
    cin >> s; // Species

    int start;
    int end;
    cin >> start;
    cin >> end;

    Graph g(v);
//    property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);

    // fix
    vector<vector<int> > species(s, vector<int>(e, 0));
    for (int i=0; i<e; i++) {
        int u, v;
        cin >> u;
        cin >> v;
        int w = INT_MAX;
        bool success;
        Edge e;
        tie(e, success) = add_edge(u, v, g);
        // Find minimum weight
        for (int k=0; k<s; k++) {
            int t;
            cin >> t;
            species[k][i] = t;
//            species[s][e] = t;
        }
    }

    int b;
    for (int k=0; k<s; k++) {
        cin >> b;
    }
//    property_map<Graph, edge_index_t>::type indices = get(edge_index, g);

    property_map<Graph, edge_index_t>::type indices = get(edge_index, g);

    vector<int> edge_weights(e, INT_MAX);
    for (int i=0; i<s; i++) {
        vector<Edge> spanning_tree;
        kruskal_minimum_spanning_tree(g, back_inserter(spanning_tree),
                                      weight_map(make_iterator_property_map(species[i].begin(), indices)));

        for (vector < Edge >::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
            Edge e = *ei;
            if (edge_weights[indices[e]] < species[i][indices[e]])
                edge_weights[indices[e]] = species[i][indices[e]];
            //total_weight += weight[*ei];
        }
        //        kruskal_minimum_spanning_tree(g, back_inserter(spanning_tree), weight_map(&species[i][0]));
    }

    // Compute dijkstra
    std::vector<Vertex> predecessors(num_vertices(g));
    std::vector<int> distances(num_vertices(g));

    dijkstra_shortest_paths(g, start,
      predecessor_map(&predecessors[0])
                            .distance_map(&distances[0])
                            .weight_map(
                                make_iterator_property_map(
                                    weight_map.begin(),
                                    get(edge_index, g))));
//    dijkstra_shortest_paths(g, start, predecessor_map(&predecessors[0]),
//                            distance_map(&distances[0]),
//                            weight_map(&edge_weights[0]),
//                            get(vertex_index, g),
//                            std::less<int>(),
//                            closed_plus<int>(),
//                            (std::numeric_limits<int>::max)(),
//                            0,
//                            default_dijkstra_visitor());


//                            indices,
//                            std::less<int>(), closed_plus<int>(),
//                            (std::numeric_limits<int>::max)(), 0,
//                            default_dijkstra_visitor());

    cout << distances[end] << "\n";
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

