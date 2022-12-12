NAME		= compiler
SRCS 		= compiler.c 
OBJS 		= $(SRCS:.c=.o)
CFLAGS		= -g
.PHONY:		all clean fclean test run-test
.SUFIXES:	

all: $(NAME)

%.o: %.c compiler.h Makefile
	cc $(CFLAGS) -c $< -o $@

$(NAME): main.c $(OBJS)
	make -C lib/ft
	cc $(CFLAGS) main.c compiler.o lib/ft/libft.a -o $(NAME)

run-test: $(NAME)
	make -C test re
	make -C test run

clean:
	make -C test 	clean
	make -C lib/ft 	clean
	rm -rf $(OBJS)

fclean: clean
	make -C lib/ft 	fclean
	rm -rf $(NAME)

re: clean all