#include <CGAL/Exact_predicates_exact_constructions_kernel.h>


#include <iostream>
#include <vector>
#include <algorithm>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
using namespace std;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}
double ceil_to_double(const K::FT& x)
{
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void shorten_segment(K::Segment_2 &s, CGAL::Object o) {
    if (const K::Point_2 *p = CGAL::object_cast<K::Point_2>(&o)) {
        s = K::Segment_2(s.source(), *p);
    } else if (const K::Segment_2 *t = CGAL::object_cast<K::Segment_2>(&o)) {
        // select endpoint of *t closer to s.source()
        if (CGAL::collinear_are_ordered_along_line(s.source(), t->source(), t->target())) {
            s = K::Segment_2(s.source(), t->source());
        } else {
          s = K::Segment_2(s.source(), t->target());
        }
    } else {
        throw runtime_error("Strange Error");
    }
}

void testcases() {
//    cout << fixed << setprecision(0);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

    while(true) {
        size_t n;
        cin >> n;

        if (n == 0)
            break;

        double ix, iy, jx, jy;
//        cin >> ix >> iy >> jx >> jy;
//        K::Ray_2 r(K::Point_2(ix, iy), K::Point_2(jx, jy));
        K::Ray_2 r;
        cin >> r;
        K::Segment_2 rc(r.source(), r.source());

        vector<K::Segment_2> segments;
        segments.reserve(n);

        size_t i = 0;
        for (; i<n; ++i) {
            // We are losing accuracy
            cin >> ix >> iy >> jx >> jy;
            segments.push_back(K::Segment_2(K::Point_2(ix, iy), K::Point_2(jx, jy)));
//            K::Segment_2 ss;
//            cin >> ss;
//            segments.push_back(ss);
        }
//        random_shuffle(segments.begin(), segments.end());

        for (i=0; i<n; ++i) {
            if (CGAL::do_intersect(segments[i], r)) {
                shorten_segment(rc, CGAL::intersection(r, segments[i]));
                break;
            }
        }
        if (i >= n) {
            cout << "no" << endl;
            continue;
        }
        while (++i < n) {
            if (CGAL::do_intersect(segments[i], rc)) {
                shorten_segment(rc, CGAL::intersection(r, segments[i]));
            }
        }
        cout << floor_to_double(rc.target().x()) << " "
                << floor_to_double(rc.target().y()) << endl;
        segments.clear();
    }
}

int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    testcases();
    return 0;
}
