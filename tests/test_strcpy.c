// test_strcpy.c

#include <stdio.h>
#include <string.h>

extern char *ft_strcpy(char *dest, const char *src);

int main(void)
{
	char *src[] = {"", "a", "hello", "42gyeongsan", "yuna", NULL};
	char dest_mine[10];
	char dest_libc[10];
	int fail = 0;

	char *mine;
	char *libc;

	int i = 0;
	for (; i < 5; ++i) {
		mine = ft_strcpy(dest_mine, src[i]);	
		libc = strcpy(dest_libc, src[i]);
		if (i == 3) printf("src[%d] is UB. buffer size missing\n", i);
		printf("src: %s\n", src[i]);
		printf("dest_mine: %s, mine: %s\n", dest_mine, mine);
		printf("dest_libc: %s, libc: %s\n", dest_libc, libc);
		printf(strcmp(dest_mine, dest_libc) ? "FAIL" : "OK");
		printf("\n\n");
		if (strcmp(dest_mine, dest_libc)) fail = 1;
	}

	//TODO: fork() SEGFAULT tests
	mine = ft_strcpy(NULL, src[i-1]);	
	libc = strcpy(NULL, src[i-1]);
	printf("src: %s\n", src[i]);
	printf("dest_mine: %s\n, mine: %s", dest_mine, mine);
	printf("dest_libc: %s\n, libc: %s", dest_libc, libc);
	printf(strcmp(dest_mine, dest_libc) ? "FAIL" : "OK");
	printf("\n\n");
	if (strcmp(dest_mine, dest_libc)) fail = 1;

	mine = ft_strcpy(NULL, NULL);	
	libc = strcpy(NULL, NULL);
	printf("src: %s\n", src[i]);
	printf("dest_mine: %s\n, mine: %s", dest_mine, mine);
	printf("dest_libc: %s\n, libc: %s", dest_libc, libc);
	printf(strcmp(dest_mine, dest_libc) ? "FAIL" : "OK");
	printf("\n\n");
	if (strcmp(dest_mine, dest_libc)) fail = 1;
	return (fail);
}
