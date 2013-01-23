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


int characterisitics_map[400][10];
int characterisitics_student[400][400];

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

//    cout << "Reading" << endl;
    vector<string> characteristics;
    for (int i=0; i<n; i++) {
        for (int j=0; j<c; j++) {
            string s;
            cin >> s;
            int idx = get_characteristics_index(characteristics, s);
            characterisitics_map[i][j] = idx;
        }
    }

//    cout << "arMap" << endl;
    fill(&characterisitics_student[0][0], &characterisitics_student[399][399], 0);

    for (int x=0; x<n; x++) {
        for (int i=0; i<c; i++) {
            int ci = characterisitics_map[x][i];
            for (int y=0; y<n; y++) {
                if (x == y) {
                    continue;
                }
                for (int j=0; j<c; j++) {
                    int cj = characterisitics_map[y][j];
                    if (ci == cj) {
                        characterisitics_student[x][y]++;
//                        characterisitics_student[y][x]++;
                        break;
                    }
                }
            }
        }
    }

    Graph g(n);
    for (int x=0; x<n; x++) {
        for (int y=x+1; y<n; y++) {
            if (characterisitics_student[x][y] > f) {
                Edge e;
                bool success;
                tie(e, success) = add_edge(x,y,g);
            }
        }
    }
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
        testcase();
    }
    return 0;
}

