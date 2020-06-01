#include <criterion/criterion.h>
#include <stddef.h>
#include <x_ctype.h>
#include <x_string.h>

Test(string, memset)
{
	char *s = (char *)malloc(10);

	cr_assert(x_memset(s, '!', 10));
	cr_assert_str_eq(s, "!!!!!!!!!!");

	cr_assert(x_memset(s, '0', 5));
	cr_assert_str_eq(s, "00000!!!!!");

	free(s);
}

Test(string, memcmp)
{
	cr_assert_eq(x_memcmp("ABC", "ABC", 3), 0);
	cr_assert_eq(x_memcmp("ABC", "AB", 3), 67);
	cr_assert_eq(x_memcmp("ABC", "AB", 2), 0);
	cr_assert_eq(x_memcmp("ABA", "ABZ", 3), -25);
	cr_assert_eq(x_memcmp("ABJ", "ABC", 3), 7);
	cr_assert_eq(x_memcmp("ABC", "CBA", 0), 0);
}

Test(string, memchr)
{
	const char s[] = "hello world";

	cr_assert_eq(x_memchr(s, 'h', 0), NULL);
	cr_assert_eq(x_memchr(s, 'h', 11), s);
	cr_assert_eq(x_memchr(s, 'l', 11), s + 2);
	cr_assert_eq(x_memchr(s, 'd', 11), s + 10);
	cr_assert_eq(x_memchr(s, '\0', 12), s + 11);
	cr_assert_eq(x_memchr(s, 'x', 11), NULL);
}

Test(string, memrchr)
{
	const char s[] = "hello world";

	cr_assert_eq(x_memrchr(s, 'h', 11), s);
	cr_assert_eq(x_memrchr(s, 'l', 11), s + 9);
	cr_assert_eq(x_memrchr(s, 'd', 11), s + 10);
	cr_assert_eq(x_memrchr(s, '\0', 12), s + 11);
	cr_assert_eq(x_memrchr(s, 'x', 11), NULL);
}

Test(string, strlen)
{
	cr_assert(x_strlen("hello world") == 11);
	cr_assert(x_strlen("hello\0world") == 5);
	cr_assert(x_strlen("") == 0);
}

Test(string, strnlen)
{
	cr_assert(x_strnlen("hello world", 20) == 11);
	cr_assert(x_strnlen("hello\0world", 20) == 5);
	cr_assert(x_strnlen("", 20) == 0);

	cr_assert(x_strnlen("hello world", 8) == 8);
	cr_assert(x_strnlen("hello\0world", 8) == 5);
	cr_assert(x_strnlen("", 0) == 0);
}

Test(string, strcpy)
{
	char *result;

	const char src1[] = "hello world";
	char dst1[11] = "";
	result = x_strcpy(dst1, src1);
	cr_assert_str_eq(dst1, src1);
	cr_assert_str_eq(result, dst1);

	char dst2[11] = "hi";
	result = x_strcpy(dst2, src1);
	cr_assert_str_eq(dst2, src1);
	cr_assert_str_eq(result, dst2);

	const char src2[] = "";
	char dst3[11] = "hello world";
	result = x_strcpy(dst3, src2);
	cr_assert_str_eq(dst3, src2);
	cr_assert_str_eq(result, dst3);

	const char src3[] = "hello w\0rld";
	char dst4[11] = "";
	result = x_strcpy(dst4, src3);
	cr_assert_str_eq(dst4, src3);
	cr_assert_str_eq(result, dst4);
}

Test(string, strncpy)
{
	char *result;

	const char src1[] = "hello world";
	char dst1[11] = "";
	result = x_strncpy(dst1, src1, 11);
	cr_assert_str_eq(dst1, src1);
	cr_assert_str_eq(result, dst1);

	char dst2[11] = "hi";
	result = x_strncpy(dst2, src1, 11);
	cr_assert_str_eq(dst2, src1);
	cr_assert_str_eq(result, dst2);

	const char src2[] = "";
	char dst3[11] = "hello world";
	result = x_strncpy(dst3, src2, 11);
	cr_assert_str_eq(dst3, src2);
	cr_assert_str_eq(result, dst3);

	char dst4[13] = "hi";
	result = x_strncpy(dst4, src1, 13);
	cr_assert_str_eq(dst4, src1);
	cr_assert_str_eq(result, dst4);

	const char src3[] = "";
	char dst5[11] = "hello world";
	result = x_strncpy(dst5, src3, 3);
	cr_assert_str_eq(dst5, src3);
	cr_assert_str_eq(result, dst5);
}

