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
		*tok = TOK_SPACE;
	} else if (isdigit(*t)) {
		*tok = TOK_INT;
		if (*t == '0' && (t[1] == 'x' || t[1] == 'X')) {
			++t;	/* skip 'x' */
			while (isxdigit(*++t))
				;
		} else {
			while (isdigit(*++t))
				;
tok_float:
			if (*t == '.') {
				*tok = TOK_FLOAT;
				while (isdigit(*++t))
					;
			}
			if (*t == 'e' || *t == 'E') {
				if (t[1] == '+' || t[1] == '-')
					++t;
				if (!isdigit(*++t)) {
					*tok = TOK_ERROR;
					return 0;
				}
				while (isdigit(*++t))
					;
			}
		}
	} else if (*t == '.' && isdigit(t[1])) {
		goto tok_float;
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
		*tok = TOK_NAME;
	} else if (ispunct(*t)) {
		/* TODO multi-character symbol */
		++t;
		*tok = TOK_SYMBOL;
	} else {
		*tok = TOK_ERROR;
	}
	return (size_t) (t - s);
}
