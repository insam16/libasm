// test_write.c

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

extern ssize_t ft_write(int fd, const void *buf, size_t count);

int test_write(char *func_name, ssize_t (*func)(int, const void *, size_t), int fd, const char *str);
int test_null_case(char *func_name, ssize_t (*func)(int, const void *, size_t), int fd, const char *str);

int main(void)
{
	char *str[] = {"", "a", "abc", "mat", "cat", "helloWorld",
					"\x80\x01", 
					"What is Lorem Ipsum? Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since 1966, when designers at Letraset and James Mosley, the librarian at St Bride Printing Library in London, took a 1914 Cicero translation and scrambled it to make dummy text for Letraset's Body Type sheets. It has survived not only many decades, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised thanks to these sheets and more recently with desktop publishing software like Aldus PageMaker and Microsoft Word including versions of Lorem Ipsum.", 
					"moew", NULL
				};
	int i = 0;

	int mine;
	int libc;

	int errno_mine;
	int errno_libc;

	int ret_cmp;
	int fail = 0;

	for (int fd = -1; fd <= 3; ++fd)
	{
		i = 0;
		for (; i < 9; ++i)
		{
			printf("str: %s\n", str[i]);
			mine = test_write("ft_write", ft_write, fd, str[i]);
			errno_mine = errno;
			libc = test_write("   write",    write, fd, str[i]);
			errno_libc = errno;
			ret_cmp = mine == libc;
			printf(ret_cmp ? "OK" : "FAIL");
			if (!ret_cmp) fail = 1;
			printf("\nerrno: %d %d: ", errno_mine, errno_libc);
			ret_cmp = errno_mine == errno_libc;
			printf(ret_cmp ? "OK" : "FAIL");
			if (!ret_cmp) fail = 1;
			printf("\n\n");
		}
	
		for (; i < 10; ++i)
		{
			printf("str: %s\n", str[i]);
			mine = test_null_case("ft_write", ft_write, fd, str[i]);
			errno_mine = errno;
			libc = test_null_case("   write",    write, fd, str[i]);
			errno_libc = errno;
			ret_cmp = mine == libc;
			printf(ret_cmp ? "OK" : "FAIL");
			if (!ret_cmp) fail = 1;
			printf("\nerrno: %d %d: ", errno_mine, errno_libc);
			ret_cmp = errno_mine == errno_libc;
			printf(ret_cmp ? "OK" : "FAIL");
			if (!ret_cmp) fail = 1;
			printf("\n\n");
		}
	}

	printf("=== ");
	printf(fail ? "FAIL" : "OK");
	printf(" ===\n");
	write(1, "\n", 1);
	return (fail);
}

int test_write(char *func_name, ssize_t (*func)(int, const void *, size_t), int fd, const char *str)
{
	int ret;

	ret = func(fd, str, strlen(str));
	printf(": %s(%d, %s, %lu) -> %d\n", func_name, fd, str, (unsigned long)strlen(str), ret);

	return (ret);
}

int test_null_case(char *func_name, ssize_t (*func)(int, const void *, size_t), int fd, const char *str)
{
	pid_t pid = fork();

	if (pid == 0) {
		test_write(func_name, func, fd, str);
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