Test(string, stpcpy)
{
	char *result;

	const char src1[] = "hello world";
	char dst1[11] = "";
	result = x_stpcpy(dst1, src1);
	cr_assert_str_eq(dst1, src1);
	cr_assert_str_eq(result, dst1 + 11);

	char dst2[11] = "hi";
	result = x_stpcpy(dst2, src1);
	cr_assert_str_eq(dst2, src1);
	cr_assert_str_eq(result, dst2 + 11);

	const char src2[] = "";
	char dst3[11] = "hello world";
	result = x_stpcpy(dst3, src2);
	cr_assert_str_eq(dst3, src2);
	cr_assert_str_eq(result, dst3);

	const char src3[] = "hello w\0rld";
	char dst4[11] = "";
	result = x_stpcpy(dst4, src3);
	cr_assert_str_eq(dst4, src3);
	cr_assert_str_eq(result, dst4 + 7);
}

Test(string, stpncpy)
{
	char *result;

	const char src1[] = "hello world";
	char dst1[11] = "";
	result = x_stpncpy(dst1, src1, 11);
	cr_assert_str_eq(dst1, src1);
	cr_assert_str_eq(result, dst1 + 11);

	char dst2[11] = "hi";
	result = x_stpncpy(dst2, src1, 11);
	cr_assert_str_eq(dst2, src1);
	cr_assert_str_eq(result, dst2 + 11);

	const char src2[] = "";
	char dst3[11] = "hello world";
	result = x_stpncpy(dst3, src2, 11);
	cr_assert_str_eq(dst3, src2);
	cr_assert_str_eq(result, dst3);

	char dst4[13] = "hi";
	result = x_stpncpy(dst4, src1, 13);
	cr_assert_str_eq(dst4, src1);
	cr_assert_str_eq(result, dst4 + 11);

	const char src3[] = "";
	char dst5[11] = "hello world";
	result = x_stpncpy(dst5, src3, 3);
	cr_assert_str_eq(dst5, src3);
	cr_assert_str_eq(result, dst5);
}

Test(string, strcat)
{
	char *result;

	const char src1[] = " world";
	char dst1[11] = "hello";
	result = x_strcat(dst1, src1);
	cr_assert_str_eq(dst1, "hello world");
	cr_assert_str_eq(result, "hello world");

	const char src2[] = "";
	char dst2[11] = "hello";
	result = x_strcat(dst2, src2);
	cr_assert_str_eq(dst2, "hello");
	cr_assert_str_eq(result, "hello");

	const char src3[] = "hello";
	char dst3[11] = "";
	result = x_strcat(dst3, src3);
	cr_assert_str_eq(dst3, "hello");
	cr_assert_str_eq(result, "hello");
}

Test(string, strncat)
{
	char *result;

	const char src1[] = " world";
	char dst1[11] = "hello";
	result = x_strncat(dst1, src1, 6);
	cr_assert_str_eq(dst1, "hello world");
	cr_assert_str_eq(result, "hello world");

	const char src2[] = "";
	char dst2[11] = "hello";
	result = x_strncat(dst2, src2, 0);
	cr_assert_str_eq(dst2, "hello");
	cr_assert_str_eq(result, "hello");

	const char src3[] = "hello";
	char dst3[11] = "";
	result = x_strncat(dst3, src3, 5);
	cr_assert_str_eq(dst3, "hello");
	cr_assert_str_eq(result, "hello");

	const char src4[] = " world";
	char dst4[11] = "hello";
	result = x_strncat(dst4, src4, 3);
	cr_assert_str_eq(dst4, "hello wo");
	cr_assert_str_eq(result, "hello wo");

	const char src5[] = " world";
	char dst5[11] = "hello";
	result = x_strncat(dst5, src5, 0);
	cr_assert_str_eq(dst5, "hello");
	cr_assert_str_eq(result, "hello");
}

