NAME=compiler

all: $(NAME)

$(NAME): compiler.c compiler.h
	cc compiler.c -o $(NAME)

test: $(NAME)
	./compiler -E --EXTS="ext/cpp/ext.so" compiler.c

clean:
	rm -rf $(NAME)

re: clean all