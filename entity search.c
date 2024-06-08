#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <string.h>
#include <malloc.h>

int counter = 0;

struct list_of_sons {
	struct trie* son;
	struct list_of_sons* next;
};


struct trie {
	char letter;
	int IsEndOfNum;
	struct list_of_sons* first_son;
};


void add(char word[], struct trie* root) {
	struct trie* potential_father = root;
	int i = 0;
	int len_word = strlen(word);
	while (i < len_word) {
		if (word[i] == potential_father->letter && ((i + 1) == len_word)) {
			i++;
			potential_father->IsEndOfNum = 1;
		}
		else if (word[i] == potential_father->letter && potential_father->first_son->son == NULL) {
			i++;
			struct trie* SON = (struct trie*)malloc(sizeof(struct trie));
			SON->letter = word[i];
			potential_father->first_son->son = SON;
			struct list_of_sons* FIRST_SON = (struct list_of_sons*)malloc(sizeof(struct list_of_sons));
			FIRST_SON->son = NULL;
			FIRST_SON->next = NULL;
			SON->first_son = FIRST_SON;
			if (i + 1 == len_word) {
				SON->IsEndOfNum = 1;
				potential_father = SON;
				break;
			}
			potential_father = SON;
		}
		else if (word[i] == potential_father->letter && potential_father->first_son->son != NULL) {
			i++;
			struct list_of_sons* LIST_OF_SONS = potential_father->first_son;
			struct trie* CURRENT_SON = LIST_OF_SONS->son;
			struct list_of_sons* PREVIOUS_SON = LIST_OF_SONS;
			while (CURRENT_SON != NULL) {
				if (word[i] == CURRENT_SON->letter) {
					potential_father = CURRENT_SON;
					break;
				}
				else {
					PREVIOUS_SON = LIST_OF_SONS;
					LIST_OF_SONS = LIST_OF_SONS->next;
					if (LIST_OF_SONS == NULL) break;
					CURRENT_SON = LIST_OF_SONS->son;
				}
			}
			if (LIST_OF_SONS == NULL) {
				struct trie* NEW_SON = (struct trie*)malloc(sizeof(struct trie));
				struct list_of_sons* temp = (struct list_of_sons*)malloc(sizeof(struct list_of_sons));
				temp->next = NULL;
				temp->son = NEW_SON;
				NEW_SON->letter = word[i];
				PREVIOUS_SON->next = temp;
				struct list_of_sons* FIRST_SON = (struct list_of_sons*)malloc(sizeof(struct list_of_sons));
				FIRST_SON->son = NULL;
				FIRST_SON->next = NULL;
				NEW_SON->first_son = FIRST_SON;
				if (i + 1 == len_word) {
					NEW_SON->IsEndOfNum = 1;
					potential_father = NEW_SON;
					break;
				}
				potential_father = NEW_SON;
			}
		}
	}
}



void print_numbers(struct trie* current_knot, char pattern[]) {
		struct list_of_sons* LIST_OF_SONS = current_knot->first_son;
		struct trie* CURRENT_SON = LIST_OF_SONS->son;
		struct list_of_sons* PREVIOUS_SON = LIST_OF_SONS;
		strncat(pattern, &CURRENT_SON->letter, 1);
		while (CURRENT_SON != NULL) {
			if (CURRENT_SON->first_son->son == NULL) {
				printf("%s\n", pattern);
				counter++;
				LIST_OF_SONS = LIST_OF_SONS->next;
				if (LIST_OF_SONS == NULL) {
					pattern[strlen(pattern) - 1] = '\0';
					break;
				}
				CURRENT_SON = LIST_OF_SONS->son;
				pattern[strlen(pattern) - 1] = '\0';

				strncat(pattern, &CURRENT_SON->letter, 1);
			}
			else {
				if (CURRENT_SON->IsEndOfNum == 1) { counter++; 	printf("%s\n", pattern); }
				print_numbers(CURRENT_SON, pattern);
				LIST_OF_SONS = LIST_OF_SONS->next;
				if (LIST_OF_SONS == NULL) {
					pattern[strlen(pattern) - 1] = '\0';
					break;
				}
				CURRENT_SON = LIST_OF_SONS->son;
				pattern[strlen(pattern) - 1] = '\0';
				strncat(pattern, &CURRENT_SON->letter, 1);
			}
		}
}