Test(string, strchr)
{
	const char s[] = "hello world";

	cr_assert_eq(x_strchr(s, 'h'), s);
	cr_assert_eq(x_strchr(s, 'l'), s + 2);
	cr_assert_eq(x_strchr(s, 'd'), s + 10);
	cr_assert_eq(x_strchr(s, '\0'), s + 11);
	cr_assert_eq(x_strchr(s, 'x'), NULL);
}

Test(string, strrchr)
{
	const char s[] = "hello world";

	cr_assert_eq(x_strrchr(s, 'h'), s);
	cr_assert_eq(x_strrchr(s, 'l'), s + 9);
	cr_assert_eq(x_strrchr(s, 'd'), s + 10);
	cr_assert_eq(x_strrchr(s, '\0'), s + 11);
	cr_assert_eq(x_strrchr(s, 'x'), NULL);
}

Test(string, strchrnul)
{
	const char s[] = "hello world";

	cr_assert_eq(x_strchrnul(s, 'h'), s);
	cr_assert_eq(x_strchrnul(s, 'l'), s + 2);
	cr_assert_eq(x_strchrnul(s, 'd'), s + 10);
	cr_assert_eq(x_strchrnul(s, '\0'), s + 11);
	cr_assert_eq(x_strchrnul(s, 'x'), s + 11);
}

Test(string, strcmp)
{
	cr_assert_eq(x_strcmp("ABC", "ABC"), 0);
	cr_assert_eq(x_strcmp("ABC", "AB"), 67);
	cr_assert_eq(x_strcmp("ABA", "ABZ"), -25);
	cr_assert_eq(x_strcmp("ABJ", "ABC"), 7);
}

Test(string, strncmp)
{
	cr_assert_eq(x_strncmp("ABC", "ABC", 3), 0);
	cr_assert_eq(x_strncmp("ABC", "AB", 3), 67);
	cr_assert_eq(x_strncmp("ABC", "AB", 2), 0);
	cr_assert_eq(x_strncmp("ABA", "ABZ", 3), -25);
	cr_assert_eq(x_strncmp("ABJ", "ABC", 3), 7);
	cr_assert_eq(x_strncmp("ABC", "CBA", 0), 0);
}

Test(string, strdup)
{
	char *result;

	const char s1[] = "hello world";
	result = x_strdup(s1);
	cr_assert_neq(result, s1);
	cr_assert_str_eq(result, s1);
	cr_assert(x_strlen(result) == x_strlen(s1));

	const char s2[] = "";
	result = x_strdup(s2);
	cr_assert_neq(result, s2);
	cr_assert_str_eq(result, s2);
	cr_assert(x_strlen(result) == x_strlen(s2));

	free(result);
}

Test(string, strndup)
{
	char *result;

	const char s1[] = "hello world";
	result = x_strndup(s1, 11);
	cr_assert_neq(result, s1);
	cr_assert_str_eq(result, s1);
	cr_assert(x_strlen(result) == x_strlen(s1));

	result = x_strndup(s1, 8);
	cr_assert_neq(result, s1);
	cr_assert_str_eq(result, "hello wo");
	cr_assert(x_strlen(result) == x_strlen("hello wo"));

	const char s2[] = "";
	result = x_strndup(s2, 0);
	cr_assert_neq(result, s2);
	cr_assert_str_eq(result, s2);
	cr_assert(x_strlen(result) == x_strlen(s2));

	free(result);
}

Test(string, strpbrk)
{
	const char s[] = "hello world";

	cr_assert_eq(x_strpbrk(s, "le"), s + 1);
	cr_assert_eq(x_strpbrk(s, "r"), s + 8);
	cr_assert_eq(x_strpbrk(s, ""), NULL);
	cr_assert_eq(x_strpbrk(s, "x"), NULL);
}

