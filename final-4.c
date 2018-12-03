/*
 * final-4.c
 *
 * Problem 4.
 * This problem tests your ability to take an algorithm for
 * a familiar operation and turn it into a function that
 * performs that operation.
 *
 * The problem is to implement a 4-function calculator that
 * performs arithmetic calculations by taking input from a
 * null-terminated array of strings. Use the algorithm  that
 * is described in the function documentation block below.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** Enumeration values representing the calculator operations */
typedef enum { NONE, ADD, SUB, MULT, DIV} Op;

/**
 * This function implements a 4-function calculator that performs
 * arithmetic calculations by taking input from a null-terminated
 * array of strings representing numbers and arithmetic operations
 * ("+", "-", "*", and "/").  The input "C" causes the calculator
 * to reset the result to 0 and the pending operation to NONE.
 *
 * When all the input strings have been processed, the calculator
 * returns the result of the calculation. A typical input array
 * {"4.5", "+", "2.5", "/", "2", NULL} returns the value 3.5.
 *
 * Here is the algorithm for the calculator:
 *
 * Set the result to 0, and the the pending operation to NONE.
 *
 * Process each input string, If the string represents an arithmetic
 * operation, save it as the pending operation. If the string is "C",
 * immediately reset the result to 0 and the pending operation to NONE.
 * if the string is a number, then perform the pending operation on
 * the result and the number.
 *
 *  - NONE sets the result to the number.
 *  - ADD adds the number to the result
 *  - SUB subtracts the number from the result
 * -  MULT multiplies the result by the number
 *
 * Reset the pending operation to NONE after performing the operation.
 *
 * Ignore any unexpected input strings. When no more input strings,
 * return the result.
 *
 * Note: use sscanf() with the format string "%lf" to parse a double
 * number. The function returns 1 if successful and 0 if not a number.
 *
 * @param input null-terminated array of input strings
 * @return the result of the calculation
 */
double calc(const char* input[]) {
	Op pendingOp = NONE;
	double result = 0;
	double pendingNum = 0;
	int index = 0;

	while (input[index] != NULL) {
		const char *str = input[index]; // get the current string
		int flag = sscanf(str, "%lf", &pendingNum); // copy current string to pendingNum
		if (!flag) { // the string is an operator
			if (strcmp(str, "NONE") == 0) {
				result = pendingNum;
			} else if (strcmp(str, "+") == 0) {
				pendingOp = ADD;
			} else if (strcmp(str, "-") == 0) {
				pendingOp = SUB;
			} else if (strcmp(str, "*") == 0) {
				pendingOp = MULT;
			} else if (strcmp(str, "/") == 0) {
				pendingOp = DIV;
			} else if (strcmp(str, "C") == 0) {
				pendingOp = NONE;
				pendingNum = 0;
				result = 0;
			}
		} else { // the string is a number
			switch (pendingOp) {
			case NONE:
				result = pendingNum;
				break;
			case ADD:
				result += pendingNum;
				break;
			case SUB:
				result -= pendingNum;
				break;
			case MULT:
				result *= pendingNum;
				break;
			case DIV:
				result /= pendingNum;
				break;
			default:
				break;
			}
		}

		index++; //increment index for next operation
	}

	return result;
}

/**
 * Main function tests calc function.
 */
int main(void) {

	printf("Start Problem 4\n\n");

	// input values
	char **cmds[] = {
		(char *[]){ NULL },
		(char *[]){ "4", NULL },
		(char *[]){ "4", "+", "5", NULL },
		(char *[]){ "4", "+", "5", "/", "2", NULL },
		(char *[]){ "4", "+", "5", "/", "2", "C", "5", NULL },
		(char *[]){ "3", "+", "C", "4", "+", "7", "/", "2", NULL },
		NULL
	};

	// expected results
	double expected[] = {0, 4, 9, 4.5, 5, 5.5 };

	// report actual and expected results
	for (int i = 0; cmds[i] != NULL; i++) {
		printf("%.2f expected: %.2f\n", calc(cmds[i]), expected[i]);
	}

	printf("\nEnd Problem 4\n");
	return EXIT_SUCCESS;
}
