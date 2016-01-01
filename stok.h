#define TOK_EOF 0
#define TOK_WHITESPACE 1
#define TOK_SYMBOL 2
#define TOK_NUMBER 3
#define TOK_IDENT 4
#define TOK_LITERAL 5
#define TOK_ERROR 6

#include <stddef.h>	/* size_t */
extern size_t stok(const char *, int *);
