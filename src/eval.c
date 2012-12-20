//Written bu Joseph
#include "main.h"

token_t *nest_value(token_t *ret, token_t *token);
token_t *prev_ret = NULL;

/* return the token has a certain value(answer).*/
token_t *Eval (token_t *token) {
	token_t *check = token;
	token_t *ret = token;

/*the case of one term*/
	if(ret->cdr->tt == END) {
		if ((prev_ret = get_value(token)) == NULL) { return NULL; }
		return prev_ret;
	} else {
		while (ret->cdr != NULL) { ret = ret->cdr; }
	}

/*the case of multi term*/
	while (check->tt == OPEN) { check = check->car; }
	if (check->tt == INT || check->tt == CHAR || check->tt == OPERATOR) {
		i_calculate_priority(ret, token);
		ret = i_calculate(ret, token);
		ret->tt = INT;
	} else if (check->tt == DOUBLE || check->tt == CHAR || check->tt == OPERATOR) {
		f_calculate_priority(ret, token);
		ret = f_calculate(ret, token);
		ret->tt = DOUBLE;
	}
	prev_ret = ret;
	return ret;
}

/*To handle nest*/
token_t *get_value (token_t *token) {
	token_t *check = token;
	token_t *ret = NULL;
	switch (token->tt) {
		case OPEN:
			ret = token->car;
			token = token->car;
			while (ret->tt != END) { ret = ret->cdr; }
			while (check->tt == OPEN) { check = check->car; }
			if (check->tt == INT) {
				i_calculate_priority(ret, token);
				ret = i_calculate(ret, token);
				ret->tt = INT;
			} else if (check->tt == DOUBLE) {
				f_calculate_priority(ret, token);
				ret = f_calculate(ret, token);
				ret->tt = DOUBLE;
			} else if (check->tt == OPERATOR) {
				ret = nest_value(ret, token);
			}
			return ret;
		case INT:
		case DOUBLE:
			return token;
		case CHAR:
			if (strncmp(token->str, "Ans", 3) == 0) {
				if (prev_ret == NULL) {
					printf("This is your first calc. Previous answer is not exist.\n");
					break;
				}
				return prev_ret;
			} else {
				printf("eval:CHAR:error\n");
			}
			break;
		case OPERATOR:
			printf("eval:OPERATOR:error\n");
			break;
		default:
			break;
	}
	return NULL;
}

/*Handle (-1) or (+1). Some expression like (*2) is NG.*/
token_t *nest_value(token_t *ret, token_t *token) {
	token_t *operator = token;
	token_t *number = token->cdr;
	if (operator->counter == 0) {
		if (number->tt == INT) {
			ret->tt = INT;
			ret->integer = number->integer;
		} else if (token->cdr->tt == DOUBLE) {
			ret->tt = DOUBLE;
			ret->decimal = number->decimal;
		}
	} else if (operator->counter == 1) {
		if (number->tt == INT) {
			ret->tt = INT;
			ret->integer = number->integer * (-1);
		} else if (token->cdr->tt == DOUBLE) {
			ret->tt = DOUBLE;
			ret->decimal = number->decimal * (-1.0);
		}
	} else {
		printf("Invalid number.\n");
	}
	return ret;
}
