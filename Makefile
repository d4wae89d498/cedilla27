NAME=compiler

all: $(NAME)

$(NAME): compiler.c compiler.h
	cc compiler.c -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean all