//Written by Joseph
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum token_type {
	OPEN, CLOSE, INT, DOUBLE, CHAR, OPERATOR
} token_type;

/*TO Debug. How to use type_name[token_type]*/
extern char *type_name[];

typedef struct token_t {
	token_type tt;
	union{
		char *str;
		int integer;
		double decimal;
		struct token_t *car;
	};
	/*str_size means the size of char *str(including ingeger and decimal as string).
	And, When this token is OPEN or CLOSE, counter means checking the number between OPEN bracket and CLOSE bracket*/
	union {
	int str_size;
	int counter;
	};
	struct token_t *cdr;
} token_t;

/*tokenize.c*/
token_t *Tokenize(const char *str, int index);
token_t *token_init();
void list_free(token_t *root);

/*parse.c*/
token_t *Parse(token_t *root);
void tree_free(token_t *root);

/*eval.c*/
token_t *eval(token_t *token);

/*print.c*/
void tree_print(token_t *root);
void list_print(token_t *root);

/*check.c*/
int syntax_check(token_t *root, int count);
int position_check(token_t *root);