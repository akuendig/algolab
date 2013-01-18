#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>
#include <iostream>
#include <vector>
#include <cmath>

typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt K;
typedef CGAL::Min_circle_2_traits_2<K>  Min_Circle_Traits;
typedef  CGAL::Min_circle_2<Min_Circle_Traits> Min_Circle;
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

void testcases() {
    vector<K::Point_2> points;
    cout << fixed << setprecision(0);
    while(true) {
        int n;
        cin >> n;

        if (n <= 0)
            break;

        points.reserve(n);
        for (int i=0; i <n; i++) {
//            K::Point_2 p;
//            cin >> p;
            double x, y;
            cin >>x >> y;
//            p(x,y);
            K::Point_2 p(x, y);
            points.push_back(p);
        }

        Min_Circle mc(points.begin(), points.begin()+n, true);
        Min_Circle_Traits::Circle c = mc.circle();
        K::FT r = sqrt(c.squared_radius()); // you need Exact_predicates_exact_constructions_kernel_with_sqrt
        cout << ceil_to_double(r) << endl;

        points.clear();
    }
}

int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    testcases();
    return 0;
}
