//Written by Joseph
#include "main.h"

void list_print(token_t *root) {
	token_t *Debug = root;
	while (Debug != NULL) {
		if (Debug->tt == OPEN || Debug->tt == CLOSE) {
			printf("tt = %s, counter = %d, str = %s\n", type_name[Debug->tt], Debug->counter, Debug->str);
		} else if (Debug->tt == END) {
			printf("tt = %s, car = %p, cdr = %p\n", type_name[Debug->tt], Debug->car, Debug->cdr);
		} else {
			printf("tt = %s, str_size = %d, str = %s\n", type_name[Debug->tt], Debug->str_size, Debug->str);
		}
		Debug = Debug->cdr;
	}
	printf("\n");
}

void tree_print(token_t *root) {
	token_t *Debug = root;
	while (Debug != NULL) {
		switch(Debug->tt) {
			case OPEN:
				printf("cdr->type = %s, car = %p, cdr = %p\n",type_name[Debug->tt], Debug->car, Debug->cdr);
				tree_print(Debug->car);
				break;
			case CLOSE:
				printf("type = %s, car = %p, cdr = %p\n",type_name[Debug->tt], Debug->car, Debug->cdr);
				break;
			case INT:
				printf("type = %s, int = %d\n",type_name[Debug->tt], Debug->integer);
				break;
			case DOUBLE:
				printf("type = %s, double = %f\n",type_name[Debug->tt], Debug->decimal);
				break;
			case CHAR:
			case OPERATOR:
				printf("type = %s, str = %s, counter = %d\n",type_name[Debug->tt], Debug->str, Debug->counter);
				break;
			case END:
				printf("type = %s, car = %p, cdr = %p\n",type_name[Debug->tt], Debug->car, Debug->cdr);
		}
		Debug = Debug->cdr;
	}
}
