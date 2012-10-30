#include <iostream>
#include <climits>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
using namespace std;

using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
                        no_property, property <edge_index_t, size_t > > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

// Obviously we need Dijkstra...
void testcase() {
    int nvertices;
    int nedges;
    cin >> nvertices;
    cin >> nedges;
    int nspecies;
    cin >> nspecies; // Species

    int start;
    int end;
    cin >> start;
    cin >> end;

    Graph g(nvertices);
    property_map<Graph, edge_index_t>::type indices = get(edge_index, g);

    vector<vector<int> > species_weights(nspecies, vector<int>(nedges, 0));
    // Load all edges
    for (int i=0; i<nedges; i++) {
        int u, v;
        cin >> u;
        cin >> v;
        bool success;
        Edge e;
        // Don't forget to set edge_index through i (we need it below)
        tie(e, success) = add_edge(u, v, g);
        // Insert weight for all species individually
        indices[e] = i;
        for (int k=0; k<nspecies; k++) {
            int t;
            cin >> t;
            species_weights[k][i] = t;
        }
    }

    int b;
    for (int k=0; k<nspecies; k++) {
        cin >> b;
    }

    vector<int> edge_weights(nedges, INT_MAX);
    for (int i=0; i<nspecies; i++) {
        vector<Edge> spanning_tree;
        kruskal_minimum_spanning_tree(g,
                                      back_inserter(spanning_tree),
                                      weight_map(
                                          make_iterator_property_map(
                                              species_weights[i].begin(),
                                              indices
                                              )
                                          )
                                      );

        for (vector < Edge >::iterator ei = spanning_tree.begin(); ei != spanning_tree.end(); ++ei) {
            Edge e = *ei;
            if (edge_weights[indices[e]] > species_weights[i][indices[e]]) {
                edge_weights[indices[e]] = species_weights[i][indices[e]];
            }
        }
    }

    // Compute dijkstra
    std::vector<Vertex> predecessors(num_vertices(g));
    std::vector<int> distances(num_vertices(g), INT_MAX);

    dijkstra_shortest_paths(g, start,
                            predecessor_map(&predecessors[0])
                            .distance_map(&distances[0])
                            .weight_map(
                                make_iterator_property_map(
                                    &edge_weights[0],
                                    indices
                                    )
                                )
                            );

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

