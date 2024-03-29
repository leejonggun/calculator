//Written by Joseph
#include "main.h"

int position_check(token_t *tree) {
	int ret = 0;
	while (tree->cdr->tt != END) {
		if (tree->tt == OPEN) {
			if (tree->cdr->tt == INT || tree->cdr->tt == DOUBLE) {
				printf("No operator between numbers\n");
				return -1;
			}
			if (tree->car->tt == END) {
				printf("You need one term at least\n");
				return -1;
			}
			ret = position_check(tree->car);
		} else if (tree->tt == tree->cdr->tt ||
				(tree->tt == INT && tree->cdr->tt == OPEN) ||
				(tree->tt == DOUBLE && tree->cdr->tt == OPEN)
				) {
			if (tree->tt == OPERATOR)
				printf("No number between operators\n");
			else if (tree->tt == INT || tree->tt == DOUBLE)
				printf("No operator between numbers\n");
			return -1;
		}
		tree = tree->cdr;
	}
	/*The token type before CLOSE bracket must be INT or DOUBLE*/
	if (tree->tt == OPERATOR && tree->counter != 5) {
		printf("operator can\'t be just before the last \')\'\n");
		return -1;
	}
	return ret;
}

static void change_int_to_double(token_t *root) {
	char *tmp;
	int size;
	while (root->cdr != NULL) {
		if (root->tt == INT) {
			root->tt = DOUBLE;
			size = root->str_size;
			tmp = (char *)malloc(sizeof(char) * (size+2));
			tmp = strncpy(tmp, root->str, size);
			tmp[size] = '.'; tmp[size+1] = '0'; tmp[size+2] = '\0';
			free(root->str);
			root->str = tmp;
		}
		root = root->cdr;
	}
}

static void check_double(token_t *root) {
	token_t *tmp = root;
	while (root->cdr != NULL) {
		if (root->tt == DOUBLE) {
			change_int_to_double(tmp);
		}
		root = root->cdr;
	}
}

static int check_overflow(token_t *root) {
	while (root->cdr != NULL) {
		if (root->tt == INT && root->str_size >= 10) {
			printf("Too big number.\n");
			printf("The number digits should be smaller than 10.\n");
			return -1;
		}
		root = root->cdr;
	}
	return 0;
}

int syntax_check(token_t *root, int count) {
	/*the number of OPEN brackets and CLOSE brackets check*/
	if (count != 0) {
		printf("error:The number of \'(\' and \')\' have to be equal\n");
		return -1;
	}
	token_t *tmp = root;
	if (check_overflow(tmp) == -1) {
		return -1;
	}
	check_double(tmp);
	return 0;
}
