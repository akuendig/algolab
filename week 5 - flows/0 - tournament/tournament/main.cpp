#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> Traits;

typedef adjacency_list<vecS, vecS, no_property,
    property<edge_capacity_t, long,
    property<edge_residual_capacity_t, long,
    property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity>::type EdgeCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef graph_traits<Graph>::edge_descriptor EdgeDescriptor;

int get_index(const vector<string> &team_name, const string &str) {
    int i=0;
    for (vector<pair<string, int> >::iterator it=team_name.begin();
         it != team_name.end(); it++) {
        if (str.compare((*it).first) == 0) {
            return i;
        }
        i++;
    }
}

void testcase() {
    int num_teams;
    int num_matchups;
    cin >> num_teams;
    cin >> num_matchups;


    Graph g
    vector<string> team_name;
    vector<int> team_points;
    for (int i=0; i<num_teams; i++) {
        string t;
        int p;
        cin >> p;
        cin >> t;
        team_name.push_back(t);
        team_points.push_back(p);
    }

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

