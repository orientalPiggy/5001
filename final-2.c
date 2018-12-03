/*
 * final-2.c
 *
 * Problem 2.
 *
 * This problem tests your knowledge of allocating arrays of basic
 * values and pointers from the heap, and working with pointers to
 * one- and two-dimensional arrays.
 *
 * C supports two representations of 2D arrays. The first is as
 * a contiguous block of storage in row-major order. The second is
 * as an array of row pointers that point to storage for each
 * of the row arrays.
 *
 * Example:
 *   Contiguous block	Array of pointers to row arrays
 * 		1   2   3			| * | -> [ 1   2   3 ]
 * 		4   5   6			| * | -> [ 4   5   6 ]
 * 		7   8   9			| * | -> [ 7   8   9 ]
 *
 * This problem is to implement functions that allocate, initialize,
 * and return storage for both kinds of arrays.
 *
 * The main() method will call these functions and compare their
 * values against the input 2D array that was passed in and used
 * to initialize them.
 */
#include <stdlib.h>
#include <stdio.h>

/**
 * This function allocates storage for an nrows x ncols 2D array
 * of ints, and initializes the array from the corresponding values
 * in the input 2D array.
 * @param nrows the number of rows in the input array
 * @param ncols the number of columns in the input array
 * @param array2D the input 2D array
 * @param the allocated array of array pointers
 */
int *copyArray2D_V1(size_t nrows, size_t ncols, int array2D[][ncols]) {
	int *arr2D = malloc(nrows * ncols * sizeof(int));
	int *curr = arr2D;
	for (int r = 0; r < nrows; r++) {
		for (int c = 0; c < ncols; c++) {
			*curr++ = array2D[r][c];
		}
	}

	return arr2D;
}

/**
 * This function allocates an nrows array of int pointers. The
 * pointers are initialized to allocated storage for rows of ncols
 * and the rows are initialized from the corresponding values in
 * the input 2D array.
 * @param nrows the number of rows in the input array
 * @param ncols the number of columns in the input array
 * @param array2D the input 2D array
 * @param the allocated array of array pointers
 */
int **copyArray2D_V2(size_t nrows, size_t ncols, int array2D[][ncols]) {
	// allocate memory for array of row pointers
	int **arr2D = malloc(nrows * sizeof(int*));
	int **curr = arr2D;
	for (int r = 0; r < nrows; r++) {
		// allocate memory for one row
		int *singleRow = malloc(ncols * (sizeof(int)));
		*curr++ = singleRow; // add pointer to this row to array of row pointers
		for (int c = 0; c < ncols; c++) {
			*singleRow++ = array2D[r][c];
		}
	}

	return arr2D;
}

/**
 * Test copyArray2D_V1() function with test input array.
 * @param nrows number of rows
 * @param ncols number of cols
 * @param array2d input array2D
 */
void test_copyArray2D_V1(size_t nrows, size_t ncols, int array2D[][ncols]) {
	// test copyArray2D_V1 allocating 2D array as contiguous array
	printf("\nCalling copyArray2D_V1(%lu, %lu, array2D)\n", nrows, ncols);
	int *array2D_V1 = copyArray2D_V1(nrows, ncols, array2D);
	if (array2D_V1 == NULL) {
		printf("Unexpected return of NULL pointer\n");
	} else {
		int* p = array2D_V1;
		for (int r = 0; r < nrows; r++) {
			for (int c = 0; c < ncols; c++) {
				printf("%d (expect %d) ", *p++, array2D[r][c]);
			}
			printf("\n");
		}

		// free array storage
		free(array2D_V1);
	}
}

/**
 * Test copyArray2D_V2() function with test input array.
 * @param nrows number of rows
 * @param ncols number of cols
 * @param array2d input array2D
 */
void test_copyArray2D_V2(size_t nrows, size_t ncols, int array2D[][ncols]) {
	// test copyArray2D_V1 allocating 2D array array of pointers
	// to allocated row arrays.
	printf("\nCalling copyArray2D_V2(%lu, %lu, array2D)\n", nrows, ncols);
	int **array2D_V2 = copyArray2D_V2(nrows, ncols, array2D);
	if (array2D_V2 == NULL) {
		printf("Unexpected return of NULL pointer\n");
	} else {
		for (int r = 0; r < nrows; r++) {
			for (int c = 0; c < ncols; c++) {
				printf("%d (expect %d) ", array2D_V2[r][c], array2D[r][c]);
			}
			printf("\n");
		}

		// free row storage
		for (int r = 0; r < nrows; r++) {
			free (array2D_V2[r]);
		}

		// free row pointer array
		free(array2D_V2);
	}
}

/**
 * Main function tests array copy functions
 */
int main(void) {
	printf("Start Problem 2\n");

	int array2D_1_3[1][3] = {
		{ 1, 2, 3 }
	};
	printf("\nTesting array2D_1_3[1][3]:\n");
	test_copyArray2D_V1(1, 3, array2D_1_3);
	test_copyArray2D_V2(1, 3, array2D_1_3);

	int array2D_3_1[3][1] = {
		{ 1 },
		{ 4 },
		{ 7 }
	};
	printf("\nTesting array2D_3_1[3][1]:\n");
	test_copyArray2D_V1(3, 1, array2D_3_1);
	test_copyArray2D_V2(3, 1, array2D_3_1);

	int array2D_3_3[3][3] = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	};
	printf("\nTesting array2D_3_3[3][3]:\n");
	test_copyArray2D_V1(3, 3, array2D_3_3);
	test_copyArray2D_V2(3, 3, array2D_3_3);

	printf("\nEnd Problem 2\n");
	return EXIT_SUCCESS;
}
