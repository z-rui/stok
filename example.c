#include <stdio.h>
#include "stok.h"

int main()
{
	static char buffer[65536];
	int tok;
	const char *s, *t;

	fread(buffer, 1, sizeof buffer, stdin);

	s = buffer;
	do {
		tok = stok(s, (char **) &t);
		printf("%d\t%.*s\n", tok, (int) (t-s), s);
		if (tok == TOK_ERROR) {
			printf("illegal token: %.*s\n", (int) (t-s), s);
		}
		s = t;
	} while (tok > 0);

	return 0;
}
