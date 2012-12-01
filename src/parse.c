//Written by Joseph
#include "main.h"

static void make_tree(token_t *tree, token_t *list) {
	tree->tt = list->tt;
	tree->str_size = list->str_size;
	tree->cdr = NULL;
	switch (tree->tt) {
		case OPEN:
		case CLOSE:
			tree->car = NULL;
			break;
		case INT:
			tree->integer = atoi(list->str);
			break;
		case DOUBLE:
			tree->decimal = atof(list->str);
			break;
		case CHAR:
			/*TODO For Syntax*/
			break;
		case OPERATOR:
			tree->str = (char *)malloc(sizeof(char) * 2);
			tree->str = strncpy(tree->str, list->str, 1);
			tree->str[2] = '\0';
			break;
	}
}

/*It means a correct nest that an OPEN-list->counter equals an CLOSE-list->counter.*/
static int check_nest(token_t *list) {
	token_t *start = list;
	int counter = 0;
	while (!(list->tt == CLOSE && start->counter == list->counter)) {
		counter++;
		list = list->cdr;
	}
	return counter;
}

token_t *Parse(token_t *root) {
	int counter = 0;
	token_t *list = root;
	token_t *token_tree = token_init();
	token_t *token_root;
	switch (list->tt) {
	case OPEN:
		token_root = token_tree;
		make_tree(token_tree, list);
		/*Firstly, set an open bracket, then start tree structure*/
		list = list->cdr;
		while (list->tt != CLOSE) {
			counter = 1;
			if (list->tt == OPEN) {
				/*count how many list-tokens should be skipped to cons a tree structure*/
				counter += check_nest(list);
			}
			token_tree->car = Parse(list);
			token_tree->cdr = token_init();
			token_tree = token_tree->cdr;
				do {
				/*skip '( ~ )' nest*/
				list = list->cdr;
				counter--;
			} while (counter > 0);
		}
		/*CLOSE*/
		make_tree(token_tree, list);
		if (position_check(token_root) == -1) {
			return NULL;
		}
		return token_root;
	case CLOSE:
		/*MUST NOT*/
		printf("error\n");
		free(token_tree);
		break;
	case INT:
		make_tree(token_tree, list);
		return token_tree;
	case DOUBLE:
		make_tree(token_tree, list);
		return token_tree;
	case CHAR:
	case OPERATOR:
		make_tree(token_tree, list);
		return token_tree;
	}
	return NULL;
}

void tree_free(token_t *root) {
	token_t *del = root;
	switch(del->tt) {
		case OPEN:
			while (del->cdr != NULL) {
				tree_free(del->car);
				free(del);
				del = del->cdr;
			}
			break;
		case CLOSE:
		case INT:
		case DOUBLE:
			free(del);
			break;
		case CHAR:
		case OPERATOR:
			free(del->str);
			free(del);
			break;
	}
}
