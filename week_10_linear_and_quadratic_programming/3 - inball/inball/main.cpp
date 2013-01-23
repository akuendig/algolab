#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>
#include <vector>
#include <cmath>

using namespace std;

#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

// program and solution types
typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

double floor_to_double(const CGAL::Quotient<ET>& x)
{
    double a = floor(CGAL::to_double(x));
    while (a > x) a -= 1;
    while (a+1 <= x) a += 1;
    return a;
}

double ceil_to_double(const CGAL::Quotient<ET>& x) {
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void testcases() {
	while (true) {
		int n, d;
    	cin >> n;
    	if (n == 0) {
    		break;
    	}
    	cin >> d;

    	int R = d;
    	Program qp (CGAL::SMALLER, false, 0, false, 0);
    	qp.set_c(R, -1);
    	for (int i=0; i<n; i++) {
    		int la = 0;
    		for (int j=0; j<d; j++) {
    			int a;
    			cin >> a;
        		qp.set_a(j, i, a);
        		qp.set_a(j, i+n, a);

        		la += a*a;
    		}
    		qp.set_a(R, i, int(sqrt(la)));

    		int b;
    		cin >> b;
    		qp.set_b(i, b);
    		qp.set_b(i+n, b);
    	}

    	Solution s = CGAL::solve_linear_program(qp, ET());
    	if (s.is_infeasible()){
			cout << "none" << endl;
		} else if (s.is_unbounded()) {
			cout << "inf" << endl;
		} else {
//            CGAL::Quadratic_program_solution<ET>::Variable_value_iterator
//            opt = s.variable_values_begin();
//            CGAL::Quotient<ET> radius = *(opt);
//            cout << floor_to_double(radius) << endl;
			cout << abs( ceil_to_double(s.objective_value()) ) << endl;
    	}
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

