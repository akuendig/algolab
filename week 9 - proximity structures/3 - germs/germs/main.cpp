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
typedef Triangulation::Vertex_handle  Vertex_handle;
typedef Triangulation::Point  Point;
using namespace std;

double bl, bb, br, bt;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}
inline double compute_size(int time) {
	double dtime = double(time);
	double size = (dtime*dtime)+0.5;
	return size;
}
int update(int time, int alive, map<Vertex_handle, bool> &alive_map, Triangulation &t) {
	double size = compute_size(time);
	double size2 = size*size;
	double size24 = size2*4.0;
    for (Triangulation::Vertex_iterator it=t.finite_vertices_begin(); it !=t.finite_vertices_end(); it++) {
    	if (t.is_infinite(it)) {
    		cout << "finite edge" << endl;
    		continue;
    	}
        if (alive_map[it]) {
        	Point p = it->point();
        	double px = CGAL::to_double(p.hx());
        	double py = CGAL::to_double(p.hy());
        	if (px-size <= bl || px+size >= br || py-size <= bb || py+size >= bt) {
        		alive_map[it] = false;
        		alive--;
//        		cout << "Colliding with border" << endl;
//    			cout << px << " " << py << "s: " << size << " b: " << bl << " " << br << " " << bb << " " << bt << endl;
        		continue;
        	}

            Triangulation::Vertex_circulator c = t.incident_vertices(it);
            if (c == 0) {
            	continue;
            }
            do {
            	if (t.is_infinite(c)) {
            		continue;
            	}
            	Point p2 = c->point();
            	double d2 = CGAL::to_double(CGAL::squared_distance(p, p2));
            	if (size24 >= d2) {
            		Vertex_handle sv = it;
            		Vertex_handle se = c.base();
            		if (alive_map[sv]) {
            			alive--;
//            			cout << "updating alive" << endl;
            			alive_map[sv] = false;
            		}
            		if (alive_map[se]) {
            			alive--;
            			alive_map[se] = false;
//            			cout << "updating alive" << endl;
            		}
            	}
            } while (++c != t.incident_vertices(it));
        }
    }
    return alive;
}

void testcases() {
    size_t n;
    std::vector<Triangulation::Point> points;
    while (cin >> n && n > 0) {
        points.reserve(n);

        // left, bottom, right, top
        cin >> bl >> bb >> br >> bt;

        for (size_t i = 0; i < n; i++) {
        	double x, y;
        	cin >> x >> y;
            Triangulation::Point p(x,y);
            points.push_back(p);
        }

        Triangulation t;
        t.insert(points.begin(), points.end());
        int alive = n;
        map<Vertex_handle, bool> alive_map;
        // Set
        for (Triangulation::Vertex_iterator it=t.vertices_begin(); it !=t.vertices_end(); it++) {
            alive_map[it] = true;
        }

        int time = 0;
        bool fbool = false;
        bool mbool = false;
        bool lbool = false;
//        cout  << "new testcase: "<< n << " " << (n/2) << "d" << endl;
        while (true) {
        	alive = update(time, alive, alive_map, t);
//        	cout << endl << "time: " << time << ": alive: " << alive << endl;
        	if (!fbool && alive < n) {
        		fbool = true;
        		cout << time << " ";
        	}
        	if (!mbool && (alive*2 < (n) || alive == 0)) {
        		mbool = true;
        		cout << time << " ";
        	}
        	if (!lbool && alive <= 0) {

        		cout << time;
        		break;
        	}
        	time++;
        }
//        cout << " end ";
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

