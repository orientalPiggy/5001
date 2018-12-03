/*
 * final-5.c
 *
 * This assignment tests your understanding basic programming
 * concepts, loops, arrays, and pointers.
 *
 * This problem is to write a function findInString() that
 * returns a pointer to the first occurrence of a string in
 * another string. See the function description for details.
 *
 * Here is an algorithm for this function:
 *
 * For each starting position in 'lookingIn', compare each
 * character in lookingFor to the corresponding character in
 * 'lookingIn'.
 *
 * If reached the end of 'lookingFor', then return the current
 * starting position in 'lookingIn, else keep comparing the
 * characters in the two arrays while they are equal.
 *
 * If not found at the current starting position in 'lookingIn',
 * try again at the next position until reaching the end  of
 * 'lookingIn' At that point, return NULL.
 *
 * Important: Do not use any functions from "string.h" to
 * implement this function.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Returns pointer to first occurrence of lookingFor string in
 * lookingIn string. If lookingFor string is empty, returns
 * pointer to lookingIn string. If not found, returns NULL.
 *
 * @param lookingIn the string to look in
 * @param lookingFor the string to look for
 * @return pointer to first occurrence of lookingFor in
 *   lookingIn or NULL if not found
 */
const char *findInString(const char *lookingIn, const char *lookingFor) {
	if (strlen(lookingFor) == 0) { // if lookingFor is empty, return lookingIn
		return lookingIn;
	}

	const char *inp = lookingIn, *forp = lookingFor;
	const char *lastp = lookingIn;

	while (*inp != '\0') {
		if (*inp == *forp) { // if first char of lookingFor matches a char in lookingIn
			lastp = inp; // store the start position for this search
			while (*inp != '\0' && *forp != '\0' && *inp == *forp) {
				// check if rest of lookingIn matches lookingFor
				inp++;
				forp++;
			}
			if (*forp == '\0') { // lookingFor contains lookingIn
				return lastp;
			}
			// lookingFor doesn't contain lookingIn,
			inp = lastp++; // restore search start position to the next one of last search
			forp = lookingFor;
		}
		inp++;
	}

	return NULL; // lookingFor doesn't contain lookingIn
}

/**
 * Main function tests strInStr function.
 */
int main(void) {
	const char *lookingIn[] = {
		"",
		"the",
		"the rain in Spain",
		NULL
	};

	const char *lookingFor[] = {
		"",
		"rain",
		"the rain",
		"rain in",
		NULL
	};

	const char *expectedVals[] = {
			"", NULL, NULL,
			NULL, "the", NULL,
			NULL, NULL, "the rain in Spain",
			"rain in Spain", "the rain in Spain", "rain in Spain"
	};
	printf("Start Problem 5\n");

	// try each lookingFor string against each lookingIn string
	const char **expect = expectedVals;
	for (int i = 0; lookingIn[i] != NULL; i++) {
		for (int j = 0; lookingFor[j] != NULL; j++) {
			const char *result = findInString(lookingIn[i], lookingFor[j]);
			printf("for:    '%s'\n", lookingFor[j]);
			printf("in:     '%s'\n", lookingIn[i]);
			printf("found:  '%s'\n", result);
			printf("expect: '%s'\n\n", *(expect++));
		}
	}

	printf("\nEnd Problem 5\n");
	return EXIT_SUCCESS;
}
