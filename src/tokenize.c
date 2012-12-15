//Written by Joseph
#include "main.h"

static void set_char(token_t *token, const char *buf, int count, token_type TYPE);
static void set_str(token_t *token, const char *buf, int buf_len, token_type TYPE);
token_t *token_init(token_type tt);

//static int pass_space(const char *input, int index) {
//	while (input[index + 1] == ' ' || input[index + 1] == '\n' || input[index + 1] == '\t') {
//		index++;
//	}
//	return index;
//}

token_t *Tokenize(const char *str) {
	int size, index = 0;
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
				set_char(list, &str[index], count, OPEN);
				list->cdr = token_init(END);
				list = list->cdr;
				index++;
				break;
			case ')':
//				index = pass_space(str, index);
				if (index == str_len) {
					set_char(list, &str[index], count, CLOSE);
					list->cdr = NULL;
					count--;
				} else {
					set_char(list, &str[index], count, CLOSE);
					list->cdr = token_init(END);
					list = list->cdr;
					count--;
					index++;
				}
				break;
			case '+':
				set_char(list, &str[index], 0, OPERATOR);
				list->cdr = token_init(END);
				list = list->cdr;
				index++;
				break;
			case '-':
				set_char(list, &str[index], 1, OPERATOR);
				list->cdr = token_init(END);
				list = list->cdr;
				index++;
				break;
			case '*':
				set_char(list, &str[index], 2, OPERATOR);
				list->cdr = token_init(END);
				list = list->cdr;
				index++;
				break;
			case '/':
				set_char(list, &str[index], 3, OPERATOR);
				list->cdr = token_init(END);
				list = list->cdr;
				index++;
				break;
			case '^':
				set_char(list, &str[index], 4, OPERATOR);
				list->cdr = token_init(END);
				list = list->cdr;
				index++;
				break;
			case '!':
				set_char(list, &str[index], 5, OPERATOR);
				list->cdr = token_init(END);
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
					set_str(list, &str[index], size, DOUBLE);
				} else {
					set_str(list, &str[index], size, INT);
				}
				index += size;
				if (index == str_len) {
					list->cdr = NULL;
				} else {
					list->cdr = token_init(END);
					list = list->cdr;
				}
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
token_t *token_init(token_type tt) {
	token_t *new = (token_t *)malloc(sizeof(token_t));
	new->tt = tt;
	new->str_size = 0;
	new->cdr = NULL;
	new->str = NULL;
	return new;
}

/*set one size charater*/
static void set_char(token_t *token, const char *buf, int count, token_type TYPE) {
	token->tt = TYPE;
	token->counter = count;
	token->str = (char *)malloc(sizeof(char) * 2);
	token->str = strncpy(token->str, buf, 1);
	token->str[1] = '\0';
}
/*set multi size token to cons list*/
static void set_str(token_t *token, const char *buf, int buf_len, token_type TYPE) {
	token->tt = TYPE;
	token->str_size = buf_len;
	token->str = (char *)malloc(sizeof(char) * (buf_len));
	token->str = strncpy(token->str, buf, buf_len);
	token->str[buf_len] = '\0';
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
		case END:
			free(del);
	}
}
