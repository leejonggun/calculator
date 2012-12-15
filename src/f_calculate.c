//Written bu Joseph
#include "main.h"

static double f_add (double left_value, double right_value);
static double f_sub (double left_value, double right_value);
static double f_mul (double left_value, double right_value);
static double f_div (double left_value, double right_value);
static double f_pow (double left_value, double right_value);
static double f_fac (double left_value, double right_value);

static double (*f_func[])(double, double) = { f_add, f_sub, f_mul, f_div, f_pow, f_fac };

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
static double double_calc(token_t *ret, token_t *token) {
	/*ALL DOUBLE*/
	double value;
	token_t *operator = token->cdr;//operator
	ret->decimal = (get_value(token))->decimal;//left number
	if (operator->counter == 5) {//factory (3!) doesn't have right number
		return (*f_func[operator->counter])(ret->decimal, 0);
	} else {
		value = (get_value(token->cdr->cdr))->decimal;//right number
		return (*f_func[operator->counter])(ret->decimal, value);
	}
}

/*calculate multiplication and division first.
 And remake AST. After this function, The operator in AST will be only + and -*/
void f_calculate_priority(token_t *ret, token_t *token) {
	while (token->cdr->cdr != NULL) {
		if ((token->cdr->tt == OPERATOR) && (token->cdr->counter > 1)) {
			ret->decimal = double_calc(ret, token);
			if (token->tt == OPEN) {
				tree_free(token->car);
			}
			token->tt = DOUBLE;
			token->decimal = ret->decimal;
/*remake tree*/
			token->cdr = remake_tree(token->cdr);
/*remake tree*/
		} else {
			token = token->cdr->cdr;
		}
	}
}

/*calculate addition and subtraction.*/
token_t *f_calculate(token_t *ret, token_t *token) {
	ret->decimal = token->decimal;
	while (token->cdr->cdr != NULL) {
		if ((token->cdr->tt == OPERATOR)) {
			ret->decimal = double_calc(ret, token);
			if (token->tt == OPEN) {
				tree_free(token->car);
			}
			token->tt = DOUBLE;
			token->decimal = ret->decimal;
/*remake tree*/
			token->cdr = remake_tree(token->cdr);
/*remake tree*/
		} else {
			token = token->cdr->cdr;
		}
	}
	return ret;
}

static double f_add (double left_value, double right_value) {
	return (left_value + right_value);
}
static double f_sub (double left_value, double right_value) {
	return (left_value - right_value);
}
static double f_mul (double left_value, double right_value) {
	return (left_value * right_value);
}
static double f_div (double left_value, double right_value) {
	return (left_value / right_value);
}
static double f_pow (double left_value, double right_value) {
	double i, ret = 1.0;
	for (i = 0; i < right_value; i++) {
		ret *= left_value;
	}
	return ret;
}
static double f_fac (double left_value, double right_value) {
	int i;
	double ret = 1.0;
	for (i = 1; i < left_value+1; i++) {
		ret *= (double)i;
	}
	return ret;
}
