NAME		= compiler
SRCS 		= compiler.c 
OBJS 		= $(SRCS:.c=.o)
CFLAGS		= -g
.PHONY:		all clean fclean test run-test
.SUFIXES:	

all: $(NAME)

%.o: %.c compiler.h Makefile
	cc $(CFLAGS) -c $< -o $@

deps: 
	make -C lib/list 	
	make -C lib/ft 	 	

$(NAME): deps main.c $(OBJS) lib/ft/libft.a
	make -C lib/ft
	cc $(CFLAGS) main.c compiler.o lib/ft/libft.a -o $(NAME)

run-test: $(NAME)
	make -C lib/list 	run-test
	make -C lib/ft 	 	run-test
	make -C test 		run

run:
	make -C ext/cpp	

clean:
	make -C test 		clean
	make -C lib/ft 		clean
	make -C ext/cpp		clean	
	rm -rf $(OBJS)

fclean: clean
	make -C lib/ft 		fclean
	make -C ext/cpp		fclean	
	rm -rf $(NAME)

re: clean all
	make -C lib/list 	re
	make -C lib/ft 	 	re
	make -C test 		re 
	make -C . 			clean all