//Written by Joseph
#include "main.h"

void list_print(token_t *root) {
	token_t *Debug = root;
	while (Debug->cdr != NULL) {
		if (Debug->tt == OPEN || Debug->tt == CLOSE) {
			printf("tt = %s, counter = %d, str = %s\n", type_name[Debug->tt], Debug->counter, Debug->str);
		} else {
			printf("tt = %s, str_size = %d, str = %s\n", type_name[Debug->tt], Debug->str_size, Debug->str);
		}
		Debug = Debug->cdr;
	}
	printf("\n");
}

void tree_print(token_t *root) {
	token_t *Debug = root;
	switch(Debug->tt) {
		case OPEN:
		printf("cdr->type = %s, car = %p, cdr = %p\n",type_name[Debug->tt], Debug->car, Debug->cdr);
			while (Debug->cdr != NULL) {
				tree_print(Debug->car);
				Debug = Debug->cdr;
			}
			/*case CLOSE:*/
			printf("type = %s, car = %p, cdr = %p\n",type_name[Debug->tt], Debug->car, Debug->cdr);
			break;
		case CLOSE:
			/*MUST NOT*/
			printf("type = %s, car = %p, cdr = %p\n",type_name[Debug->tt], Debug->car, Debug->cdr);
			break;
		case INT:
			printf("car->type = %s, int = %d\n",type_name[Debug->tt], Debug->integer);
			break;
		case DOUBLE:
			printf("car->type = %s, double = %f\n",type_name[Debug->tt], Debug->decimal);
			break;
		case CHAR:
		case OPERATOR:
			printf("car->type = %s, str = %s\n",type_name[Debug->tt], Debug->str);
			break;
	}
}
