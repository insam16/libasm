CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBASM = ../libasm.a
FUNCS = strlen strcpy strcmp write read strdup

.PHONY: all clean fclean re $(FUNCS)

all: $(FUNCS)

$(FUNCS): %: test_%.o $(LIBASM)
	$(CC) $< $(LIBASM) -o test_$@          
	./test_$@

test_%.o: test_%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find . -maxdepth 1 -name 'test_*.o' -delete

fclean: clean
	find . -maxdepth 1 -name 'test_*' ! -name '*.c' -delete

re: fclean all
