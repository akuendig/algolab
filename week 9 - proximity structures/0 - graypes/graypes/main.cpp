#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/squared_distance_2.h>
#include <iostream>
#include <vector>
#include <cmath>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Finite_edges_iterator  Edge_iterator;

using namespace std;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcases() {
    size_t n;
    std::vector<Triangulation::Point> points;
    while (cin >> n && n > 0) {
        points.reserve(n);
        for (size_t i = 0; i < n; i++) {
            Triangulation::Point p;
            cin >> p;
            points.push_back(p);
        }

        Triangulation t;
        t.insert(points.begin(), points.end());

        double distance = -1;
        for (Edge_iterator it = t.finite_edges_begin(); it != t.finite_edges_end(); it++) {
//            K::Ft d = CGAL::squared_distance()
//            K::FT d = CGAL::squ
            Triangulation::Segment seg = t.segment( it );

            Triangulation::Point p0 = seg.point(0);
            Triangulation::Point p1 = seg.point(1);
            double d = CGAL::to_double(CGAL::squared_distance(p0, p1));
//            cout << d << endl;
            if (d < distance || distance < 0.0) {
                distance = d;
            }
        }

        cout << ceil(sqrt(distance)/2.0*100.0) << endl;
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

