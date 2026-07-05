// test_strcmp.c

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

extern int ft_strcmp(const char *s1, const char *s2);

int test_cmp(char *func_name, int (*func)(const char *, const char *), const char *s1, const char *s2);
int test_null_case(char *func_name, int (*func)(const char *, const char *), const char *s1, const char *s2);

int main(void)
{
	char *s1[] = {"", "a", "abc", "mat", "cat", "hello",		"moew", NULL, NULL};
	char *s2[] = {"", "a", "abc", "map", "rat", "helloWorld",	NULL, "moew", NULL};
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

	for (; i < 9; ++i)
	{
		printf("s1: %s, s2: %s\n", s1[i], s2[i]);
		mine = test_null_case("ft_strcmp", ft_strcmp, s1[i], s2[i]);
		libc = test_null_case("   strcmp", strcmp, s1[i], s2[i]);
		ret_cmp = mine == libc;
		printf(ret_cmp ? "OK" : "FAIL");
		if (!ret_cmp) fail = 1;
		printf("\n\n");
	}

	printf("=== ");
	printf(fail ? "FAIL" : "OK");
	printf(" ===\n");
	return (fail);
}

int test_cmp(char *func_name, int (*func)(const char *, const char *), const char *s1, const char *s2)
{
	int ret;

	ret = func(s1, s2);
	printf("%s(%s, %s) -> %d\n", func_name, s1, s2, ret);

	return (ret);
}

int test_null_case(char *func_name, int (*func)(const char *, const char *), const char *s1, const char *s2)
{
	pid_t pid = fork();

	if (pid == 0) {
		test_cmp(func_name, func, s1, s2);
		_exit(0);
	} else {
		int status;
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status)) {
			printf("%s: 시그널 %d로 종료됨 (예상: SIGSEGV==%d, 일치:%d)\n",
				func_name, WTERMSIG(status), SIGSEGV, WTERMSIG(status) == SIGSEGV);
			return 1; // 세그폴트
		}
		return 0;
	}
}
