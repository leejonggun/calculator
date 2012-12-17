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
				printf("type = %s, car = %p, cdr = %p\n",type_name[Debug->tt], Debug->car, Debug->cdr);
				printf("nest start\n");
				tree_print(Debug->car);
				printf("nest end\n");
				break;
			case CLOSE:
				printf("type = %s, car = %p, cdr = %p\n",type_name[Debug->tt], Debug->car, Debug->cdr);
				break;
			case INT:
				printf("type = %s, int = %d, cdr = %p\n",type_name[Debug->tt], Debug->integer, Debug->cdr);
				break;
			case DOUBLE:
				printf("type = %s, double = %f, cdr = %p\n",type_name[Debug->tt], Debug->decimal, Debug->cdr);
				break;
			case CHAR:
			case OPERATOR:
				printf("type = %s, str = %s, counter = %d, cdr = %p\n",type_name[Debug->tt], Debug->str, Debug->counter, Debug->cdr);
				break;
			case END:
				printf("type = %s, car = %p, cdr = %p\n",type_name[Debug->tt], Debug->car, Debug->cdr);
		}
		Debug = Debug->cdr;
	}
}
