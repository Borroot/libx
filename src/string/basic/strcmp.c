#include <stddef.h>

int bt_strcmp(const char *s1, const char *s2)
{
	for (size_t i = 0; s1[i] != '\0' || s2[i] != '\0'; i++)
		if (s1[i] - s2[i] != 0)
			return s1[i] - s2[i];
	return 0;
}
