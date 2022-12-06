CFLAGS 	= -Wall -Werror -Wextra #-g
DEPS 	= Makefile

all: 	test
re:		clean all

test: 	test.c
	cc $(CFLAGS) test.c $(NAME) -o test 

run-test: test
	./test

clean: 
	rm -rf ./test

