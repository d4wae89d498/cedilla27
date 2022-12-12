NAME 	= libft.a
SRCS 	= str_list.c args.c explode.c read_file.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c ft.h Makefile
	cc -c $< -o $@

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

test: $(NAME)
	cc test.c $(NAME) -o test

run-test: test
	./test

clean:
	rm -rf test
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

.PHONY	= all clean fclean test run-test
.SUFIXES=