Test(string, strstr)
{
	const char s[] = "hello world";

	cr_assert_eq(x_strstr(s, "hello"), s);
	cr_assert_eq(x_strstr(s, "llo"), s + 2);
	cr_assert_eq(x_strstr(s, "d"), s + 10);
	cr_assert_eq(x_strstr(s, ""), s);
	cr_assert_eq(x_strstr(s, "x"), NULL);
	cr_assert_eq(x_strstr(s, "worlds"), NULL);
}

Test(string, strcasestr)
{
	const char s[] = "heLlO WorLD";

	cr_assert_eq(x_strcasestr(s, "hEllo"), s);
	cr_assert_eq(x_strcasestr(s, "lLo"), s + 2);
	cr_assert_eq(x_strcasestr(s, "D"), s + 10);
	cr_assert_eq(x_strcasestr(s, ""), s);
	cr_assert_eq(x_strcasestr(s, "x"), NULL);
	cr_assert_eq(x_strcasestr(s, "worLds"), NULL);
}

Test(string, strspn)
{
	cr_assert_eq(x_strspn("hello world", ""), 0);
	cr_assert_eq(x_strspn("hello world", "helo"), 5);
	cr_assert_eq(x_strspn("hello world", "e"), 0);
	cr_assert_eq(x_strspn("hello world", "hello world"), 11);
	cr_assert_eq(x_strspn("hello world", "helowrd "), 11);
	cr_assert_eq(x_strspn("hello world", "H "), 0);
}

Test(string, strcspn)
{
	cr_assert_eq(x_strcspn("hello world", ""), 11);
	cr_assert_eq(x_strcspn("hello world", "h"), 0);
	cr_assert_eq(x_strcspn("hello world", "e"), 1);
	cr_assert_eq(x_strcspn("hello world", "xyz"), 11);
	cr_assert_eq(x_strcspn("hello world", " "), 5);
	cr_assert_eq(x_strcspn("hello world", "\0"), 11);
}

Test(string_extra, strclr)
{
	char s[] = "hello world";
	x_strclr(s);
	for (int i = 0; i < (int)sizeof s; i++) {
		cr_assert_eq(s[i], '\0');
	}
}

static void tmp1_tolower(char *c) { *c = (char)x_tolower((int)*c); }
static void tmp1_toupper(char *c) { *c = (char)x_toupper((int)*c); }

Test(string_extra, striter)
{
	char s1[] = "hello world";
	char s2[] = "hello, world! :)";

	x_striter(s1, tmp1_toupper);
	cr_assert_str_eq(s1, "HELLO WORLD");

	x_striter(s1, tmp1_tolower);
	cr_assert_str_eq(s1, "hello world");

	x_striter(s1, tmp1_tolower);
	cr_assert_str_eq(s1, "hello world");

	x_striter(s2, tmp1_toupper);
	cr_assert_str_eq(s2, "HELLO, WORLD! :)");
}

static char tmp2_tolower(char c) { return (char)x_tolower((int)c); }
static char tmp2_toupper(char c) { return (char)x_toupper((int)c); }

Test(string_extra, strmap)
{
	char *result1 = x_strmap("HELLO WORLD", tmp2_tolower);
	cr_assert_str_eq(result1, "hello world");

	char *result2 = x_strmap("hello world", tmp2_toupper);
	cr_assert_str_eq(result2, "HELLO WORLD");

	char *result3 = x_strmap("hello, world! :)", tmp2_toupper);
	cr_assert_str_eq(result3, "HELLO, WORLD! :)");

	free(result1);
	free(result2);
	free(result3);
}

Test(string_extra, strequ)
{
	cr_assert_eq(x_strequ("", ""), 1);
	cr_assert_eq(x_strequ("hello world", "hello world"), 1);
	cr_assert_eq(x_strequ("hello worlD", "hello world"), 0);
}

Test(string_extra, strnequ)
{
	cr_assert_eq(x_strnequ("", "", 1), 1);
	cr_assert_eq(x_strnequ("", "", 0), 1);
	cr_assert_eq(x_strnequ("hello world", "hello world", 11), 1);
	cr_assert_eq(x_strnequ("hello worlD", "hello world", 11), 0);
	cr_assert_eq(x_strnequ("hello worlD", "hello world", 10), 1);
}
