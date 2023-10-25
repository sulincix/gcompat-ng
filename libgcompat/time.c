#include <time.h>

size_t __strftime_l(char *restrict s, size_t n, const char *restrict f,
		    const struct tm *restrict tm, locale_t loc)
{
	return strftime_l(s, n, f, tm, loc);
}

