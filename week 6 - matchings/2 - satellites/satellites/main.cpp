#include <iostream>
#include <vector>
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

void testcase() {
    int g, s, l;
    cin >> g >> s >> l;

    Graph graph(g+s);
    vector<vector<int> > connections(g+s, vector<int>());

    vector<int > edges_count(g+s, 0);
    for (int i=0; i<l; i++) {
        int gi, si;
        cin >> gi >> si;
        Edge e;
        bool success;
        tie(e, success) = add_edge(gi,g+si, graph);
        edges_count[gi]++;
        edges_count[g+si]++;
        connections[gi].push_back(g+si);
        connections[g+si].push_back(g);
    }
    vector<VertexDescriptor> mate(g+s);
    edmonds_maximum_cardinality_matching(graph, &mate[0]);
    const VertexDescriptor NULL_VERTEX = graph_traits<Graph>::null_vertex();

    vector<int> nground;
    vector<int> nsatellite;

    vector<bool> covered(g+s, false);

    for(int i = 0; i < g+s; ++i) {
        if(mate[i] == NULL_VERTEX) {
//            cout << "This shouldn't happen" << endl;
            covered[i] = true;
            continue;
        }
        int other = mate[i];
        if (other < i) {
            continue;
        }
        int chosen;

//        if (edges_count[i] >= edges_count[other]) {
//            chosen = i;
//        } else {
//            chosen = other;
//        }
        if (covered[i] && covered[other]) {
            continue;
        }
        // choose max
        if (!covered[i] && !covered[other]) {
            if (connections[i].size() >= connections[other].size()) {
                covered[i] = true;
                chosen = i;
                for (vector<int>::iterator it=connections[i].begin(); it != connections[i].end(); it++) {
                    covered[*it] = true;
                }
            } else {
                covered[other] = true;
                chosen = other;
                for (vector<int>::iterator it=connections[other].begin(); it != connections[other].end(); it++) {
                    covered[*it] = true;
                }
            }
        } else if (covered[i]) {
            covered[other] = true;
            for (vector<int>::iterator it=connections[other].begin(); it != connections[other].end(); it++) {
                covered[*it] = true;
            }
            chosen = other;
        } else {
            covered[i] = true;
            for (vector<int>::iterator it=connections[i].begin(); it != connections[i].end(); it++) {
                covered[*it] = true;
            }
            chosen = i;
        }

        if (chosen < g) {
            nground.push_back(chosen);
        } else {
            nsatellite.push_back(chosen-g);
        }
    }
    cout << nground.size() << " " << nsatellite.size() << endl;
    for (int i=0; i<nground.size(); i++) {
        cout << nground[i] << " ";
    }
    for (int i=0; i<nsatellite.size(); i++) {
        cout << nsatellite[i] << " ";
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
