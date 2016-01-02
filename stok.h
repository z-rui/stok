#define TOK_ERROR (-1)
#define TOK_EOF 0
#define TOK_SPACE 1
#define TOK_INT 2
#define TOK_FLOAT 3
#define TOK_NAME 4
#define TOK_SYMBOL 5
#define TOK_LITERAL 6

#include <stddef.h>	/* size_t */
extern size_t stok(const char *, int *);
