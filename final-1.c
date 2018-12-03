/*
 * final-1.c
 *
 * Problem 1.
 * This problem tests your basic knowledge of null-terminated
 * string arrays, passing strings to functions and loops that
 * operate over string arrays.
 *
 * In this problem, you will implement a transliteration function
 * that copies characters of the 'fromText' input string to the
 * 'toText' output string, If a character in the input string
 * matches a character in a separate 'fromChars' array, copy the
 * corresponding character in a toCHars' array instead. You may
 * use standard string library functions for this problem.
 *
 * For example:
 *
 * a   c   e				(fromChars)
 * A   C   E				(toChars)
 *
 * a   b   c   d   e 	(fromText)
 * |   |   |   |   |
 * A   |   C   |   E		(transliterations)
 * v   v   v   v   v
 * A   b   C   d   E		(toText)
 *
 * The main program tests the function for various transliteration
 * arrays. The first test transliterates lower-case to upper-case
 * characters, for example. Several other tests show how the
 * function can be used to implement simple substitution ciphers,
 * including one invented by Julius Caeser.
 *
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Copy fromText to toText, transliterating characters in
 * fromChars to positionally corresponding characters in
 * toChars. Characters not in fromChars are copied directly
 * to toText.
 *
 * The toText array must be large enough to copy fromText.
 * The fromChars and toChars arrays must be the same size.
 *
 * @param toText the destination string
 * @param toChars the characters to replace with
 * @param fromText the source string
 * @param fromChars the characters to replace
 */
void translit (char *toText, const char *toChars,
			   const char *fromText, const char *fromChars) {
	char *toTextp = toText;
	const char *fromTextp = fromText;

	while (*fromTextp != '\0') {
		// get the position where current char appears in fromChars array
		char *posInFromChars = strchr(fromChars, *fromTextp);
		// if fromChars array contains current char, copy corresponding char from toChars
		if (posInFromChars != NULL) {
			*toTextp++ = *(posInFromChars - fromChars + toChars);
			fromTextp++;
			continue;
		}
		// if doesn't contain, copy from fromText
		*toTextp++ = *fromTextp++;
	}
}

/**
 * Main program tests translit function.
 */
int main(void) {
	printf("Start Problem 1\n");

	char translitText[128];
	char plainText[128];

	const char *plainChars = "abcdefghijklmnopqrstuvwxyz";
	const char *message = "runforyourlifewearediscovered";

	// transliterate from lower to upper case
	const char *upperChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	printf("\nTransliterate lower to upper case characters\n");
	printf("original: %s\n", message);
	translit(translitText, upperChars, message, plainChars);
	printf("translit: %s\n", translitText);
	translit(plainText, plainChars, translitText, upperChars);
	printf("plain: %s\n", plainText);

	// empty transliteration arrays perform no transliteration
	const char *noChars = "";
	printf("\nTransliterate no characters\n");
	printf("original: %s\n", message);
	translit(translitText, noChars, message, noChars);
	printf("translit: %s\n", translitText);
	translit(plainText, noChars, translitText, noChars);
	printf("plain: %s\n", plainText);

	// same transliteration arrays perform no transliteration
	printf("\nTransliterate all characters to themselves\n");
	printf("original: %s\n", message);
	translit(translitText, plainChars, message, plainChars);
	printf("translit: %s\n", translitText);
	translit(plainText, plainChars, translitText, plainChars);
	printf("plain: %s\n", plainText);
	// mixed substitution cipher uses a code word with non-repeating

	// characters followed by the unused letters of the alphabet;
	// code word is 'monarchy'.
	const char *mixedChars = "monarchybdefgijklpqstuvwxz";
	printf("\nMixed or Deranged code word alphabet substitution cipher\n");
	printf("original: %s\n", message);
	translit(translitText, mixedChars, message, plainChars);
	printf("translit: %s\n", translitText);
	translit(plainText, plainChars, translitText, mixedChars);
	printf("plain: %s\n", plainText);

	// Caesar substitution cipher invented by Julius Caesar
	// transliterates using transposed upper- and lower-halves of alphabet
	const char *caesarChars = "nopqrstuvwxyzabcdefghijklm";
	printf("\nCaesar transposed upper and lower alphabet substitution cipher\n");
	printf("original: %s\n", message);
	translit(translitText, caesarChars, message, plainChars);
	printf("translit: %s\n", translitText);
	translit(plainText, plainChars, translitText, caesarChars);
	printf("plain: %s\n", plainText);

	// Atbash substitution cypher transposes using reversed alphabet
	const char *atbashChars = "zyxwvutsrqponmlkjihgfedcba";
	printf("\nAtbash reversed alphabet substitution cypher\n");
	printf("original: %s\n", message);
	translit(translitText, atbashChars, message, plainChars);
	printf("translit: %s\n", translitText);
	translit(plainText, plainChars, translitText, atbashChars);
	printf("plain: %s\n", plainText);

	printf("\nEnd Problem 1\n");
	return EXIT_SUCCESS;
}
