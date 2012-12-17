//Written bu Joseph
#include "main.h"

token_t *prev_ret = NULL;

/* return the token has a certain value(answer).*/
token_t *eval (token_t *token) {
	token_t *check = token;
	token_t *ret = token;

/*the case of one term*/
	if(ret->cdr->tt == END) {
		return get_value(token);
	} else {
		while (ret->cdr != NULL) { ret = ret->cdr; }
	}

/*the case of multi term*/
	while (check->tt == OPEN) { check = check->car; }
	if (check->tt == INT || check->tt == CHAR) {
		i_calculate_priority(ret, token);
		ret = i_calculate(ret, token);
		ret->tt = INT;
	} else if (check->tt == DOUBLE || check->tt == CHAR) {
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
			while (ret->tt != CLOSE) { ret = ret->cdr; }
			while (check->tt == OPEN) { check = check->car; }
			if (check->tt == INT) {
				i_calculate_priority(ret, token);
				ret = i_calculate(ret, token);
				ret->tt = INT;
			} else if (check->tt == DOUBLE) {
				f_calculate_priority(ret, token);
				ret = f_calculate(ret, token);
				ret->tt = DOUBLE;
			}
			return ret;
		case INT:
		case DOUBLE:
			return token;
		case CHAR:
			if (strncmp(token->str, "Ans", 3) == 0) {
				if (prev_ret == NULL) {
					printf("prev_ret is NULL. This is your first time to calculate.\n");
					return NULL;
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
