#include <stddef.h>

char *x_stpcpy(char *dst, const char *src)
{
	size_t i = 0;

	for ( ; src[i] != '\0'; i++)
		dst[i] = src[i];
	dst[i] = '\0';

	return dst + i;
}
