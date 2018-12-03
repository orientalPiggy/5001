/*
 * final-3.c
 *
 *  Problem 3.
 *
 *	This problem tests your understanding of using enums and
 *	structs plus functions to create local and dynamic data types.
 *
 *	This problem defines a playing card Card with a Suit and
 *	Value, and a deck of cards Deck as a counted collection of
 *	cards.
 *
 *	Use these enumerations, string arrays, and typedef structs
 *	to implement the playing card functions below. Carefully
 *	follow the instructions for each of the functions.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/** Enumeration of card suits */
typedef enum {
	Hearts, Diamonds, Clubs, Spades
} Suit;

/** Enumeration of card values */
typedef enum {
	Ace=1, Two, Three, Four, Five, Six, Seven, Eight,
	Nine, Ten, Jack, Queen, King
} Value;

/** Suit names corresponding to Suit enum. */
const char *suitName[] = { "Hearts", "Diamonds", "Clubs", "Spades" };

/** Card value names corresponding to Value enum. ([0] unused) */
const char *valueName[] = {
	"*", "Ace", "2", "3", "4", "5", "6", "7", "8",
	"9", "10", "Jack", "Queen", "King"
};

/** A playing card with suit and value */
typedef struct {
	/** the suit of the card */
	Suit suit;
	/** the value of the card */
	Value value;
} Card;

/**
 * A deck of cards
 */
typedef struct {
	/** array of up to 52 cards (4 suits, 13 values) */
	Card cards[52];
	/** the number of cards in the deck */
	int ncards;
} Deck;

/**
 * Creates a card. If card is NULL, allocates storage, otherwise
 * uses the storage passed in.
 *
 * @param value the card Value
 * @param suit the card Suit
 * @param card pointer to a card or NULL if this function
 *   should allocate the card
 * @return initialized card
 */
Card *createCard(Value value, Suit suit, Card *card) {
	if (card == NULL) {
		card = malloc(sizeof(Card));
	}
	card->value = value;
	card->suit = suit;

	return card;
}

/**
 * Creates a full deck of cards. If deck is NULL, allocates
 * storage, otherwise uses the storage passed in.
 *
 * Use Suit and Value types and enumeration values rather than
 * integers for loop indexes, and use createCard() to initialize
 * each card in the cards array. The the deck ncards field is set
 * to the number of cards in the deck.
 *
 * @param deck the deck to initialize or NULL if this function
 * 	should allocate the deck
 * @return an initialize deck of cards
 */
Deck *createDeck(Deck *deck) {
	if (deck == NULL) {
		deck = malloc(sizeof(Deck));
	}
	for (Suit s = Hearts; s <= Spades; s++) {
		for (Value v = Ace; v <= King; v++) {
			// create card
			Card *card = createCard(v, s, NULL);
			// add card to Card array & increment card number
			deck->cards[deck->ncards++] = *card;
		}
	}

	return deck;
}

/**
 * Returns string representation of a Card. For example,
 * the card  Jack of Diamonds returns "Jack of Diamonds".
 *
 * @param card pointer to a card
 * @param str pointer to result string
 * @param result string for card;
 * @return pointer to the string
 */
char *cardToString(Card *card, char *str) {
	const char *val = *(card->value + valueName);
	const char *suit = *(card->suit + suitName);
	sprintf(str, "%s %s %s", val, "of", suit);
	return str;
}

/**
 * Prints the deck of cards to standard output, one card per
 * line. Use cardToString() to produce string representations
 * of the cards.
 *
 * @param deck pointer to the deck to print
 */
void printDeck(Deck *deck) {
	char cardStr[128];
	for (int card = 0; card < deck->ncards; card++) {
		char *str = cardToString(&deck->cards[card], cardStr);
		printf("%s\n", str);
	}
}

/**
 * Tests the card and deck functions
 */
int main(void) {
	printf("Start Problem 3\n");

	// create local card
	Card c;
	char cardstr[128];
	Card *localCard = createCard(Jack, Diamonds, &c);
	printf("\nLocal card: %s  expected: %s\n",
		   cardToString(localCard, cardstr), "Jack of Diamonds");

	// create allocated card
	Card *allocatedCard = createCard(Three, Clubs, NULL);
	if (allocatedCard == NULL) {
		printf("\nAllocated card is NULL\n");
	} else {
		printf("\nAllocated card: %s  expected: %s\n",
				cardToString(allocatedCard, cardstr), "3 of Clubs");
		// free allocated card
		free(allocatedCard);
	}

	// create local deck
	Deck d;
	Deck *localDeck = createDeck(&d);

	// print local deck
	printf("\nLocal deck:\n");
	printDeck(localDeck);

	// create allocated deck
	Deck *allocatedDeck = createDeck(NULL);
	if (allocatedDeck == NULL) {
		printf("Allocated deck is NULL\n");
	} else {
		// print allocated deck
		printf("\nAllocated deck:\n");
		printDeck(allocatedDeck);

		// free allocated deck
		free(allocatedDeck);
	}

	printf("\nEnd Problem 3\n");
	return EXIT_SUCCESS;
}
