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

int ceil_to_double(const CGAL::Quotient<ET>& x) {
  double a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}


void testcases() {
    size_t p;
	const int X = 0;
	const int Y = 1;
	const int ZZ = 2;
	int a, b;

    while (cin >> p && p > 0) {
    	int a, b;
    	cin >> a >> b;

        Program qp1 (CGAL::SMALLER, true, 0, false, 0);
        // -b*y + a*x^2
        	qp1.set_c(Y, -b);
        	qp1.set_d(X, X, 2*a);

        // x + y <= 4
    		qp1.set_a(X, 0, 1);
    		qp1.set_a(Y, 0, 1);
    		qp1.set_b(0, 4);
    	// 4x + 2y <= ab
    		qp1.set_a(X, 1, 4);
    		qp1.set_a(Y, 1, 2);
    		qp1.set_b(1, a*b);

    	// -x + y <= 1
    		qp1.set_a(X, 2, -1);
    		qp1.set_a(Y, 2, 1);
    		qp1.set_b(2, 1);

    	// X >= 0
//    		qp1.set_l(X, true, 0);
    	// Y >= 0
//   		qp1.set_l(Y, true, 0);

    	Program qp2 (CGAL::LARGER, false, 0, false, 0);
    	// a*x^2 + b*y + zz^2
    		qp2.set_d(X, X, 2*a);
    		qp2.set_c(Y, b);
    		qp2.set_d(ZZ, ZZ, 2);

    	// x + y >= -4
    		qp2.set_a(X, 0, 1);
    		qp2.set_a(Y, 0, 1);
    		qp2.set_b(0, -4);
       	// 4x + 2y  + zz >= -ab
    		qp2.set_a(X, 1, 4);
    		qp2.set_a(Y, 1, 2);
    		qp2.set_a(ZZ, 1, 1);
    		qp2.set_b(1, -a*b);

    	// -x + y >= -1
    		qp2.set_a(X, 2, -1);
    		qp2.set_a(Y, 2, 1);
    		qp2.set_b(2, -1);

    	// X <= 0
    		qp2.set_u(X, true, 0);
    	// Y <= 0
    		qp2.set_u(Y, true, 0);
    	// ZZ >= 0
    		qp2.set_l(ZZ, true, 0);


		Solution s = (p==1 ?
					  CGAL::solve_nonnegative_quadratic_program(qp1, ET()) :
					  CGAL::solve_quadratic_program(qp2, ET()) );
		if (s.is_infeasible()) std::cout << "no" << std::endl;
		else if (s.is_unbounded()) std::cout << "unbounded" << std::endl;
		else std::cout << (p==1?-1:1)*ceil_to_double(s.objective_value())
			 << std::endl;


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

