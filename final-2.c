/*
 * final-2.c
 *
 * Problem 2.
 *
 * This problem tests your understanding of 2D arrays and
 * loops. You will create a function diagonalUpRight2D
 * that traverses an 2D array diagonally starting at the
 * top left cell and moving from bottom right to top left.
 * The function adds the values at the cells it traverses
 * to a 1D array.
 *
 * Here is a sample for a 5x5 array whose cell values also
 * represent the order of traversal
 *        1     3     6    10    15
 *
 *        2     5     9    14    19
 *
 *        4     8    13    18    22
 *
 *        7    12    17    21    24
 *
 *       11    16    20    23    25
 *
 *  Here is the algorithm:
 *  1. Step down the first column. For each cell, copy
 *  the cell value to the 1D array
 *
 *  2. Repeat for the previous row in the next column
 *  until reaching the first row.
 *
 *  3. Step across the last row. For each cell, copy the
 *  cell value to the 1D array.
 *
 *  4. Repeat for the previous row in the next column
 * until reaching the last column.
 *
 */
#include <stdio.h>

/**
 * This function traverses a square 2D array with n rows
 * and n columns diagonally up and to the right. For each
 * cell it visits, the function copies the value to a 1D
 * path array of size n*n.
 *
 * @param n the number of rows and columns in the 2D array
 * @param array2D the 2D array of size nxn
 * @param a 1D array of size n*n that receives the values of cells traversed
 */
void diagonalUpRight2D(int n, int array2D[n][n], int array1D[]) {

//	if (n==0){
//		printf("Error. no element.\n")
//	}
	int r = 0;
	int c = 0;

	// 1*1 matrix , no LowerHalf matrix, only 1 element
	if (n == 1) {
		array1D[0] = array2D[0][0];
	} else {

		// Print UpperHalf matrix including diagonal line

		int i = 0;
		// Traverse First column
		for (; r < n; r++) {
			int rowR = r;
			// Fixed first column
			int columnC = 0;
			do {
				// First element in each column is guaranteed to be included
				array1D[i] = array2D[rowR][columnC];
				// Shift to next element in upper right direction
				rowR--;
				columnC++;
				i++;
				// the loop ends when the row and column index no longer exists
			} while (rowR >= 0 && columnC < n);
		}

		// Print LowerHalf matrix (excluding diagonal line)
		// Traverse Last Row
		r = n - 1;
		// Excluding the diagonal line
		c = 1;
		// Traverse until last column
		for (; c < n; c++){
			// Fixed last row
			int rowR = n - 1;
			// starting position for each column in last row
			int columnC = c;
			do{
				array1D[i] = array2D[rowR][columnC];
				rowR--;
				columnC++;
				i++;
			}while (rowR >= 0 && columnC < n);
		}
	}
}

/**
 * Main function tests array copy functions
 */
int main(void) {
printf("Start Problem 2\n");

// test 1x1 array
int a2D_1x1[1][1] = { { 1 } };
int a1D_1x1[1];
diagonalUpRight2D(1, a2D_1x1, a1D_1x1);
printf("%dx%d: ", 1, 1);
for (int i = 0; i < 1; i++) {
	printf(" %d", a1D_1x1[i]);
}
printf("\n");

printf("expected:");
for (int i = 0; i < 1; i++) {
	printf(" %d", i + 1);
}
printf("\n");

// test 2x2 array
int a2D_2x2[2][2] = { { 1, 3 }, { 2, 4 } };
int a1D_2x2[4];
diagonalUpRight2D(2, a2D_2x2, a1D_2x2);
printf("a1D_%dx%d: ", 2, 2);
for (int i = 0; i < 4; i++) {
	printf(" %d", a1D_2x2[i]);
}
printf("\n");

printf("expected:");
for (int i = 0; i < 4; i++) {
	printf(" %d", i + 1);
}
printf("\n");

// test 5x5 array
int a2D_5x5[5][5] = { { 1, 3, 6, 10, 15 }, { 2, 5, 9, 14, 19 }, { 4, 8, 13, 18,
		22 }, { 7, 12, 17, 21, 24 }, { 11, 16, 20, 23, 25 } };
int a1D_5x5[25];
diagonalUpRight2D(5, a2D_5x5, a1D_5x5);
printf("a1D_%dx%d: ", 5, 5);
for (int i = 0; i < 25; i++) {
	printf(" %d", a1D_5x5[i]);
}
printf("\n");

printf("expected:");
for (int i = 0; i < 25; i++) {
	printf(" %d", i + 1);
}
printf("\n");

printf("\nEnd Problem 2\n");
}
