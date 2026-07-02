all: strlen

strlen:
	gcc -Wall -Wextra -Werror -c test_strlen.c -o test_strlen.o
	gcc test_strlen.o ../libasm.a -o test_strlen          
	./test_strlen

strcpy:
	gcc -Wall -Wextra -Werror -c test_strcpy.c -o test_strcpy.o
	gcc test_strcpy.o ../libasm.a -o test_strcpy          
	./test_strcpy

strcmp:
	gcc -Wall -Wextra -Werror -c test_strcmp.c -o test_strcmp.o
	gcc test_strcmp.o ../libasm.a -o test_strcmp          
	./test_strcmp

write:
	gcc -Wall -Wextra -Werror -c test_write.c -o test_write.o
	gcc test_write.o ../libasm.a -o test_write          
	./test_write

read:
	gcc -Wall -Wextra -Werror -c test_read.c -o test_read.o
	gcc test_read.o ../libasm.a -o test_read          
	./test_read

strdup:
	gcc -Wall -Wextra -Werror -c test_strdup.c -o test_strdup.o
	gcc test_strdup.o ../libasm.a -o test_strdup          
	./test_strdup

clean:
	rm -rf test_*.o

fclean: clean
	find . -maxdepth 1 -name 'test_*' ! -name '*.c' -delete

.PHONY: all strlen strcpy strcmp write read strdup clean fclean
