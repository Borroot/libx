#include <stddef.h>

char *x_strcpy(char *dst, const char *src)
{
	for (size_t i = 0; (dst[i] = src[i]) != '\0'; i++)
		;

	return dst;
}
