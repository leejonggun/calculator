//Written by Joseph
#include "main.h"

token_t *set_counter(token_t *open, const char *buf, int count, token_type TYPE);
token_t *set_token(token_t *root, const char *buf, int buf_len, token_type TYPE);
token_t *token_init();

int pass_space(const char *input, int index) {
	int counter = 0;
	while (input[index+counter] == ' ' || input[index+counter] == '\n' || input[index+counter] == '\t') {
		counter++;
	}
	return (index + counter);
}

token_t *Tokenize(const char *str, int index) {
	int size = 0;
	int count = 0;// When OPEN bracket, counter++. When CLOSE bracket, counter--.
	token_t *list = (token_t*)malloc(sizeof(token_t));
	token_t *root = list;
	int str_len = strlen(str);
	while (index < str_len) {
		switch (str[index]) {
			case ' ':
			case '\t':
			case '\n':
				index++;
				break;
			case '(':
				count++;
				list = set_counter(list, &str[index], count, OPEN);
				list->cdr = token_init();
				list = list->cdr;
				index++;
				break;
			case ')':
				index = pass_space(str, index);
				if (index == str_len) {
					list = set_counter(list, &str[index], count, CLOSE);
					list->cdr = NULL;
					count--;
				} else {
					list = set_counter(list, &str[index], count, CLOSE);
					list->cdr = token_init();
					list = list->cdr;
					count--;
					index++;
				}
				break;
			case '^':
				/*TODO*/
			case '!':
				/*TODO*/
			case '+':
				list = set_counter(list, &str[index], 0, OPERATOR);
				list->cdr = token_init();
				list = list->cdr;
				index++;
				break;
			case '-':
				list = set_counter(list, &str[index], 1, OPERATOR);
				list->cdr = token_init();
				list = list->cdr;
				index++;
				break;
			case '*':
				list = set_counter(list, &str[index], 2, OPERATOR);
				list->cdr = token_init();
				list = list->cdr;
				index++;
				break;
			case '/':
				list = set_counter(list, &str[index], 3, OPERATOR);
				list->cdr = token_init();
				list = list->cdr;
				index++;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				size = 1;
				while (isdigit(str[index+size]) > 0) {
					size++;
				}
				if (str[index+size] == '.') {
					size++;
					while (isdigit(str[index+size]) > 0) {
						size++;
					}
					list = set_token(list, &str[index], size, DOUBLE);
				} else {
					list = set_token(list, &str[index], size, INT);
				}
				index += size;
				list->cdr = token_init();
				list = list->cdr;
				break;
			default:
				printf("You can't input alphabet.\n");
				return NULL;
		}
	}
	if (syntax_check(root, count) == -1) {
		return NULL;
	}
	return root;
}

/*init a token to construct list & tree*/
token_t *token_init() {
	token_t *new = (token_t *)malloc(sizeof(token_t));
	new->tt = OPEN;
	new->str_size = 0;
	new->cdr = NULL;
	new->str = NULL;
	return new;
}

/*set one size charater*/
token_t *set_counter(token_t *open, const char *buf, int count, token_type TYPE) {
	open->tt = TYPE;
	open->counter = count;
	open->str = (char *)malloc(sizeof(char) * 2);
	open->str = strncpy(open->str, buf, 1);
	open->str[1] = '\0';
	return open;
}
/*set multi size token to cons list*/
token_t *set_token(token_t *open, const char *buf, int buf_len, token_type TYPE) {
	open->tt = TYPE;
	open->str_size = buf_len;
	open->str = (char *)malloc(sizeof(char) * (buf_len));
	open->str = strncpy(open->str, buf, buf_len);
	open->str[buf_len] = '\0';
	return open;
}

/*free all tokens in list*/
void list_free(token_t *root) {
	token_t *del = root;
	switch(del->tt) {
		case OPEN:
			while (del->cdr != NULL) {
				list_free(del->cdr);
				del = del->cdr;
			}
			break;
		case CLOSE:
		case INT:
		case DOUBLE:
		case CHAR:
		case OPERATOR:
			free(del->str);
			free(del);
			break;
	}
}
