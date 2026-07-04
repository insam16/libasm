// test_strcpy.c

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

extern char *ft_strcpy(char *dest, const char *src);

int test_null_case(char *func_name, char *(*func)(char *, const char *), char *dest, char *src);

int main(void)
{
	char *src[] = {"", "a", "hello", "42gyeongsan", "yuna"};
	char dest_mine[12];
	char dest_libc[12];
	int fail = 0;

	char *mine;
	char *libc;

	int ret_cmp;
	int ret_ok;

	int i = 0;
	for (; i < 5; ++i) {
		mine = ft_strcpy(dest_mine, src[i]);	
		libc = strcpy(dest_libc, src[i]);
		printf("src: %s\n", src[i]);
		printf("dest_mine: %s, mine: %s\n", dest_mine, mine);
		printf("dest_libc: %s, libc: %s\n", dest_libc, libc);
		ret_cmp = strcmp(dest_mine, dest_libc);
		ret_ok = (mine == dest_mine);
		printf("strcmp(dest_mine, dest_libc): ");
		printf(ret_cmp ? "FAIL" : "OK");
		printf("\n(mine == dest_mine): ");
		printf(ret_ok ? "OK" : "FAIL");
		printf("\n\n");
		if (ret_cmp || !ret_ok) fail = 1;
	}

	//fork() SEGFAULT tests
	int r_mine;
	int r_libc;

	//(NULL, "yuna")
	printf("(NULL, \"yuna\")\n");
	r_mine = test_null_case("ft_strcpy", ft_strcpy, NULL, "yuna");
	r_libc = test_null_case("strcpy", strcpy, NULL, "yuna");
	printf(r_mine == r_libc ? "OK" : "FAIL");
	if (r_mine != r_libc) fail = 1;
	printf("\n\n");

	//(dest, NULL)
	printf("(dest, NULL)\n");
	r_mine = test_null_case("ft_strcpy", ft_strcpy, dest_mine, NULL);
	r_libc = test_null_case("strcpy", strcpy, dest_libc, NULL);
	printf(r_mine == r_libc ? "OK" : "FAIL");
	if (r_mine != r_libc) fail = 1;
	printf("\n\n");

	//(NULL, NULL)
	printf("(NULL, NULL)\n");
	r_mine = test_null_case("ft_strcpy", ft_strcpy, NULL, NULL);
	r_libc = test_null_case("strcpy", strcpy, NULL, NULL);
	printf(r_mine == r_libc ? "OK" : "FAIL");
	if (r_mine != r_libc) fail = 1;
	printf("\n\n");

	printf("=== ");
	printf(fail ? "FAIL" : "OK");
	printf(" ===\n");
	return (fail);
}

int test_null_case(char *func_name, char *(*func)(char *, const char *), char *dest, char *src)
{
	pid_t pid = fork();

	if (pid == 0) {
		func(dest, src);
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
