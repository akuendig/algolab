#include <iostream>
#include <vector>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

#include <algorithm>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
                        property<vertex_index_t, int>,
                        property<edge_index_t, int>
                      > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef graph_traits<Graph>::vertex_descriptor VertexDescriptor;

const VertexDescriptor NULL_VERTEX = graph_traits<Graph>::null_vertex();

void coverPath(Graph& g, int current, vector<VertexDescriptor>& mate, vector<bool>& covered, vector<vector<int> >& connections) {
    for (vector<int>::iterator it=connections[current].begin(); it != connections[current].end(); it++) {
        int nb = *it;
        covered[nb] = true;
        if (mate[nb] != NULL_VERTEX) {
            int ground_node = mate[nb];
            if (!covered[ground_node]) {
                covered[ground_node] = true;
                coverPath(g, ground_node, mate, covered, connections);
            }
        }
    }
}

void testcase() {
    int num_g, num_s, l;
    cin >> num_g >> num_s >> l;

    int total_vertices = num_g+num_s;
    Graph graph(total_vertices);

    vector<vector<int> > connections(total_vertices, vector<int>());
    for (int i=0; i<l; i++) {
        int gi, si;
        cin >> gi >> si;
        Edge e;
        bool success;
        tie(e, success) = add_edge(gi,num_g+si, graph);
        connections[gi].push_back(num_g+si);
        connections[num_g+si].push_back(num_g);
    }

    vector<VertexDescriptor> mate(total_vertices);
    vector<bool> covered(total_vertices,false);
    vector<bool> unmatched(total_vertices, false);

    edmonds_maximum_cardinality_matching(graph, &mate[0]);
    int m=0;
    for(int i = 0; i < num_g; ++i) {
        if(mate[i] == NULL_VERTEX) {
            ////            cout << i << " -- " << mate[i] << endl;
            ////            m++;
            //            cout << "optimal" << endl;
            //            return;
            covered[i]   = true;
            unmatched[i] = true;
        }
    }

    // make use of structure of the graph.
    for (int i=0; i < num_g; i++) {
        if (unmatched[i]) {
            coverPath(graph, i, mate, covered, connections);
        }
    }

    vector<int> out_grounds;
    vector<int> out_sattellite;
    for (int i=0; i<num_g; i++) {
        if (!covered[i]) {
            out_grounds.push_back(i);
        }
    }
    for (int i=num_g; i<total_vertices; i++) {
        if (covered[i]) {
            out_sattellite.push_back(i-num_g);
        }
    }
    cout << out_grounds.size() << " " << out_sattellite.size() << endl;
    for (vector<int>::iterator it=out_grounds.begin(); it!=out_grounds.end(); it++) {
        cout << *it << " ";
    }
    for (vector<int>::iterator it=out_sattellite.begin(); it!=out_sattellite.end(); it++) {
        cout << *it << " ";
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
