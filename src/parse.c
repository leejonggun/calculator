//Written by Joseph
#include "main.h"

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

/*set elements each token from list properly*/
static token_t *make_tree(token_t *tree, token_t *list) {
	token_t *token_open;
	tree->tt = list->tt;
	tree->cdr = NULL;
	switch (tree->tt) {
		case OPEN:
			token_open = tree;
			tree->counter = list->counter;
			list = list->cdr;
			tree->car = Parse(list);
			return token_open;
		case CLOSE:
			tree->car = NULL;
			tree->counter = list->counter;
			break;
		case INT:
			tree->str_size = list->str_size;
			tree->integer = atoi(list->str);
			break;
		case DOUBLE:
			tree->str_size = list->str_size;
			tree->decimal = atof(list->str);
			break;
		case CHAR:
			/*for 'Ans' Syntax*/
			tree->str_size = list->str_size;
			tree->str = (char *)malloc(sizeof(char) * 2);
			tree->str = strncpy(tree->str, list->str, list->str_size);
			tree->str[list->str_size] = '\0';
			break;
		case OPERATOR:
			tree->counter = list->counter;
			tree->str = (char *)malloc(sizeof(char) * 2);
			tree->str = strncpy(tree->str, list->str, 1);
			tree->str[1] = '\0';
			break;
		case END:
			break;
	}
	return tree;
}

/*cons tree structure based on list*/
token_t *Parse(token_t *list_root) {
	int counter = 0;//to parse nests
	token_t *list = list_root;
	token_t *token_tree = token_init(END);
	token_t *token_root = token_tree;
	while (list->cdr != NULL) {//Parse called in main.c, Parse called in case of OPEN nest
		if (list->tt == OPEN) {
			counter = 1;
			/*count how many list-tokens should be skipped to cons a tree structure*/
			counter += check_nest(list);
		} else if (list->tt == CLOSE) {
			/*make CLOSE token & the end of nest*/
			token_tree = make_tree(token_tree, list);
			return token_root;
		}
		token_tree = make_tree(token_tree, list);
		token_tree->cdr = token_init(END);
		token_tree = token_tree->cdr;
		do {
			/*skip '( ~ )' nest*/
			list = list->cdr;
			counter--;
		} while (counter > 0);
	}
	if (position_check(token_root) == -1) {
		return NULL;
	}
	return token_root;
}

void tree_free(token_t *root) {
	token_t *del = root;
	while (del->cdr != NULL) {
		switch(del->tt) {
			case OPEN:
				tree_free(del->car);
				free(del);
				break;
			case CLOSE:
			case INT:
			case DOUBLE:
			case END:
				free(del);
				break;
			case CHAR:
			case OPERATOR:
				free(del->str);
				free(del);
				break;
		}
		del = del->cdr;
	}
}
