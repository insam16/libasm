// test_strcmp.c

#include <stdio.h>
#include <string.h>

extern int ft_strcmp(const char *s1, const char *s2);

int test_cmp(char *func_name, int (*func)(const char *, const char *), const char *s1, const char *s2);

int main(void)
{
	char *s1[] = {"", "a", "abc", "mat", "cat", "hello"};
	char *s2[] = {"", "a", "abc", "map", "rat", "helloWorld"};
	int i = 0;

	int mine;
	int libc;

	int ret_cmp;
	int fail = 0;

	for (; i < 6; ++i)
	{
		printf("s1: %s, s2: %s\n", s1[i], s2[i]);
		mine = test_cmp("ft_strcmp", ft_strcmp, s1[i], s2[i]);
		libc = test_cmp("   strcmp", strcmp, s1[i], s2[i]);
		ret_cmp = mine == libc;
		printf(ret_cmp ? "OK" : "FAIL");
		if (!ret_cmp) fail = 1;
		printf("\n\n");
	}
	return (fail);
}

int test_cmp(char *func_name, int (*func)(const char *, const char *), const char *s1, const char *s2)
{
	int ret;

	ret = func(s1, s2);
	printf("%s(%s, %s) -> %d\n", func_name, s1, s2, ret);

	return (ret);
}
