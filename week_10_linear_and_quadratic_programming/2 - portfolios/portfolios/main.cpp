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

typedef struct {
	int cost;
	int ret;
	int var;
} cust;
void testcases() {
    size_t p;
//	const int X = 0;
//	const int Y = 1;
//	const int ZZ = 2;

    int costs[101];
    int ereturn[101];
    int covariances[101][101];
    cust customers[11];

    while (true) {
    	int n_assets, m_customers;
    	cin >> n_assets >> m_customers;
    	if (n_assets == 0 && m_customers == 0) {
    		break;
    	}
    	for (int i=0; i<n_assets; i++) {
    		cin >> costs[i] >> ereturn[i];
    	}
    	for (int i=0; i<n_assets; i++) {
    		for (int j=0; j<n_assets; j++) {
    			cin >> covariances[i][j];
    		}
    	}

    	for (int i=0; i<m_customers; i++) {
    		int cost, ret, var;
    		cin >> cost >> ret >> var;
    		Program qp (CGAL::SMALLER, true, 0, false, 0);
    		for (int i=0; i<n_assets; i++) {
    			for (int j=0; j<n_assets; j++) {
    				qp.set_d(i, j, 2*covariances[i][j]);
    			}
    		}

    		for (int i=0; i<n_assets; i++) {
    			qp.set_a(i, 0, ereturn[i]);

    			qp.set_a(i, 1, costs[i]);

    		}
			qp.set_r(0, CGAL::LARGER);
			qp.set_b(0, ret);

			qp.set_b(1, cost);

			Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
    		if (s.is_optimal() && CGAL::to_double(s.objective_value()) <= var) {
    			//cout << CGAL::to_double(s.objective_value()) << " var: " << var << " ";
    			cout << "Yes." << endl;
    		} else {
    			cout << "No." << endl;
    		}
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

