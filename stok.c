#include <ctype.h>
#include "stok.h"

size_t stok(const char *s, int *tok)
{
	const char *t = s;

	if (*t == '\0') {
		*tok = TOK_EOF;
	} else if (isspace(*t)) {
		/* TODO comment */
		while (isspace(*++t))
			;
		*tok = TOK_WHITESPACE;
	} else if (isdigit(*t)) {
		/* TODO floating point */
		if (*t == '0' && (t[1] == 'x' || t[1] == 'X')) {
			++t;	/* skip 'x' */
			while (isxdigit(*++t))
				;
		} else {
			while (isdigit(*++t))
				;
		}
		*tok = TOK_NUMBER;
	} else if (*t == '\'' || *t == '"') {
		char delimiter = *t;

		*tok = TOK_LITERAL;
		while (*++t != delimiter) {
			if (*t == '\\')
				++t;
			if (*t == '\0') {
				*tok = TOK_ERROR;
				return 0;
			}
		}
		++t;
	} else if (*t == '_' || isalpha(*t)) {
		while (*++t == '_' || isalnum(*t))
			;
		*tok = TOK_IDENT;
	} else if (ispunct(*t)) {
		/* TODO multi-character symbol */
		++t;
		*tok = TOK_SYMBOL;
	} else {
		*tok = TOK_ERROR;
	}
	return (size_t) (t - s);
}
