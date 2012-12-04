//Written bu Joseph
#include "main.h"

/* return the token has a certain value(answer).*/
token_t *eval (token_t *token) {
	token_t *ret = NULL;
	switch (token->tt) {
		case OPEN:
			ret = token_init();
			//branch int or double
			if (token->car->tt == INT) {
				i_calculate_priority(token);
//				tree_print(token);
				ret = i_calculate(token);
//				tree_print(ret);
			} else if (token->car->tt == DOUBLE) {
				f_calculate_priority(token);
//				tree_print(token);
				ret = f_calculate(token);
//				tree_print(ret);
			} else {
				printf("error:After OPEN-token, NUMBER-token has to be.\n");
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
