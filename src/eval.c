//Written bu Joseph
#include "main.h"

static token_t *int_calc(token_t *result, token_t *token);
static token_t *double_calc(token_t *result, token_t *token);
static int i_add (int left_value, int right_value);
static int i_sub (int left_value, int right_value);
static int i_mul (int left_value, int right_value);
static int i_div (int left_value, int right_value);
static double f_add (double left_value, double right_value);
static double f_sub (double left_value, double right_value);
static double f_mul (double left_value, double right_value);
static double f_div (double left_value, double right_value);

int (*i_func[])(int, int) = { i_add, i_sub, i_mul, i_div };
double (*f_func[])(double, double) = { f_add, f_sub, f_mul, f_div };

token_t *eval (token_t *token) {
	token_t *ret = token_init();
	switch (token->tt) {
		case OPEN:
			switch (token->car->tt) {
				case OPEN:
				case INT:
				case DOUBLE:
					if (token->cdr->tt == CLOSE) {
						ret = eval(token->car);
						return ret;
					}
					/*The token before OPERATOR is NUMBER*/
					if (token->cdr->car->tt == OPERATOR) {
						if (token->car->tt == INT) {
							ret = int_calc(ret, token);
						} else {
							ret = double_calc(ret, token);
						}
					} else {
						ret = eval(token->car);
					}
					break;
				case CHAR:
				case OPERATOR:
					return NULL;
				case CLOSE:
					printf("error:CLOSE can't be set in OPEN-bracket->car\n");
					return NULL;
			}
			return ret;
		case INT:
			ret->tt = INT;
			ret->str_size = 0;
			ret->integer = token->integer;
			ret->cdr = NULL;
			return ret;
		case DOUBLE:
			ret->tt = DOUBLE;
			ret->str_size = 0;
			ret->decimal = token->decimal;
			ret->cdr = NULL;
			return ret;
		case CHAR:
			printf("eval:CHAR:error");
		case OPERATOR:
			printf("eval:OPERATOR:error");
		default:
			break;
	}
	return NULL;
}

static token_t *set_retvalue (token_t *result, int ivalue, double fvalue, token_type type) {
	result->tt = type;
	result->str_size = 0;
	result->cdr = NULL;
	if (result->tt == INT)
			result->integer = ivalue;
	else if (result->tt == DOUBLE)
			result->decimal = fvalue;
	return result;
}

/*token->car is left-num to be calculated, token->cdr->car is operator, and token->cdr->cdr->car is right-num to be calculated*/
static token_t *int_calc(token_t *ret, token_t *token) {
	/*ALL INT*/
	token_t *operator = NULL;
	int value, result;
	result = eval(token->car)->integer;//first number
	token = token->cdr;
	while (token->tt != CLOSE) {
		operator = token->car;//operator
		value = (eval(token->cdr->car))->integer;//next number
		result = (*i_func[operator->counter])(result, value);
		token = token->cdr->cdr;
	}
	set_retvalue(ret, result, 0.0, INT);
	return ret;
	}

/*token->car is left-num to be calculated, token->cdr->car is operator, and token->cdr->cdr->car is right-num to be calculated*/
static token_t *double_calc(token_t *ret, token_t *token) {
	/*ALL DOUBLE*/
	token_t *operator = NULL;
	double value, result;
	result = eval(token->car)->decimal;//first number
	token = token->cdr;
	while (token->tt != CLOSE) {
		operator = token->car;//operator
		value = (eval(token->cdr->car))->decimal;//next number
		result = (*f_func[operator->counter])(result, value);
		token = token->cdr->cdr;
	}
	set_retvalue(ret, 0, result, DOUBLE);
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
