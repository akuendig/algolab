#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
using namespace std;

double floor_to_double(const K::FT& x)
{
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}

void testcases() {
    while(true) {
        int n;
        cin >> n;
        if (n == 0) {
            break;
        }
        double lx, ly, rx, ry;
        cin >> lx >> ly >> rx >> ry;
        K::Ray_2 r(K::Point_2(lx, ly), K::Point_2(rx, ry));
        bool intersected = false;
        for (int i=0; i < n; i++) {
            cin >> lx >> ly >> rx >> ry;
            if (!intersected) {
                K::Segment_2 s(K::Point_2(lx, ly), K::Point_2(rx, ry));
                if (CGAL::do_intersect(r,s)) {
                    intersected = true;
                }
            }
        }
        if (intersected) {
            cout << "yes" << endl;
        } else {
            cout << "no" << endl;
        }
    }
}

int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    testcases();
    return 0;
}

