#include <stdio.h>
#include <string.h>

extern unsigned long ft_strlen(const char *str);

int main(void)
{
	char *tests[] = {"", "a", "hello", "42gyeongsan", "yuna", NULL};
	int fail = 0;

	int i = 0;
	for (; i < 5; ++i) {
		unsigned long mine = ft_strlen(tests[i]);	
		unsigned long libc = strlen(tests[i]);	
		printf("%15s -> mine=%2lu libc=%2lu %s\n", tests[i], mine, libc, mine == libc ? "OK" : "FAIL");
		if (mine != libc) fail = 1;
	}
	// printf("mine=%lu ", ft_strlen(tests[i]));
	// printf("libc=%lu ", strlen(tests[i]));
	return (fail);
}
