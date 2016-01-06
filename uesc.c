#include <ctype.h>
#include <stdlib.h>
#include <string.h>

size_t uesc(char *out, const char *in)
{
	char *out_start = out;

	while (*in) {
		if (*in != '\\') {
			*out++ = *in++;
		} else {
			/* escape */
			int n = 0;

			++in;
			if (isdigit(in[n])) ++n;
			if (isdigit(in[n])) ++n;
			if (isdigit(in[n])) ++n;

			if (n > 0) { /* \ooo */
				char buf[4];

				memcpy(buf, in, n);
				buf[n] = '\0';
				*out++ = (char) strtol(buf, 0, 8);
				in += n;
			} else switch (*in) {
				case 'a': *out++ = '\a'; ++in; break;
				case 'b': *out++ = '\b'; ++in; break;
				case 'f': *out++ = '\f'; ++in; break;
				case 'n': *out++ = '\n'; ++in; break;
				case 'r': *out++ = '\r'; ++in; break;
				case 't': *out++ = '\t'; ++in; break;
				case 'v': *out++ = '\v'; ++in; break;
				case '\'': *out++ = '\''; ++in; break;
				case '"': *out++ = '"'; ++in; break;
				case '\\': *out++ = '\\'; ++in; break;
				case 'x':
					if (isxdigit(in[1]) && isxdigit(in[2])) {
						char buf[3];

						memcpy(buf, ++in, 2);
						buf[2] = '\0';
						*out++ = (char) strtol(buf, 0, 16);
						in += 2;	/* \x## */
						break;
					}
					/* else fallthrough */
				default:
					*out++ = *in++;
					break;
			}
		}
	}
	*out = '\0';
	return (size_t) (out - out_start);
}
