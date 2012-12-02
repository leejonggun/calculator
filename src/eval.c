//Written bu Joseph
#include "main.h"

static int int_calc(token_t *token);
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

/*	token->cdr->cdr->cdr->car->tt should be next OPERATOR. This is garanteed by syntax_check()
	But, token->cdr->car->tt is OPERATOR to have been calculated by above int_calc()*/
//move token->cdr->cdr because token->cdr, token->cdr->cdr has been calculated.
static token_t *after_calc(token_t *token) {
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

static void cpy_token(token_t *dest, token_t *src) {
	dest->tt = src->tt;
	dest->cdr = NULL;
	switch (dest->tt) {
		case OPEN:
		case CLOSE:
			dest->car = src->car;
			break;
		case INT:
			dest->integer = src->integer;
			break;
		case DOUBLE:
			dest->decimal = src->decimal;
			break;
		case CHAR:
			/*TODO For Syntax*/
			break;
		case OPERATOR:
			dest->str = (char *)malloc(sizeof(char) * 2);
			dest->str = strncpy(dest->str, src->str, 1);
			dest->str[2] = '\0';
			break;
	}
}
/*calculate multiplication and division first.*/
static void calculate_priority( token_t *token) {
	token_t *ret = NULL;
	while (token->cdr->tt != CLOSE) {
		ret = token_init();
		if ((token->cdr->car->tt == OPERATOR) && (token->cdr->car->counter > 1)) {
			cpy_token(ret, token->car);
			ret->integer = int_calc(token);
/*remake tree*/
			tree_free(token->car);
			token->car = ret;
			token->cdr = after_calc(token->cdr);
/*remake tree*/
		} else {
			token = token->cdr->cdr;
		}
	}
	free(ret);
}

/*calculate addition and subtraction.*/
static token_t *calculate(token_t *token) {
	int value;
	while (token->cdr->tt != CLOSE) {
		value = int_calc(token);
		token = token->cdr->cdr;
		token->car->integer = value;
	}
	return token;
}
token_t *eval (token_t *token) {
	token_t *ret = NULL;
	switch (token->tt) {
		case OPEN:
			/*priority can be OPERATOR-token->counter.
			 add->counter = 0, sub->counter = 1 < mul->counter = 2, div->counter = 3
			 */
			calculate_priority(token);
			tree_print(token);
/***************************/

			ret = calculate(token);
			return ret;
		case INT:
			return token;
		case DOUBLE:
			return token;
		case CHAR:
			printf("eval:CHAR:error");
			break;
		case OPERATOR:
			printf("eval:OPERATOR:error");
			break;
		default:
			break;
	}
	return NULL;
}

static token_t *set_retvalue (token_t *result, int ivalue, double fvalue, token_type type) {
	result->tt = type;
	if (result->tt == INT)
			result->integer = ivalue;
	else if (result->tt == DOUBLE)
			result->decimal = fvalue;
	return result;
}

/*token->car is left-num to be calculated, token->cdr->car is operator, and token->cdr->cdr->car is right-num to be calculated*/
/*This function is to calculate left_token and right_token*/
static int int_calc(token_t *token) {
	/*ALL INT*/
	token_t *operator = token->cdr->car;//operator
	int value, result;
	result = (eval(token->car))->integer;//left number
	value = (eval(token->cdr->cdr->car))->integer;//right number
	return (*i_func[operator->counter])(result, value);
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
