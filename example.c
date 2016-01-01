#include <stdio.h>
#include "stok.h"

int main()
{
	static char buffer[65536];
	int tok;
	size_t len;
	const char *s;

	fread(buffer, 1, sizeof buffer, stdin);

	s = buffer;
	do {
		len = stok(s, &tok);
		printf("%d\t%.*s\n", tok, (int) len, s);
		s += len;
	} while (len > 0);

	return 0;
}
