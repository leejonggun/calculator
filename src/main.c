//Written by Joseph
#include "main.h"

#define BUF_SIZE 256

/*TO Debug*/
char *type_name[] = {"OPEN", "CLOSE", "INT", "DOUBLE", "CHAR", "OPERATOR", "COMP"};

void commandline() {
	char *line;
	using_history();
	token_t *list_root = NULL;
	token_t *tree_root = NULL;
	token_t *result = NULL;

	while((line = readline("calc>")) != NULL) {
		add_history(line);

		/*tokenize*/
		if ((list_root = Tokenize(line)) == NULL) {
			continue;
		}
//		list_print(list_root);

		/*parse*/
		if ((tree_root = Parse(list_root)) == NULL) {
			continue;
		}
//		tree_print(tree_root);
		list_free(list_root);

		/*eval*/
		if ((result = eval(tree_root)) == NULL) {
			continue;
		}
//		tree_print(result);

		if (result->tt == INT) {
			printf("Answer = %d\n", result->integer);
		} else if (result->tt == DOUBLE) {
			printf("Answer = %f\n", result->decimal);
		}

		tree_free(tree_root);
		tree_free(result);
		free(line);
	}
}

void readfile (char *filename) {
	FILE *fp;
	char *buf = (char *)malloc(sizeof(char*) * BUF_SIZE);
	token_t *list_root = NULL;
	token_t *tree_root = NULL;
	token_t *result = NULL;
	if ((fp = fopen(filename, "r")) == NULL) {
		printf("file open error\n");
		exit(0);
	}
	while ((buf = fgets(buf, BUF_SIZE, fp)) != NULL) {
		printf("buf = %s\n", buf);

		/*tokenize*/
		if ((list_root = Tokenize(buf)) == NULL) {
			continue;
		}
//		list_print(list_root);

		/*parse*/
		if ((tree_root = Parse(list_root)) == NULL) {
			continue;
		}
//		tree_print(tree_root);
		list_free(list_root);

		/*eval*/
		if ((result = eval(tree_root)) == NULL) {
			continue;
		}
//		tree_print(result);


		if (result->tt == INT) {
			printf("Answer = %d\n", result->integer);
		} else if (result->tt == DOUBLE) {
			printf("Answer = %f\n", result->decimal);
		}

		tree_free(tree_root);
		tree_free(result);
	}
	free(buf);
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		commandline();
	} else if (argc == 2) {
		readfile(argv[1]);
	} else {
		printf("Too many argument\n");
		return 1;
	}
	return 0;
}
