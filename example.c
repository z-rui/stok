#include <stdio.h>
#include <string.h>
#include "stok.h"
#include "uesc.h"

int main()
{
	static char buffer[65536];
	static char *names[] = {
		"EOF", "SPACE", "INT", "FLOAT", "NAME", "SYMBOL", "LITERAL"
	};
	int tok;
	const char *s, *t;

	fread(buffer, 1, sizeof buffer, stdin);

	s = buffer;
	do {
		static char buf[65536];

		tok = stok(s, (char **) &t);
		memcpy(buf, s, t-s);
		buf[t-s] = '\0';
		if (tok == TOK_LITERAL) {
			uesc(buf, buf);
		}
		printf("%s\t%s\n", (tok < 0 ? "INVALID" : names[tok]), buf);
		s = t;
	} while (tok > 0);

	return 0;
}
