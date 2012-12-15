//Written bu Joseph
#include "main.h"

/* return the token has a certain value(answer).*/
token_t *eval (token_t *token) {
	token_t *check = token;
	token_t *ret = token;
	while (ret->cdr != NULL) { ret = ret->cdr; }
	while (check->tt == OPEN) { check = check->car; }
	if (check->tt == INT) {
		i_calculate_priority(ret, token);
		ret = i_calculate(ret, token);
	} else if (check->tt == DOUBLE) {
		f_calculate_priority(ret, token);
		ret = f_calculate(ret, token);
	}
	return ret;
}

/*To handle nest*/
token_t *get_value (token_t *token) {
	token_t *check = NULL;
	token_t *ret = NULL;
	switch (token->tt) {
		case OPEN:
			check = token->car;
			ret = token->car;
			token = token->car;
			while (ret->tt != CLOSE) { ret = ret->cdr; }
			while (check->tt == OPEN) { check = check->car; }
			if (check->tt == INT) {
				i_calculate_priority(ret, token);
				ret = i_calculate(ret, token);
			} else if (check->tt == DOUBLE) {
				f_calculate_priority(ret, token);
				ret = f_calculate(ret, token);
			}
			return ret;
		case INT:
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
