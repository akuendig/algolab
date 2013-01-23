#include <iostream>
#include <vector>
#include <queue>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

#include <algorithm>
#include <cassert>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS,
                        property<vertex_index_t, int>,
                        property<edge_index_t, int>
                      > Graph;

typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits<Graph>::out_edge_iterator OutEdgeIterator;
typedef graph_traits<Graph>::vertex_descriptor VertexDescriptor;


bool tiles[52][52];
int get_index(int w, int i, int j) {
    assert(i>0);
    assert(j>0 && j <= w);
    return ((w)*(i-1))+j-1;
}

pair<int,int> get_coord(int w, int idx) {
    assert(idx >= 0);
    if (idx < w) {
//        cout << idx << ": " << idx+1 << " " << 1 << " (w: " << w << ")" <<endl;
        return make_pair(1,idx+1);
    }
    int j=idx%w;
    int i=((idx-j)/w);
//    cout << idx << ": " << i+1 << " " << j+1 << " (w: " << w << ")" <<endl;
    return make_pair(i+1,j+1);
}

void testcase() {
    int h, w;
    cin >> w >> h;
    for (int i=1; i<=h; i++) {
        for (int j=1; j<=w; j++) {
            char c;
            cin >> c;
            bool t = true;
            if (c == 'x') {
                t = false;
            }
            tiles[i][j] = t;
        }
    }
    for (int i=0; i<=w+1; i++) {
        tiles[0][i] = false;
        tiles[h+1][i] = false;
    }
    for (int i=1; i<=h; i++) {
        tiles[i][0] = false;
        tiles[i][w+1] = false;
    }
    int total_vertices = h*w;
    int num_active_tiles = 0;
    Graph g(total_vertices);
    for (int i=1; i<=h; i++) {
        for (int j=1; j<=w; j++) {
            if (!tiles[i][j]) {
                continue;
            }
            num_active_tiles++;
            int s = get_index(w, i, j);
            if (tiles[i][j+1]) {
                add_edge(s, get_index(w, i, j+1), g);
            }
            if (tiles[i][j-1]) {
                add_edge(s, get_index(w, i, j-1), g);
            }
            if (tiles[i+1][j]) {
                add_edge(s, get_index(w, i+1, j), g);
            }
            if (tiles[i-1][j]) {
                add_edge(s, get_index(w, i-1, j), g);
            }
        }
    }

    const VertexDescriptor NULL_VERTEX = graph_traits<Graph>::null_vertex();
    vector<VertexDescriptor> mate(total_vertices);
    edmonds_maximum_cardinality_matching(g, &mate[0]);
//    if (num_active_tiles%2 == 1) {
//        cout << endl;
//        for (int i=0; i<=h+1; i++) {
//            for (int j=0; j<=w+1; j++) {
//                if (tiles[i][j])
//                    cout << ".";
//                else
//                    cout << "x";
//            }
//            cout << endl;
//        }
//    }
    for (int i=0; i<total_vertices; i++) {
//        cout << "mate " << i << ": " << mate[i] << endl;
        if(mate[i] == NULL_VERTEX || mate[i] == i) {
            pair<int, int> cd = get_coord(w, i);
//            cout << i << ": " << cd.first << " " << cd.second << " (w: "<<w<<")" << endl;
            if (tiles[cd.first][cd.second]) {
                cout << "no" << endl;
                return;
            }
        }
//        if (num_active_tiles%2 == 1) {
//            pair<int, int> c = get_coord(w, i);
//            int l = mate[i];
//            pair<int, int> cl = get_coord(w, i);
//            cout << i << ":" << l << " " << c.first << " " << c.second << " has mate " << cl.first << " " << cl.second << endl;
//        }
    }
    cout << "yes" << endl;

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


