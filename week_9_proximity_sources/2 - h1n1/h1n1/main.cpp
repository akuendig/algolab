#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/squared_distance_2.h>
#include <iostream>
#include <vector>
#include <cmath>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_edges_iterator  Edge_iterator;
typedef Triangulation::Face_handle  Face_handle;
typedef Triangulation::Point  Point;
using namespace std;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

bool dfs(Triangulation &t, double distance, Face_handle origin, map<Face_handle, int>& visitor_map, int cur_it) {
	for (int i=0; i<3; i++) {
        Triangulation::Segment s = t.segment(origin,i);
        double d = CGAL::to_double(s.squared_length());
        if (d >= distance) {
        	Face_handle nb = origin->neighbor(i);
        	if (visitor_map[nb] == cur_it) {
        		continue;
        	}

        	if (t.is_infinite(nb)) {
        		return true;
        	}
        	visitor_map[nb] = cur_it;
        	if (dfs(t, distance, nb, visitor_map, cur_it)) {
        		return true;
        	}
        }
    }
    return false;
}

void testcases() {
    size_t n;
    std::vector<Triangulation::Point> points;
    while (cin >> n && n > 0) {
        points.reserve(n);
        for (size_t i = 0; i < n; i++) {
        	double x, y;
        	cin >> x >> y;
            Triangulation::Point p(x,y);
//            cin >> p;
            points.push_back(p);
        }

        Triangulation t;
        t.insert(points.begin(), points.end());
        map<Face_handle, int> visitor_map;
        for (Triangulation::Face_iterator it=t.finite_faces_begin(); it !=t.finite_faces_end(); it++) {
            visitor_map[it] = -1;
        }

        size_t m;
        cin >> m;
        for (size_t i=0; i<m; i++) {
        	double x, y;
        	cin >> x >> y;
            Triangulation::Point p(x,y);
//            Triangulation::Point p;
//            cin >> p;
            double d;
            cin >> d;
            Triangulation::Point nv = t.nearest_vertex(p)->point();
            double distance2 = CGAL::to_double(CGAL::squared_distance(nv, p));
            if (distance2 < d) {
                cout << "n";
                continue;
            }
            Triangulation::Face_handle f = t.locate(p);

            visitor_map[f] = i;
            if (t.is_infinite(f) || dfs(t, d*4.0, f, visitor_map, i)) {
                cout << "y";
            } else {
                cout << "n";
            }

        }
        cout << endl;

        points.clear();
    }
}

int main()
{
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    testcases();
    return 0;
}

