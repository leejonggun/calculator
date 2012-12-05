//Written bu Joseph
#include "main.h"

static int i_add (int left_value, int right_value);
static int i_sub (int left_value, int right_value);
static int i_mul (int left_value, int right_value);
static int i_div (int left_value, int right_value);
static int i_pow (int left_value, int right_value);

static int (*i_func[])(int, int) = { i_add, i_sub, i_mul, i_div, i_pow };

//remove token->cdr, token->cdr->cdr because they have been calculated.
static token_t *remake_tree(token_t *token) {
	do {
		tree_free(token->car);
		free(token);
		token = token->cdr;
		if (token->tt == CLOSE) {
			return token;
		}
	} while (token->car->tt != OPERATOR);
	return token;
}

/*This function is to calculate left_token and right_token*/
int int_calc(token_t *token) {
	/*ALL INT*/
	token_t *operator = token->cdr->car;//operator
	int value, result;
	result = (eval(token->car))->integer;//left number
	value = (eval(token->cdr->cdr->car))->integer;//right number
	return (*i_func[operator->counter])(result, value);
	}

/*calculate multiplication and division first.
 And remake AST. After this function, The operator in AST will be only + and -*/
void i_calculate_priority(token_t *token) {
	token_t *ret = NULL;
	while (token->cdr->tt != CLOSE) {
		if ((token->cdr->car->tt == OPERATOR) && (token->cdr->car->counter > 1)) {
			ret = token_init(INT);
			ret->integer = int_calc(token);
/*remake tree*/
			tree_free(token->car);
			token->car = ret;
			token->cdr = remake_tree(token->cdr);
/*remake tree*/
		} else {
			token = token->cdr->cdr;
		}
	}
}

/*calculate addition and subtraction.*/
token_t *i_calculate(token_t *token) {
	token_t *ret = NULL;
	while (token->cdr->tt != CLOSE) {
		if ((token->cdr->car->tt == OPERATOR)) {
			ret = token_init(INT);
			ret->integer = int_calc(token);
/*remake tree*/
			tree_free(token->car);
			token->car = ret;
			token->cdr = remake_tree(token->cdr);
/*remake tree*/
		} else {
			token = token->cdr->cdr;
		}
	}
	if (token->cdr->tt == CLOSE) {
		return token->car;
	}
	return ret;
}

static int i_add (int left_value, int right_value) {
	return (left_value + right_value);
}
static int i_sub (int left_value, int right_value) {
	return (left_value - right_value);
}
static int i_mul (int left_value, int right_value) {
	return (left_value * right_value);
}
static int i_div (int left_value, int right_value) {
	return (left_value / right_value);
}
static int i_pow (int left_value, int right_value) {
	int i, ret = 1;
	for (i = 0; i < right_value; i++) {
		ret *= left_value;
	}
	return ret;
}
