// test_write.c

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>

extern ssize_t ft_write(int fd, const void *buf, size_t count);

int test_write(char *func_name, ssize_t (*func)(int, const void *, size_t), int fd, const char *str, int *errno_ptr);
int test_null_case(char *func_name, ssize_t (*func)(int, const void *, size_t), int fd, int *errno_ptr);

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
			mine = test_write("ft_write", ft_write, fd, str[i], &errno_mine);
			errno_mine = errno;
			libc = test_write("   write",    write, fd, str[i], &errno_libc);
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
			mine = test_null_case("ft_write", ft_write, fd, &errno_mine);
			libc = test_null_case("   write",    write, fd, &errno_libc);
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

int test_write(char *func_name, ssize_t (*func)(int, const void *, size_t), int fd, const char *str, int *errno_ptr)
{
	int ret;

	if (str == NULL)
		ret = func(fd, str, 5);
	else
		ret = func(fd, str, strlen(str));
	*errno_ptr = errno;
	if (str == NULL)
		printf(": %s(%d, %s, %lu) -> %d\n", func_name, fd, str, (unsigned long)5, ret);
	else
		printf(": %s(%d, %s, %lu) -> %d\n", func_name, fd, str, (unsigned long)strlen(str), ret);

	return (ret);
}

int test_null_case(char *func_name, ssize_t (*func)(int, const void *, size_t), int fd, int *errno_ptr)
{
	int pipe_fd[2];
	pipe(pipe_fd);
	
	pid_t pid = fork();
	
	if (pid == 0) {
		close(pipe_fd[0]);
		int ret = test_write(func_name, func, fd, NULL, errno_ptr);
		int payload[2] = {ret, *errno_ptr};
		write(pipe_fd[1], payload, sizeof(payload));
		close(pipe_fd[1]);
		_exit(0);
	} else {
		close(pipe_fd[1]);
		int status;
		waitpid(pid, &status, 0);
	
		if (WIFSIGNALED(status)) {
			printf("%s: 시그널 %d로 종료됨 (예상: SIGPIPE==%d, 일치:%d)\n",
				func_name, WTERMSIG(status), SIGPIPE, WTERMSIG(status) == SIGPIPE);
			close(pipe_fd[0]);
			return 1;
		}
		int payload[2] = {0, 0};
		read(pipe_fd[0], payload, sizeof(payload));
		close(pipe_fd[0]);
		*errno_ptr = payload[1];
		printf("%s: 정상 종료됨, ret=%d, errno=%d\n",
			func_name, payload[0], payload[1]);
		return 0;
	}
}
