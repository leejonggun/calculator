//Written bu Joseph
#include "main.h"

/* return the token has a certain value(answer).*/
token_t *eval (token_t *token) {
	token_t *ret = token;
	while (ret->cdr != NULL) {
		ret = ret->cdr;
	}
	switch (token->tt) {
		case OPEN:
			if (token->cdr != NULL && (token->cdr->tt == INT||token->cdr->tt == OPEN)) {
				i_calculate_priority(ret, token);
				ret = i_calculate(ret, token);
			} else if (token->car != NULL && (token->car->tt == DOUBLE||token->car->tt == OPEN)) {
				f_calculate_priority(token);
				ret = f_calculate(token);
			} else {
				printf("error:After OPEN-token, NUMBER-token has to come.\n");
				return NULL;
			}
			return ret;
		case INT:
			printf("eval:int\n");
			i_calculate_priority(ret, token);
			ret = i_calculate(ret, token);
			printf("ret->integer=%d\n", ret->integer);
			return ret;
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
