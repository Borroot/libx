#include <stddef.h>

size_t bt_strlen(const char *s)
{
	size_t i;

	for (i = 0; s[i] != '\0'; i++)
		;

	return i;
}
