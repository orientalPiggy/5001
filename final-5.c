/*
 * final-5.c
 *
 * Problem 5.
 * This problem tests your ability to take an algorithm
 * for a familiar operation and implement it by iteratively
 * computing successively closer approximations to the
 * actual value for a given input value.
 *
 * The problem is to implement the square root (root2)
 * function using a method described in an ancient Indian
 * mathematical manuscript.
 *
 * Let s be a double for which we want the square root.
 * Here is an iterative algorithm that computes the
 * next approximation x(n+1), given the previous one x(n).
 *
 * a = (s/x(n) - x(n))/2
 * x(n+1) = x(n) + a * (1 - a/(2*(x(n)+a))
 *
 * Initialize x(0) = s as first approximation of its
 * square root
 *
 * The method is quartically convergent, which means
 * the number of correct digits roughly quadruples with
 * each iteration.
 *
 * The approximation stops when the next term is within
 * the precision of a double.
 */

#include <stdio.h>
#include <math.h>
#include <float.h>

// epsilon value for precision of a double
static const double epsln = (sizeof(double) >= 8) ? 1e-15 : 1e-7;

// format width for precision of a double
static const unsigned fmtw = (sizeof(double) >= 8) ? 14 : 6;

/**
 * This function computes the square root of a double
 * using approximation that is quartically convergent.
 *
 * Returns NAN if s < 0 or s is NAN, +INFINITY if s is
 * +INFINITY, or 0 if s < epsln. Otherwise, result is
 * returned to the precision of epsln for double format.
 *
 * @param s the number to take the square root.
 * @return the square root of the number.
 */
double root2(const double s) {
	// your code here.
	// note: see isnan(s), isinf(s), NAN, INFINITY in math.h

	// set result to sentinel value
	double result = -1;

	// corner cases
	if ( isnan(s) || s < 0) {
		return NAN;
	} else if (isinf(s)) {
		return +INFINITY;
	} else if (s < epsln) {
		return 0;
	} else {
		// Initialize x(0) = s as first approximation
		double previousEntry = s;
		double a = ((s / previousEntry) - previousEntry) / 2;
		double nextEntry = previousEntry
				+ a * (1 - a / (2 * (previousEntry + a)));
		// The loop continues when the difference between the
		// nextEntry and previousEntry is greater than epsln
		while (fabs(nextEntry - previousEntry) >= epsln) {

			// Update two entries
			previousEntry = nextEntry;
			a = ((s / previousEntry) - previousEntry) / 2;
			nextEntry = previousEntry + a * (1 - a / (2 * (previousEntry + a)));

		}
		result = nextEntry;
	}

	return result;
}

/**
 * Main function tests root2 function.
 */
int main(void) {

	printf("Start Problem 5\n\n");

	// test values
	double squares[] = { 0.0, 1.0, 2.0, 144.0, 336009.0, 15241383936.0, DBL_MAX,
			-1.0, NAN, INFINITY };

	for (int i = 0; i < 10; i++) {
		double root = root2(squares[i]);
		printf("root2(%.*g): %.*g expected: %.*g\n", // format width of double
				fmtw, squares[i], fmtw, root, fmtw, sqrt(squares[i]));
	}

	printf("\nEnd Problem 5\n");
}
