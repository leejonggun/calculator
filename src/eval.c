//Written bu Joseph
#include "main.h"

static int int_calc(token_t *result, token_t *token);
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
	} while (token->car->tt != OPERATOR);
	return token;
}

static token_t *calculate_priority(token_t *ret, token_t *token) {
	token_t *root = token;
	while (token->cdr->tt != CLOSE) {
		if ((token->cdr->car->tt == OPERATOR) && (token->cdr->car->counter > 1)) {
			ret->integer = int_calc(ret, token);
			tree_free(token->car);
			token->car = ret;
			token->cdr = after_calc(token->cdr);
		} else {
			token = token->cdr->cdr;
		}
	}
	return root;
}

static token_t *calculate(token_t *ret, token_t *token) {
	token_t *root = token;
	while (token->cdr->tt != CLOSE) {
		ret->integer = int_calc(ret, token);
		token = token->cdr->cdr;
	}
	return root;
}
token_t *eval (token_t *token) {
	token_t *ret = NULL;
	switch (token->tt) {
		case OPEN:
			/*priority can be OPERATOR-token->counter.
			 add->counter = 0, sub->counter = 1 < mul->counter = 2, div->counter = 3
			 */
			//calculate multiplication and division first.
			ret = token_init();
			ret = calculate_priority(ret, token);
			//calculate addition and subtraction.
			ret = calculate(ret, token);
			printf("ret->tt = %s, ret->integer = %d\n", type_name[ret->tt], ret->integer);
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
static int int_calc(token_t *ret, token_t *token) {
	/*ALL INT*/
	token_t *tmp = token;
	token_t *operator = tmp->cdr->car;//operator
	int value, result;
	result = eval(tmp->car)->integer;//left number
	value = (eval(tmp->cdr->cdr->car))->integer;//right number
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
