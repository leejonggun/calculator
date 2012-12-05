//Written bu Joseph
#include "main.h"

/* return the token has a certain value(answer).*/
token_t *eval (token_t *token) {
	token_t *ret = NULL;
	switch (token->tt) {
		case OPEN:
			ret = token_init();
			if (token->car != NULL && (token->car->tt == INT||token->car->tt == OPEN)) {
				i_calculate_priority(token);
				ret = i_calculate(token);
			} else if (token->car != NULL && (token->car->tt == DOUBLE||token->car->tt == OPEN)) {
				f_calculate_priority(token);
				ret = f_calculate(token);
			} else {
				printf("error:After OPEN-token, NUMBER-token has to come.\n");
				return NULL;
			}
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
