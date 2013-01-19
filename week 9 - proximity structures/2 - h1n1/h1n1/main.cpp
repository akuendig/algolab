#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/squared_distance_2.h>
#include <iostream>
#include <vector>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
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

bool dfs(Triangulation &t, double d, Face_handle origin, map<Face_handle, bool>& visitor_map) {
    for (int i=0; i<3; i++) {
        Triangulation::Segment s = t.segment(origin,0);
//        double d = CGAL::to_double(s)
    }
}

void testcases() {
    size_t n;
    std::vector<Triangulation::Point> points;
    map<Face_handle, bool> visitor_map;
    while (cin >> n && n > 0) {
        points.reserve(n);
        for (size_t i = 0; i < n; i++) {
            Triangulation::Point p;
            cin >> p;
            points.push_back(p);
        }

        Triangulation t;
        t.insert(points.begin(), points.end());

        size_t m;
        cin >> m;
        for (size_t i=0; i<m; i++) {
            Triangulation::Point p;
            cin >> p;
            double d;
            cin >> d;
            Triangulation::Point nv = t.nearest_vertex(p)->point();
            double distance2 = CGAL::to_double(CGAL::squared_distance(nv, p));
            if (distance2 > d) {
                cout << "n";
                continue;
            }
            Triangulation::Face_handle f = t.locate(p);

            for (Triangulation::Face_iterator it=t.finite_faces_begin(); it !=t.finite_faces_end(); it++) {
                visitor_map[it] = false;
            }
            visitor_map[f] = true;
            if (dfs(t, d, f, visitor_map)) {
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

