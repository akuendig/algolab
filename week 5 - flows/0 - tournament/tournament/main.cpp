#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <algorithm>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, directedS> Traits;

typedef adjacency_list<vecS, vecS, directedS, no_property,
                            property<edge_capacity_t, long,
                            property<edge_residual_capacity_t, long,
                            property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef graph_traits<Graph>::edge_descriptor Edge;

inline int get_index(const vector<string> &team_name, const string &str) {
    int i=0;
    for (vector<string>::const_iterator it=team_name.begin();
         it != team_name.end(); it++) {
        if (str.compare((*it)) == 0) {
            return i;
        }
        i++;
    }
}

void testcase() {
    int n;
    int m;
    cin >> n;
    cin >> m;


    Graph g(n+m+2);
    EdgeCapacityMap capacity = get(edge_capacity, g);
    ReverseEdgeMap rev_edge = get(edge_reverse, g);
    ResidualCapacityMap res_capacity = get(edge_residual_capacity, g);

    vector<string> team_name(n);
    vector<int> team_points(n);

    int source_edge = n+m;
    int sink_edge = n+m+1;

    long sum_points = m; // the number of matches and the sum of all player points
    vector<Edge> sink_edges;
    for (int i=0; i<n; i++) {
        string t;
        int p;
        cin >> p;
        cin >> t;
        team_name[i] = t;
        team_points[i] = p;
        sum_points += p;
        Edge e, rev_e;
        bool success;
        // Create edge from source to player
        tie(e, success) = add_edge(source_edge, i, g);
        tie(rev_e, success) = add_edge(i, source_edge, g);
        capacity[e] = p;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;

        // Create edge from player to sink
        tie(e, success) = add_edge(i, sink_edge, g);
        tie(rev_e, success) = add_edge(sink_edge, i, g);
        capacity[e] = p;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
        // Store sink edges
        sink_edges.push_back(e);
    }

    // Process matchings
    for (int i=0; i<m; i++) {
        string t1, t2, vs;
        cin >> t1 >> vs >> t2;
        int i1 = get_index(team_name, t1);
        int i2 = get_index(team_name, t2);

        // Count the matches
        team_points[i1]++;
        team_points[i2]++;

        Edge e, rev_e;
        bool success;
        // Set edge from source to match
        tie(e, success) = add_edge(source_edge, n+i, g);
        tie(rev_e, success) = add_edge(n+i, source_edge, g);
        capacity[e] = 1;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;

        // Set edge from match to player1
        tie(e, success) = add_edge(n+i, i1, g);
        tie(rev_e, success) = add_edge(i1, n+i, g);
        capacity[e] = 1;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;

        // Set edge from match to player2
        tie(e, success) = add_edge(n+i, i2, g);
        tie(rev_e, success) = add_edge(i2, n+i, g);
        capacity[e] = 1;
        capacity[rev_e] = 0;
        rev_edge[e] = rev_e;
        rev_edge[rev_e] = e;
    }

    vector<string> winning_teams;
    for (int i=0; i<n; i++) {
        // Set all sink edges to the maximum capacity of the current team
        long max_points = team_points[i];
        for (vector<Edge>::iterator it=sink_edges.begin(); it != sink_edges.end(); it++) {
            capacity[*it] = max_points;
        }


        int max = push_relabel_max_flow(g, source_edge, sink_edge);
        // use sum_points to check if we got the maximum and all edges are used
        if (max == sum_points) {
            winning_teams.push_back(team_name[i]);
        }
    }
    sort(winning_teams.begin(), winning_teams.end());
    int counter = 0;
    for (vector<string>::iterator it=winning_teams.begin(); it!= winning_teams.end(); it++) {
        cout << *it;
        if ((it+1) != winning_teams.end()) {
            cout << " ";
        }
    }
    cout << endl;

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