int main() {
	struct trie* root = (struct trie*)malloc(sizeof(struct trie));
	root->letter = '0';
	struct list_of_sons* FIRST_SON = (struct list_of_sons*)malloc(sizeof(struct list_of_sons));
	FIRST_SON->son = NULL;
	FIRST_SON->next = NULL;
	root->first_son = FIRST_SON;

	FILE* input = fopen("input.txt", "r");
	char potential_number[20];
	potential_number[0] = '\0';

	char c, nextChar, next_c;
	int insideQuotes = 0;
	int multyComment = 0;
	int perenos = 0;
	int mono_quotes = 0;
	int double_quotes = 0;
	int perenos_vipolnen = 0;
	int into_comment = 0;
	while ((c = fgetc(input)) != EOF) {

		if (!multyComment) {

			if (!insideQuotes) {

				if (c == '/') {
					nextChar = fgetc(input);
					if ((int)nextChar >= 0) {


						if (nextChar == '/') {
							into_comment = 1;
							while ((c = fgetc(input)) != EOF && c != '\n') {
								if (c == 1) {
									break;
								}
								else if (c == '\\' && (next_c = fgetc(input) == '\n')) {
									perenos = !perenos;
									ungetc(next_c, input);
								}
							}
							while (perenos) {
								perenos = 0;
								while ((c = fgetc(input)) != EOF && c != '\n') {
									if (c == '\\' && (next_c = fgetc(input) == '\n')) {
										perenos = !perenos;
										ungetc(next_c, input);
									}
								}
							}
							into_comment = 0;
						}
						else if (nextChar == '*') {
							multyComment = !multyComment;
						}
						else if (nextChar == '"') {
							insideQuotes = !insideQuotes;
							double_quotes = !double_quotes;

						}
						else if (nextChar == 39) {
							insideQuotes = !insideQuotes;
							mono_quotes = !mono_quotes;
						}
					}
				}
				else if (c == '"') {
					insideQuotes = !insideQuotes;
					double_quotes = !double_quotes;
				}
				else if (c == 39) {
					insideQuotes = !insideQuotes;
					mono_quotes = !mono_quotes;
				}
				else if (c == '0') {
					char next_C;
					next_C = fgetc(input);
					if (next_C == 'x') {
					letsgo:	potential_number[0] = '0';
						potential_number[1] = 'x';
						potential_number[2] = '\0';
						next_C = fgetc(input);
						while (next_C == '0' || next_C == '1' || next_C == '2' || next_C == '3' || next_C == '4' || next_C == '5' || \
							next_C == '6' || next_C == '7' || next_C == '8' || next_C == '9' || next_C == 'A' || next_C == 'B' || \
							next_C == 'C' || next_C == 'D' || next_C == 'E' || next_C == 'F') {
							strncat(potential_number, &next_C, 1);
							next_C = fgetc(input);
						}
						if (next_C == 'x' && potential_number[strlen(potential_number) - 1] == '0') {
							potential_number[strlen(potential_number) - 1] = '\0';
							if (strlen(potential_number) > 2) {
								add(potential_number, root);
							}
							potential_number[0] = '\0';
							goto letsgo;
						}
						else {
							add(potential_number, root);
							potential_number[0] = '\0';

						}
					}
					else {
						ungetc(next_C, input);
					}
				}
			}
			else {
				if (c == '"' && double_quotes == 1) {
					insideQuotes = !insideQuotes;
					double_quotes = !double_quotes;
					if (perenos == 1) {
						perenos = 0;
					}
				}
				else if (c == 39 && mono_quotes == 1) {
					insideQuotes = !insideQuotes;
					mono_quotes = !mono_quotes;
					if (perenos == 1) {
						perenos = 0;
					}
				}
				else if (c == '\\' && (nextChar = fgetc(input)) == '\n') {
					if (into_comment) {
						perenos = 1;
					}
					else if (mono_quotes) {
						mono_quotes = 0;
						insideQuotes = 0;
					}
				}
				else if (c == '\\' && nextChar != '\n') {

				}
				else if (c == '\\' && nextChar == 39) {
					ungetc(nextChar, input);
				}
				else if (c == '\n' && insideQuotes == 1 && perenos == 0) {
					insideQuotes = !insideQuotes;
					if (mono_quotes == 1) {
						mono_quotes = !mono_quotes;
					}
					else if (double_quotes == 1) {
						double_quotes = !double_quotes;
					}
					perenos_vipolnen = 1;
				}
				else {
					if (perenos_vipolnen == 1) {
						perenos_vipolnen = 0;
						perenos = 0;
					}
				}
			}
		}
		else {
			if (c == '*') {
				if ((nextChar = fgetc(input)) == '/') {
					multyComment = !multyComment;
				}
				else {
					ungetc(nextChar, input);
				}
			}
		}
	}

	char pattern[16] = { '0' };
	print_numbers(root, pattern);
	printf("\n");
	printf("Count of numbers: %d\n", counter);
	return 0;
}
