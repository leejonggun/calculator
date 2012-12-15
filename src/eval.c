//Written bu Joseph
#include "main.h"

/* return the token has a certain value(answer).*/
//token_t *eval (token_t *token) {
//	token_t *ret = NULL;
//	switch (token->tt) {
//		case OPEN:
//			ret = token_init();
//			if (token->car != NULL && (token->car->tt == INT||token->car->tt == OPEN)) {
//				i_calculate_priority(token);
//				ret = i_calculate(token);
//			} else if (token->car != NULL && (token->car->tt == DOUBLE||token->car->tt == OPEN)) {
//				f_calculate_priority(token);
//				ret = f_calculate(token);
//			} else {
//				printf("error:After OPEN-token, NUMBER-token has to come.\n");
//				return NULL;
//			}
//			return ret;
//		case INT:
//			return token;
//		case DOUBLE:
//			return token;
//		case CHAR:
//			printf("eval:CHAR:error");
//			break;
//		case OPERATOR:
//			printf("eval:OPERATOR:error");
//			break;
//		default:
//			break;
//	}
//	return NULL;
//}

//remove token->cdr, token->cdr->cdr because they have been calculated.
//static token_t *remake_tree(token_t *token) {
//	do {
//		tree_free(token);
//		token = token->cdr;
//		if (token->cdr == NULL) {
//			return token;
//		}
//	} while (token->cdr == NULL || token->tt != OPERATOR);
//	return token;
//}
//
//static int int_calc(token_t *token) {
//	/*ALL INT*/
//	int value = 0, result;
//	token_t *operator = token->cdr;//operator
//	result = (eval(token))->integer;//left number
//	if (operator->counter < 5) {
//		value = (eval(token->cdr->cdr))->integer;//right number
//	}
//	return (*i_func[operator->counter])(result, value);
//}
//
//static void calculate_priority(token_t *token) {
//	int ret = 0;
//	while (token->cdr != NULL) {
//		if ((token->cdr->tt == OPERATOR) && (token->cdr->counter > 1)) {
//			ret = int_calc(token);
///*remake tree*/
//			token->tt = INT;
//			token->integer = ret;
//			token->cdr = remake_tree(token->cdr);
///*remake tree*/
//	} else {
//		token = token->cdr->cdr;
//	}
//}

token_t *eval (token_t *token) {
	token_t *ret = NULL;
	token_t *end = token;
	while (end->tt != END) {
		end = end->cdr;
	}
	ret = end;
//	switch (token->tt) {
//		case OPEN:
			if (token->car->tt == INT||token->car->tt == OPEN) {
				i_calculate_priority(token);
				ret = i_calculate(token);
			} else if (token->car->tt == DOUBLE||token->car->tt == OPEN) {
				f_calculate_priority(token);
				ret = f_calculate(token);
			} else {
				printf("error:After OPEN-token, NUMBER-token has to come.\n");
				return NULL;
			}
			return ret;
//	}
}
