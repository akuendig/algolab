#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/stoer_wagner_min_cut.hpp>
#include <boost/graph/one_bit_color_map.hpp>
#include <boost/property_map/property_map.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
                        no_property, property <edge_weight_t, int > > Graph;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef graph_traits<Graph>::vertex_descriptor Vertex;

// Solving the problem using mincut

void testcase() {
    int n;
    int m;
    cin >> n >> m;
    Graph g(n);

    property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);

    for (int i=0; i<m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        bool s;
        Edge e;
        tie(e, s) = add_edge(u,v,g);
        weightmap[e] = w;
    }
//    vector<default_color_type> parities(n);
    BOOST_AUTO(parities, boost::make_one_bit_color_map(num_vertices(g), get(boost::vertex_index, g)));
    int w = boost::stoer_wagner_min_cut(g, weightmap,parity_map(parities));
//    cout << "The min-cut weight of G is " << w << ".\n" << endl;

//    cout << "One set of vertices consists of:" << endl;
//    size_t i;
//    for (i = 0; i < num_vertices(g); ++i) {
//      if (get(parities, i))
//        cout << i << endl;
//    }
//    cout << endl;

//    cout << "The other set of vertices consists of:" << endl;
//    for (i = 0; i < num_vertices(g); ++i) {
//      if (!get(parities, i))
//        cout << i << endl;
//    }
//    cout << endl;

    vector<int> my_stuff;
    int i;
    for (i = 0; i < num_vertices(g); ++i) {
      if (get(parities, i))
//        cout << i << endl;
          my_stuff.push_back(i);
    }
    cout << w << endl;
    cout << my_stuff.size() << " ";
    for (vector<int>::iterator it=my_stuff.begin(); it !=my_stuff.end(); it++) {
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
//        testcase(grid);
        testcase();
    }
    return 0;
}

