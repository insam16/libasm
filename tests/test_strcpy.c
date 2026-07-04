// test_strcpy.c

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

extern char *ft_strcpy(char *dest, const char *src);

int test_null_case(char *func_name, char *func(char *, const char *), char *dest, char *src);

int main(void)
{
	char *src[] = {"", "a", "hello", "42gyeongsan", "yuna"};
	char dest_mine[12];
	char dest_libc[12];
	int fail = 0;

	char *mine;
	char *libc;

	int i = 0;
	for (; i < 5; ++i) {
		mine = ft_strcpy(dest_mine, src[i]);	
		libc = strcpy(dest_libc, src[i]);
		printf("src: %s\n", src[i]);
		printf("dest_mine: %s, mine: %s\n", dest_mine, mine);
		printf("dest_libc: %s, libc: %s\n", dest_libc, libc);
		printf(strcmp(dest_mine, dest_libc) ? "FAIL" : "OK");
		printf("\n\n");
		if (strcmp(dest_mine, dest_libc)) fail = 1;
	}

	//fork() SEGFAULT tests

	//(NULL, "yuna")
	printf("(NULL, \"yuna\")\n");
	test_null_case("ft_strcpy", ft_strcpy, NULL, "yuna");
	test_null_case("strcpy", strcpy, NULL, "yuna");
	printf("\n\n");

	//(dest, NULL)
	printf("(dest, NULL)\n");
	test_null_case("ft_strcpy", ft_strcpy, dest_mine, NULL);
	test_null_case("strcpy", strcpy, dest_libc, NULL);
	printf("\n\n");

	//(NULL, NULL)
	printf("(NULL, NULL)\n");
	test_null_case("ft_strcpy", ft_strcpy, NULL, NULL);
	test_null_case("strcpy", strcpy, NULL, NULL);
	printf("\n\n");

	return (fail);
}

int test_null_case(char *func_name, char *func(char *, const char *), char *dest, char *src)
{
	pid_t pid = fork();

	if (pid == 0) {
		func(dest, src);
		_exit(0);
	} else {
		int status;
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status)) {
			printf("%s: 자식이 시그널 %d로 종료됨 (SIGSEGV==%d)\n",
				func_name, WTERMSIG(status), SIGSEGV);
			return 1; // 세그폴트
		}
		return 0;
	}
}
