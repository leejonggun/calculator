//Written by Joseph
#include "main.h"

static void set_char(token_t *token, const char *buf, int count, token_type TYPE);
static void set_str(token_t *token, const char *buf, int buf_len, token_type TYPE);
token_t *token_init(token_type tt);

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
				if (index == str_len) {
					set_char(list, &str[index], count, END);
					list->cdr = NULL;
					count--;
				} else {
					set_char(list, &str[index], count, END);
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
			case 'A'://To tokenize Ans
				size = 3;
				if (str[index+1] == 'n' && str[index+2] == 's') {
					set_str(list, &str[index], size, CHAR);
					list->cdr = token_init(END);
					list = list->cdr;
					index += size;
					break;
				} else {
					printf("\'Ans\', which means previous Answer, is available. Please check your spelling.");
					return NULL;
				}
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
				list->cdr = token_init(END);
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
	while (del->cdr != NULL) {
		switch(del->tt) {
			case OPEN:
				free(del->str);
				free(del);
				break;
			case INT:
			case DOUBLE:
			case CHAR:
			case OPERATOR:
				free(del->str);
				free(del);
				break;
			case END:
				free(del);
				break;
		}
	del = del->cdr;
	}
}
