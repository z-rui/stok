#include <ctype.h>
#include "stok.h"

int stok(const char *s, char **endptr)
{
	int rc;
	const char *t = s;

	if (*t == '\0') {
		rc = TOK_EOF;
	} else if (isspace(*t)) {
		/* TODO comment */
		while (isspace(*++t))
			;
		rc = TOK_SPACE;
	} else if (isdigit(*t)) {
		rc = TOK_INT;
		if (*t == '0' && (t[1] == 'x' || t[1] == 'X')) {
			++t;	/* skip 'x' */
			while (isxdigit(*++t))
				;
		} else {
			while (isdigit(*++t))
				;
tok_float:
			if (*t == '.') {
				rc = TOK_FLOAT;
				while (isdigit(*++t))
					;
			}
			if (*t == 'e' || *t == 'E') {
				if (t[1] == '+' || t[1] == '-')
					++t;
				if (!isdigit(*++t)) {
					rc = TOK_ERROR;
				} else {
					while (isdigit(*++t))
						;
				}
			}
		}
	} else if (*t == '.' && isdigit(t[1])) {
		goto tok_float;
	} else if (*t == '\'' || *t == '"') {
		char delimiter = *t;

		rc = TOK_LITERAL;
		while (*++t != delimiter) {
			if (*t == '\\')
				++t;
			if (*t == '\0') {
				rc = TOK_ERROR;
				--t; /* to cancel ++t after the loop */
				break;
			}
		}
		++t;
	} else if (*t == '_' || isalpha(*t)) {
		while (*++t == '_' || isalnum(*t))
			;
		rc = TOK_NAME;
	} else if (ispunct(*t)) {
		/* TODO multi-character symbol */
		++t;
		rc = TOK_SYMBOL;
	} else {
		rc = TOK_ERROR;
	}
	if (endptr) {
		*endptr = (char *) t;
	}
	return rc;
}
