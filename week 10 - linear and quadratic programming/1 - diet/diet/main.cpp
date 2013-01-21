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
//	const int X = 0;
//	const int Y = 1;
//	const int ZZ = 2;

	int num_nutrients, num_foods;
	int nutrients[41][2];
	int food_nutrients[101][41];
	int	prices[101];
    while (true) {
    	cin >> num_nutrients >> num_foods;
    	if (num_nutrients == 0 && num_foods == 0) {
    		break;
    	}
    	for (int i=0; i<num_nutrients; i++) {
    		cin >> nutrients[i][0] >> nutrients[i][1];
    	}
    	for (int i=0; i<num_foods; i++) {
    		cin >> prices[i];
    		for (int j=0; j<num_nutrients; j++) {
    			cin >> food_nutrients[i][j];
    		}
    	}
    	int FOODS = 0;
    	Program qp (CGAL::SMALLER, true, 0, false, 0);
    	// function to minimize
    	for (int i=0; i < num_foods; i++) {
    		qp.set_c(FOODS+i, prices[i]);
    	}

    	int eq_counter = 0;

    	for (int i=0; i<num_nutrients; i++) {
    		for (int j=0;j<num_foods;j++) {
        		qp.set_a(FOODS+j,eq_counter,food_nutrients[j][i]);
    		}
    		qp.set_b(eq_counter, nutrients[i][1]);
    		eq_counter++;
    	}

    	for (int i=0; i<num_nutrients; i++) {
    		for (int j=0;j<num_foods;j++) {
        		qp.set_a(FOODS+j,eq_counter,food_nutrients[j][i]);
    		}
    		qp.set_b(eq_counter, nutrients[i][0]);
    		qp.set_r(eq_counter, CGAL::LARGER);
    		eq_counter++;
    	}

    	Solution s = CGAL::solve_nonnegative_quadratic_program(qp, ET());
    	if (s.is_optimal()) {
			cout << floor(CGAL::to_double(s.objective_value())) << endl;
		} else {
			cout << "No such diet.\n";
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

