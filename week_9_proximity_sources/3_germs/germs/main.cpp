#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/squared_distance_2.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

typedef CGAL::Exact_predicates_inexact_constructions_kernel  K;
typedef CGAL::Triangulation_vertex_base_with_info_2<K::FT,K> Vb;
typedef CGAL::Triangulation_face_base_2<K>                   Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb>          Tds;
typedef CGAL::Delaunay_triangulation_2<K,Tds>                Delaunay;
typedef Delaunay::Finite_vertices_iterator                   VI;
typedef Delaunay::Finite_edges_iterator                      EI;
using namespace std;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

int hours(K::FT& in) {
	double d = CGAL::to_double(in);
	double z = sqrt(d)-0.5;
	int k;
	if (z <= 0.0) {
		k = 0;
	} else {
		k = ceil(sqrt(z));
	}
	return k;
}

void testcases() {
    size_t n;
    std::vector<Delaunay::Point> points;
    while (cin >> n && n > 0) {
        points.reserve(n);

        double l, b, r, t;
        // left, bottom, right, top
        cin >> l >> b >> r >> t;

        for (size_t i = 0; i < n; i++) {
        	double x, y;
        	cin >> x >> y;
            Delaunay::Point p(x,y);
            points.push_back(p);
        }


        Delaunay dt;
        dt.insert(points.begin(), points.end());
        // info (-> squared distance to nearest neighbor, initially, the boundary)
        for (VI v = dt.finite_vertices_begin(); v != dt.finite_vertices_end(); ++v) {
        	v->info() = min(min(v->point().x() - l, r - v->point().x()),
        				std::min(v->point().y() - b, t - v->point().y()));
        	v->info() *= v->info();
         }

        // compute all nearest neighbors
        for (EI e = dt.finite_edges_begin(); e != dt.finite_edges_end(); ++e) {
            Delaunay::Vertex_handle v1 = e->first->vertex(dt.cw(e->second));
            Delaunay::Vertex_handle v2 = e->first->vertex(dt.ccw(e->second));
            K::FT d = CGAL::squared_distance(v1->point(), v2->point()) / 4;
            v1->info() = std::min(v1->info(), d);
            v2->info() = std::min(v2->info(), d);
        }
        vector<K::FT> ltv;
        ltv.reserve(n);
        for (VI v = dt.finite_vertices_begin(); v != dt.finite_vertices_end(); ++v) {
        	ltv.push_back(v->info());
        }
        sort(ltv.begin(), ltv.end());
//        for (vector<int>::iterator it=minf.begin(); it!=minf.end(); it++) {
//        	cout << *it << " ";
//        }
//        cout << endl;
        cout << hours(ltv[0]) << " " << hours(ltv[n/2]) << " " << hours(ltv[n-1]) << endl;
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

