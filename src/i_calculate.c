//Written bu Joseph
#include "main.h"

static int i_add (int left_value, int right_value);
static int i_sub (int left_value, int right_value);
static int i_mul (int left_value, int right_value);
static int i_div (int left_value, int right_value);
static int i_pow (int left_value, int right_value);
static int i_fac (int left_value, int right_value);

static int (*i_func[])(int, int) = { i_add, i_sub, i_mul, i_div, i_pow, i_fac };

//remove token->cdr, token->cdr->cdr because they have been calculated.
static token_t *remake_tree(token_t *token) {
	do {
		free(token);
		token = token->cdr;
		if (token->cdr == NULL) {
			return token;
		}
	} while (token->tt != OPERATOR);
	return token;
}

/*This function is to calculate left_token and right_token*/
static int int_calc(token_t *ret, token_t *token) {
	/*ALL INT*/
	token_t *value, *tmp;
	token_t *operator = token->cdr;//operator
	/*left number*/
	if ((tmp = get_value(token)) == NULL) { return 0; }
	ret->integer = tmp->integer;//left number
	if (operator->counter == 5) {//factory (3!) doesn't have right number
		return (*i_func[operator->counter])(ret->integer, 0);
	}
	/*right number*/
	if ((value = get_value(token->cdr->cdr)) == NULL) { return 0; }
	return (*i_func[operator->counter])(ret->integer, value->integer);
}

/*calculate multiplication and division first.
 And remake AST. After this function, The operator in AST will be only + and -*/
void i_calculate_priority(token_t *ret, token_t *token) {
	while (token->cdr->cdr != NULL) {
		if ((token->cdr->tt == OPERATOR) && (token->cdr->counter > 1)) {
			ret->integer = int_calc(ret, token);
			if (token->tt == OPEN) {
				tree_free(token->car);
			}
			token->tt = INT;
			token->integer = ret->integer;
/*remake tree*/
			token->cdr = remake_tree(token->cdr);
/*remake tree*/
		} else {
			token = token->cdr->cdr;
		}
	}
}

/*calculate addition and subtraction.*/
token_t *i_calculate(token_t *ret, token_t *token) {
	ret->integer = token->integer;
	while (token->cdr->cdr != NULL) {
		if ((token->cdr->tt == OPERATOR)) {
			ret->integer = int_calc(ret, token);
			if (token->tt == OPEN) {
				tree_free(token->car);
			}
			token->tt = INT;
			token->integer = ret->integer;
/*remake tree*/
			token->cdr = remake_tree(token->cdr);
/*remake tree*/
		} else {
			token = token->cdr->cdr;
		}
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
static int i_fac (int left_value, int right_value) {
	int i, ret = 1;
	for (i = 1; i < left_value+1; i++) {
		ret *= i;
	}
	return ret;
}
