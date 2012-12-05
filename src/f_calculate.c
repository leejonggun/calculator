//Written bu Joseph
#include "main.h"

static double f_add (double left_value, double right_value);
static double f_sub (double left_value, double right_value);
static double f_mul (double left_value, double right_value);
static double f_div (double left_value, double right_value);
static double f_pow (double left_value, double right_value);

static double (*f_func[])(double, double) = { f_add, f_sub, f_mul, f_div, f_pow };

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
static double double_calc(token_t *token) {
	/*ALL DOUBLE*/
	token_t *operator = token->cdr->car;//operator
	double value, result;
	result = (eval(token->car))->decimal;//left number
	value = (eval(token->cdr->cdr->car))->decimal;//right number
	return (*f_func[operator->counter])(result, value);
}

/*calculate multiplication and division first.
 And remake AST. After this function, The operator in AST will be only + and -*/
void f_calculate_priority(token_t *token) {
	token_t *ret = NULL;
	while (token->cdr->tt != CLOSE) {
		if ((token->cdr->car->tt == OPERATOR) && (token->cdr->car->counter > 1)) {
			ret = token_init(DOUBLE);
			ret->decimal = double_calc(token);
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
token_t *f_calculate(token_t *token) {
	token_t *ret = NULL;
	while (token->cdr->tt != CLOSE) {
		if ((token->cdr->car->tt == OPERATOR)) {
			ret = token_init(DOUBLE);
			ret->decimal = double_calc(token);
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
	int i, ret = 1;
	for (i = 0; i < right_value; i++) {
		ret *= left_value;
	}
	return ret;
}
