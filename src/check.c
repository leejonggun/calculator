//Written by Joseph
#include "main.h"

int position_check(token_t *root) {
	if (root->tt == CLOSE) {
		printf("No token between \'(\'~\')\'\n");
		return -1;
	} else if (root->car->tt == OPERATOR) {
		printf("operator can\'t be just after the first \'(\'\n");
	}
	while (root->cdr->tt != CLOSE) {
		if (root->car->tt == root->cdr->car->tt ||
				(root->car->tt == INT && root->cdr->car->tt == DOUBLE) ||
				(root->car->tt == DOUBLE && root->cdr->car->tt == INT)
				) {
			if (root->car->tt == OPERATOR)
				printf("No number between operators\n");
			else if (root->car->tt == INT || root->car->tt == DOUBLE)
				printf("No operator between numbers\n");
			return -1;
		}
		root = root->cdr;
	}
	/*The token type before CLOSE bracket must be INT or DOUBLE*/
	if (root->car->tt != INT && root->car->tt != DOUBLE) {
		printf("operator can\'t be just before the last \')\'\n");
		return -1;
	}
	return 0;
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
