//Written bu Joseph
#include "main.h"

/* return the token has a certain value(answer).*/
token_t *eval (token_t *token) {
	token_t *ret = token;
	while (ret->cdr != NULL) {
		ret = ret->cdr;
	}
	i_calculate_priority(ret, token);
	ret = i_calculate(ret, token);
	return ret;
}

token_t *get_value (token_t *token) {
	token_t *ret = NULL;
	switch (token->tt) {
		case OPEN:
			ret = token->car;
			while (ret->tt != CLOSE) {
				ret = ret->cdr;
			}
			token = token->car;
			i_calculate_priority(ret, token);
			ret = i_calculate(ret, token);
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
