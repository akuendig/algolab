#include <iostream>

#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
                        property<vertex_index_t, int>,
                        property<edge_index_t, int>
                      > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

void testcase() {
    int n; // students
    cin >> n;
    int m; // pairs
    cin >> m;
    Graph g(n+1);
    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u;
        cin >> v;
        Edge e;
        bool success;
        tie(e, success) = add_edge(u,v,g);
    }

    for (int i=0; i<n; i++) {
        Edge e;
        bool success;
        tie(e, success) = add_edge(i,n,g);
    }

//    vector< vector<Edge> > embedding(n+1);
    bool is_planar = boyer_myrvold_planarity_test(boyer_myrvold_params::graph = g
//                                                  boyer_myrvold_params::embedding = &embedding[0]
                                                 );

    if (!is_planar) {
        cout << "no" << endl;
        return;
    }
    cout << "yes" << endl;
//    cout << "Testcase, n: " << n << endl;


//    for (vector<vector<Edge> >::iterator it=embedding.begin();
//            it != embedding.end(); it++) {
//        cout << (*it).size() << endl;
//    }

//    // Check for K4
//    for (vector<vector<Edge> >::iterator it=embedding.begin();
//            it != embedding.end(); it++) {
////        cout << (*it).size() << endl;

//    }
//    for (vector<Edge>::iterator it=kuratowski_edges.begin();
//         it != kuratowski_edges.end(); it++) {
//        cout << *it << endl;
//    }
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

