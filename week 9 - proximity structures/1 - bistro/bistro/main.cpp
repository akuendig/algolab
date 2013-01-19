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

        size_t nres;
        cin >> nres;
        for (size_t i=0; i<nres; i++) {
            Triangulation::Point p;
            cin >> p;
            Triangulation::Point v = t.nearest_vertex(p)->point();
            double d = CGAL::to_double(CGAL::squared_distance(p, v));
            cout << d << endl;
        }
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

